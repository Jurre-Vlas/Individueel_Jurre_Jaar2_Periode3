idf_component_register(
	SRCS "statusbar/statusbar.c" "LCD/LCD.c" "Time/Time.c"
	INCLUDE_DIRS .
	REQUIRES hd44780 pcf8574 freertos menuitems audiocontroller
)