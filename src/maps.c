
// map matrix
// map_data[level][row/x][col/y]

#define map_levels 9
#define map_width 128
#define map_height 80

int map_data[map_levels][map_width][map_height];
SDL_Texture * map_texture[9]; // XXX rename map_playfield_texture?
SDL_Rect map_texture_rect = { 0, 0, map_width * 10, map_height * 10 };
SDL_Texture * map_view_texture;



void map_plot_wall_tile(int x, int y, SDL_Rect rect) {
	SDL_Rect pixel = { 0, 0, 2, 2 };
	int colors[4] = { 4, 5, 6, 7 };
	for (int x2 = 0; x2 < 10; x2++) {
		for (int y2 = 0; y2 < 10; y2++) {
			if (x == 10 && y == 40) {
//				printf("%d\n", x + x2 + (y + y2) * rect.w);
//				printf("%d\n", rect.w);
			}
			int color_id = colors[rng8() & 3];
			pixel.x = x + x2;
			pixel.y = y + y2;
			set_render_color(renderer, color_id);
//			printf("%d %d %d\t", color_id, pixel.x, pixel.y);
			SDL_RenderDrawRect(renderer, &pixel);
		}
	}
}

void map_playfield_render() {
	SDL_Texture * stash = SDL_GetRenderTarget(renderer);
	// DRAW THE WHOLE MAP
	SDL_DestroyTexture(map_texture[0]);
	map_texture[0] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, map_texture_rect.w, map_texture_rect.h);
	SDL_SetTextureBlendMode(map_texture[0], SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &map_texture_rect);
	if (SDL_SetRenderTarget(renderer, map_texture[0]) < 0) printf("SDL_Init failed: %s\n", SDL_GetError());
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			if (map_data[0][x][y] == 1) {
				map_plot_wall_tile(x * 10, y * 10, map_texture_rect);
			}
		}
	}
	SDL_SetRenderTarget(renderer, stash);
}


void map_view_texture_update(int level) {
	SDL_Texture * stash = SDL_GetRenderTarget(renderer);
	// DRAW THE WHOLE MAP
	SDL_SetRenderTarget(renderer, map_view_texture);
	set_render_color(renderer, 7);
	SDL_Rect map_rect = { 0, 0, map_width * 2, map_height * 2 };
	SDL_RenderFillRect(renderer, &map_rect);
	SDL_Rect pixel = { 32, 20, 2, 2 };
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			int tile = map_data[0][x][y];
			if (tile == 0) set_render_color(renderer, 7);
			if (tile == 1) set_render_color(renderer, 6);
			pixel.x = x << 1;
			pixel.y = y << 1;
			SDL_RenderFillRect(renderer, &pixel);
		}
	}
	SDL_SetRenderTarget(renderer, stash);
}
