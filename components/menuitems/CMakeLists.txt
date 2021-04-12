idf_component_register(
	SRCS "bluetooth.c" "home.c" "internetradio.c" "klok.c" "mp3.c" "reminders.c" 
	"whitenoise.c" "settings.c" "../menutools/Time/Time.c" "popups/homeworkReminder.c"
	INCLUDE_DIRS .
	REQUIRES hd44780 pcf8574 freertos audiocontroller menutools
)