#include <mchck.h>
#include "DAP_config.h"

enum {
        PIN_TCK_SWCLK = PIN_PTD5,
        PIN_TMS_SWDIO = PIN_PTC6,
        PIN_TDI = PIN_PTD6,
        PIN_TDO = PIN_PTD7,
        PIN_nRESET = PIN_PTE0,

        PIN_LED_RED = PIN_PTB0,
        PIN_LED_GREEN = PIN_PTB1,
};

void
PORT_JTAG_SETUP(void)
{
        gpio_write(PIN_TCK_SWCLK, GPIO_HIGH);
        gpio_write(PIN_TMS_SWDIO, GPIO_HIGH);
        gpio_write(PIN_TDI, GPIO_HIGH);

        gpio_dir(PIN_TCK_SWCLK, GPIO_OUTPUT);
        gpio_dir(PIN_TMS_SWDIO, GPIO_OUTPUT);
        gpio_dir(PIN_TDI, GPIO_OUTPUT);
        gpio_dir(PIN_nRESET, GPIO_INPUT);
}

void
PORT_SWD_SETUP(void)
{
        gpio_write(PIN_TCK_SWCLK, GPIO_HIGH);
        gpio_write(PIN_TMS_SWDIO, GPIO_HIGH);

        gpio_dir(PIN_TCK_SWCLK, GPIO_OUTPUT);
        gpio_dir(PIN_TMS_SWDIO, GPIO_OUTPUT);
        gpio_dir(PIN_TDI, GPIO_DISABLE);
        gpio_dir(PIN_nRESET, GPIO_INPUT);
}

void
PORT_OFF(void)
{
        gpio_dir(PIN_TCK_SWCLK, GPIO_DISABLE);
        gpio_dir(PIN_TMS_SWDIO, GPIO_DISABLE);
        gpio_dir(PIN_TDI, GPIO_DISABLE);
        gpio_dir(PIN_nRESET, GPIO_DISABLE);
}

uint32_t
PIN_SWCLK_TCK_IN(void)
{
        return (gpio_read(PIN_TCK_SWCLK));
}

void
PIN_SWCLK_TCK_SET(void)
{
        fgpio_set(PIN_TCK_SWCLK, GPIO_HIGH);
}

void
PIN_SWCLK_TCK_CLR(void)
{
        fgpio_clear(PIN_TCK_SWCLK, GPIO_LOW);
}

uint32_t
PIN_SWDIO_TMS_IN(void)
{
        return (fgpio_read(PIN_TMS_SWDIO));
}

void
PIN_SWDIO_TMS_SET(void)
{
        fgpio_set(PIN_TMS_SWDIO, GPIO_HIGH);
}

void
PIN_SWDIO_TMS_CLR(void)
{
        fgpio_clear(PIN_TMS_SWDIO, GPIO_LOW);
}

uint32_t
PIN_SWDIO_IN(void)
{
        return (fgpio_read(PIN_TMS_SWDIO));
}

void
PIN_SWDIO_OUT(uint32_t bit)
{
        gpio_write(PIN_TMS_SWDIO, bit & 1);
}

void
PIN_SWDIO_OUT_ENABLE(void)
{
        gpio_dir(PIN_TMS_SWDIO, GPIO_OUTPUT);
}

void
PIN_SWDIO_OUT_DISABLE(void)
{
        gpio_dir(PIN_TMS_SWDIO, GPIO_INPUT);
}

uint32_t
PIN_TDI_IN(void)
{
        return (fgpio_read(PIN_TDI));
}

void
PIN_TDI_OUT(uint32_t bit)
{
        gpio_write(PIN_TDI, bit & 1);
}

uint32_t
PIN_TDO_IN(void)
{
        return (fgpio_read(PIN_TDO));
}

uint32_t
PIN_nRESET_IN(void)
{
        return (fgpio_read(PIN_nRESET));
}

void
PIN_nRESET_OUT(uint32_t bit)
{
        if (bit == 0) {
                gpio_write(PIN_nRESET, 0);
                gpio_dir(PIN_nRESET, GPIO_OUTPUT);
        } else {
                gpio_dir(PIN_nRESET, GPIO_INPUT);
        }
}

void
LED_CONNECTED_OUT(uint32_t bit)
{
        gpio_write(PIN_LED_GREEN, bit & 1);
}

void
LED_RUNNING_OUT(uint32_t bit)
{
        gpio_write(PIN_LED_RED, !(bit & 1));
}

void
DAP_SETUP(void)
{
        pin_mode(PIN_TCK_SWCLK, PIN_MODE_RESET);
        pin_mode(PIN_TMS_SWDIO, PIN_MODE_RESET);
        pin_mode(PIN_TDI, PIN_MODE_RESET);
        pin_mode(PIN_TDO, PIN_MODE_RESET);
        pin_mode(PIN_nRESET, PIN_MODE_RESET);

        gpio_dir(PIN_LED_RED, GPIO_OUTPUT);
        gpio_dir(PIN_LED_GREEN, GPIO_OUTPUT);
        gpio_dir(PIN_TDO, GPIO_INPUT);

        gpio_write(PIN_LED_RED, GPIO_LOW);
        gpio_write(PIN_LED_GREEN, GPIO_LOW);
}

uint32_t
RESET_TARGET(void)
{
        return (0);
}
