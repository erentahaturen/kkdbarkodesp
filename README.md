# KKD Barkod, RDM6300 RFID ve ST7789 Ekran Sistemi (ESP32)

Bu proje; **MH-ET LIVE Barkod Okuyucu**, **RDM6300 125KHz RFID Kart Okuyucu** ve **ST7789 240x240 IPS Renkli Ekran** ile çalışan endüstriyel zimmetleme yazılımıdır.

## 📌 Tam Pin ve Bağlantı Tablosu

### 1. MH-ET LIVE Barkod Okuyucu
| Modül Pini | Kablo Rengi | ESP32 GPIO / Güç | Açıklama |
|---|---|---|---|
| **5V** | 🔴 Kırmızı | **5V (VIN)** | 5V Güç Beslemesi |
| **GND** | ⚫ Siyah | **GND** | Ortak Toprak Hattı |
| **TX** | 🟣 Mor | **GPIO 16 (G16)** | ESP32 HardwareSerial2 RX |
| **RX** | 🟠 Turuncu | **GPIO 17 (G17)** | ESP32 HardwareSerial2 TX (Opsiyonel) |

### 2. RDM6300 RFID Kart Okuyucu (125KHz)
| Modül Pini | ESP32 GPIO / Güç | Açıklama |
|---|---|---|
| **TX** | **GPIO 26 (G26)** | ESP32 HardwareSerial1 RX (9600 Baud) |
| **VCC** | **5V** | 5V Güç Beslemesi |
| **GND** | **GND** | Ortak Toprak Hattı |

### 3. ST7789 240x240 IPS Renkli Ekran
| Modül Pini | ESP32 GPIO / Güç | Açıklama |
|---|---|---|
| **SCL / SCK** | **GPIO 18 (G18)** | Donanımsal SPI Saat Hattı |
| **SDA / MOSI** | **GPIO 23 (G23)** | Donanımsal SPI Veri Hattı |
| **DC** | **GPIO 4 (G4)** | Data / Command Seçim Pini |
| **VCC / BLK** | **3.3V** | Güç ve Arka Aydınlatma |
| **GND** | **GND** | Ortak Toprak Hattı |

### 4. Tetik / Çıkış (LED/Röle/Buzzer)
| Donanım | ESP32 GPIO | Mantık |
|---|---|---|
| **Tetik Sinyali** | **GPIO 2 (G2)** | Barkod veya Kart okunduğunda **1** olur, **2 sn bekler**, **0** olur |

---

## ⚙️ Çalışma Akışı
1. **MH-ET LIVE** modülünden bir barkod okutulduğunda veri `G16` üzerinden yakalanır.
2. ST7789 ekranda okunan ürün sayısı yeşil renkte gösterilir.
3. `G2` pini 2 saniye boyunca aktif edilir.
4. İstenen sayıda barkod okutulduktan sonra **RDM6300** modülüne 125KHz personel kartı yaklaştırılır.
5. Sistem toplanan tüm barkodları bu karta zimmetler, ekranda başarı raporu gösterir ve `G2` pinini 2 saniye aktif ederek oturumu tamamlar.
