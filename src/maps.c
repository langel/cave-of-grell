
// map matrix
// map_data[level][row/x][col/y]

int map_data[9][256][256];
SDL_Texture * map_texture[9];

void map_init() {
	// wall tiles
	for (int x = 0; x < 32; x++) {
		map_data[0][x][0] = 1;
		map_data[0][x][19] = 1;
	}
	for (int y = 0; y < 20; y++) {
		map_data[0][0][y] = 1;
		map_data[0][31][y] = 1;
	}
	for (int i = 0; i < 16; i++) {
		int x = rand() % 32;
		int y = rand() % 20;
		map_data[0][x][y] = 1;
	}
}

void map_plot_wall_tile(uint32_t pixels[], int x, int y, SDL_Rect rect) {
	int colors[4] = { 0, 5, 6, 7 };
	for (int x2 = 0; x2 < 10; x2++) {
		for (int y2 = 0; y2 < 10; y2++) {
			int color_id = colors[rng8() & 3];
			pixels[x + x2 + (y + y2) * rect.w] = surface_palette[color_id];
		}
	}
}

void map_playfield_render(SDL_Rect rect, SDL_Renderer * renderer) {
	uint32_t * pixels = malloc(rect.w * rect.h * 4);
	map_texture[0] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, rect.w, rect.h);
	// dirt floor
	for (int x = 0; x < rect.w; x++) {
		for (int y = 0; y < rect.h; y++) {
			int color_id = (rng8() & rng8() & rng8() & rng8() & rng8() & 13) ? 5 : 7;
			uint32_t dirt = 0;
			if (color_id == 7) {
				dirt += (sdl_palette[color_id].r + (rand() % 16) - 8) << 24;
				dirt += (sdl_palette[color_id].g + (rand() % 16) - 8) << 16;
				dirt += (sdl_palette[color_id].b + (rand() % 16) - 8) << 8;
			}
			pixels[x + y * rect.w] = dirt;
		}
	}
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 20; y++) {
			if (map_data[0][x][y] == 1) {
				map_plot_wall_tile(pixels, x * 10, y * 10, rect);
			}
		}
	}
	SDL_UpdateTexture(map_texture[0], NULL, pixels, rect.w * 4);
}

