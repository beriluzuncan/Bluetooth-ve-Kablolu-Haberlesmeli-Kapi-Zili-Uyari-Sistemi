# Bluetooth ve Kablolu Haberleşmeli Kapı Zili Uyarı Sistemi

## Proje Özeti
Bu proje, kapı zilinin sesini algılayarak Arduino Nano ve Arduino Uno modülleri arasında Bluetooth veya kablolu seri iletişim yoluyla veri gönderen bir uyarı sistemi geliştirmeyi amaçlamaktadır. Kullanıcı kapı zilini duymasa bile, oda modülünde görsel ve işitsel uyarılarla kapı zilinin çaldığı anlaşılmaktadır.

## Donanım Bileşenleri
- Arduino Nano (Kapı Modülü)
- Arduino Uno (Oda Modülü)
- Mikrofon Sensörü
- HC-05 ve HC-06 Bluetooth Modülleri (Bluetooth iletişim için, kablolu alternatif de mevcut)
- 16x2 I2C LCD Ekran
- Kırmızı ve Yeşil LED’ler
- Mikro Servo Motor
- Buzzer

## Bağlantılar
- Arduino Nano D3 ↔ Arduino Uno D4 (TX/RX haberleşme)
- Arduino Nano D4 ↔ Arduino Uno D3 (RX/TX haberleşme)
- Mikrofon sensörü A0 (Arduino Nano)
- LCD ekran SDA → A4, SCL → A5 (Arduino Uno)
- Kırmızı LED → D6 (Arduino Uno)
- Yeşil LED → D7 (Arduino Uno)
- Servo Motor → D5 (Arduino Uno)
- Buzzer → D12 (Arduino Uno)

## Yazılım
- Kapı modülü mikrofon sesi algılar, eşik değerini aşınca "DOOR_BELL" mesajını gönderir.
- Oda modülü bu mesajı alır, LCD’de “Kapı Çaldı” mesajını gösterir, LED’leri yanıp söndürür, servo motor hareket eder ve buzzer melodili zil sesi çalar.

## Kurulum ve Kullanım
1. Tüm donanım bağlantılarını şemaya göre yapınız.
2. Arduino IDE’de kapı ve oda modülleri için ayrı ayrı kodları yükleyiniz.
3. Sistemi güç kaynağına bağlayıp çalıştırınız.
4. Kapı zili sesi algılandığında uyarılar aktif olacaktır.


---

**Proje Sahibi:** Beril Uzuncan  
**Tarih:** 2025

