#include <robusto_system.h>


#if !(defined(ARDUINO) || defined(ESP_PLATFORM))
#include "stdlib.h"
#include <sys/cdefs.h>
#endif

#ifdef ESP_PLATFORM
    #include <esp_heap_caps.h>
    #include <driver/gpio.h>
#endif

#ifdef ARDUINO
#include <Arduino.h>
#endif

#include "compat_crc32.h"


char * system_log_prefix;

void * robusto_malloc(size_t size) {
    #ifdef ESP_PLATFORM
    return heap_caps_malloc(size, MALLOC_CAP_8BIT);
    #else
    return malloc(size);
    #endif
}

void * robusto_realloc(void **ptr, size_t size) {
    #ifdef ESP_PLATFORM
    return heap_caps_realloc(ptr,size, MALLOC_CAP_8BIT);
    #else
    return realloc(ptr, size);
    #endif
}

void robusto_free(void *ptr) {  
    free(ptr);
}

uint32_t robusto_crc32(uint32_t crc, const uint8_t *buf, size_t len) {

    return crc32_be_compat(crc, buf, len);
}


rob_err_t robusto_gpio_set_level(uint8_t gpio_num, uint8_t value) {
    #ifdef ESP_PLATFORM
    return gpio_set_level(gpio_num, value);
    #endif
    #ifdef ARDUINO    
    digitalWrite(gpio_num, value);
    return ROB_OK;
    #else
    return ROB_OK;
    #endif 
}


bool robusto_gpio_get_level(uint8_t gpio_num) {
    #ifdef ESP_PLATFORM
    return gpio_get_level(gpio_num);
    #endif
    #ifdef ARDUINO    
    return digitalRead(gpio_num);
    #else    
    return false;
    // TODO: This should probably simulate something..
    #endif 
}


void robusto_system_init(char * _log_prefix) {
    system_log_prefix = _log_prefix;
    init_crc32();
}
