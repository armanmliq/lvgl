// Read the ID from the TFT controller

// No other libraries are needed

// Original author unknown
// Adapted by Bodmer

// Change the pin settings to suit your hardware

//ESP32
#include "stdio.h"
#include "Arduino.h"

#define TFT_MISO 19
#define TFT_MOSI  23
#define TFT_SCK 18
#define TFT_CS 5
#define TFT_DC  17
#define TFT_RESET 16
#define TOUCH_CS 4
#define TFT_LED 22

// #define TFT_MOSI 23
// #define TFT_SCLK 18
// #define TFT_CS 5   // Chip select control pin
// #define TFT_DC 17  // Data Command control pin
// #define TFT_RST 16 // Reset pin (could connect to RST pin)
// #define TFT_LED 22
// #define TOUCH_CLK 18
// #define TOUCH_CS 4
// #define TOUCH_DIN 23
// #define TOUCH_DO 19
/* Example Serial Monitor output:

TFT driver register values:
===========================
Register 0x01: 0x00
Register 0x04: 0x548066
Register 0x09: 0x610000
Register 0x0A: 0x08
Register 0x0B: 0x00
Register 0x0C: 0x06
Register 0x0D: 0x00
Register 0x0E: 0x00
Register 0x0F: 0x00
Register 0x2E: 0x545454
Register 0x3F: 0x00
Register 0xDA: 0x54
Register 0xDB: 0x80
Register 0xDC: 0x66
===========================

*/

uint16_t rr = 4;

uint32_t readwrite8(uint8_t cmd, uint8_t bits, uint8_t dummy)
{
    uint32_t ret = 0;
    uint8_t val = cmd;
    int cnt = 8;
    digitalWrite(TFT_CS, LOW);
    digitalWrite(TFT_DC, LOW);
    pinMode(TFT_MOSI, OUTPUT);
    for (int i = 0; i < 8; i++) {   //send command
        digitalWrite(TFT_MOSI, (val & 0x80) != 0);
        digitalWrite(TFT_SCK, HIGH);
        digitalWrite(TFT_SCK, LOW);
        val <<= 1;
    }
    if (bits == 0) {
        digitalWrite(TFT_CS, HIGH);
        return 0;
    }
    pinMode(TFT_MISO, INPUT_PULLUP);
    digitalWrite(TFT_DC, HIGH);
    for (int i = 0; i < dummy; i++) {  //any dummy clocks
        digitalWrite(TFT_SCK, HIGH);
        digitalWrite(TFT_SCK, LOW);
    }
    for (int i = 0; i < bits; i++) {  // read results
        ret <<= 1;
        if (digitalRead(TFT_MISO)) ret |= 1;;
        digitalWrite(TFT_SCK, HIGH);
        digitalWrite(TFT_SCK, LOW);
    }
    digitalWrite(TFT_CS, HIGH);
    return ret;
}

void showreg(uint8_t reg, uint8_t bits, uint8_t dummy)
{
    uint32_t val;
    val = readwrite8(reg, bits, dummy);

    Serial.print("Register 0x");
    if (reg < 0x10) Serial.print("0");
    Serial.print(reg , HEX);
    Serial.print(": 0x");
    if (val < 0x10) Serial.print("0");
    Serial.println(val, HEX);
}

void setup() {
    // put your setup code here, to run once:
    uint32_t ID = 0;
    Serial.begin(115200);

    delay(4000); // Delay to allow USB to connect

    Serial.println("");
    Serial.println("TFT driver register values:");
    Serial.println("===========================");
    
    digitalWrite(TOUCH_CS, HIGH);
    digitalWrite(TFT_CS, HIGH);
    //    digitalWrite(TFT_SCK, HIGH);
    pinMode(TOUCH_CS, OUTPUT);
    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_SCK, OUTPUT);
    pinMode(TFT_MOSI, OUTPUT);
    pinMode(TFT_MISO, INPUT_PULLUP);
    pinMode(TFT_DC, OUTPUT);
    pinMode(TFT_RESET, OUTPUT);
    digitalWrite(TFT_RESET, HIGH);

    digitalWrite(TFT_RESET, LOW);   //Hardware Reset
    delay(50);
    digitalWrite(TFT_RESET, HIGH);
    delay(100);

    showreg(0x01, 0, 0);            //Software Reset
    delay(100);

    showreg(0x04, 24, 1);   //RDDID
    showreg(0x09, 32, 1);   //RDSTATUS
    showreg(0x0A, 8, 0);
    showreg(0x0B, 8, 0);
    showreg(0x0C, 8, 0);
    showreg(0x0D, 8, 0);
    showreg(0x0E, 8, 0);
    showreg(0x0F, 8, 0);
    showreg(0x2E, 24, 8);   //readGRAM
    showreg(0x3F, 32, 1);   //readGRAM
    showreg(0xDA, 8, 0);
    showreg(0xDB, 8, 0);
    showreg(0xDC, 8, 0);

    Serial.println("===========================");
}

void loop() {
//showreg(rr, 8, 0);
//showreg(rr, 24, 1);
//showreg(rr, 32, 1);
//rr++;
//if (rr >= 256) while(1) rr = 4;
//delay(25);
}



