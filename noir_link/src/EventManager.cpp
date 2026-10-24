
#include "EventManager.h"
#include "SerialLogger.h"

void EventManager::recordEvent(EventType event)
{
    switch (event)
    {
        case EventType::DOOR_LOCKED:
            serialLog("[EVENT] Door locked");
            break;

        case EventType::DOOR_UNLOCKED:
            serialLog("[EVENT] Door unlocked");
            break;

        case EventType::AUTH_SUCCESS:
            serialLog("[EVENT] Authentication successful");
            break;

        case EventType::AUTH_FAILED:
            serialLog("[EVENT] Authentication failed");
            break;

        case EventType::SOS_TRIGGERED:
            serialLog("[EVENT] SOS triggered");
            break;

        default:
            serialLog("[EVENT] Unknown event");
            break;
    }
}
