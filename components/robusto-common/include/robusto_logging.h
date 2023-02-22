/**
 * @file robusto_logging.h
 * @author Nicklas Börjesson (nicklasb@gmail.com)
 * @brief Logging functionality.
 * @note The functional interface is modeled after the ESP-IDF ESP-LOG functionality.
 * It implements some of the functionality, but not all.
 * see: https://github.com/espressif/esp-idf/blob/master/components/log/include/esp_log.h
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

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdarg.h>

#include "robusto_time.h"
// TODO: There are lots of conditions wrt bootloaders and so on in esp_log.h, see if they are affected.

// TODO: Figure out how and when to do coloring

#ifdef ESP_PLATFORM
#include <sdkconfig.h>
#endif


#define ROB_LOG_DO_FORMAT 1
/**
 * @brief Log level
 */
typedef enum
{
    ROB_LOG_NONE,   /*!< No log output */
    ROB_LOG_ERROR,  /*!< Critical errors, software module can not recover on its own */
    ROB_LOG_WARN,   /*!< Error conditions from which recovery measures have been taken */
    ROB_LOG_INFO,   /*!< Information messages which describe normal flow of events */
    ROB_LOG_DEBUG,  /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    ROB_LOG_VERBOSE /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
} rob_log_level_t;

#ifndef ESP_PLATFORM
    // Set info as default level for native platform. 
    #define CONFIG_LOG_MAXIMUM_LEVEL ROB_LOG_INFO
#endif
#define ROB_LOG_LOCAL_LEVEL CONFIG_LOG_MAXIMUM_LEVEL

void rob_log_write(rob_log_level_t level, const char *tag, const char *format, ...) __attribute__((format(printf, 3, 4)));

void compat_log_writev(rob_log_level_t level, const char* tag, const char* format, va_list args);
void r_init_logging();

/* Selection of colors from esp_log.h*/
#define ROB_LOG_COLOR_BLACK "30"
#define ROB_LOG_COLOR_RED "31"
#define ROB_LOG_COLOR_GREEN "32"
#define ROB_LOG_COLOR_BROWN "33"
#define ROB_LOG_COLOR_BLUE "34"
#define ROB_LOG_COLOR_PURPLE "35"
#define ROB_LOG_COLOR_CYAN "36"
#define ROB_LOG_COLOR(COLOR) "\033[0;" COLOR "m"
#define ROB_LOG_BOLD(COLOR) "\033[1;" COLOR "m"
#define ROB_LOG_RESET_COLOR "\033[0m"
#define ROB_LOG_COLOR_E ROB_LOG_COLOR(ROB_LOG_COLOR_RED)
#define ROB_LOG_COLOR_W ROB_LOG_COLOR(ROB_LOG_COLOR_BROWN)
#define ROB_LOG_COLOR_I ROB_LOG_COLOR(ROB_LOG_COLOR_GREEN)
#define ROB_LOG_COLOR_D
#define ROB_LOG_COLOR_V

#if ROB_LOG_DO_FORMAT == 1
#define ROB_LOG_FORMAT(letter, format) ROB_LOG_COLOR_##letter #letter " (%lu) %s: " format ROB_LOG_RESET_COLOR "\n"
#else
#define ROB_LOG_FORMAT(letter, format) #letter " (%lu) %s: " format "\n"
#endif

#define ROB_LOG_LEVEL(level, tag, format, ...)                                                                       \
    do                                                                                                               \
    {                                                                                                                \
        if (level == ROB_LOG_ERROR)                                                                                  \
        {                                                                                                            \
            rob_log_write(ROB_LOG_ERROR, tag, ROB_LOG_FORMAT(E, format), r_millis(), tag, ##__VA_ARGS__);   \
        }                                                                                                            \
        else if (level == ROB_LOG_WARN)                                                                              \
        {                                                                                                            \
            rob_log_write(ROB_LOG_WARN, tag, ROB_LOG_FORMAT(W, format), r_millis(), tag, ##__VA_ARGS__);    \
        }                                                                                                            \
        else if (level == ROB_LOG_DEBUG)                                                                             \
        {                                                                                                            \
            rob_log_write(ROB_LOG_DEBUG, tag, ROB_LOG_FORMAT(D, format), r_millis(), tag, ##__VA_ARGS__);   \
        }                                                                                                            \
        else if (level == ROB_LOG_VERBOSE)                                                                           \
        {                                                                                                            \
            rob_log_write(ROB_LOG_VERBOSE, tag, ROB_LOG_FORMAT(V, format), r_millis(), tag, ##__VA_ARGS__); \
        }                                                                                                            \
        else                                                                                                         \
        {                                                                                                            \
            rob_log_write(ROB_LOG_INFO, tag, ROB_LOG_FORMAT(I, format), r_millis(), tag, ##__VA_ARGS__);    \
        }                                                                                                            \
    } while (0)

/** runtime macro to output logs at a specified level. Also check the level with ``LOG_LOCAL_LEVEL``.
 *
 * @see ``printf``, ``ROB_LOG_LEVEL``
 */
#define ROB_LOG_LEVEL_LOCAL(level, tag, format, ...)          \
    do                                                        \
    {                                                         \
        if (ROB_LOG_LOCAL_LEVEL >= level)                     \
            ROB_LOG_LEVEL(level, tag, format, ##__VA_ARGS__); \
    } while (0)

#define ROB_LOGE(tag, format, ...) ROB_LOG_LEVEL_LOCAL(ROB_LOG_ERROR, tag, format, ##__VA_ARGS__)
#define ROB_LOGW(tag, format, ...) ROB_LOG_LEVEL_LOCAL(ROB_LOG_WARN, tag, format, ##__VA_ARGS__)
#define ROB_LOGI(tag, format, ...) ROB_LOG_LEVEL_LOCAL(ROB_LOG_INFO, tag, format, ##__VA_ARGS__)
#define ROB_LOGD(tag, format, ...) ROB_LOG_LEVEL_LOCAL(ROB_LOG_DEBUG, tag, format, ##__VA_ARGS__)
#define ROB_LOGV(tag, format, ...) ROB_LOG_LEVEL_LOCAL(ROB_LOG_VERBOSE, tag, format, ##__VA_ARGS__)

#ifdef __cplusplus
} /* extern "C" */
#endif