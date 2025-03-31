#ifndef ESP32_MCU_ALIAS_H
#define ESP32_MCU_ALIAS_H

#include <Arduino.h>

uint32_t getChipIDFromMacAddress();
String getCompleteMCUNameFromChipID( long aChipID );

#endif /* ESP32_MCU_ALIAS_H */