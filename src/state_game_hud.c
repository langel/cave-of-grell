
SDL_Rect hud_rect = { 320, 0, 100, 200 };
SDL_Rect hud_title_rect;


void state_game_hud_init() {
	hud_title_rect = (SDL_Rect) { 330, 2, 100, fonts[0].height };
}


void state_game_hud_render(SDL_Renderer * renderer) {
	// clear hud space
	grafx_set_color(7);
	SDL_RenderFillRect(renderer, &hud_rect);
	// title of game
	hud_title_rect.h = fonts[0].height;
	font_set_color(fonts[0], sdl_palette[1]);
	hud_title_rect.x = 330;
	hud_title_rect.y = 2;
	font_render_text("Cave", fonts[0], renderer, hud_title_rect);
	hud_title_rect.y = 12;
	font_render_text("     of", fonts[0], renderer, hud_title_rect);
	hud_title_rect.y = 4;
	hud_title_rect.x = 360;
	hud_title_rect.h = fonts[1].height;
	font_set_color(fonts[1], sdl_palette[4]);
	font_render_text("Grell", fonts[1], renderer, hud_title_rect);
	// footer
	font_set_color(fonts[2], sdl_palette[1]);
	hud_title_rect.y = 188;
	hud_title_rect.x = 322;
	hud_title_rect.h = fonts[2].height;
	font_render_text("#7DRL  2022  puke7", fonts[2], renderer, hud_title_rect);

	// PLAYER DATA
	hud_title_rect.x = 320;
	hud_title_rect.y = 48;
	hud_title_rect.h = fonts[0].height;
	SDL_Rect text = { 330, 30, 100, fonts[0].height };
	font_set_color(fonts[0], sdl_palette[0]);
	char words[32];
	// Health
	if (player_hp >= 0) sprintf(words, "Health  %d/%d", player_hp, player_hp_max);
	else sprintf(words, "Player Died.");
	font_render_text(words, fonts[0], renderer, text);
	// GP
	text.y += fonts[0].height;
	sprintf(words, "GP   %d", player_gp);
	font_render_text(words, fonts[0], renderer, text);
	// XP 
	text.y += fonts[0].height;
	sprintf(words, "XP   %d", player_xp);
	font_render_text(words, fonts[0], renderer, text);
	// Level 
	text.y += fonts[0].height;
	sprintf(words, "Depth   %d", player_level + 1);
	font_render_text(words, fonts[0], renderer, text);

	// action text
	text.y += 10;
	font_set_color(fonts[2], sdl_palette[0]);
	hud_title_rect.x = 324;
	hud_title_rect.h = fonts[2].height;
	text.y += fonts[2].height;
	sprintf(words, "Wow did something");
//	font_render_text(words, fonts[2], renderer, text);
	text.y += fonts[2].height;
	sprintf(words, "  happen?");
//	font_render_text(words, fonts[2], renderer, text);

	/*
	SDL_Rect ent_label_border = { 330, 32, 32, 10 };
	SDL_Rect ent_label_fill = { 332, 34, 28, 6 };
	SDL_Rect ent_label_text = { 380, 30, 28, fonts[0].height };
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
	*/
}


