#include <stdint.h>
#include <mchck.h>

enum {
        PIN_TCK_SWCLK = PIN_PTC5,
        PIN_TCK_SWCLK_DIR = PIN_PTC7,
        PIN_TMS_SWDIO = PIN_PTC6,
        PIN_TMS_SWDIO_DIR = PIN_PTC4,
        PIN_TDI = PIN_PTD7,
        PIN_TDI_DIR = PIN_PTE0,
        PIN_TDO = PIN_PTD6,
        PIN_nRESET_INPUT = PIN_PTD4,
        PIN_nRESET_OUTPUT = PIN_PTE30,

        PIN_LED_RED = PIN_PTB0,
        PIN_LED_GREEN = PIN_PTB1,

        PIN_ADC_VTARGET_SENSE = 11,
};

enum {
        MUX_OUTPUT = GPIO_HIGH,
        MUX_INPUT = GPIO_LOW,
};

#define CPU_CLOCK 48000000
#define IO_PORT_WRITE_CYCLES 2
#define DAP_SWD 1
#define DAP_JTAG 1
#define DAP_JTAG_DEV_CNT 8
#define DAP_DEFAULT_PORT 1
#define DAP_DEFAULT_SWJ_CLOCK 1000000
#define DAP_PACKET_SIZE 64
#define DAP_PACKET_COUNT 20
#define TARGET_DEVICE_FIXED 0

void PORT_JTAG_SETUP(void);
void PORT_SWD_SETUP(void);
void PORT_OFF(void);
uint32_t PIN_SWCLK_TCK_IN(void);
void PIN_SWCLK_TCK_SET(void);
void PIN_SWCLK_TCK_CLR(void);
uint32_t PIN_SWDIO_TMS_IN(void);
void PIN_SWDIO_TMS_SET(void);
void PIN_SWDIO_TMS_CLR(void);
uint32_t PIN_SWDIO_IN(void);
void PIN_SWDIO_OUT(uint32_t bit);
void PIN_SWDIO_OUT_ENABLE(void);
void PIN_SWDIO_OUT_DISABLE(void);
uint32_t PIN_TDI_IN(void);
void PIN_TDI_OUT(uint32_t bit);
uint32_t PIN_TDO_IN(void);
uint32_t PIN_nRESET_IN(void);
void PIN_nRESET_OUT(uint32_t bit);
void LED_CONNECTED_OUT(uint32_t bit);
void LED_RUNNING_OUT(uint32_t bit);
void DAP_SETUP(void);
uint32_t RESET_TARGET(void);

#define PIN_nTRST_IN() (0)
#define PIN_nTRST_OUT(x) /**/


void serial_setup(int enable);
void serial_init(void);
