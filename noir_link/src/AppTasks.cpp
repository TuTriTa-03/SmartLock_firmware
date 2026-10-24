#include <Arduino.h>
#include <cstring>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "AppTasks.h"
#include "AccessManager.h"
#include "DoorController.h"
#include "SerialLogger.h"

// Cac doi tuong dung chung
extern AccessManager accessManager;
extern DoorController doorController;

// Kich thuoc toi da cua PIN (bao gom ky tu '\0')
static constexpr size_t PIN_BUFFER_SIZE = 16;

// So luong yeu cau toi da moi Queue co the luu
static constexpr UBaseType_t QUEUE_LENGTH = 5;

// Cau truc luu yeu cau xac thuc PIN
struct AuthRequest
{
    char pin[PIN_BUFFER_SIZE];
};

// Queue chua cac lenh dieu khien cua
static QueueHandle_t doorCommandQueue = nullptr;

// Queue chua cac yeu cau xac thuc PIN
static QueueHandle_t authRequestQueue = nullptr;

bool beginDoorCommandQueue()
{
    // Neu queue da ton tai => ko tao lai
    if (doorCommandQueue != nullptr)
    {
        return true;
    }

    // Tao Queue chua toi da 5 lenh DoorCommand
    doorCommandQueue = xQueueCreate(
        QUEUE_LENGTH,
        sizeof(DoorCommand));

    if (doorCommandQueue == nullptr)
    {
        serialLog("[RTOS] Failed to create DoorCommand Queue");
        return false;
    }

    serialLog("[RTOS] DoorCommand Queue created");
    return true;
}

bool sendDoorCommand(DoorCommand command)
{
    // Ko gui neu Queue chua duoc tao
    if (doorCommandQueue == nullptr)
    {
        serialLog("[RTOS] DoorCommandQueue is not initialized");
        return false;
    }

    // Cho toi da 100ms neu Queue dang day
    BaseType_t result = xQueueSend(
        doorCommandQueue,
        &command,
        pdMS_TO_TICKS(100));

    if (result != pdPASS)
    {
        serialLog("[RTOS] Failed to send door command");
        return false;
    }

    return true;
}

static bool beginAuthRequestQueue()
{
    if (authRequestQueue != nullptr)
    {
        return true;
    }

    authRequestQueue = xQueueCreate(
        QUEUE_LENGTH,
        sizeof(AuthRequest));

    if (authRequestQueue == nullptr)
    {
        serialLog("[RTOS] Failed to create AuthRequestQueue");
        return false;
    }

    serialLog("[RTOS] AuthRequestQueue created");
    return true;
}

bool requestPinAuthentication(const char *pin)
{
    if (authRequestQueue == nullptr)
    {
        serialLog("[AUTH] AuthRequestuthQueue is not initialized");
        return false;
    }

    if (pin == nullptr)
    {
        serialLog("[AUTH] PIN input is NULL");
        return false;
    }

    size_t pinLength = strlen(pin);

    if (pinLength == 0 || pinLength >= PIN_BUFFER_SIZE)
    {
        serialLog("[AUTH] PIN length is invalid");
        return false;
    }

    AuthRequest request{};

    memcpy(request.pin, pin, pinLength);
    request.pin[pinLength] = '\0';

    BaseType_t result = xQueueSend(
        authRequestQueue,
        &request,
        pdMS_TO_TICKS(100));

    if (result != pdPASS)
    {
        serialLog("[AUTH] Failed to queue PIN request");
        return false;
    }

    serialLog("[AUTH] PIN request queued");
    return true;
}

// Xu ly lenh nhan duoc tu Queue
static void processDoorCommand(DoorCommand command)
{
    switch (command)
    {
    case DoorCommand::UNLOCK:
        doorController.unlock();
        break;
    case DoorCommand::LOCK:
        doorController.lock();
        break;

    default:
        serialLog("[DOOR] Invalid door command");
        break;
    }
}

// Task quan ly cua
static void doorTask(void *pvParameters)
{
    (void)pvParameters;

    DoorCommand command;

    while (true)
    {
        // Cho doi lenh toi da 50ms
        if (xQueueReceive(
                doorCommandQueue,
                &command,
                pdMS_TO_TICKS(50)) == pdPASS)
        {
            processDoorCommand(command);
        }

        // Cap nhat tu dong khoa cua
        doorController.update();
    }
}

// Task cap nhat trang thai khoa xac thuc
static void accessTask(void *pvParameters)
{
    (void)pvParameters;

    AuthRequest request{};

    while (true)
    {
        // Cho doi yeu cau PIN toi da 50ms
        if (xQueueReceive(
                authRequestQueue,
                &request,
                pdMS_TO_TICKS(50)) == pdPASS)
        {
            // Xac thuc PIN
            AuthResult result = accessManager.authenticatePin(request.pin);

            switch (result)
            {
            case AuthResult::SUCCESS:
                serialLog("[AUTH] Authentication SUCCESS");

                if (sendDoorCommand(DoorCommand::UNLOCK))
                {
                    serialLog("[AUTH] Unlock command queued");
                }

                else
                {
                    serialLog("[AUTH] Failed to queue unlock command");
                }

                break;

            case AuthResult::FAILED:
                serialLog("[AUTH] Authentication failed");
                break;

            case AuthResult::LOCKED_OUT:
                serialLog("[AUTH] Authentication locked out");
                break;

            default:
                serialLog("[AUTH] Unknown authentication result");
                break;
            }
        }
        // Cap nhat trang thai AccessManager
        accessManager.update();
    }
}

bool startAppTasks()
{
    // Buoc 1 : Dam bao Queue da duoc da khoi tao
    if (!beginDoorCommandQueue())
    {
        serialLog("[RTOS] Cannot start tasks : Queue initialization failed");
        return false;
    }

    if (!beginAuthRequestQueue())
    {
        serialLog("[RTOS] Cannot create AuthRequestQueue");
        return false;
    }

    // Buoc 2 : Tao DoorTask
    TaskHandle_t doorTaskHandle = nullptr;

    BaseType_t doorResult = xTaskCreate(
        doorTask,
        "DoorTask",
        3072,
        nullptr,
        1,
        &doorTaskHandle);

    if (doorResult != pdPASS)
    {
        serialLog("[RTOS] Failed to create DoorTask");
        return false;
    }

    serialLog("[RTOS] DoorTask created");

    // Buoc 3 : Tao AccessTask
    TaskHandle_t accessTaskHandle = nullptr;

    BaseType_t accessResult = xTaskCreate(
        accessTask,
        "AccessTask",
        3072,
        nullptr,
        1,
        &accessTaskHandle);

    if (accessResult != pdPASS)
    {
        serialLog("[RTOS] Failed to create AccessTask");

        // AccessTask tao that bai:
        // xoa DoorTask da tao truoc do
        vTaskDelete(doorTaskHandle);

        return false;
    }

    serialLog("[RTOS] AccessTask created");
    serialLog("[RTOS] All application tasks started");

    return true;
}