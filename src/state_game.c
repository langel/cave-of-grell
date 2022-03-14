
int game_state_id = 0;

int sfx_crown_counter = 0;

void state_game_init() {
}

void state_game_new_player() {
	player_hp_max = 100;
	player_hp = player_hp_max;
	player_xp = 0;
	player_gp = 0;
	player_level = 0; // dungeon/map level
	player_has_crown = 0;
	sfx_crown_counter = 0;
	ents[player_level][0].hp = player_hp;
	for (int i = 0; i < map_levels; i++) {
		map_gen_new(i);
	}
	player_frame_counter = 0;
	state_game_map_render_level();
}

void state_game_enter_level(int modifier) {
	int old_level = player_level;
	player_level += modifier;
	ents[player_level][0].hp = player_hp;
	ents[player_level][0].state = ents[old_level][0].state;
	state_game_map_render_level();
}

void state_game_frame() {

	player_hp = ents[player_level][0].hp;
	player_frame_counter++;

	// LADDER HANDLING
	if (player_update_level != 0) {
		printf("%d frames aka %f seconds aka %f minutes\n", player_frame_counter, (float) player_frame_counter / 60.f, (float) player_frame_counter / 3600.f);
		// going up
		if (player_update_level == -1) {
			if (player_level == 0) {
				// do crown check 
				if (player_has_crown) state_congration_init();
				// otherwise text
				else state_narration_init();
			}
			else state_game_enter_level(player_update_level);
		}
		// going down
		if (player_update_level == 1) {
			state_game_enter_level(player_update_level);
		}
		// reset
		player_update_level = 0;
	}
	
	if (player_has_crown) {
		if (sfx_crown_counter % 12 == 0) {
			if (sfx_crown_counter < 80) sfx_crown();
		}
		sfx_crown_counter++;
	}

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
		//printf("game_state_id : %d\n", game_state_id);
	}

	if (keys[SDL_SCANCODE_SPACE] && player_hp < 0) {
		state_id = 0;
	}
}


