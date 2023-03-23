/**
 * @file robusto_retval.h
 * @author Nicklas Börjesson (nicklasb@gmail.com)
 * @brief Return values functionality.
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

#ifdef __cplusplus
extern "C"
{
#endif



// We use the same principle as ESP-IDF
typedef int rob_err_t;


/* Common error codes */
typedef enum e_robusto_error_codes
{
    /* An "error" code of 0x0 means success */
    ROB_OK = 0,
    /* And of 0x1 means failure */
    ROB_FAIL = 1,
    /* A message failed to send for some reason */
    ROB_ERR_SEND_FAIL = 2,
    /* A one or more messages failed to send during a broadcast */
    ROB_ERR_SEND_SOME_FAIL = 3,
    /* There was an error adding a conversation to the conversation queue */
    ROB_ERR_CONV_QUEUE = 4,
    /* The conversation queue is full, too many concurrent conversations. TODO: Add setting? */
    ROB_ERR_CONV_QUEUE_FULL = 5,
    /* An identifier was not found */
    ROB_ERR_INVALID_ID = 6,
    /* Couldn't get a semaphore to successfully lock a resource for thread safe usage. */
    ROB_ERR_MUTEX = 7,
    /* SDP failed in its initiation. */
    ROB_ERR_INIT_FAIL = 8,
    /* Incoming message filtered */
    ROB_ERR_MESSAGE_FILTERED = 9,
    /* Invalid input argument */
    ROB_ERR_INVALID_ARG = 10,
    /* Message to short to comply */
    ROB_ERR_MESSAGE_TOO_SHORT = 11,
    /* Peer not found (handle or name not found) */
    ROB_ERR_PEER_NOT_FOUND = 12,
    /* Peer already exists */
    ROB_ERR_PEER_EXISTS = 13,
    /* Out of memory */
    ROB_ERR_OUT_OF_MEMORY = 14,
    /* OS error.  See enum os_error in os/os_error.h for meaning of values when debugging */
    ROB_ERR_OS_ERROR = 15,
    /* Parsing error */
    ROB_ERR_PARSING_FAILED = 16,
    /* Message to long to comply */
    ROB_ERR_MESSAGE_TOO_LONG = 17,
    /* This feature is not supported */
    ROB_ERR_NOT_SUPPORTED = 18    
} e_robusto_error_codes;

/* Common warning codes */
typedef enum e_robusto_warning_codes
{
    /* No peers */
    ROB_WARN_NO_PEERS = 1
} e_robusto_warning_codes;


#ifdef __cplusplus
} /* extern "C" */
#endif