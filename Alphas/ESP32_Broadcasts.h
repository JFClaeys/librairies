#ifndef ESP32_BROADCAST_LIB_H
#define ESP32_BROADCAST_LIB_H

/*Since iit is using the ESP NOW protocol, this structuer cannot exceed 250 bytes*/

/* Versinn 1
 */
 #define LATEST_BROADCAST_PACKET_VERSION 1
 
typedef struct {
  byte Version;  // with new versions come new features.
  byte ColorHueToDisplay;
  byte Delay;
} TExchangeDataPacket;


#endif// ALPHAS_LIB_H