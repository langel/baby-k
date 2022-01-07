#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "lib/core.c"

int window_w = 800;
int window_h = 600;

int main(int argc, char* args[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event event;
	SDL_Window * window = SDL_CreateWindow("baby-k", 200, 200, window_w, window_h, SDL_WINDOW_RESIZABLE);
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	// char rom initialization
	char_rom_load_set(renderer, petscii_8032_bin);
	SDL_Color green = { 0, 255, 0, 255 };
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color colors[16] = {
		{ 0x00, 0x00, 0x00, 0xff }, // black
		{ 0xff, 0xff, 0xff, 0xff }, // white
		{ 0xb6, 0x1f, 0x21, 0xff }, // red
		{ 0x4d, 0xf0, 0xff, 0xff }, // cyan
		{ 0xb4, 0x3f, 0xff, 0xff }, // purple
		{ 0x44, 0xe2, 0x37, 0xff }, // green
		{ 0x1a, 0x34, 0xff, 0xff }, // blue
		{ 0xdc, 0xd7, 0x1b, 0xff }, // yellow
		// background/border colors
		{ 0xca, 0x54, 0x00, 0xff },
		{ 0xe9, 0xb0, 0x72, 0xff },
		{ 0xe7, 0x92, 0x93, 0xff },
		{ 0x9a, 0xf7, 0xfd, 0xff },
		{ 0xe0, 0x9f, 0xff, 0xff },
		{ 0x8f, 0xe4, 0x93, 0xff },
		{ 0x82, 0x90, 0xff, 0xff },
		{ 0xe5, 0xde, 0x85, 0xff },
	};

	//char_rom petscii = char_rom_create_texture(renderer, "petscii_8032.bin");
	SDL_Texture * counter_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 16*8, 8);
	SDL_Rect counter_rect = { 0, (window_h / 2) - 16, 16*32, 32 };
	unsigned long long counter_value = 3141592653589793;
	double x_pos_counter = 0.0;
	char counter_string[17];

	int char_width = 28;
	int char_height = 20;
	SDL_Texture * screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, char_width * 8, char_height * 8);
	SDL_Rect screen_rect = { 0, 0, char_width * 16, char_height * 16 };

	char_rom_set_color(&green);
	for (int y = 0; y < char_height; y++) {
		for (int x = 0; x < char_width; x++) {
			char_rom_plot_char(renderer, screen_texture, (x + y * char_width) % 256, x, y);
		}
	}

	
	int running = 1;
	while (running) {

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		for (int i = 0; i < 64; i++) {
			char_rom_set_color(&colors[rand() % 16]);
			char_rom_plot_char(renderer, screen_texture, rand() % 256, rand() % char_width, rand() % char_height);
		}
		SDL_RenderCopy(renderer, screen_texture, NULL, NULL);

		counter_value += 123456789;
		sprintf(counter_string, "%016llu", counter_value);
		char_rom_set_color(&white);
		char_rom_string_to_texture(renderer, counter_texture, counter_string);
		x_pos_counter += 0.03;
		counter_rect.x = (int) (sin(x_pos_counter) * 100.0) + (window_w - 16*32) / 2;
		SDL_RenderCopy(renderer, counter_texture, NULL, &counter_rect);

		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || 
			(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
				running = 0;
			}
		}
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_CloseAudio();
	SDL_Quit();

	return 0;
}
