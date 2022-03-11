
int state_help_previous = 0;


SDL_Rect help_text_rect = { 42, 20, 300, 100};

void state_help_init() {
	help_text_rect.h = fonts[0].height;
}

void state_help_return() {
	state_id = state_help_previous;
}

void state_help_h_pressed() {
	if (state_id != 1) {
		state_help_previous = state_id;
		state_id = 1;
	}
	else state_help_return();
}

void state_help_frame() {
	SDL_RenderCopy(renderer, dirt_texture, NULL, NULL);
	font_set_color(fonts[0], sdl_palette[1]);
	font_render_text("Press Any Key to Continue", fonts[0], renderer, help_text_rect);
	if (keys_pressed && !keys[SDL_SCANCODE_H]) {
		state_help_return();
	}
}
