#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

#include <Arduino.h>

class CommunicationManager {
public:
    //Khoi tao bo quan ly giao tiep
    void begin();

    //Gui thong diep van ban
    void sendMessage(const char* message);
};

#endif // COMMUNICATION_MANAGER_H