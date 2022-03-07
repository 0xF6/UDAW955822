#ifndef _UDAW95_H_
#define _UDAW95_H_

#include <Arduino.h>



#define UDAW95_I2C_ADDRESS 0x58   // base addr
#define UDAW95_REG_ID 0x10        // id register
#define UDAW95_ID 0x23            // id value
#define UDAW95_P0_IN_STATE 0x00   // P0 port input state
#define UDAW95_P1_IN_STATE 0x01   // P1 port input state
#define UDAW95_P0_OUT_STATE 0x02  // P0 port output state
#define UDAW95_P1_OUT_STATE 0x03  // P1 port output state
#define UDAW95_P0_CONF_STATE 0x04 // P0 port config state
#define UDAW95_P1_CONF_STATE 0x05 // P1 port config state
#define UDAW95_REG_GLOB_CTR 0x11  // global control register
#define UDAW95_P0_LED_MODE 0x12   // P0 port led mode switch register
#define UDAW95_P1_LED_MODE 0x13   // P1 port led mode switch register
#define UDAW95_REG_SOFT_RST 0x7F  // soft reset register


#ifdef DEBUG
#define DEBUG_PRINTER Serial
#define DEBUG_PRINT(...)                  \
    {                                     \
        DEBUG_PRINTER.print(__VA_ARGS__); \
    }
#define DEBUG_PRINTLN(...)                  \
    {                                       \
        DEBUG_PRINTER.println(__VA_ARGS__); \
    }
#else
#define DEBUG_PRINT(...) \
    {                    \
    }
#define DEBUG_PRINTLN(...) \
    {                      \
    }
#endif

enum UDAW95Port
{
    P0 = 0x00, // Port 0
    P1 = 0x01, // Port 1
};

enum UDAW95PortMode
{
    OPEN_DRAIN = 0x00, // Port 0 open drain mode
    PUSH_PULL = 1 << 4 // Port 0 push pull mode
};

enum UDAW95LedsDim
{
    DIM_MAX = B00, // 0~IMAX 37mA(typical)
    DIM_MED = B01, // 0~(IMAX×3/4)
    DIM_LOW = B10, // 0~(IMAX×2/4)
    DIM_MIN = B11, // 0~(IMAX×1/4)
};

enum UDAW95LedDimCtrl
{
    P1_0 = 0x20, // DIM0
    P1_1 = 0x21, // DIM1
    P1_2 = 0x22, // DIM2
    P1_3 = 0x23, // DIM3
    P0_0 = 0x24, // DIM4
    P0_1 = 0x25, // DIM5
    P0_2 = 0x26, // DIM6
    P0_3 = 0x27, // DIM7
    P0_4 = 0x28, // DIM8
    P0_5 = 0x29, // DIM9
    P0_6 = 0x2A, // DIM10
    P0_7 = 0x2B, // DIM11
    P1_4 = 0x2C, // DIM12
    P1_5 = 0x2D, // DIM13
    P1_6 = 0x2E, // DIM14
    P1_7 = 0x2F, // DIM15
};


class UDAW95
{
    public: 
        UDAW95(uint8_t offset = 0);
        boolean begin();
        void reset();
    private:
        uint8_t writeI2C(uint8_t reg, uint8_t val);
        uint8_t readI2C(uint8_t reg);
        uint8_t _addr;
        uint8_t _portIn = UDAW95_P0_IN_STATE;
        uint8_t _portOut = UDAW95_P0_OUT_STATE;
        UDAW95PortMode portMode = OPEN_DRAIN;
        UDAW95LedsDim ledsDim = DIM_MAX;
}