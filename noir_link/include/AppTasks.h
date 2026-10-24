#ifndef APP_TASKS_H
#define APP_TASKS_H

#include <stdbool.h>
#include "AppTypes.h"

// Khoi tao Queue chua lenh dieu khien cua
bool beginDoorCommandQueue();

// Gui lenh dieu khien cua vao Queue
bool sendDoorCommand(DoorCommand command);

// Gui yeu cau xac thuc PIN vao Queue
bool requestPinAuthentication(const char* pin);

// Khoi dong cac FreeRTOS task
bool startAppTasks();

#endif // APP_TASKS_H
