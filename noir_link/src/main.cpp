
#include <Arduino.h>

#include "SerialLogger.h"
#include "AppTasks.h"
#include "AccessManager.h"
#include "EventManager.h"
#include "DoorController.h"
#include "AppConfig.h"

// Cac doi tuong dung chung
EventManager eventManager;
AccessManager accessManager;
DoorController doorController;

void setup()
{
    Serial.begin(115200);
    delay(10000);

    if (!beginSerialLogger())
    {
        Serial.println("[FATAL] Cannot initialize SerialLogger");

        while (true)
        {
            delay(1000);
        }
    }

    serialLog("=== NOIR HOME RTOS STARTING ===");

    accessManager.begin();
    doorController.begin();

    if (!startAppTasks())
    {
        serialLog("[FATAL] Cannot start application tasks");

        while (true)
        {
            delay(1000);
        }
    }

    serialLog("[MAIN] Application tasks started");

    // Buoc 1: Gui 5 PIN sai de kich hoat lockout
    serialLog("[TEST] Starting lockout test");

    for (int i = 1; i <= AppConfig::MAX_FAILED_ATTEMPTS; i++)
    {
        serialLog("[TEST] Sending incorrect PIN");

        if (requestPinAuthentication("000000"))
        {
            serialLog("[TEST] Incorrect PIN queued");
        }
        else
        {
            serialLog("[TEST] Failed to queue incorrect PIN");
        }

        delay(200);
    }

    // Cho AccessTask xu ly cac request truoc khi gui tiep
    delay(500);

    // Buoc 2: Thu PIN dung trong thoi gian lockout
    serialLog("[TEST] Sending correct PIN during lockout");

    if (requestPinAuthentication("123456"))
    {
        serialLog("[TEST] Correct PIN request queued");
    }

    // Cho AccessTask xu ly request
    delay(500);

    // Buoc 3: Cho lockout het han
    serialLog("[TEST] Waiting for lockout to expire");
    delay(AppConfig::AUTH_LOCKOUT_DURATION_MS + 1000);

    // Buoc 4: Thu lai PIN dung sau lockout
    serialLog("[TEST] Retesting correct PIN after lockout");

    if (requestPinAuthentication("123456"))
    {
        serialLog("[TEST] Final PIN request queued");
    }
    else
    {
        serialLog("[TEST] Failed to queue final PIN request");
    }

    serialLog("[TEST] Lockout test sequence completed");
}

void loop()
{
    delay(1000);
}
