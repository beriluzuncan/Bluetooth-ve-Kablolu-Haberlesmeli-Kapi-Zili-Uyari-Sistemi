#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

// Pin tanımları
#define RX_PIN 4           // Uno RX ← Nano TX (D3)
#define TX_PIN 3           // Uno TX → Nano RX (D4)
#define RED_LED_PIN 6
#define GREEN_LED_PIN 7
#define SERVO_PIN 5
#define BUZZER_PIN 12

SoftwareSerial seri(RX_PIN, TX_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo doorServo;

bool alertActive = false;
unsigned long alertStartTime = 0;
const unsigned long alertDuration = 10000; // 10 saniye
unsigned long lastLedToggle = 0;
const unsigned long ledBlinkInterval = 200; // 200ms
bool redLedState = false;
bool greenLedState = false;
int servoPosition = 90;
int servoDirection = 1;

void setup() {
  Serial.begin(9600);
  seri.begin(9600);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("Sistem Hazir");
  lcd.setCursor(0, 1);
  lcd.print("Zil Bekleniyor..");

  doorServo.attach(SERVO_PIN);
  doorServo.write(servoPosition);

  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Oda modülü hazır, mesaj bekleniyor...");
}

void loop() {
  if (seri.available()) {
    String message = seri.readStringUntil('\n');
    message.trim();

    if (message == "DOOR_BELL") {
      activateAlert();
    }
  }

  if (alertActive) {
    handleAlert();
  }

  delay(50);
}

void activateAlert() {
  Serial.println("KAPI ÇALDI - Uyarı başlatılıyor!");

  alertActive = true;
  alertStartTime = millis();

  lcd.clear();
  lcd.print("  KAPI CALDI!");
  lcd.setCursor(0, 1);
  lcd.print("Misafir Geldi");

  playBuzzerAlert();

  digitalWrite(RED_LED_PIN, HIGH);
  redLedState = true;
  greenLedState = false;
  lastLedToggle = millis();
}

void handleAlert() {
  unsigned long currentTime = millis();

  if (currentTime - alertStartTime > alertDuration) {
    deactivateAlert();
    return;
  }

  if (currentTime - lastLedToggle > ledBlinkInterval) {
    if (redLedState) {
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);
      redLedState = false;
      greenLedState = true;
    } else {
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(RED_LED_PIN, HIGH);
      redLedState = true;
      greenLedState = false;
    }
    lastLedToggle = currentTime;
  }

  servoPosition += servoDirection * 2;
  if (servoPosition >= 135) servoDirection = -1;
  else if (servoPosition <= 45) servoDirection = 1;
  doorServo.write(servoPosition);

  // Her 3 saniyede buzzer sesi tekrarı
  if ((currentTime - alertStartTime) % 3000 < 100) {
    playBuzzerAlert();
  }
}

void deactivateAlert() {
  Serial.println("Uyarı sona erdi");

  alertActive = false;

  lcd.clear();
  lcd.print("Sistem Hazir");
  lcd.setCursor(0, 1);
  lcd.print("Zil Bekleniyor..");

  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);

  doorServo.write(90);

  digitalWrite(BUZZER_PIN, LOW);
}

void playBuzzerAlert() {
  int melody[] = {262, 262, 294, 262, 349, 330};          // Do Do Re Do Fa Mi
  int noteDurations[] = {300, 300, 300, 300, 600, 600};  // ms cinsinden süreler

  for (int i = 0; i < 6; i++) {
    tone(BUZZER_PIN, melody[i], noteDurations[i]);
    delay(noteDurations[i] * 1.3);
  }
}

