#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "char_rom.c"

int window_w = 800;
int window_h = 600;

int main(int argc, char* args[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event event;
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Window * window = SDL_CreateWindow("baby-k", 200, 200, window_w, window_h, SDL_WINDOW_RESIZABLE);

	char_rom petscii = char_rom_create_texture(renderer, "petscii_8032.bin");
	//SDL_Texture * counter_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 64, 8);
	int counter_value = 0;
	char counter_string[16];
	
	int running = 1;
	while (running) {
		//sprintf(counter_string, "%016u", counter_value);
		counter_value++;

		//counter_texture = char_rom_get_texture_from_string(renderer, petscii, counter_string);
		//SDL_RenderCopy(renderer, counter_texture, NULL, NULL);
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
