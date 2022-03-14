#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "lib/debug.c"
#include "lib/font.c"
#include "lib/generic.c"
#include "lib/keyboard.c"

int video_w = 420;
int video_h = 200;
int window_w = 1280;
int window_h = 720;
int frame_counter = 0;

#include "lib/audio.c"

font_struct fonts[4];

SDL_Renderer * renderer;
SDL_Event event;
SDL_Rect video_rect;
SDL_DisplayMode display_mode;
int fps;

int running = 1;
int state_id = 0;

SDL_Rect camera_rect = { 0, 0, 320, 200 };

int player_hp; // max hp not current hp
int player_hp_max;
int player_xp;
int player_gp;
int player_level;
int player_update_level = 0;
int player_has_crown = 0;
int player_steps = 0;
int games_won = 0;
int player_frame_counter;
SDL_Texture * dirt_texture;

#include "src/core.c"


int main(int argc, char* args[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	audio_init(32000, 2, 1024, AUDIO_F32SYS, &audio_callback);
	SDL_Window * window = SDL_CreateWindow("Cave of Grell", 100, 200,
		window_w, window_h, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window,
		-1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	SDL_GetDisplayMode(0, 0, &display_mode);
	printf("Display Mode : \tbbp %i\t%s\t%i x %i\tfps %i\n", SDL_BITSPERPIXEL(display_mode.format), SDL_GetPixelFormatName(display_mode.format), display_mode.w, display_mode.h, display_mode.refresh_rate);
	fps = display_mode.refresh_rate;

	// setup grafx
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	grafx_init(renderer);
	video_rect = (SDL_Rect) { 0, 0, video_w, video_h };
	
	SDL_Texture * vid_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, video_w, video_h);

	// fonts
	fonts[0] = font_load("font00_14x14", 14, renderer);
	fonts[1] = font_load("font01_25x24", 24, renderer);
	fonts[2] = font_load("font02_12x15", 12, renderer);

	keyboard_init();

	// initiallize all states
	srand(time(0));
	state_controller_init();

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	SDL_Texture * overscale_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, video_w * 3, video_h * 3);

	uint64_t start;
	uint64_t end;
	float elapsed;

	while (running) {
		start = SDL_GetPerformanceCounter();
		SDL_SetRenderTarget(renderer, vid_texture);
		grafx_set_color(7);
		SDL_RenderFillRect(renderer, &video_rect);
		state_controller_frame(renderer);
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
		// fps throttle
		end = SDL_GetPerformanceCounter();
		elapsed = (float) (end - start) / (float) SDL_GetPerformanceFrequency() * 1000.f;
		// only delay if framerate is above 60
		if (fps > 60) SDL_Delay(floor(1000.f / 60.f - elapsed));

	}

	SDL_Quit();
	return 0;
}
