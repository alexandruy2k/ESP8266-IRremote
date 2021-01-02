#ifndef CONSTANTS_H
#define CONSTANTS_H


const char* ssid = " ";
const char* password = " ";

static const uint32_t LedOn =           0xFFE01F;
static const uint32_t QPlusOnOff =      0x407F02FD;
static const uint32_t QPlusVolumeUp =   0x407F18E7;
static const uint32_t QPlusVolumeDown = 0x407F08F7;
static const uint32_t OptomaHd65OnOff = 0xF20A40BF;
static const uint32_t LgOnOff =         0x34347887;
static const uint32_t LgOpticalChannel =0x34346D92;
static const uint32_t LgVolumeUp =      0x3434E817;
static const uint32_t LgVolumeDown =    0x34346897;
static const uint32_t HdmiChannel1 =    0x1FE58A7;
static const uint32_t HdmiChannel2 =    0x1FE20DF;
static const uint32_t HdmiChannel3 =    0x1FE609F;

const int led = 16;
const uint16_t kIrLed = 4;  // ESP GPIO pin to use. Recommended: 4 (D2).

#endif  // CONSTANTS_H
