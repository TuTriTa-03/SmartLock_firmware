#ifndef DOOR_CONTROLLER_H
#define DOOR_CONTROLLER_H

#include "AppTypes.h"
#include "AppConfig.h"

class DoorController {
public:
    // Khoi tao bo dieu khien cua
    void begin();

    // Yeu cau mo khoa
    bool unlock();

    // Khoa cua
    void lock();

    // Lay trang thai hien tai
    DoorState getState() const;

    // Cap nhat logic theo thoi gian
    void update();
private:
    // Trang thai hien tai cua cua
    DoorState state = DoorState::LOCKED;

    // Thoi diem bat dau mo khoa
    uint32_t unclockStartTime = 0;

};

#endif // DOOR_CONTROLLER_H