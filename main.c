#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "lib/debug.c"
#include "lib/generic.c"
#include "lib/fonts.c"

int video_w = 420;
int video_h = 200;
int window_w = 1280;
int window_h = 720;

float audio_amp = 0.f;
float audio_hertz = 0.f;
float audio_phase = 0.f;
#include "lib/audio.c"


#include "src/core.c"


int main(int argc, char* args[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	audio_init(32000, 2, 1024, AUDIO_F32SYS, &audio_callback);
	SDL_Event event;
	SDL_Window * window = SDL_CreateWindow("Cave of Grell", 100, 200,
		window_w, window_h, SDL_WINDOW_RESIZABLE);
	SDL_Renderer * renderer = SDL_CreateRenderer(window,
		-1, SDL_RENDERER_PRESENTVSYNC);

	// setup grafx
	grafx_init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	SDL_Rect playfield_rect = { 0, 0, 320, 200 };
	SDL_Texture * bg_texture = grafx_playfield_render(playfield_rect, renderer);
	
	SDL_Texture * vid_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, video_w, video_h);

	// setup ents
	ent ents[ENTS_COUNT];
	ents_init(ents, renderer, playfield_rect);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	SDL_Texture * overscale_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, video_w * 3, video_h * 3);

	int running = 1;
	int frame_counter = 0;

	font font00 = fonts_load("font00_14x14", 14, renderer);
//	SDL_Texture * lorum = fonts_render_text("Lorum ipsum", font00, renderer);
	font_text_rendered lorum = fonts_render_text(" !'#0123456789 Lorum Ipsum @ ABCDEFGHIJKLMNOP", font00, renderer);
	lorum.rect.y = 185;

	while (running) {

		SDL_SetRenderTarget(renderer, vid_texture);
//		SDL_RenderClear(renderer);
		// background refresh
		SDL_RenderCopy(renderer, bg_texture, NULL, &playfield_rect);
//		SDL_RenderCopy(renderer, font00.texture, NULL, &font00.shit_rect);
		SDL_RenderCopy(renderer, lorum.texture, NULL, &lorum.rect);
		// sprites
		ents_update(ents, playfield_rect);
		ents_render(ents, renderer);
//		SDL_RenderCopy(renderer, font00.texture, NULL, NULL);
		// "shader effects" xD
		SDL_SetRenderTarget(renderer, overscale_texture);
		SDL_RenderCopy(renderer, vid_texture, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, overscale_texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		frame_counter++;
		if (frame_counter % 60 == 0) {
//			printf("%f\n", ents[0].x);
		}

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
