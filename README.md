# KKD Barkod, RDM6300 RFID ve ST7789 Ekran Sistemi (ESP32-S)

Bu proje; **ESP32-S (NodeMCU-32S)**, **MH-ET LIVE Barkod Okuyucu**, **RDM6300 125KHz RFID Okuyucu** ve **ST7789 240x240 IPS Renkli Ekran** bileşenlerini içeren endüstriyel zimmetleme gömülü yazılımıdır.

---

## 📌 Tam ve Kesin Pin Bağlantı Şeması

### 1. MH-ET LIVE Barkod Okuyucu Modülü ➔ ESP32-S
> **NOT:** MH-ET LIVE modülünde Seri TX/RX pinleri üretici tarafından **SDA / SCL** olarak etiketlenmiştir.

| MH-ET LIVE Pini | ESP32-S Pini / Güç | Açıklama |
|---|---|---|
| **VDD** | **5V (VIN)** | 5V Güç Beslemesi |
| **GND** | **GND** | Ortak Toprak Hattı |
| **SDA** | **P16 (GPIO 16)** | **Asıl Veri Hattı:** Okunan barkod ESP32 RX2 (P16) pinine akar |
| **SCL** | **Boşta (NC)** | Bağlanmaz |
| **RST** | **Boşta (NC)** | Bağlanmaz |

---

### 2. RDM6300 RFID Kart Okuyucu (125KHz) ➔ ESP32-S
> **NOT:** Modülün 4'lü pin grubundan bağlanır. 3'lü grup harici LED içindir (boş kalır).

| RDM6300 Pini | ESP32-S Pini / Güç | Açıklama |
|---|---|---|
| **VCC (+5V)** | **5V (VIN)** | 5V Güç Beslemesi |
| **GND** | **GND** | Ortak Toprak Hattı |
| **TX** | **P26 (GPIO 26)** | **Asıl Veri Hattı:** Kart ID verisi ESP32 RX1 (P26) pinine akar |
| **RX** | **Boşta (NC)** | Bağlanmaz |
| **ANT (2 Pin)** | **Bobin Anten** | Bakır sargılı bobin anten bağlanır (Yön fark etmez) |

---

### 3. ST7789 240x240 IPS Renkli Ekran ➔ ESP32-S
| ST7789 Ekran Pini | ESP32-S Pini / Güç | Açıklama |
|---|---|---|
| **VDD / VCC** | **3.3V** | **DİKKAT:** Ekran 3.3V ile beslenir |
| **GND** | **GND** | Ekran Toprak Hattı |
| **SCL** | **P18 (GPIO 18)** | Donanımsal SPI Saat Hattı (SCK) |
| **SDA** | **P23 (GPIO 23)** | Donanımsal SPI Veri Hattı (MOSI) |
| **DC / RS** | **P4 (GPIO 4)** | Data / Command Seçim Pini |
| **BLK / LED** | **3.3V** | Ekran Arka Aydınlatması |
| **RES / RST** | **3.3V** veya **EN** | Donanımsal Reset Hattı |

---

### 4. Tetik / Onay Çıkışı (P2)
* **ESP32 P2 (GPIO 2):**
  * Barkod okutulduğunda **1 (HIGH)** olur, **2 saniye bekler**, **0 (LOW)** olur.
  * Kart okutulduğunda **1 (HIGH)** olur, **2 saniye bekler**, **0 (LOW)** olur.
  * *Not:* ESP32-S kartı üzerindeki dahili mavi LED P2 pinine bağlıdır.

---

## ⚙️ Çalışma Mantığı
1. **Barkod Okuma:** Barkod okutulduğunda veri `P16` pininden yakalanır ve ESP32'nin kalıcı NVS hafızasına kaydedilir. ST7789 ekranda yeşil tema ile kaçıncı ürünün eklendiği gösterilir. `P2` pini 2 saniye boyunca aktif edilir.
2. **Kart Okuma ve Zimmetleme:** İşlem sonunda RDM6300 modülüne 125KHz personel kartı yaklaştırılır. `P26` üzerinden gelen kart ID'si doğrulanır ve hafızadaki tüm barkodlar bu karta zimmetlenir. Ekranda zimmet raporu gösterilir, `P2` pini 2 saniye aktif edilerek döngü sıfırlanır.

---

## 🚀 Derleme ve Yükleme (VS Code / PlatformIO)
1. USB kablosunu bilgisayara takın.
2. VS Code alt mavi çubuğundan **Build (✓)** ve ardından **Upload (→)** butonuna basın.
3. Seri port ekranını **115200 baud** hızında açarak canlı logları izleyin.
