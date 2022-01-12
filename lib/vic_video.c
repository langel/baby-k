/*
	handles VIC-I style screen simulation
*/

enum color_names {
	black, white, red, cyan, purple, green, blue, yellow,
	orange, lt_orange, pink, lt_cyan, lt_purple, lt_green, ltblue, lt_yellow,
};


SDL_Color colors[16] = {
	// foreground/primary colours
	{ 0x00, 0x00, 0x00, 0xff }, // black
	{ 0xff, 0xff, 0xff, 0xff }, // white
	{ 0xb6, 0x1f, 0x21, 0xff }, // red
	{ 0x4d, 0xf0, 0xff, 0xff }, // cyan
	{ 0xb4, 0x3f, 0xff, 0xff }, // purple
	{ 0x44, 0xe2, 0x37, 0xff }, // green
	{ 0x1a, 0x34, 0xff, 0xff }, // blue
	{ 0xdc, 0xd7, 0x1b, 0xff }, // yellow
	// background/border colours
	{ 0xca, 0x54, 0x00, 0xff },
	{ 0xe9, 0xb0, 0x72, 0xff },
	{ 0xe7, 0x92, 0x93, 0xff },
	{ 0x9a, 0xf7, 0xfd, 0xff },
	{ 0xe0, 0x9f, 0xff, 0xff },
	{ 0x8f, 0xe4, 0x93, 0xff },
	{ 0x82, 0x90, 0xff, 0xff },
	{ 0xe5, 0xde, 0x85, 0xff },
};
