
int game_state_id = 0;

void state_game_init() {
}


void state_game_frame() {

	SDL_RenderCopy(renderer, dirt_texture, NULL, &playfield_rect);

	if (game_state_id % 2 == 0) {
		state_game_playfield_frame();
	}
	else {
		state_game_map_frame();
	}

	state_game_hud_render(renderer);
	
	if (keys[SDL_SCANCODE_TAB] == 1) {
		game_state_id++;
		printf("game_state_id : %d\n", game_state_id);
	}
}


