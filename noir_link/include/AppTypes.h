#ifndef APP_TYPES_H
#define APP_TYPES_H

#include <cstdint>

// 1. Door State
enum class DoorState : uint8_t {
    LOCKED,
    UNLOCKED
};

// 2. AuthResult
enum class AuthResult : uint8_t {
    SUCCESS,
    FAILED,
    LOCKED_OUT
};

// 3. Type of Event 
enum class EventType : uint8_t {
    DOOR_LOCKED,
    DOOR_UNLOCKED,
    AUTH_SUCCESS,
    AUTH_FAILED,
    SOS_TRIGGERED
};

#endif // APP_TYPES_H