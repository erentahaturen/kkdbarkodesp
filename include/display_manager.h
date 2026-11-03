#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "config.h"

class DisplayManager {
public:
    static DisplayManager& getInstance() {
        static DisplayManager instance;
        return instance;
    }

    void begin() {
        tft.init(240, 240); // 240x240 ST7789 başlat
        tft.setRotation(2); // Düz ekran yönü
        showIdleScreen();
    }

    void showIdleScreen() {
        tft.fillScreen(ST77XX_BLACK);
        
        // Üst Başlık Bandı
        tft.fillRect(0, 0, 240, 35, ST77XX_NAVY);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(2);
        tft.setCursor(18, 10);
        tft.println("KKD TAKIP SISTEMI");

        // Durum Metinleri
        tft.setTextColor(ST77XX_CYAN);
        tft.setTextSize(2);
        tft.setCursor(20, 80);
        tft.println("SISTEM HAZIR");

        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(1);
        tft.setCursor(20, 120);
        tft.println("1. Barkod okutun (G16)");
        tft.setCursor(20, 145);
        tft.println("2. Kart okutun (G26)");

        tft.drawFastHLine(20, 180, 200, ST77XX_DARKGREY);

        tft.setTextColor(ST77XX_YELLOW);
        tft.setTextSize(2);
        tft.setCursor(20, 200);
        tft.println("Okunan: 0 adet");
    }

    void showBarcodeRead(int count, const String& barcode) {
        tft.fillScreen(ST77XX_BLACK);

        // Yeşil Başlık Bandı
        tft.fillRect(0, 0, 240, 35, ST77XX_DARKGREEN);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(2);
        tft.setCursor(25, 10);
        tft.println("BARKOD OKUNDU!");

        tft.setTextColor(ST77XX_GREEN);
        tft.setTextSize(2);
        tft.setCursor(20, 70);
        tft.printf("%d. URUN EKLENDI\n", count);

        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(1);
        tft.setCursor(20, 110);
        tft.println("Kod: " + barcode);

        tft.fillRect(20, 150, 200, 30, ST77XX_NAVY);
        tft.setTextColor(ST77XX_ORANGE);
        tft.setTextSize(1);
        tft.setCursor(30, 160);
        tft.println("G2 AKTIF (2 SN)...");
    }

    void showCardAssigned(const String& cardId, int totalCount) {
        tft.fillScreen(ST77XX_BLACK);

        // Mavi Başlık Bandı
        tft.fillRect(0, 0, 240, 35, ST77XX_BLUE);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(2);
        tft.setCursor(15, 10);
        tft.println("ZIMMETLENDI!");

        tft.setTextColor(ST77XX_YELLOW);
        tft.setTextSize(2);
        tft.setCursor(20, 70);
        tft.println("KART ID:");
        tft.setTextSize(1);
        tft.setTextColor(ST77XX_WHITE);
        tft.setCursor(20, 95);
        tft.println(cardId);

        tft.setTextColor(ST77XX_GREEN);
        tft.setTextSize(2);
        tft.setCursor(20, 130);
        tft.printf("Toplam: %d Urun\n", totalCount);

        tft.fillRect(20, 175, 200, 30, ST77XX_DARKGREEN);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(1);
        tft.setCursor(45, 185);
        tft.println("ISLEM BASARILI");
    }

private:
    DisplayManager() : tft(PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_RST) {}
    Adafruit_ST7789 tft;
};
