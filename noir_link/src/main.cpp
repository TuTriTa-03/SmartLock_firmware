
#include <Arduino.h>

#include "AccessManager.h"
#include "EventManager.h"
#include "DoorController.h"

// Cac doi tuong dung chung
EventManager eventManager;
AccessManager accessManager;
DoorController doorController;

void setup()
{
    Serial.begin(115200);
    delay(10000);

    Serial.println();
    Serial.println("=== NOIR HOME MODULE TEST ===");

    accessManager.begin();
    doorController.begin();

    // Test 1: PIN dung -> mo cua
    Serial.println("\n[Test 1] Correct PIN");

    AuthResult result = accessManager.authenticatePin("123456");

    Serial.print("Result: ");
    Serial.println(static_cast<int>(result));

    if (result == AuthResult::SUCCESS)
    {
        doorController.unlock();
    }

    // Test 2: Cho cua tu khoa sau 5 giay
    Serial.println("\n[Test 2] Auto-lock after 5 seconds");

    while (doorController.getState() == DoorState::UNLOCKED)
    {
        doorController.update();
        delay(50);
    }

    Serial.println("[TEST] Auto-lock test completed");

    // Test 3: Nhap sai den gioi han
    Serial.println("\n[Test 3] Failed attempts limit");

    for (int i = 1; i <= 5; i++)
    {
        result = accessManager.authenticatePin("000000");

        Serial.print("Attempt ");
        Serial.print(i);
        Serial.print(", result: ");
        Serial.println(static_cast<int>(result));
    }

    // Test 4: Thu PIN dung khi dang bi khoa
    Serial.println("\n[Test 4] Correct PIN during lockout");

    result = accessManager.authenticatePin("123456");

    Serial.print("Result: ");
    Serial.println(static_cast<int>(result));

    Serial.println("\n=== TESTS COMPLETED ===");
}

void loop()
{
    accessManager.update();
}
