#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <mavlink.h>

/**
 * Initialize comms
 */
ssize_t hal_comms_init(void *options, size_t size);

/**
 * Send buffer over comms, ret bytes sent
 * @param buf
 * @param len
 * @return
 */
ssize_t hal_comms_send_buffer(uint8_t *buf, size_t len);

/**
 * Recev mesg from comms, ret bytes recev
 * @param buf
 * @param buf_len
 * @return
 */
ssize_t hal_comms_recv_buffer(mavlink_message_t *msg, mavlink_status_t* status);

ssize_t hal_comms_close();