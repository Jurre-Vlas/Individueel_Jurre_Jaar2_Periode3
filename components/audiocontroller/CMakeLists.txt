idf_component_register(
	SRCS "Sources/httpstream.c" "Sources/whitenoise.c" "Sources/rawStream.c" "Sources/mp3.c" "Sources/timesource.c" "AudioSetup/AudioSetup.c" "audioController.c" 
	INCLUDE_DIRS .
	REQUIRES freertos audio_pipeline audio_stream esp_peripherals audio_board menuitems goertzel audioRecognition
)