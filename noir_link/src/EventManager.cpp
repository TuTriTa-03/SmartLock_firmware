#include <Arduino.h>
#include "EventManager.h"

void EventManager::recordEvent(EventType event)
{
    switch(event) {
        case EventType::DOOR_LOCKED:
            Serial.println("EVEN: Door locked");
            break;

        case EventType::DOOR_UNLOCKED:
            Serial.println("EVENT: Door unlocked");
            break;

        case EventType::AUTH_SUCCESS:
            Serial.println("EVENT: Authentication successful");
            break;

        case EventType::AUTH_FAILED:
            Serial.println("EVENT: Authentication failed");
            break;
        case EventType::SOS_TRIGGERED:
            Serial.println("EVENT: SOS triggered");
            break;
    }
}