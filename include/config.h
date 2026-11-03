#pragma once

#include <Arduino.h>

// ==========================================
// PIN TANIMLAMALARI (Donanım Haritası)
// ==========================================

// Barkod Okuyucu (UART2)
#define PIN_BARCODE_RX      16  // ESP32 GPIO16 (G16) -> Barkod Okuyucu TX
#define PIN_BARCODE_TX      17  // ESP32 GPIO17 -> Barkod Okuyucu RX (Varsayılan boşta)
#define BARCODE_BAUDRATE    9600

// RDM6300 125KHz RFID Kart Okuyucu (UART1 / Seri İletişim)
#define PIN_RDM6300_RX      26  // ESP32 GPIO26 (G26) -> RDM6300 TX pini bağlanır
#define PIN_RDM6300_TX      25  // ESP32 GPIO25 (Kullanılmıyor, RDM6300 tek yönlüdür)
#define RDM6300_BAUDRATE    9600

// Tetik ve Ekran Pinleri
#define PIN_OUT_G2          2   // G2 (Tetik / Sinyal çıkışı: 1 yap, 2 sn bekle)
#define PIN_DISP_RS         18  // G18
#define PIN_DISP_EN         23  // G23
#define PIN_DISP_D4         4   // G4

// ==========================================
// SISTEM PARAMETRELERI
// ==========================================
#define SERIAL_DEBUG_BAUD   115200
#define PULSE_DURATION_MS   2000    // 2 saniye bekleme süresi (G2 tetikleme)
