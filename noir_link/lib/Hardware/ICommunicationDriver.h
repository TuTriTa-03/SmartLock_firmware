#ifndef I_COMMUNICATION_DRIVER_H
#define I_COMMUNICATION_DRIVER_H

#include <stddef.h>
#include <stdint.h>

class ICommunicationDriver
{
public:
    virtual ~ICommunicationDriver() = default;

    virtual bool begin() = 0;
    virtual size_t send(const uint8_t* data, size_t length) = 0;
    virtual size_t receive(uint8_t* buffer, size_t bufferSize) = 0;
};

#endif