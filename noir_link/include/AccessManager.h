
#ifndef ACCESS_MANAGER_H
#define ACCESS_MANAGER_H

#include <cstdint>
#include "AppTypes.h"

class AccessManager {
public:
    // Khoi tao bo quan ly xac thuc
    void begin();

    // Kiem tra PIN
    AuthResult authenticatePin(const char* pin);

    // Cap nhat thong tin khoa tam thoi
    void update();

private:
    // Dem so lan nhap sai
    uint8_t failedAttempts = 0;

    // Trang thai khoa tam thoi
    bool lockedOut = false;

    // Thoi diem bat dau khoa tam thoi (milliseconds)
    uint32_t lockoutStartTime = 0;
};

#endif // ACCESS_MANAGER_H
