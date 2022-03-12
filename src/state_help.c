
int state_help_previous = 0;


SDL_Rect help_text_rect = { 42, 20, 300, 100 };
SDL_Rect help_key_rect;
SDL_Rect help_function_rect;

typedef struct {
	char key[8];
	char function[32];
} help_key_text;

help_key_text help_key_texts[] = {
	{ "Arrows", "Moveth teh Player" },
	{ "Tab", "Dungeon & Map Swap" },
	{ "H",   "Halp, PLEASE!" },
	{ "C",   "Cornputer Controlled Player" },
	{ "Esc", "Quitteth Cave of Grell" },
};

void state_help_init() {
	help_text_rect.h = fonts[0].height;
	help_key_rect = help_function_rect = help_text_rect;
	help_key_rect.x = 115;
	help_function_rect.x = 180;
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

	help_text_rect.x = 150;
	help_text_rect.y = 15;
	font_render_text("Ye in needeth of halp?", fonts[0], renderer, help_text_rect);
	
	help_key_rect.y = help_function_rect.y = 50;
	for (int i = 0; i < 5; i++) {
		font_render_text(help_key_texts[i].key, fonts[0], renderer, help_key_rect);
		font_render_text(help_key_texts[i].function, fonts[0], renderer, help_function_rect);
		help_key_rect.y = help_function_rect.y += 20;
	}

	help_text_rect.x = 140;
	help_text_rect.y = 175;
	font_render_text("Press Any Key to Continue", fonts[0], renderer, help_text_rect);
	if (keys_pressed && !keys[SDL_SCANCODE_H]) {
		state_help_return();
	}
}
