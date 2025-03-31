#include "ESP32_MCU_Alias.h"
#include <Arduino.h>
#include "Esp.h"


/*************************************************************************/

const String ManuFacturers[3] = {
  "XIAO",
  "Lolin_pico",
  "WROOOM"
};

const String MCU_Models[3] {
  "C3",
  "S3",
  "DevKitC V4"
};

typedef struct {
  uint8_t ManufactID;
  uint8_t ChipModel;
  long ChipID;
  uint8_t InnerSerial;
} Chip_Definition;

const Chip_Definition Chip_Alias[ALIAS_LENGTH] = {
  {0,    0,    15493324,   1},    //ESP32-C3 XIAO 1
  {1,    0,      207720,   1},    //ESP32-C3 Lolin pico 1
  {1,    0,     1822096,   2},    //ESP32-C3 Lolin pico
  {1,    0,      272564,   3},    //ESP32-C3 Lolin pico 3
  {1,    0,     2254280,   4},    //ESP32-C3 Lolin pico 4
  {0,    1,    10332768,   1},    //ESP32-S3 XIAO 1          X450  014C4
  {0,    1,    10328512,   2},    //ESP32-S3 XIAO 2          X450  01990
  {2,    2,     2533560,   1},    //ESP32-DevKitC V4 WROOOM 1
  {2,    2,    12800616,   2},    //ESP32-DevKitC V4 WROOOM 2
  {2,    2,    12799352,   3},    //ESP32-DevKitC V4 WROOOM 3
};

/*************************************************************************/

/**/
uint32_t getChipIDFromMacAddress(){
  uint32_t chipId = 0;

  for (int i = 0; i < 17; i = i + 8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  return chipId;
}

/**/
String getCompleteMCUNameFromChipID( long aChipID) {
 char buffer[30];
 String tempStr = "EPS32-";
 for (int i = 0; i < ALIAS_LENGTH; i++) {
    if (aChipID == Chip_Alias[i].ChipID) {
      tempStr = tempStr +  MCU_Models[Chip_Alias[i].ChipModel] + "_" + ManuFacturers[Chip_Alias[i].ManufactID] + "_" + Chip_Alias[i].InnerSerial;
      return tempStr;
    }  
  }
  /*If ever that chip is unknown, we'll get a lookalike name*/
  sprintf("%s_Rev_%d_(%d)", ESP.getChipModel(), ESP.getChipRevision(), aChipID);
  return buffer;
}