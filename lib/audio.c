/*

			  X is the number from 0 to 127 that is put into the frequency
			register. If X is 127, then use -1 for X in the formula. The value of
			Clock comes from the following table:
			 +----------+-----------------+-----------------+
			 | Register |  NTSC (US TV's) |  PAL (European) |
			 +----------+-----------------+-----------------+
			 |  36874   |       3995      |       4329      |
			 |  36875   |       7990      |       8659      |
			 |  36876   |      15980      |      17320      |
			 |  36877   |      31960      |      34640      |
			 +----------+-----------------+-----------------+

			 N: bass enable,    R: freq f=Phi2/256/(128-(($900a+1)&127))
			 O: alto enable,    S: freq f=Phi2/128/(128-(($900b+1)&127))
			 P: soprano enable, T: freq f=Phi2/64/(128-(($900c+1)&127))
			 Q: noise enable,   U: freq f=Phi2/32/(128-(($900d+1)&127))
			 * PAL:  Phi2=4433618/4 Hz
			 * NTSC: Phi2=14318181/14 Hz

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





