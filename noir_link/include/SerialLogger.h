
#ifndef SERIAL_LOGGER_H
#define SERIAL_LOGGER_H

// Khoi tao mutex bao ve Serial
bool beginSerialLogger();

// In mot thong bao log an toan giua cac task
void serialLog(const char* message);

#endif // SERIAL_LOGGER_H