/**
 * @file main.c
 * @author Nicklas Börjesson (nicklasb@gmail.com)
 * @brief Main entry point for the Robusto project.
 * @note This file is not supposed to be executed, but a part of the development functionality.
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

#ifdef ESP_PLATFORM
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#elif ARDUINO
#include <Arduino.h>
#endif

#include "robusto_logging.h"
#include "robusto_init.h"

void log_test() {
    ROB_LOGI("Test_Tag", "Before delay %i", 1001);
    r_delay(1000);
    ROB_LOGI("Test_Tag", "After delay %i", 1002);
}

#if !(defined(ARDUINO) || defined(ESP_PLATFORM))

/**
 * For native dev-platform or for some embedded frameworks
 */
int main(void)
{

    log_test();

}

#endif

#ifdef ESP_PLATFORM

/**
 * For ESP-IDF framework
 */
void app_main()
{
    log_test();
    while(1) {vTaskDelay(1);};
}

#endif

#ifdef ARDUINO

/**
 * For Arduino framework
 */
void setup()
{
    init_robusto();
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);
    log_test();
 

}
void loop() {
  ROB_LOGI("Arduino", "Again");
   // Wait for a second
  delay(1000);
  // Set the LED LOW
  digitalWrite(LED_BUILTIN, LOW);
 
   // Wait for a second
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
}

#endif
