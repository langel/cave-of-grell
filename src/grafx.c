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

void plot_wall_tile(uint32_t pixels[], int x, int y) {
	int colors[4] = { 0, 5, 6, 7 };

	for (int x2 = 0; x2 < 10; x2++) {
		for (int y2 = 0; y2 < 10; y2++) {
			int color_id = colors[rng8() & 3];
			pixels[x + x2 + (y + y2) * texture_w] = surface_palette[color_id];
		}
	}
}
