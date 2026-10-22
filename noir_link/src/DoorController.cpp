#include <Arduino.h>

#include "DoorController.h"
#include "EventManager.h"

extern EventManager eventManager;

void DoorController::begin()
{
    state = DoorState::LOCKED;
    unclockStartTime = 0;

    Serial.println("[DOOR] Door controller initialized");
    Serial.println("[DOOR] Initial state: LOCKED");
}

bool DoorController::unlock()
{
    if (state == DoorState::UNLOCKED)
    {
        Serial.println("[DOOR] Door is already unlocked");
        return false;
    }

    state = DoorState::UNLOCKED;
    unclockStartTime = millis(); // Thoi diem bat dau mo khoa

    Serial.println("[DOOR] Door unlocked");

    eventManager.recordEvent(EventType::DOOR_UNLOCKED);

    return true;
}

void DoorController::lock()
{
    if (state == DoorState::LOCKED)
    {
        return;
    }

    state = DoorState::LOCKED;

    Serial.println("[DOOR] Door locked");

    eventManager.recordEvent(EventType::DOOR_LOCKED);
}


DoorState DoorController::getState() const 
{
    return state;
}

void DoorController::update()
{
    if (state != DoorState::UNLOCKED)
    {
        return;
    }

    uint32_t elapsedTime = millis() - unclockStartTime;

    if (elapsedTime >= AppConfig::UNLOCK_DURATION_MS)
    {
        Serial.println("[DOOR] Unlock duration expired");
        lock();
    }
}