# KKD Barkod & RDM6300 RFID Zimmetleme Sistemi (ESP32)

Bu proje, ardışık okutulan barkodları ESP32'nin kalıcı NVS hafızasında biriktiren ve son olarak okutulan **RDM6300 125KHz RFID** kart sahibine zimmetleyen gömülü yazılımdır.

## 📌 Pin Bağlantı Şeması

| Modül / Aygıt | Fonksiyon / Pin | ESP32 GPIO | Açıklama |
|---|---|---|---|
| **Barkod Okuyucu** | TX (Veri Çıkışı) | **GPIO 16 (G16)** | ESP32 HardwareSerial2 RX |
| **RDM6300 RFID (125KHz)** | **TX Pini** | **GPIO 26 (G26)** | ESP32 HardwareSerial1 RX (9600 Baud) |
| **RDM6300 RFID (125KHz)** | **VCC** | **5V** | RDM6300 5V ile beslenir |
| **RDM6300 RFID (125KHz)** | **GND** | **GND** | Ortak Toprak Hattı |
| **Tetik / Çıkış (LED/Röle)** | Sinyal Çıkışı | **GPIO 2 (G2)** | Barkod veya Kart okunduğunda 2 sn aktif |
| **Ekran** | RS | **GPIO 18 (G18)** | Ekran RS Pini |
| **Ekran** | EN | **GPIO 23 (G23)** | Ekran Enable Pini |
| **Ekran** | D4 | **GPIO 4 (G4)** | Ekran Data 4 Pini |

## ⚙️ RDM6300 Çalışma Mantığı
* **RDM6300**, seri port (UART - 9600 baud) üzerinden 14 baytlık paket gönderir (`0x02` başlangıç + 10 bayt Kart ID + 2 bayt Checksum + `0x03` bitiş).
* Kod içinde yer alan `parseRdm6300Tag` fonksiyonu checksum kontrolü yaparak kart ID'sini doğrular ve anında zimmetleme fonksiyonuna aktarır.
* Barkod okunduğunda `G2 = 1` olur ve 2 saniye beklenir.
* Kart okunduğunda `G2 = 1` olur, 2 saniye beklenir ve oturum başarıyla tamamlanır.
