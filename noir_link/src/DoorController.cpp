
#include <Arduino.h>

#include "DoorController.h"
#include "AppConfig.h"
#include "EventManager.h"
#include "SerialLogger.h"

extern EventManager eventManager;

void DoorController::begin()
{
    state = DoorState::LOCKED;
    unclockStartTime = 0;

    serialLog("[DOOR] Door controller initialized");
    serialLog("[DOOR] Initial state: LOCKED");
}

bool DoorController::unlock()
{
    if (state == DoorState::UNLOCKED)
    {
        serialLog("[DOOR] Door is already unlocked");
        return false;
    }

    state = DoorState::UNLOCKED;
    unclockStartTime = millis();

    serialLog("[DOOR] Door unlocked");

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

    serialLog("[DOOR] Door locked");

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

    const uint32_t elapsedTime = millis() - unclockStartTime;

    if (elapsedTime >= AppConfig::UNLOCK_DURATION_MS)
    {
        serialLog("[DOOR] Unlock duration expired");
        lock();
    }
}
