#pragma once

#include <Arduino.h>

// ==========================================
// PIN TANIMLAMALARI (Donanım Haritası)
// ==========================================

// Barkod Okuyucu (UART2)
#define PIN_BARCODE_RX      16  // ESP32 GPIO16 -> Barkod Okuyucu TX
#define PIN_BARCODE_TX      17  // ESP32 GPIO17 -> Barkod Okuyucu RX (Varsayılan boşta)
#define BARCODE_BAUDRATE    9600

// RFID / NFC Okuyucu (RC522 - SPI Varsayılanı / SS Pin)
#define PIN_RFID_SS         26  // ESP32 GPIO26 (SDA / SS Pini)
#define PIN_RFID_RST        27  // ESP32 GPIO27 (Reset Pini)
#define PIN_RFID_SCK        18  // Standart VSPI SCK
#define PIN_RFID_MISO       19  // Standart VSPI MISO
#define PIN_RFID_MOSI       23  // Standart VSPI MOSI

// Ekran / Durum Kontrol Pinleri
#define PIN_DISP_RS         18  // G18
#define PIN_DISP_EN         23  // G23
#define PIN_OUT_G2          2   // G2 (Tetik / LED / Sinyal çıkışı)
#define PIN_DISP_D4         4   // G4

// ==========================================
// SISTEM PARAMETRELERI
// ==========================================
#define SERIAL_DEBUG_BAUD   115200
#define MAX_BARCODES        50      // Tek zimmetleme periyodunda okunabilecek azami barkod
#define PULSE_DURATION_MS   2000    // İstediğin 2 saniye bekleme süresi (G2 aktifleştirme)
