# KKD Barkod & RDM6300 RFID & ST7789 Ekran Sistemi (ESP32)

Bu proje; **Barkod Okuyucu**, **RDM6300 125KHz RFID Okuyucu** ve **ST7789 240x240 IPS Renkli Ekran** bileşenlerini içeren endüstriyel zimmetleme yazılımıdır.

## 📌 Tam Pin Bağlantı Şeması

| Modül / Aygıt | Modül Pini | ESP32 GPIO | Açıklama |
|---|---|---|---|
| **Barkod Okuyucu** | TX | **GPIO 16 (G16)** | HardwareSerial2 RX |
| **Barkod Okuyucu** | GND | **GND** | Ortak Toprak |
| **RDM6300 RFID** | TX | **GPIO 26 (G26)** | HardwareSerial1 RX (9600 Baud) |
| **RDM6300 RFID** | VCC | **5V** | 5V Güç Beslemesi |
| **RDM6300 RFID** | GND | **GND** | Ortak Toprak |
| **ST7789 Ekran** | **SCL / SCK** | **GPIO 18 (G18)** | Donanımsal SPI Saat Hattı |
| **ST7789 Ekran** | **SDA / MOSI** | **GPIO 23 (G23)** | Donanımsal SPI Veri Hattı |
| **ST7789 Ekran** | **DC (Data/Command)** | **GPIO 4 (G4)** | Komut / Veri Seçim Pini |
| **ST7789 Ekran** | **RES / RST** | **3.3V veya EN** | Reset Pini (Yazılımsal -1) |
| **ST7789 Ekran** | **BLK / LED** | **3.3V** | Ekran Arka Işığı |
| **ST7789 Ekran** | **VCC / GND** | **3.3V / GND** | Güç Beslemesi |
| **Tetik Çıkışı** | Sinyal | **GPIO 2 (G2)** | Barkod/Kart okunduğunda 2 sn aktif |

## 🖥️ ST7789 Ekran Arayüzü
1. **Bekleme Modu:** "KKD TAKIP SISTEMI - SISTEM HAZIR"
2. **Barkod Okunduğunda:** Yeşil tema ile okunan ürün sayısı ve barkod kodu ekranda gösterilir.
3. **Kart Okunduğunda:** Mavi/Yeşil tema ile Kart ID'si ve toplam zimmetlenen ürün adedi ekranda raporlanır.
