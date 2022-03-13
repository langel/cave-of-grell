void state_controller_init() {
	state_menu_init();
	state_help_init();
	state_game_hud_init();
	state_game_map_init();
	state_game_playfield_init();
}

void state_controller_frame(SDL_Renderer * renderer) {

	if (state_id == 0) {
		state_menu_frame();
	}
	else if (state_id == 1) {
		state_help_frame();
	}
	else if (state_id == 2) {
		state_game_frame();
	}
	else if (state_id == 3) {
		state_map_render_loading_frame();
	}
	else if (state_id == 4) {
		state_congration_frame();
	}

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_KEYDOWN:
//				printf( "keydown: %8s\n", SDL_GetKeyName( event.key.keysym.sym ) );
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					window_w = event.window.data1;
					window_h = event.window.data2;
					printf("window size changed: %d x %d\n", window_w, window_h);
				}
				break;
		}
	}
	keyboard_frame();
	if (keys[SDL_SCANCODE_H] == 1) state_help_h_pressed();
	// XXX need quit confirmation screen
//	if (keys[SDL_SCANCODE_ESCAPE] == 1) state_quit_esc_pressed();
	if (keys[SDL_SCANCODE_ESCAPE]) running = 0;
}

