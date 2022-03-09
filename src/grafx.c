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

// used for writing bitmapped pixels to surfaces
uint32_t surface_palette[8];

SDL_Texture * spriteshit;

SDL_Texture * debug;

void grafx_init(SDL_Renderer * renderer) {
	// convert palette for bitmap usage
	for (int i = 0; i < 8; i++) {
		uint32_t color = 0;
		color += sdl_palette[i].r << 24;
		color += sdl_palette[i].g << 16;
		color += sdl_palette[i].b << 8;
		color += 255;
		surface_palette[i] = color;
	}
	// load the spriteshit
	SDL_Surface * image = SDL_LoadBMP("assets/spriteshit.bmp");
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 207, 0 , 255)); 
	spriteshit = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	// debug layer
//	debug = texture_create_generic(renderer, window_w, window_h);
}


void set_render_color(SDL_Renderer * renderer, int color_id) {
		SDL_SetRenderDrawColor(renderer, sdl_palette[color_id].r, sdl_palette[color_id].g, sdl_palette[color_id].b, sdl_palette[color_id].a);
}


