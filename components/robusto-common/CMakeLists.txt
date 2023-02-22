FILE(GLOB rob_sources 
"include/*.h"
"src/logging/*.c" 
"src/time/*.c" 
"src/init/*.c" 
)

idf_component_register(
    SRCS ${rob_sources} 
    INCLUDE_DIRS . include 
    REQUIRES esp_timer
)
