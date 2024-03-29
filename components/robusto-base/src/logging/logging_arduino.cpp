/**
 * @file logging_arduino.cpp
 * @author Nicklas Börjesson (nicklasb@gmail.com)
 * @brief Logging implementation for the Arduino platform. 
 * @version 0.1
 * @date 2023-02-19
 * 
 * @copyright 
 * Copyright (c) 2022, Nicklas Börjesson <nicklasb at gmail dot com>
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
#ifdef ARDUINO
#include <robusto_logging.h>
#if ROB_LOG_LOCAL_LEVEL > ROB_LOG_NONE  
#include <Arduino.h>
#include <stdio.h>



void test_write(const char * msg) {
    Serial.println(msg);
}

void compat_log_writev(rob_log_level_t level, const char* tag, const char* format, va_list args) {
    
    char msg[128];
    vsprintf(msg, format, args);
    Serial.println(msg);

}
#endif
void r_init_logging() {
#if ROB_LOG_LOCAL_LEVEL > ROB_LOG_NONE  
    Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
    }
    Serial.print("Robusto initiated serial communication for Arduino.\n");
#endif
}

#endif
