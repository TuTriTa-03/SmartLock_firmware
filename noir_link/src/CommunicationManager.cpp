#include "CommunicationManager.h"

void CommunicationManager::begin() {
    Serial.println("[COMM] Communication manager initialized");
}

void CommunicationManager::sendMessage(const char* message) {
    if (message == nullptr)
    {
        Serial.println("[COMM] Error: null message");
        return;
    }

    Serial.println("[COMM] Sending: ");
    Serial.println(message);
}