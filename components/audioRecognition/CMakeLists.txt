idf_component_register(
	SRCS "audioRecognition.c"
	INCLUDE_DIRS .
	REQUIRES freertos audio_pipeline audio_stream esp_peripherals audio_board audiocontroller goertzel
)