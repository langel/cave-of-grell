#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "lib/debug.c"
#include "lib/generic.c"

int video_w = 420;
int video_h = 200;
int window_w = 1280;
int window_h = 720;

float audio_amp = 0.f;
float audio_hertz = 0.f;
float audio_phase = 0.f;
#include "lib/audio.c"


#include "src/core.c"
#include "lib/font.c"


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
	SDL_Rect video_rect = { 0, 0, video_w, video_h };
	SDL_Rect playfield_rect = { 0, 0, 320, 200 };
	SDL_Texture * bg_texture = grafx_playfield_render(playfield_rect, renderer);
	
	SDL_Texture * vid_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, video_w, video_h);

	// fonts
	font_struct font00 = font_load("font00_14x14", 14, renderer);
	SDL_Rect text_title = { 320, 2, 100, font00.height };

	// setup ents
	ent ents[ENTS_COUNT];
	ents_init(ents, renderer, playfield_rect);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	SDL_Texture * overscale_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, video_w * 3, video_h * 3);

	int running = 1;
	int frame_counter = 0;


	while (running) {

		SDL_SetRenderTarget(renderer, vid_texture);
		set_render_color(renderer, 7);
		SDL_RenderFillRect(renderer, &video_rect);
		// background refresh
		SDL_RenderCopy(renderer, bg_texture, NULL, &playfield_rect);
//		SDL_RenderCopy(renderer, font00.texture, NULL, &font00.shit_rect);
		// sprites
		ents_update(ents, playfield_rect);
		ents_render(ents, renderer);
		// hud
		font_set_color(1, font00);
		font_render_text("Cave of Grell #7DRL", font00, renderer, text_title);
		SDL_Rect ent_label_border = { 330, 32, 32, 10 };
		SDL_Rect ent_label_fill = { 332, 34, 28, 6 };
		SDL_Rect ent_label_text = { 380, 30, 28, font00.height };
		font_set_color(0, font00);
		for (int i = 0; i < ENTS_COUNT; i++) {
			// ent border
			set_render_color(renderer, 0);
			SDL_RenderDrawRect(renderer, &ent_label_border);
			ent_label_border.y += 20;
			// ent fill
			set_render_color(renderer, i);
			SDL_RenderFillRect(renderer, &ent_label_fill);
			ent_label_fill.y += 20;
			// ent text
			char coll[10];
			sprintf(coll, "%d", ents[i].collisions);
			font_render_text(coll, font00, renderer, ent_label_text);
			ent_label_text.y += 20;
		}
//		SDL_RenderCopy(renderer, font00.texture, NULL, NULL);
		// "shader effects" xD
		SDL_SetRenderTarget(renderer, overscale_texture);
		SDL_RenderCopy(renderer, vid_texture, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, overscale_texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		// debug once per frame
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
