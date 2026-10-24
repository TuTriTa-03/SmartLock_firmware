#include <Arduino.h>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include "SerialLogger.h"

// Mutex dung chung de bao ve Serial
static SemaphoreHandle_t serialMutex = nullptr;

bool beginSerialLogger()
{
     // Tranh tao mutex moi neu logger da duoc khoi tao
    if (serialMutex != nullptr)
    {
        return true;
    }

    serialMutex = xSemaphoreCreateMutex();

    if (serialMutex == nullptr)
    {
        Serial.println("[LOGGER] Failed to create Serial mutex");
        return false;
    }

    Serial.println("[LOGGER] Serial mutex initialized");
    return true;
}


void serialLog(const char* message)
{
    // Khong in log neu mutex chua duoc khoi tao
    if (serialMutex == nullptr || message == nullptr)
    {
        return;
    }

    // Cho den khi lay duoc quyen su dung Serial
    if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE)
    {
        Serial.println(message);

        // Tra quyen su dung Serial cho task khac
        xSemaphoreGive(serialMutex);
    }
}