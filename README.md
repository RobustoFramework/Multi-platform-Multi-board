
*DISCLAIMER  
This is kind of an advanced setup, and will be very hard to keep on track for a newbie.  
So this is not for people just starting out with C/C++, microprocessor programming or PlatformIO.  
In the latter case, please begin at [PlatformIO:s tutorials](https://docs.platformio.org/en/stable/tutorials/index.html) and try out some easier stuff first. No offence.*

# Multi-platform, multi-board and PlatformIO 

One of the many great things about PlatformIO is its ability to have projects  
that build and run on several platforms simultaneously. This shows how this is done.   

It provides a starting point for those who need it and runs on:
* Platforms
  * Native
  * ESP-IDF
  * Arduino
* Hardware
  * PC (Linux/MacOs/Windows)
  * LILYGO® TTGO LoRa32 V1.0 SX1276/SX1278
  * LILYGO® TTGO T-Beam V1.1 ESP32 LORA SX1262
  * Arduino Uno Rev3

It has:
* *One* runnable main.c for all platforms
* Unit testing
  * Local on the native platform
  * And running on the boards
* a [Kconfig implementation](development/README.md#kconfig-config) to help you hold your config even if you don't use ESP-IDF.

# Making it work for you

All changes are, hopefully, in platform.ini

1. Change the serial id:s to your own:  
`/dev/cu.wchusbserialNNNNNNNNN`  
You'll find it in PIO Home - Devices  
*(no, the serial ids of my test boards are hardly attack vectors)*
2. Add your own board's configuration in an `[env:yourboard]`-section
3. Go do great things!



# Tips & takeaways

1. The build times are *very* different for the different platforms. 
2. Arduino don't have to have a `main.cpp`..
3. ..because we only need .cpp when we need c++ features  
   like `Serial.begin(9600)` for Arduino to be able to log.
4. Config 
  * `platformio.ini`
    * Both Arduino and Native needs lib_extra_dirs = components
    * Native platform need `lib_compat_mode = off`.  
      I am have not found out why for sure. Any ideas?

5. If you want a command run in all environments, look in the "General" project task group. 
6. There is a /development folder, take a look.
  
