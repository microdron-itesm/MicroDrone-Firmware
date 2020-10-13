//
// Created by abiel on 9/4/20.
//

/**
 * Used to facilitate comms between firmware running on linux and simulator
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
//#include "PC/PC_HAL_CONFIG.h"

/**
 * Initialize comms
 */
ssize_t hal_sim_comms_init(void *options);

/**
 * Send buffer over comms, ret bytes sent
 * @param buf
 * @param len
 * @return
 */
ssize_t hal_sim_comms_send_buffer(uint8_t *buf, size_t len);

/**
 * Recev mesg from comms, ret bytes recev
 * @param buf
 * @param buf_len
 * @return
 */
ssize_t hal_sim_comms_recv_buffer(uint8_t *buf, size_t buf_len);


ssize_t hal_sim_comms_close();

