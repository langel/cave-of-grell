
char nar_player_death[] = "'Twas I was never one for living much really meh n'anywayz.";


char nar_story[5][64] = {
	"\"I shan't returneth upon ye villagers absent of thee",
	"  ancient king crown.  Those folks I have left behind;",
	"   such peasants.  High adventure awaits in this legendary",
	"    cavern.  Once, having obsconded with the prize --",
	"     I SHALL RULE WITH AN IRON FIST OF LOVE!!\"",
};

int state_nar_prev = 0;


void state_narration_init() {
	state_nar_prev = state_id;
	state_id = 5;
}

void state_narration_frame() {
	SDL_RenderCopy(renderer, dirt_texture, NULL, NULL);
	font_set_color(fonts[0], sdl_palette[1]);

	help_text_rect.x = 75;
	help_text_rect.y = 30;
	
	for (int i = 0; i < 5; i++) {
		font_render_text(nar_story[i], fonts[0], renderer, help_text_rect);
		help_text_rect.y += 20;
	}

	help_text_rect.x = 150;
	help_text_rect.y = 175;
	font_render_text("Press SPACE to Continue", fonts[0], renderer, help_text_rect);
	if (keys[SDL_SCANCODE_SPACE] == 1) {
		state_id = state_nar_prev;
	}
}
