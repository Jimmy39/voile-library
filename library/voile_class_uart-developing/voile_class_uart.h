#ifndef __VOILE_CLASS_UART_H__
#define __VOILE_CLASS_UART_H__

#include "voile_common.h"

typedef enum {
    UART_TXbuffer_full,
    UART_TXbuffer_empty,
    UART_RXbuffer_full,
    UART_RXbuffer_empty
} voile_uart_flag_t;

typedef const struct voile_const_uart_struct_t voile_const_uart_t;

struct voile_struct_uart_t {

    uint8_t (*init)(voile_const_uart_t **self);

    uint32_t (*setBaudrate)(voile_const_uart_t **self, uint32_t baudrate);

    void (*send)(voile_const_uart_t **self, uint8_t *data_p, uint8_t length);

    uint8_t (*receive)(
        voile_const_uart_t **self, uint8_t *data_p, uint8_t length);

    bool (*getFlag)(voile_const_uart_t **self, voile_uart_flag_t flag);
};

#endif  // !__VOILE_CLASS_UART_H__
