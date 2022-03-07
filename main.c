#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "lib/debug.c"

int texture_w = 420;
int texture_h = 200;
int window_w = 1280;
int window_h = 720;

float audio_amp = 0.f;
float audio_hertz = 0.f;
float audio_phase = 0.f;
#include "lib/audio.c"

SDL_Color sdl_palette[8] = {
	{ 0xf0, 0xf0, 0xdc, 0xff }, // 0 white
	{ 0xfa, 0xc8, 0x00, 0xff }, // 1 yellow
	{ 0x10, 0xc8, 0x40, 0xff }, // 2 green
	{ 0x00, 0xa0, 0xc8, 0xff }, // 3 blue
	{ 0xd2, 0x40, 0x40, 0xff }, // 4 red
	{ 0xa0, 0x69, 0x4b, 0xff }, // 5 brown
	{ 0x73, 0x64, 0x64, 0xff }, // 6 grey
	{ 0x10, 0x18, 0x20, 0xff }, // 7 black
};

uint32_t surface_palette[8];

void set_render_color(SDL_Renderer * renderer, int color_id) {
		SDL_SetRenderDrawColor(renderer, sdl_palette[color_id].r, sdl_palette[color_id].g, sdl_palette[color_id].b, sdl_palette[color_id].a);
}

typedef struct {
	float x;
	float y;
	float x_dir;
	float y_dir;
	SDL_Texture * texture;
	SDL_Rect rect;
} ent;

ent ents[8];

void ents_bubble_sort(ent ents[]) {
	// draw lower y axis ents first
	int size = sizeof *ents / sizeof ents[0];
	for (int step = 0; step < size - 1; ++step) {
		for (int i = 0; i < size - step - 1; ++i) {
			if (ents[i].y > ents[i + 1].y) {
				ent temp = ents[i];
				ents[i] = ents[i + 1];
				ents[i + 1] = temp;
			}
		}
	}
}

int collision_detection(SDL_Rect a, SDL_Rect b) {
	if (a.x + a.w < b.x) return 0;
	if (a.x > b.x + b.w) return 0;
	if (a.y + a.h < b.y) return 0;
	if (a.y > b.y + b.h) return 0;
	return 1;
}

int rng8() {
	static uint8_t val = 1;
	int carry = val & 1;
	val >>= 1;
	if (carry) val ^= 0xd4;
	return (int) val;
}

float rnd_direction() {
	return (float) ((rand() % 200) - 100) * 0.025f;
}

void plot_wall_tile(uint32_t pixels[], int x, int y) {
	int colors[4] = { 0, 5, 6, 7 };

	for (int x2 = 0; x2 < 10; x2++) {
		for (int y2 = 0; y2 < 10; y2++) {
			int color_id = colors[rng8() & 3];
			pixels[x + x2 + (y + y2) * texture_w] = surface_palette[color_id];
		}
	}
}

int main(int argc, char* args[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	audio_init(32000, 2, 1024, AUDIO_F32SYS, &audio_callback);
	SDL_Event event;
	SDL_Window * window = SDL_CreateWindow("Cave of Grell", 100, 200,
		window_w, window_h, SDL_WINDOW_RESIZABLE);
	SDL_Renderer * renderer = SDL_CreateRenderer(window,
		-1, SDL_RENDERER_PRESENTVSYNC);

	for (int i = 0; i < 8; i++) {
		uint32_t color = 0;
		color += sdl_palette[i].r << 24;
		color += sdl_palette[i].g << 16;
		color += sdl_palette[i].b << 8;
		color += 255;
		surface_palette[i] = color;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	uint32_t * pixels = malloc(texture_w * texture_h * 4);
	SDL_Texture * bg_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, texture_w, texture_h);
	// dirt floor
	for (int x = 0; x < texture_w; x++) {
		for (int y = 0; y < texture_h; y++) {
			int color_id = (rng8() & rng8() & rng8() & rng8() & rng8() & 13) ? 5 : 7;
			pixels[x + y * texture_w] = surface_palette[color_id];
		}
	}
	// wall tiles
	for (int x = 0; x < texture_w; x += 10) {
		plot_wall_tile(pixels, x, 0);
		plot_wall_tile(pixels, x, 190);
	}
	for (int y = 10; y < texture_h - 10; y += 10) {
		plot_wall_tile(pixels, 0, y);
		plot_wall_tile(pixels, 410, y);
	}
	SDL_UpdateTexture(bg_texture, NULL, pixels, texture_w * 4);
	
	SDL_Texture * vid_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, texture_w, texture_h);

	// setup ents
	for (int i = 0; i < 8; i++) {
		ents[i].x = rand() % 320 + 50;
		ents[i].y = rand() % 100 + 50;
		ents[i].x_dir = rnd_direction();
		ents[i].y_dir = rnd_direction();
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		ents[i].texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 20, 20);
		SDL_SetRenderTarget(renderer, ents[i].texture);
		SDL_RenderFillRect(renderer, NULL);
		SDL_SetTextureColorMod(ents[i].texture, sdl_palette[i].r, sdl_palette[i].g, sdl_palette[i].b);
		ents[i].rect.x = ents[i].x;
		ents[i].rect.y = ents[i].y;
		ents[i].rect.w = 20;
		ents[i].rect.h = 20;
		//SDL_SetRenderTarget(renderer, ents[i].texture);
		//set_render_color(renderer, i);
		//SDL_RenderClear(renderer);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	SDL_Texture * overscale_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, texture_w * 3, texture_h * 3);

	int running = 1;

	while (running) {

		SDL_SetRenderTarget(renderer, vid_texture);
//		SDL_RenderClear(renderer);
		// background refresh
		SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
		// sprites
		ents_bubble_sort(ents);
		for (int i = 0; i < 8; i++) {
			if (ents[i].x < 11) ents[i].x_dir = abs(rnd_direction());
			if (ents[i].x > 389) ents[i].x_dir = -abs(rnd_direction());
			if (ents[i].y < 11) ents[i].y_dir = abs(rnd_direction());
			if (ents[i].y > 169) ents[i].y_dir = -abs(rnd_direction());
			for (int j = 0; j < 8; j++) {
				if (i != j) {
					if (collision_detection(ents[i].rect, ents[j].rect)) {
						audio_amp = 0.025f;
						audio_hertz = (float) ((rand() % 420) + 80) / 32000.f;
						ents[i].x_dir = -ents[i].x_dir;
						ents[i].y_dir = -ents[i].y_dir;
					}
				}
			}
			ents[i].x += ents[i].x_dir;
			ents[i].rect.x = ents[i].x;
			ents[i].y += ents[i].y_dir;
			ents[i].rect.y = ents[i].y;
			SDL_RenderCopy(renderer, ents[i].texture, NULL, &ents[i].rect);
		}
		// "shader effects" xD
		SDL_SetRenderTarget(renderer, overscale_texture);
		SDL_RenderCopy(renderer, vid_texture, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, overscale_texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_KEYDOWN:
					printf( "keydown: %8s\n", SDL_GetKeyName( event.key.keysym.sym ) );
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							running = 0;
							break;
					}
					break;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						window_w = event.window.data1;
						window_h = event.window.data2;
						printf("window size changed: %d x %d\n", window_w, window_h);
					}
					break;
			}
		}
	}

	SDL_Quit();
	return 0;
}
