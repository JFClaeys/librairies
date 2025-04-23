#include "ESP32_MCU_Alias.h"
#include <Arduino.h>
#include "Esp.h"


/***************************Definition**********************************/

#define ALIAS_LENGTH 11
#define MANUFACT_LENGTH 3
#define MCU_LENGTH 4

const String ManuFacturers[MANUFACT_LENGTH ] = {
  "XIAO",
  "Lolin_pico",
  "WROOOM"
};

const String MCU_Models[MCU_LENGTH ] {
  "C3",
  "S3",
  "DevKitC V4",
  "C6"
};

typedef struct {
  uint8_t ManufactID;   // Board build, in fact..
  uint8_t ChipModel;    // type of Espressiv chip
  long ChipID;          // actualy, this is the last 3 digit of the MAC address 
  uint8_t InnerSerial;  // whenever there are mauny chips identical, they are numbered sequencially
} Chip_Definition;

const Chip_Definition Chip_Alias[ALIAS_LENGTH] = {
  {0,    0,    15493324,   1},    //ESP32-C3 XIAO 1  - dead
  {1,    0,      207720,   1},    //ESP32-C3 Lolin pico 1
  {1,    0,     1822096,   2},    //ESP32-C3 Lolin pico 2
  {1,    0,      272564,   3},    //ESP32-C3 Lolin pico 3
  {1,    0,     2254280,   4},    //ESP32-C3 Lolin pico 4
  {0,    1,    10332768,   1},    //ESP32-S3 XIAO 1          X450  014C4
  {0,    1,    10328512,   2},    //ESP32-S3 XIAO 2          X450  01990
  {2,    2,     2533560,   1},    //ESP32-DevKitC V4 WROOOM 1
  {2,    2,    12800616,   2},    //ESP32-DevKitC V4 WROOOM 2
  {2,    2,    12799352,   3},    //ESP32-DevKitC V4 WROOOM 3
  {0,    3,    16776886,   1},    //ESP32-C6 XIAO 1
};

/*************************************************************************/

/* MAC address is a universally unique 48 bit identifier
   As we want a relatively unique id, we're going to extract the last 3 bytes (18bits) */
uint32_t getChipIDFromMacAddress(){
  uint32_t chipId = 0;

  for (int i = 0; i < 17; i = i + 8) {  //execute 3 times, 0, 8 and 16
    /* take MAC address shift by 0,8 or 16, isolate all but the last byte
       and add it to already extracted bits*/
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
  return chipId;
}

/* Create an Alias name for that chip, based onits MAC address and a predefined array.
   This alias will be fed into ESP.BondDNS inorder to uniquely (and easily) identify
   a MCU on the Arduino IDE Network port (and local network) */
String getCompleteMCUNameFromChipID( long aChipID) {
 char buffer[30];
 String tempStr = "EPS32-";
 for (int i = 0; i < ALIAS_LENGTH; i++) {
    // Lookup for the ChipID match on the array.
    if (aChipID == Chip_Alias[i].ChipID) { 
      /* If found, buld up the alias.  
         I found out that space is not welcome in BoundDNS, this replacing by underscore */
      tempStr = tempStr +  MCU_Models[Chip_Alias[i].ChipModel] + "_" + ManuFacturers[Chip_Alias[i].ManufactID] + "_" + Chip_Alias[i].InnerSerial;
      return tempStr;
    }  
  }
  // If ever that chip is unknown, we'll get a lookalike name
  sprintf("%s_Rev_%d_(%d)", ESP.getChipModel(), ESP.getChipRevision(), aChipID);
  return buffer;
}