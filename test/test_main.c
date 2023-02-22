#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifdef ESP_PLATFORM
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#endif


#if !(defined(ARDUINO) || defined(ESP_PLATFORM))
#include <time.h>
#include <stdio.h>
#endif

#include <unity.h>
#include <stdbool.h>


#include "robusto_logging.h"
#include "robusto_time.h"
#include "robusto_init.h"


void setUp(void) {

}

void tearDown(void) {

}
/**
 * @brief Check to that at least 100 milliseconds is returned.
 */
void test_millis(void) {
    r_delay(101);
    TEST_ASSERT_TRUE((r_millis() > 100));
}
/**
 * @brief Just sends a message to the output, to see that it doesnt crash.
 */
void test_logging(void) {
    
    ROB_LOGI("Test_Tag", "Should say \"1001\" here:  %i", 1001);
    TEST_ASSERT_TRUE(true);
}



int runUnityTests(void) {
    // Initialize Robusto here, setup is per test.
    init_robusto();
    UNITY_BEGIN();  
    RUN_TEST(test_millis);
  
    RUN_TEST(test_logging);
    return UNITY_END();
}

#if !(defined(ARDUINO) || defined(ESP_PLATFORM))
/**
  * For native dev-platform or for some embedded frameworks
  */
int main(void) {
    return runUnityTests();
    // TODO: Add blink pattern like for Arduino?
}
#endif

#ifdef ARDUINO
/**
  * For Arduino framework
  */
void setup() {
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    runUnityTests();
}

void loop() {

    delay(2000);
    // Set the LED LOW
    digitalWrite(LED_BUILTIN, LOW);
    // Wait for a second
    delay(2000);
    digitalWrite(LED_BUILTIN, HIGH);
}

#endif

#ifdef ESP_PLATFORM
/**
  * For ESP-IDF framework
  */
void app_main() {
    vTaskDelay(1000/portTICK_PERIOD_MS);
    runUnityTests();
}

#endif