#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <cstdint>

namespace AppConfig {
    constexpr uint32_t UNLOCK_DURATION_MS = 5000;
    constexpr uint8_t MAX_FAILED_ATTEMPTS = 5;
    constexpr uint32_t AUTH_LOCKOUT_DURATION_MS = 30000;
}

#endif // APP_CONFIG_H