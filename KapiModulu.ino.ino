#include <SoftwareSerial.h>

// Pin tanımları
#define TX_PIN 3      // Nano TX → Uno RX (D4)
#define RX_PIN 4      // Nano RX ← Uno TX (D3)
#define MIC_PIN A0    // Mikrofon sensörü analog pin

SoftwareSerial seri(RX_PIN, TX_PIN);

const int ESIG_DEGER = 300;  // Ses eşik değeri (ayarlanabilir)
bool sesAlgilandi = false;

int ortalamaSesOku(int tekrar = 10) {
  long toplam = 0;
  for (int i = 0; i < tekrar; i++) {
    toplam += analogRead(MIC_PIN);
    delay(5);
  }
  return toplam / tekrar;
}

void setup() {
  Serial.begin(9600);
  seri.begin(9600);
  pinMode(MIC_PIN, INPUT);
  Serial.println("Kapı modülü başladı.");
}

void loop() {
  int sesDegeri = ortalamaSesOku();
  Serial.print("Ses değeri: ");
  Serial.println(sesDegeri);

  if (sesDegeri > ESIG_DEGER && !sesAlgilandi) {
    seri.println("DOOR_BELL");
    Serial.println("Mesaj gönderildi: DOOR_BELL");
    sesAlgilandi = true;
  }
  if (sesDegeri <= ESIG_DEGER) {
    sesAlgilandi = false;
  }

  delay(100);
}