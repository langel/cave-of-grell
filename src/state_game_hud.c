
SDL_Rect hud_rect = { 320, 0, 100, 200 };
SDL_Rect hud_title_rect;


void state_game_hud_init() {
	hud_title_rect = (SDL_Rect) { 330, 2, 100, fonts[0].height };
}


void state_game_hud_render(SDL_Renderer * renderer) {
	// clear hud space
	set_render_color(renderer, 7);
	SDL_RenderFillRect(renderer, &hud_rect);
	// title of game
	font_set_color(fonts[0], sdl_palette[1]);
	hud_title_rect.y = 0;
	font_render_text(" Cave of", fonts[0], renderer, hud_title_rect);
	hud_title_rect.y = 11;
	font_render_text("      Grell #7DRL", fonts[0], renderer, hud_title_rect);
	// ent data
	SDL_Rect ent_label_border = { 330, 32, 32, 10 };
	SDL_Rect ent_label_fill = { 332, 34, 28, 6 };
	SDL_Rect ent_label_text = { 380, 30, 28, fonts[0].height };
	font_set_color(fonts[0], sdl_palette[0]);
	for (int i = 0; i < 8; i++) {
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
		font_render_text(coll, fonts[0], renderer, ent_label_text);
		ent_label_text.y += 20;
	}
}


