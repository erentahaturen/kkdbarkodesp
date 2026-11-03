#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "config.h"
#include "storage_manager.h"

// Donanımsal Seri Port 2 (Barkod Okuyucu)
HardwareSerial BarcodeSerial(2);

// RFID/NFC Modülü (MFRC522)
MFRC522 rfid(PIN_RFID_SS, PIN_RFID_RST);

// Fonksiyon Prototipleri
void triggerG2Output();
void checkBarcodeReader();
void checkRfidReader();

void setup() {
    // 1. USB Seri Port (Hata Ayıklama / Debug)
    Serial.begin(SERIAL_DEBUG_BAUD);
    delay(1000);
    Serial.println("\n--- KKD BARKOD & NFC ZIMMETLEME SISTEMI BASLATILIYOR ---");

    // 2. G2 ve Ekran Kontrol Pinleri Ayarlanıyor
    pinMode(PIN_OUT_G2, OUTPUT);
    digitalWrite(PIN_OUT_G2, LOW);

    pinMode(PIN_DISP_RS, OUTPUT);
    pinMode(PIN_DISP_EN, OUTPUT);
    pinMode(PIN_DISP_D4, OUTPUT);

    // 3. Dahili Kalıcı Hafıza (NVS Flash) Başlatma
    if (StorageManager::getInstance().begin()) {
        Serial.println("[OK] Dahili NVS Flash Depolama Hazir.");
    }

    // 4. Barkod Okuyucu Donanımsal Seri Portu (GPIO 16 RX)
    BarcodeSerial.begin(BARCODE_BAUDRATE, SERIAL_8N1, PIN_BARCODE_RX, PIN_BARCODE_TX);
    Serial.printf("[OK] Barkod Okuyucu UART baslatildi (RX: GPIO%d, Baud: %d)\n", PIN_BARCODE_RX, BARCODE_BAUDRATE);

    // 5. RFID / NFC Modülü (SPI - SS: GPIO 26)
    SPI.begin(PIN_RFID_SCK, PIN_RFID_MISO, PIN_RFID_MOSI, PIN_RFID_SS);
    rfid.PCD_Init();
    Serial.printf("[OK] RFID Modulu baslatildi (SDA/SS: GPIO%d)\n", PIN_RFID_SS);

    Serial.println("Sistem hazir! Barkod okutabilir veya Kart yaklastirabilirsiniz...\n");
}

void loop() {
    // Barkod okuyucuyu dinle
    checkBarcodeReader();

    // RFID / NFC okuyucuyu dinle
    checkRfidReader();

    delay(20); // İşlemciyi rahatlatmak için kısa döngü gecikmesi
}

// -------------------------------------------------------------
// G2 Sinyal Çıkışı & 2 Saniye Bekleme Döngüsü
// (İstediğin mantık: eger barkod/kart 1 -> yaz G2 1 -> bekle 2)
// -------------------------------------------------------------
void triggerG2Output() {
    Serial.println("--> G2 Pini HIGH (1) yapildi. (2 saniye bekleniyor...)");
    digitalWrite(PIN_OUT_G2, HIGH);
    delay(PULSE_DURATION_MS); // 2 saniye bekle
    digitalWrite(PIN_OUT_G2, LOW);
    Serial.println("--> G2 Pini LOW (0) yapildi.\n");
}

// -------------------------------------------------------------
// Barkod Okuma İşlemi
// -------------------------------------------------------------
void checkBarcodeReader() {
    if (BarcodeSerial.available()) {
        String barcodeData = BarcodeSerial.readStringUntil('\n');
        barcodeData.trim(); // Boşluk ve \r temizle

        if (barcodeData.length() > 0) {
            // Hafızaya ekle
            StorageManager::getInstance().addBarcode(barcodeData);
            size_t count = StorageManager::getInstance().getBarcodeCount();

            Serial.printf("[+] %d. BARKOD OKUNDU: %s\n", (int)count, barcodeData.c_str());

            // İstediğin kural: Barkod okunduğunda G2 = 1, 2 sn bekle
            triggerG2Output();
        }
    }
}

// -------------------------------------------------------------
// RFID / NFC Kart Okuma ve Zimmetleme İşlemi
// -------------------------------------------------------------
void checkRfidReader() {
    // Yeni kart var mı?
    if (!rfid.PICC_IsNewCardPresent()) {
        return;
    }

    // Kart UID okunabiliyor mu?
    if (!rfid.PICC_ReadCardSerial()) {
        return;
    }

    // UID Hex Dizesine Dönüştürülüyor
    String cardUid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        cardUid += (rfid.uid.uidByte[i] < 0x10 ? "0" : "");
        cardUid += String(rfid.uid.uidByte[i], HEX);
        if (i < rfid.uid.size - 1) cardUid += ":";
    }
    cardUid.toUpperCase();

    Serial.printf("[NFC] KART OKUNDU! UID: %s\n", cardUid.c_str());

    // Kart sahibine mevcut barkodları zimmetle
    StorageManager::getInstance().finalizeAssignment(cardUid);

    // Kart okunduğunda G2 = 1, 2 sn bekle
    triggerG2Output();

    // Kart okuyucuyu boşa çıkar
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}
