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


void grafx_init() {
	for (int i = 0; i < 8; i++) {
		uint32_t color = 0;
		color += sdl_palette[i].r << 24;
		color += sdl_palette[i].g << 16;
		color += sdl_palette[i].b << 8;
		color += 255;
		surface_palette[i] = color;
	}
}

void set_render_color(SDL_Renderer * renderer, int color_id) {
		SDL_SetRenderDrawColor(renderer, sdl_palette[color_id].r, sdl_palette[color_id].g, sdl_palette[color_id].b, sdl_palette[color_id].a);
}

void grafx_plot_wall_tile(uint32_t pixels[], int x, int y, SDL_Rect rect) {
	int colors[4] = { 0, 5, 6, 7 };

	for (int x2 = 0; x2 < 10; x2++) {
		for (int y2 = 0; y2 < 10; y2++) {
			int color_id = colors[rng8() & 3];
			pixels[x + x2 + (y + y2) * rect.w] = surface_palette[color_id];
		}
	}
}

SDL_Texture * grafx_playfield_render(SDL_Rect rect, SDL_Renderer * renderer) {
	uint32_t * pixels = malloc(rect.w * rect.h * 4);
	SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, rect.w, rect.h);
	// dirt floor
	for (int x = 0; x < rect.w; x++) {
		for (int y = 0; y < rect.h; y++) {
			int color_id = (rng8() & rng8() & rng8() & rng8() & rng8() & 13) ? 5 : 7;
			pixels[x + y * rect.w] = surface_palette[color_id];
		}
	}
	// wall tiles
	for (int x = 0; x < rect.w; x += 10) {
		grafx_plot_wall_tile(pixels, x, 0, rect);
		grafx_plot_wall_tile(pixels, x, rect.h - 10, rect);
	}
	for (int y = 10; y < rect.h - 10; y += 10) {
		grafx_plot_wall_tile(pixels, 0, y, rect);
		grafx_plot_wall_tile(pixels, rect.w - 10, y, rect);
	}
	SDL_UpdateTexture(texture, NULL, pixels, rect.w * 4);
	return texture;
}
