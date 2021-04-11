idf_component_register(
    SRCS "RotaryEncoder_Driver.c" "RotaryEncoder_Adapter.c"
    INCLUDE_DIRS .
    REQUIRES i2cdev 
)