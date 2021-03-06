/*
	handles SDL audio interface
*/
void audio_spec_log(SDL_AudioSpec *as) {
	printf(
		" freq______%5d\n"
		" format____%5d\n"
		" channels__%5d\n"
		" silence___%5d\n"
		" samples___%5d\n"
		" size______%5d\n",
		(int) as->freq,
		(int) as->format,
		(int) as->channels,
		(int) as->silence,
		(int) as->samples,
		(int) as->size
	);
}

SDL_AudioSpec audio_spec;
SDL_AudioSpec audio_actual;
SDL_AudioDeviceID audio_device;
unsigned long audio_time_counter = 0;

void audio_callback(void* userdata, uint8_t* byte_stream, int byte_stream_length) {
	float * float_stream = (float*) byte_stream;
	int float_stream_length = byte_stream_length >> 2;
	for (int i = 0; i < float_stream_length; i += 2) {
		float output = 0.f;
		output = (audio_time_counter % 1000 > 500) ? 0.01f : -0.01f;
		float_stream[i] = output;
		float_stream[i+1] = output;
		audio_time_counter++;
	}
}

void audio_init(int sample_rate, int channels, int buffer_sample_count, SDL_AudioFormat audio_format) {
	audio_spec.freq = sample_rate;
	audio_spec.format = audio_format;
	audio_spec.channels = channels;
	audio_spec.samples = buffer_sample_count;
	audio_spec.callback = &audio_callback;
	audio_device = SDL_OpenAudioDevice(NULL, 0, &audio_spec, &audio_actual, 0);
	if (audio_device == 0) {
		printf("FAILED TO OPEN AUDIO\n");
		audio_spec_log(&audio_spec);
	}
	else {
		printf("device initialized\n");
		audio_spec_log(&audio_actual);
		SDL_PauseAudioDevice(audio_device, 0);
	}
}





