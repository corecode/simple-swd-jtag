#include <mchck.h>
#include "DAP_config.h"
#include "swd-adapter.desc.h"

static uint8_t uart2cdc_buf[1];
static struct uart_trans_ctx uart2cdc, cdc2uart;
volatile static int uart_reading;

static struct cdc_line_coding line_coding = {
        .dwDTERate = 9600,
        .bCharFormat = CDC_LINE_CODING_STOP_1,
        .bParityType = CDC_LINE_CODING_PARITY_NONE,
        .bDataBits = 8,
};

static void
set_line_coding(void *buf, ssize_t len, void *cbdata)
{
        /* XXX apply line coding to uart */
        uart_set_baudrate(&lpuart0, line_coding.dwDTERate);
        usb_handle_control_status(0);
}

int
serial_control(struct usb_ctrl_req_t *req, void *func)
{
        switch ((enum cdc_ctrl_req_code)req->bRequest) {
        case USB_CTRL_REQ_CDC_SET_LINE_CODING:
                if (req->wLength != sizeof(line_coding))
                        return (0);
                usb_ep0_rx(&line_coding, req->wLength, set_line_coding, func);
                break;
        case USB_CTRL_REQ_CDC_GET_LINE_CODING:
                usb_ep0_tx_cp(&line_coding, sizeof(line_coding), req->wLength, NULL, NULL);
                usb_handle_control_status(0);
                break;
        default:
                return (0);
        }
        return (1);
}

static void
new_uart_data(const void *buf, size_t len, void *cbdata)
{
        if (len > 0) {
                cdc_write(buf, len, &serial);
        }
        if (cdc_write_space(&serial) > 0) {
                uart_read(&lpuart0, &uart2cdc, uart2cdc_buf, sizeof(uart2cdc_buf), new_uart_data, NULL);
                uart_reading = 1;
        } else {
                uart_reading = 0;
        }
}

static void
uart_write_done(const void *buf, size_t len, void *cbdata)
{
        cdc_read_more(&serial);
}

void
serial_data_ready(uint8_t *data, size_t len)
{
        uart_write(&lpuart0, &cdc2uart, data, len, uart_write_done, NULL);
}

void
serial_data_sent(size_t len)
{
        if (!uart_reading) {
                new_uart_data(NULL, 0, NULL);
        }
}

void
serial_setup(int enable)
{
        if (enable) {
                gpio_write(PIN_TDI_DIR, MUX_OUTPUT);
                pin_mode(PIN_TDI, PIN_MODE_MUX_ALT3);
                pin_mode(PIN_TDO, PIN_MODE_MUX_ALT3);
                uart_set_baudrate(&lpuart0, line_coding.dwDTERate);
        } else {
                gpio_write(PIN_TDI_DIR, MUX_INPUT);
                pin_mode(PIN_TDI, PIN_MODE_MUX_GPIO);
                pin_mode(PIN_TDO, PIN_MODE_MUX_GPIO);
        }
}

void
serial_init(void)
{
        uart_init(&lpuart0);
        serial_setup(1);
        uart_write_done(NULL, 0, NULL);
        new_uart_data(NULL, 0, NULL);
}
