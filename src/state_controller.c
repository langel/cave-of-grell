void state_controller_init() {
	state_game_hud_init();
	state_game_map_init();
	state_game_playfield_init();
}

void state_controller_frame(SDL_Renderer * renderer) {

	state_game_frame();

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_KEYDOWN:
				printf( "keydown: %8s\n", SDL_GetKeyName( event.key.keysym.sym ) );
				switch (event.key.keysym.sym) {
					case SDLK_TAB:
						game_state_id++;
						printf("game_state_id : %d\n", game_state_id);
						break;
					case SDLK_SPACE:
					case SDLK_RETURN:
						map_drawing_new = 1;
						map_drawing_stage = 0;
						break;
					case SDLK_ESCAPE:
						running = 0;
						break;
				}
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
}

