SDL_Rect menu_title_sprite = { 0, 120, 420, 80};
SDL_Rect menu_title_rect = { 0, 20, 420, 80};
SDL_Rect menu_text_rect = { 60, 120, 300, 0 };

void state_menu_init() {
//	menu_title_rect.h = fonts[0].height;
}

void state_menu_frame() {
	// bg
	grafx_set_color(7);
	SDL_RenderFillRect(renderer, NULL);
	// title of game
	SDL_RenderCopy(renderer, spriteshit, &menu_title_sprite, &menu_title_rect);
	// menu text
	font_set_color(fonts[0], sdl_palette[1]);
	menu_text_rect.x = 110;
	menu_text_rect.y = 130;
	menu_text_rect.h = fonts[0].height;
	font_render_text("Press Space to Adventure  -  H for Halp", fonts[0], renderer, menu_text_rect);
	// copy text
	font_set_color(fonts[1], sdl_palette[4]);
	menu_text_rect.x = 75;
	menu_text_rect.y = 170;
	menu_text_rect.h = fonts[1].height;
	font_render_text("Langel/Puke7 MMXXII #7DRL", fonts[1], renderer, menu_text_rect);
	// SPACEBAR START?
	if (keys[SDL_SCANCODE_SPACE]) {
		state_id = 2;
		state_game_new_player();
	}
}
