#pragma once

#include <Arduino.h>
#include <vector>
#include <Preferences.h>

class StorageManager {
public:
    static StorageManager& getInstance() {
        static StorageManager instance;
        return instance;
    }

    bool begin() {
        return preferences.begin("kkd_storage", false);
    }

    void addBarcode(const String& barcode) {
        barcodes.push_back(barcode);
        saveSession();
    }

    const std::vector<String>& getBarcodes() const {
        return barcodes;
    }

    size_t getBarcodeCount() const {
        return barcodes.size();
    }

    void clearSession() {
        barcodes.clear();
        preferences.remove("count");
        preferences.remove("list");
    }

    void finalizeAssignment(const String& cardUid) {
        Serial.printf("\n========================================\n");
        Serial.printf(">>> ZIMMETLEME TAMAMLANDI <<<\n");
        Serial.printf("Kart UID: %s\n", cardUid.c_str());
        Serial.printf("Toplam Zimmetlenen Barkod Sayisi: %d\n", (int)barcodes.size());
        
        for (size_t i = 0; i < barcodes.size(); ++i) {
            Serial.printf("  [%d] %s\n", (int)(i + 1), barcodes[i].c_str());
        }
        Serial.printf("========================================\n\n");

        clearSession();
    }

private:
    StorageManager() = default;
    Preferences preferences;
    std::vector<String> barcodes;

    void saveSession() {
        preferences.putUInt("count", barcodes.size());
        String serialized = "";
        for (const auto& b : barcodes) {
            serialized += b + ";";
        }
        preferences.putString("list", serialized);
    }
};
