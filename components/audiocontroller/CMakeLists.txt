idf_component_register(
	SRCS "Sources/httpstream.c" "Sources/whitenoise.c" "AudioSetup/AudioSetup.c" "audioController.c" 
	INCLUDE_DIRS .
	REQUIRES freertos audio_pipeline audio_stream esp_peripherals audio_board menuitems
)