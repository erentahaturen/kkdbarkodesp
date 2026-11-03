#include <Arduino.h>
#include <SPI.h>
#include "config.h"
#include "storage_manager.h"
#include "display_manager.h"

// Donanımsal Seri Port 2 (Barkod Okuyucu - GPIO16)
HardwareSerial BarcodeSerial(2);

// Donanımsal Seri Port 1 (RDM6300 RFID Okuyucu - GPIO26)
HardwareSerial RfidSerial(1);

// Fonksiyon Prototipleri
void triggerG2Output();
void checkBarcodeReader();
void checkRdm6300Reader();
String parseRdm6300Tag(const uint8_t *buffer);

void setup() {
    // 1. USB Seri Port (Bilgisayar Debug Ekranı)
    Serial.begin(SERIAL_DEBUG_BAUD);
    delay(1000);
    Serial.println("\n--- KKD BARKOD & RDM6300 & ST7789 SISTEMI BASLATILIYOR ---");

    // 2. G2 Tetik Pini
    pinMode(PIN_OUT_G2, OUTPUT);
    digitalWrite(PIN_OUT_G2, LOW);

    // 3. ST7789 240x240 Ekran Başlatma (SPI: SCL=G18, SDA=G23, DC=G4)
    SPI.begin(PIN_TFT_SCL, -1, PIN_TFT_SDA, PIN_TFT_CS);
    DisplayManager::getInstance().begin();
    Serial.println("[OK] ST7789 240x240 Ekran Baslatildi (SCL: G18, SDA: G23, DC: G4).");

    // 4. Dahili NVS Kalıcı Hafıza
    if (StorageManager::getInstance().begin()) {
        Serial.println("[OK] NVS Flash Bellek Hazir.");
    }

    // 5. Barkod Okuyucu (UART2 - RX: GPIO16)
    BarcodeSerial.begin(BARCODE_BAUDRATE, SERIAL_8N1, PIN_BARCODE_RX, PIN_BARCODE_TX);
    Serial.printf("[OK] Barkod Okuyucu UART baslatildi (RX: GPIO%d, Baud: %d)\n", PIN_BARCODE_RX, BARCODE_BAUDRATE);

    // 6. RDM6300 125KHz RFID Okuyucu (UART1 - RX: GPIO26)
    RfidSerial.begin(RDM6300_BAUDRATE, SERIAL_8N1, PIN_RDM6300_RX, PIN_RDM6300_TX);
    Serial.printf("[OK] RDM6300 RFID UART baslatildi (RX: GPIO%d, Baud: %d)\n", PIN_RDM6300_RX, RDM6300_BAUDRATE);

    Serial.println("Sistem hazir! Barkod okutabilir veya RDM6300'e 125KHz Kart yaklastirabilirsiniz...\n");
}

void loop() {
    // Barkod okuyucuyu dinle (GPIO16)
    checkBarcodeReader();

    // RDM6300 kart okuyucuyu dinle (GPIO26)
    checkRdm6300Reader();

    delay(10);
}

// -------------------------------------------------------------
// G2 Sinyal Çıkışı & 2 Saniye Bekleme Döngüsü
// (Kural: eger barkod/kart 1 -> yaz G2 1 -> bekle 2)
// -------------------------------------------------------------
void triggerG2Output() {
    Serial.println("--> G2 Pini HIGH (1) yapildi. (2 saniye bekleniyor...)");
    digitalWrite(PIN_OUT_G2, HIGH);
    delay(PULSE_DURATION_MS); // 2 saniye bekle
    digitalWrite(PIN_OUT_G2, LOW);
    Serial.println("--> G2 Pini LOW (0) yapildi.\n");
}

// -------------------------------------------------------------
// Barkod Okuma İşlemi (GPIO16)
// -------------------------------------------------------------
void checkBarcodeReader() {
    if (BarcodeSerial.available()) {
        String barcodeData = BarcodeSerial.readStringUntil('\n');
        barcodeData.trim();

        if (barcodeData.length() > 0) {
            StorageManager::getInstance().addBarcode(barcodeData);
            size_t count = StorageManager::getInstance().getBarcodeCount();

            Serial.printf("[+] %d. BARKOD OKUNDU (G16): %s\n", (int)count, barcodeData.c_str());

            // ST7789 Ekrana Yazdır
            DisplayManager::getInstance().showBarcodeRead(count, barcodeData);

            // Tetik: G2 = 1, 2 sn bekle
            triggerG2Output();
        }
    }
}

// -------------------------------------------------------------
// RDM6300 125KHz RFID Okuma İşlemi (GPIO26)
// -------------------------------------------------------------
void checkRdm6300Reader() {
    static uint8_t buffer[14];
    static uint8_t index = 0;

    while (RfidSerial.available()) {
        uint8_t incomingByte = RfidSerial.read();

        // Başlangıç baytı (0x02 - STX)
        if (incomingByte == 0x02) {
            index = 0;
            buffer[index++] = incomingByte;
            continue;
        }

        // Paket toplanıyor
        if (index > 0 && index < 14) {
            buffer[index++] = incomingByte;

            if (index == 14) {
                if (buffer[13] == 0x03) {
                    String cardId = parseRdm6300Tag(buffer);
                    if (cardId.length() > 0) {
                        int totalCount = StorageManager::getInstance().getBarcodeCount();
                        Serial.printf("[RDM6300] 125KHz KART OKUNDU (G26)! KART ID: %s\n", cardId.c_str());

                        // ST7789 Ekrana Zimmetleme Raporunu Bas
                        DisplayManager::getInstance().showCardAssigned(cardId, totalCount);

                        // Kart sahibine mevcut barkodları zimmetle
                        StorageManager::getInstance().finalizeAssignment(cardId);

                        // Tetik: G2 = 1, 2 sn bekle
                        triggerG2Output();

                        // 3 saniye sonra ekranı başlangıç moduna al
                        delay(1000);
                        DisplayManager::getInstance().showIdleScreen();
                    }
                }
                index = 0;
            }
        }
    }
}

// -------------------------------------------------------------
// RDM6300 Checksum Kontrolü
// -------------------------------------------------------------
String parseRdm6300Tag(const uint8_t *buf) {
    char tagStr[11];
    for (int i = 0; i < 10; i++) {
        tagStr[i] = (char)buf[1 + i];
    }
    tagStr[10] = '\0';

    uint8_t checksum = 0;
    for (int i = 0; i < 5; i++) {
        char byteHex[3] = { (char)buf[1 + (i * 2)], (char)buf[2 + (i * 2)], '\0' };
        checksum ^= (uint8_t)strtol(byteHex, NULL, 16);
    }

    char chkHex[3] = { (char)buf[11], (char)buf[12], '\0' };
    uint8_t receivedChecksum = (uint8_t)strtol(chkHex, NULL, 16);

    if (checksum == receivedChecksum) {
        return String(tagStr);
    } else {
        Serial.println("[HATA] RDM6300 Checksum hatasi!");
        return "";
    }
}
