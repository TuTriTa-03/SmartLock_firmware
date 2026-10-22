#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "AppTasks.h"
#include "AccessManager.h"
#include "DoorController.h"

extern AccessManager accessManager;
extern DoorController doorController;

// Task cap nhat trang thai cua
void doorTask(void *pvParameters)
{
    while(true)
    {
        doorController.update();

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// Task cap nhat trang thai khoa xac thuc
void accessTask(void *pvParameters)
{
    while(true)
    {
        accessManager.update();

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// Tao cac task cua ung dung
void startAppTasks()
{
    xTaskCreate(
        doorTask,
        "DoorTask",
        2048,
        nullptr,
        1,
        nullptr
    );

    xTaskCreate(
        accessTask,
        "AccessTask",
        2048,
        nullptr,
        1,
        nullptr
    );
}
