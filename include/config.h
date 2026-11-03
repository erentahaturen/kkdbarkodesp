#pragma once

#include <Arduino.h>

// ==========================================
// PIN TANIMLAMALARI (Donanım Haritası)
// ==========================================

// MH-ET LIVE Barkod & QR Kod Okuyucu Modülü (UART2)
#define PIN_BARCODE_RX      16  // ESP32 GPIO16 (G16) <- MH-ET LIVE "TX" pini (Mor Kablo)
#define PIN_BARCODE_TX      17  // ESP32 GPIO17 (G17) -> MH-ET LIVE "RX" pini (Turuncu Kablo)
#define BARCODE_BAUDRATE    9600 // MH-ET LIVE varsayılan fabrika baud hızı

// RDM6300 125KHz RFID Kart Okuyucu (UART1 / Seri İletişim)
#define PIN_RDM6300_RX      26  // ESP32 GPIO26 (G26) <- RDM6300 "TX" pini
#define PIN_RDM6300_TX      25  // ESP32 GPIO25 (Kullanılmıyor)
#define RDM6300_BAUDRATE    9600

// Tetik / Sinyal Çıkış Pini
#define PIN_OUT_G2          2   // G2 (Tetik çıkışı: 1 yap, 2 sn bekle, 0 yap)

// ST7789 240x240 IPS Renkli Ekran Pinleri (Donanımsal SPI)
#define PIN_TFT_SCL         18  // G18 -> ST7789 SCL / SCK (Saat Hattı)
#define PIN_TFT_SDA         23  // G23 -> ST7789 SDA / MOSI (Veri Hattı)
#define PIN_TFT_DC          4   // G4  -> ST7789 DC / RS (Data/Command Seçimi)
#define PIN_TFT_CS          -1  // CS pini olmayan modüller için -1
#define PIN_TFT_RST         -1  // Reset pini 3.3V veya EN'e bağlıysa -1

// ==========================================
// SISTEM PARAMETRELERI
// ==========================================
#define SERIAL_DEBUG_BAUD   115200
#define PULSE_DURATION_MS   2000    // 2 saniye bekleme süresi
