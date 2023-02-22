/**
 * @file common.h
 * @author Nicklas Börjesson (nicklasb@gmail.com)
 * @brief Provides commonly used functionality for implementing the Robusto
 * communication protocol
 * @version 0.1
 * @date 2023-02-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "stdint.h"

typedef struct communication_preamble {
    uint8_t message_type;
    bool send_receipt;
    bool has_binary;
    bool has_strings;
    bool is_conversation;
    bool is_forwarding_request;
    bool is_forwarded;

} communication_preamble_t;


bool common_check_receipt(uint8_t * msg);

uint32_t common_calc_crc(uint8_t * data);

uint8_t *common_add_preamble(communication_preamble_t preamble, uint8_t msg);
communication_preamble_t common_parse_preamble();
