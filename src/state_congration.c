
SDL_Rect congration_title_sprite = { 0, 120, 420, 80};
SDL_Rect congration_title_rect = { 0, 110, 420, 80};
SDL_Rect congration_text_rect = { 60, 120, 300, 0 };

int sfx_congration_counter;

void state_congration_init() {
	state_id = 4;
	sfx_congration_counter = 0;
	games_won++;
}

void state_congration_frame() {
	// bg
	SDL_RenderCopy(renderer, dirt_texture, NULL, NULL);
	// title of game
	SDL_RenderCopy(renderer, spriteshit, &congration_title_sprite, &congration_title_rect);
	// title of game again
	congration_text_rect.h = fonts[0].height;
	font_set_color(fonts[0], sdl_palette[1]);
	congration_text_rect.x = 280;
	congration_text_rect.y = 30;
	font_render_text("Cave", fonts[0], renderer, congration_text_rect);
	congration_text_rect.y = 42;
	font_render_text("     of", fonts[0], renderer, congration_text_rect);
	congration_text_rect.y = 34;
	congration_text_rect.x = 310;
	congration_text_rect.h = fonts[1].height;
	font_set_color(fonts[1], sdl_palette[4]);
	font_render_text("Grell", fonts[1], renderer, congration_text_rect);
	// congration text
	font_set_color(fonts[0], sdl_palette[0]);
	congration_text_rect.x = 90;
	congration_text_rect.y = 45;
	congration_text_rect.h = fonts[0].height;
	font_render_text("Thou art haveth survived teh", fonts[0], renderer, congration_text_rect);
	// copy text
	font_set_color(fonts[1], sdl_palette[1]);
	congration_text_rect.x = 30;
	congration_text_rect.y = 20;
	congration_text_rect.h = fonts[1].height;
	font_render_text("Congrations!!", fonts[1], renderer, congration_text_rect);
	// xp / gp / time
	font_set_color(fonts[1], sdl_palette[1]);
	congration_text_rect.x = 80;
	congration_text_rect.y = 70;
	congration_text_rect.h = fonts[1].height;
	char str[64];
	int tf = player_frame_counter % 60;
	int ts = ((player_frame_counter - tf) % 3600) / 60;
	int tm = (player_frame_counter - ts - tf) / 3600;
	sprintf(str, "%d xp   %d gp   %02d:%02d.%02d", player_xp, player_gp, tm, ts, tf);
	font_render_text(str, fonts[1], renderer, congration_text_rect);

	// SPACEBAR START?
	if (keys[SDL_SCANCODE_SPACE]) {
		state_id = 0;
	}
	if (sfx_congration_counter % 15 == 0) {
		if (sfx_congration_counter < 120) sfx_congration();
	}
	sfx_congration_counter++;
}
