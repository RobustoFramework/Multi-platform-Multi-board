# Multi-platform, multi-board and Platform IO 

One of the great things about PlatformIO is its ability to have projects that build and run on several plattforms simultaneously.

This project runs on:
* Platforms
  * Native
  * ESP-IDF
  * Arduino
* Hardware
  * PC (Linux/MacOs/Windows)
  * LILYGO® TTGO LoRa32 V1.0
  * T-Beam Meshtastic V1.1 ESP32 LoRa SX1276/SX1278 , Arduino Uno Rev3

It has:
* One runnable main.c for all platforms
* Unit testing
  * Local on the native platform
  * And running on the boards

# Takeaways

1. The build times are *very* different for the different platforms. 
2. Arduino don't have to have a main.cpp
3. Because we only need .cpp when we need c++ features
4. Config 
  * platformio.ini
    * Both Arduino and Native needs lib_extra_dirs = components
