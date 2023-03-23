/**
 * @file robusto_system.h
 * @author Nicklas Börjesson (nicklasb@gmail.com)
 * @brief Robusto generic system functions
 * @version 0.1
 * @date 2023-02-19
 * 
 * @copyright 
 * Copyright (c) 2023, Nicklas Börjesson <nicklasb at gmail dot com>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <robusto_system.h>
#include <robusto_retval.h>
/* The length of MAC-addresses in SDP. DO NOT CHANGE.*/
#define ROBUSTO_MAC_ADDR_LEN 6

/* The SD MAC-address type */
typedef uint8_t robusto_mac_address[ROBUSTO_MAC_ADDR_LEN];
/**
 * @brief A proxy for malloc() for Rubusto
 * 
 * @param size Number of bytes to allocate
 * @return void* Pointer to the allocated memory
 */
void * robusto_malloc(size_t size);
/**
 * @brief A proxy for rermalloc() for Rubusto
 * 
 * @param ptr Pointer to the memory to be reallocate
 * @param size  Number of bytes to allocate
 * @return void* Pointer to the re-allocated memory
 */
void * robusto_realloc(void **ptr, size_t size);

/**
 * @brief Deallocates the memory at the pointer
 * 
 * @param ptr Pointer to the memory to be freed
 */
void robusto_free(void *ptr);

/**
 * @brief Calculate bitwise big-endian Ethernet AUTODIN II CRC32
 * 
 * @param crc Seed value for computation.  ~0 for Ethernet, sometimes 0 for
 *        other uses, or the previous crc32 value if computing incrementally.
 * @param buf Pointer to buffer over which CRC is run
 * @param len Length of buffer
 * @return uint32_t The CRC32 value
 */
uint32_t robusto_crc32(uint32_t crc, const uint8_t *buf, size_t len);


/**
 * @brief 
 * Sets `char **' pointer to be a buffer
 * large enough to hold the formatted string
 * accepting a `va_list' args of variadic
 * arguments.
 * @param str A pointer to a pointer that will point to the new string
 * @param fmt The format string
 * @param va_list A va_list of variadic arguments.
 * @return int The length
 */
int robusto_vasprintf (char **str, const char *fmt, va_list);

 
/**
 * @brief 
 * Sets `str **' pointer to be a buffer
 * large enough to hold the formatted
 * string accepting `n' arguments of
 * variadic arguments.
 * @param str A ponter to a pointer that will point to the new string

 * @param fmt The format string
 * @param ... Input parameters to the fmt string
 * @return int The length
 */
int robusto_asprintf (char **str, const char *fmt, ...);

rob_err_t robusto_gpio_set_level(uint8_t gpio_num, uint8_t value);


bool robusto_gpio_get_level(uint8_t gpio_num);

void robusto_system_init(char * _log_prefix);