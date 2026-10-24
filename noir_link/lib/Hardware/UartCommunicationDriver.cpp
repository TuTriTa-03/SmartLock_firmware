#include "UartCommunicationDriver.h"

UartCommunicationDriver::UartCommunicationDriver(
    HardwareSerial& serialPort,
    int8_t rxPin,
    int8_t txPin,
    uint32_t baudRate
)
    : serialPort(serialPort),
      rxPin(rxPin),
      txPin(txPin),
      baudRate(baudRate)
{
}

bool UartCommunicationDriver::begin()
{
    serialPort.begin(
        baudRate,
        SERIAL_8N1,
        rxPin,
        txPin
    );

    return true;
}

size_t UartCommunicationDriver::send(
    const uint8_t* data,
    size_t length
)
{
    if (data == nullptr || length == 0)
    {
        return 0;
    }

    return serialPort.write(data, length);
}

size_t UartCommunicationDriver::receive(
    uint8_t* buffer,
    size_t bufferSize
)
{
    if (buffer == nullptr || bufferSize == 0)
    {
        return 0;
    }

    size_t bytesRead = 0;

    while (serialPort.available() > 0 && bytesRead < bufferSize)
    {
        int receivedByte = serialPort.read();

        if (receivedByte >= 0)
        {
            buffer[bytesRead] = static_cast<uint8_t>(receivedByte);
            bytesRead++;
        }
    }

    return bytesRead;
}