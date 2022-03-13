
int inst_text_spacer = 22;

void state_instructions_frame() {
	SDL_RenderCopy(renderer, dirt_texture, NULL, NULL);
	font_set_color(fonts[0], sdl_palette[1]);
	help_text_rect.y = 10;
	font_render_text("INSTRUCTIONES", fonts[0], renderer, help_text_rect);
	help_text_rect.y += inst_text_spacer;
	font_render_text("Move into Creatures to Attack", fonts[0], renderer, help_text_rect);
	help_text_rect.y += inst_text_spacer;
	font_render_text("Some Ladders go Down", fonts[0], renderer, help_text_rect);
	help_text_rect.y += inst_text_spacer;
	font_render_text("Other Ladders go Up", fonts[0], renderer, help_text_rect);
	help_text_rect.y += inst_text_spacer;
	font_render_text("Herbs Heal", fonts[0], renderer, help_text_rect);
	help_text_rect.y += inst_text_spacer;
	font_render_text("Collect Crown & Escape to Win", fonts[0], renderer, help_text_rect);
	help_text_rect.y += inst_text_spacer;
	font_render_text("Press SPACE to BEGIN", fonts[0], renderer, help_text_rect);
	// SPACEBAR START?
	if (keys[SDL_SCANCODE_SPACE] == 1) {
		state_id = 2;
		state_game_new_player();
	}
}
