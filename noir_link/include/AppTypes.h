#ifndef APP_TYPES_H
#define APP_TYPES_H

#include <cstdint>

// 1. Door State
enum class DoorState : uint8_t {
    LOCKED,
    UNLOCKED
};


// 2. Authentication Result
enum class AuthResult : uint8_t {
    SUCCESS,
    FAILED,
    LOCKED_OUT
};

// 3. System Event
enum class EventType : uint8_t {
    DOOR_LOCKED,
    DOOR_UNLOCKED,
    AUTH_SUCCESS,
    AUTH_FAILED,
    SOS_TRIGGERED,
    AUTH_LOCKED_OUT
};

enum class DoorCommand : uint8_t {
    UNLOCK,
    LOCK
};

#endif // APP_TYPES_H