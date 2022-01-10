/*
	handles VIC-I audio emulation
*/
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

float audio_base_clock_ntsc = 4433618.f / 4.f;
float audio_base_clock_pal = 14318181.f / 14.f;
float audio_channel_divisors[4] = { 256.f, 128.f, 64.f, 32.f };
typedef struct {
	float clock_ntsc;
	float clock_pal;
	int enabled;
	float phase_rate;
	float phase_pos;
} audio_channel_struct;
audio_channel_struct audio_channels[4] = {
	audio_base_clock_ntsc / 256.f
}
