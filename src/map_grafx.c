SDL_Rect map_texture_rect = { 0, 0, map_width * 10, map_height * 10 };
SDL_Texture * map_texture;
SDL_Texture * map_view_texture;
int map_surface_size = map_width * 10 * map_height * 10 * 4;
uint32_t * map_surface_pixels;

int map_wall_pal[9][4] = {
	{ 6, 5, 0, 7 },
	{ 6, 5, 1, 7 },
	{ 2, 5, 6, 7 }, // herbs?
	{ 3, 5, 6, 7 },
	{ 4, 5, 6, 7 },
	{ 6, 2, 3, 5 },
	{ 4, 5, 7, 4 },
	{ 4, 6, 7, 1 },
	{ 5, 4, 6, 1 },
};


// x,y = tile pos ; x2, y2 = pixel position of tile
int map_tile_pixel_visible(int map_level, int type, int x, int y, int x2, int y2) {
	if (x == 0 || y == 0 || x == map_width - 1 || y == map_height - 1) return 1;
	//return 1;
	int pxlrnd = (rand() % 7 == 0);
	if (x2 < 4 && y2 < 4 && map_data[map_level][x-1][y-1] != type) return pxlrnd;
	else if (x2 < 2 && map_data[map_level][x-1][y] != type) return pxlrnd;
	else if (x2 < 4 && y2 > 6 && map_data[map_level][x-1][y+1] != type) return pxlrnd;
	else if (y2 > 7 && map_data[map_level][x][y+1] != type) return pxlrnd;
	else if (x2 > 7 && y2 > 6 && map_data[map_level][x+1][y+1] != type) return pxlrnd;
	else if (x2 > 7 && map_data[map_level][x+1][y] != type) return pxlrnd;
	else if (x2 > 6 && y2 < 4 && map_data[map_level][x+1][y-1] != type) return pxlrnd;
	else if (y2 < 2 && map_data[map_level][x][y-1] != type) return pxlrnd;
	else return 1;
}

void map_plot_wall_tile(int map_level, int x, int y, SDL_Rect rect) {
	int x1 = x * 10;
	int y1 = y * 10;
	SDL_Point map_pixel;
	int colors[4];
	for (int i = 0; i < 4; i++) colors[i] = map_wall_pal[map_level][i];
	int color_id;
	for (int x2 = 0; x2 < 10; x2++) {
		for (int y2 = 0; y2 < 10; y2++) {
			if (map_tile_pixel_visible(map_level, 1, x, y, x2, y2)) {
				color_id = colors[rng8() & 3];
				grafx_set_color(color_id);
				map_pixel.x = x1 + x2;
				map_pixel.y = y1 + y2;
				map_surface_pixels[map_pixel.x + map_pixel.y * map_width * 10] = surface_palette[color_id];
			}
		}
	}
}

void map_plot_water_tile(int map_level, int x, int y, SDL_Rect rect) {
	int x1 = x * 10;
	int y1 = y * 10;
	SDL_Point map_pixel;
	int colors[4] = { 3, 3, 0, 3 };
	int color_id;
	for (int x2 = 0; x2 < 10; x2++) {
		for (int y2 = 0; y2 < 10; y2++) {
//			printf("%d %d %d\t", color_id, pixel.x, pixel.y);
			if (map_tile_pixel_visible(map_level, 2, x, y, x2, y2)) {
				color_id = colors[rng8() & 3];
				grafx_set_color(color_id);
				map_pixel.x = x1 + x2;
				map_pixel.y = y1 + y2;
				map_surface_pixels[map_pixel.x + map_pixel.y * map_width * 10] = surface_palette[color_id];
			}
		}
	}
}

void map_playfield_render(int map_level) {
	// DRAW THE WHOLE MAP
	for (int i = 0; i < map_width * 10 * map_height * 10; i++) {
		map_surface_pixels[i] = (uint32_t) 0;
	}
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			if (map_data[map_level][x][y] == 1) {
				map_plot_wall_tile(map_level, x, y, map_texture_rect);
			}
			if (map_data[map_level][x][y] == 2) {
				map_plot_water_tile(map_level, x, y, map_texture_rect);
			}
		}
	}
	SDL_UpdateTexture(map_texture, NULL, map_surface_pixels, map_width * 10 * 4);
}


void map_view_texture_update(int level) {
	SDL_Texture * stash = SDL_GetRenderTarget(renderer);
	// DRAW THE WHOLE MAP
	SDL_SetRenderTarget(renderer, map_view_texture);
	grafx_set_color(7);
	SDL_Rect map_rect = { 0, 0, map_width * 2, map_height * 2 };
	SDL_RenderFillRect(renderer, &map_rect);
	SDL_Rect pixel = { 32, 20, 2, 2 };
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			int tile = map_data[level][x][y];
			if (tile == 0) grafx_set_color(7);
			if (tile == 1) grafx_set_color(6);
			if (tile == 2) grafx_set_color(3);
			pixel.x = x << 1;
			pixel.y = y << 1;
			SDL_RenderFillRect(renderer, &pixel);
		}
	}
	SDL_SetRenderTarget(renderer, stash);
}
