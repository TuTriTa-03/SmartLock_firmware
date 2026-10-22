#include <Arduino.h>
#include <cstring>

#include "AccessManager.h"
#include "AppConfig.h"
#include "EventManager.h"

extern EventManager eventManager;

void AccessManager::begin()
{
    failedAttempts = 0;
    lockedOut = false;
    lockoutStartTime = 0;

    Serial.println("[AUTH] Access manager initialized");
}

AuthResult AccessManager::authenticatePin(const char *pin)
{
    if (lockedOut)
    {
        Serial.println("[AUTH] Authentication is temporarily locked");
        return AuthResult::LOCKED_OUT;
    }

    if (pin == nullptr)
    {
        Serial.println("[AUTH] Invalid PIN input");
        return AuthResult::FAILED;
    }

    const char *correctPin = "123456";

    if (strcmp(pin, correctPin) == 0)
    {
        failedAttempts = 0;

        Serial.println("[AUTH] PIN accepted");
        eventManager.recordEvent(EventType::AUTH_SUCCESS);

        return AuthResult::SUCCESS;
    }

    failedAttempts++;

    Serial.println("[AUTH] Incorrect PIN");
    eventManager.recordEvent(EventType::AUTH_FAILED);

    if (failedAttempts >= AppConfig::MAX_FAILED_ATTEMPTS)
    {
        lockedOut = true;
        lockoutStartTime = millis();

        Serial.println("[AUTH] Too many failed attempts");

        return AuthResult::FAILED;
    }

    // Chua dat gioi han nhung PIN da sai
    return AuthResult::FAILED;
}

void AccessManager::update()
{
    if (!lockedOut)
    {
        return;
    }

    uint32_t elapsedTime = millis() - lockoutStartTime;

    if (elapsedTime >= AppConfig::AUTH_LOCKOUT_DURATION_MS)
    {
        lockedOut = false;
        failedAttempts = 0;
        lockoutStartTime = 0;

        Serial.println("[AUTH] Authentication lockout expired");
    }
}