#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * Initialize comms
 */
void hal_comms_init();

/**
 * Send buffer over comms, ret bytes sent
 * @param buf
 * @param len
 * @return
 */
int hal_comms_send_buffer(uint8_t *buf, char len);

/**
 * Recev mesg from comms, ret bytes recev
 * @param buf
 * @param buf_len
 * @return
 */
int hal_comms_recev_buffer(uint8_t *buf, char buf_len);

void hal_comms_close();