
int inst_text_spacer = 22;

void state_instructions_frame() {
	// bg
	SDL_RenderCopy(renderer, dirt_texture, NULL, NULL);
	// bigger text
	font_set_color(fonts[1], sdl_palette[2]);
	help_text_rect.x = 140;
	help_text_rect.y = 10;
	help_text_rect.h = fonts[1].height;
	font_render_text("INSTRUCTIONES", fonts[1], renderer, help_text_rect);
	font_set_color(fonts[1], sdl_palette[3]);
	help_text_rect.x = 105;
	help_text_rect.y = 170;
	font_render_text("Press SPACE to BEGIN", fonts[1], renderer, help_text_rect);
	// smaller text
	font_set_color(fonts[0], sdl_palette[0]);
	help_text_rect.h = fonts[0].height;
	help_text_rect.x = 150;
	help_text_rect.y = 50;
	font_render_text("Move into Creatures to Attack", fonts[0], renderer, help_text_rect);
	help_text_rect.y += inst_text_spacer;
	font_render_text("Some Ladders go Down", fonts[0], renderer, help_text_rect);
	help_text_rect.y += inst_text_spacer;
	font_render_text("Other Ladders go Up", fonts[0], renderer, help_text_rect);
	help_text_rect.y += inst_text_spacer;
	font_render_text("Herbs Heal", fonts[0], renderer, help_text_rect);
	help_text_rect.y += inst_text_spacer;
	font_render_text("Collect Crown & Escape to Win", fonts[0], renderer, help_text_rect);
	// sprites!! :U
	SDL_Rect spr_rect;
	SDL_Rect spr_targ;
	spr_targ.x = 120;
	spr_targ.y = 47;
	spr_targ.w = spr_targ.h = 20;
	spr_rect = ent_types[ent_player].sprite;
	SDL_RenderCopy(renderer, spriteshit, &spr_rect, &spr_targ);
	spr_targ.y += inst_text_spacer;
	spr_targ.h = 18;
	spr_rect = ent_types[ent_ladder_down].sprite;
	SDL_RenderCopy(renderer, spriteshit, &spr_rect, &spr_targ);
	spr_targ.y += inst_text_spacer;
	spr_targ.h = 20;
	spr_rect = ent_types[ent_ladder_up].sprite;
	SDL_RenderCopy(renderer, spriteshit, &spr_rect, &spr_targ);
	spr_targ.y += inst_text_spacer + 4;
	spr_targ.h = 9;
	spr_rect = ent_types[ent_herb].sprite;
	SDL_RenderCopy(renderer, spriteshit, &spr_rect, &spr_targ);
	spr_targ.y += inst_text_spacer - 4;
	spr_targ.h = 20;
	spr_rect = ent_types[ent_crown].sprite;
	SDL_RenderCopy(renderer, spriteshit, &spr_rect, &spr_targ);
	// SPACEBAR START?
	if (keys[SDL_SCANCODE_SPACE] == 1) {
		state_id = 2;
		state_game_new_player();
	}
}
