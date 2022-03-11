SDL_Rect menu_title_rect = { 42, 20, 300, 100};

void state_menu_init() {
	menu_title_rect.h = fonts[0].height;
}

void state_menu_frame() {
	SDL_RenderCopy(renderer, dirt_texture, NULL, NULL);
	// title of game
	font_set_color(fonts[0], sdl_palette[1]);
	font_render_text("Cave of Grell", fonts[0], renderer, menu_title_rect);
}
