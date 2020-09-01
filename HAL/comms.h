#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Initialize comms
 */
ssize_t hal_comms_init();

/**
 * Send buffer over comms, ret bytes sent
 * @param buf
 * @param len
 * @return
 */
ssize_t hal_comms_send_buffer(uint8_t *buf, char len);

/**
 * Recev mesg from comms, ret bytes recev
 * @param buf
 * @param buf_len
 * @return
 */
ssize_t hal_comms_recv_buffer(uint8_t *buf, char buf_len);

ssize_t hal_comms_close();