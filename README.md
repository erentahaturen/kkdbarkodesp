# KKD Barkod & NFC Zimmetleme Sistemi (ESP32)

Bu proje, ardışık okutulan barkodları ESP32'nin kalıcı NVS hafızasında biriktiren ve son olarak okutulan RFID/NFC kart sahibine zimmetleyen endüstriyel gömülü yazılımdır.

## 📌 Pin Bağlantı Şeması

| Modül / Aygıt | Fonksiyon | ESP32 GPIO | Açıklama |
|---|---|---|---|
| **Barkod Okuyucu** | TX (Veri Çıkışı) | **GPIO 16 (G16)** | ESP32 HardwareSerial2 RX |
| **RFID / NFC** | SDA / SS | **GPIO 26 (G26)** | RC522 Chip Select / Slave Select |
| **Tetik / Çıkış (LED/Röle)** | Sinyal Çıkışı | **GPIO 2 (G2)** | Barkod veya Kart okunduğunda 2 sn aktif |
| **Ekran** | RS | **GPIO 18 (G18)** | Ekran RS Pini |
| **Ekran** | EN | **GPIO 23 (G23)** | Ekran Enable Pini |
| **Ekran** | D4 | **GPIO 4 (G4)** | Ekran Data 4 Pini |

## ⚙️ Çalışma Mantığı
1. Barkod okutulduğunda veri seri porttan (G16) alınır ve hafızaya `1. barkod`, `2. barkod` şeklinde eklenir.
2. Barkod okunduğu anda `G2` pini `HIGH (1)` yapılır, 2 saniye beklenir ve `LOW (0)` durumuna geri döner.
3. Zimmetleme aşamasında NFC/RFID kart okutulur. Kartın UID bilgisi alınır ve toplanan tüm barkodlar bu karta zimmetlenir.
4. Kart okunduğu anda da `G2` pini `HIGH (1)` yapılır, 2 saniye beklenir ve oturum sıfırlanarak yeni döngüye geçilir.

## 🚀 VS Code ile Başlatma
1. VS Code'da `kkdbarkodesp` klasörünü açın.
2. PlatformIO eklentisi yüklü ise alt bardan **Build (✓)** ve **Upload (→)** ikonuna tıklayın.
3. Seri port ekranını **115200 baud** hızıyla açarak canlı logları takip edin.
