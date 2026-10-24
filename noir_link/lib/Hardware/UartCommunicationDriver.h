#ifndef UART_COMMUNICATION_DRIVER_H
#define UART_COMMUNICATION_DRIVER_H

#include <Arduino.h>
#include "ICommunicationDriver.h"

class UartCommunicationDriver : public ICommunicationDriver
{
public:
    UartCommunicationDriver(
        HardwareSerial& serialPort,
        int8_t rxPin,
        int8_t txPin,
        uint32_t baudRate = 115200
    );

    bool begin() override;
    size_t send(const uint8_t* data, size_t length) override;
    size_t receive(uint8_t* buffer, size_t bufferSize) override;

private:
    HardwareSerial& serialPort;
    int8_t rxPin;
    int8_t txPin;
    uint32_t baudRate;
};

#endif