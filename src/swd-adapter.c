#include <mchck.h>
#include "DAP_config.h"
#include "DAP.h"

#include "swd-adapter.desc.h"


struct fifo_head {
        volatile size_t write;
        volatile size_t read;
        volatile size_t count;
        const size_t max;
};

#define fifo_enqueue_advance(head)                              \
        do {                                                    \
                size_t next = head.write + 1;                   \
                head.write = next == head.max ? 0 : next;       \
                head.count++;                                   \
        } while (0)

#define fifo_dequeue_advance(head)                              \
        do {                                                    \
                size_t next = head.read + 1;                    \
                head.read = next == head.max ? 0 : next;        \
                head.count--;                                   \
        } while (0)


static struct fifo_head request_fifo = {.max = DAP_PACKET_COUNT};
static struct fifo_head reply_fifo = {.max = DAP_PACKET_COUNT};

static struct output_report requests[DAP_PACKET_COUNT];
static struct input_report replies[DAP_PACKET_COUNT];

static struct input_report outgoing;

static volatile int replies_running;


int
get_report(struct hid_ctx *ctx, enum hid_report_type type, uint8_t report_id, enum hid_report_req req)
{
        if (req != HID_REPORT_REQ_INT) {
                hid_update_data(ctx, report_id, NULL, 0);
                return (0);
        }

        if (reply_fifo.count > 0) {
                outgoing = replies[reply_fifo.read];
                fifo_dequeue_advance(reply_fifo);
                hid_update_data(ctx, report_id, &outgoing, sizeof(outgoing));
                return (sizeof(outgoing));
        } else {
                replies_running = 0;
                return (-1);
        }
}

int
set_report(const enum hid_report_type type, const uint8_t report_id, void **data_in, size_t data_len, const enum hid_report_req req)
{
        if (data_len == 0)
                return (1);

        if (*data_in == NULL) {
                /* setup phase */
                if (request_fifo.count == request_fifo.max)
                        return (0);

                *data_in = &requests[request_fifo.write];
        } else {
                /* transfer done */
                fifo_enqueue_advance(request_fifo);
        }

        return (1);
}

void
init_adapter(int enable)
{
}

void
main(void)
{
        DAP_Setup();

        usb_init(&swd_dev);

        for (;;) {
                /* XXX wfi */
                if (request_fifo.count > 0) {
                        DAP_ProcessCommand(requests[request_fifo.read].data,
                                           replies[reply_fifo.write].data);
                        crit_enter();
                        fifo_dequeue_advance(request_fifo);
                        fifo_enqueue_advance(reply_fifo);
                        if (!replies_running) {
                                replies_running = 1;
                                get_report(&hid_ctx, 0, 0, HID_REPORT_REQ_INT);
                        }
                        crit_exit();
                }
        }
}
