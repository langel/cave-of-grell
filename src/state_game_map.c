int state_game_map_previous_state = 0;
int state_game_map_frame_counter = 0;
SDL_Rect loading_text_rect = { 42, 20, 300, 100 };

void state_game_map_loading_screen() {
	SDL_RenderCopy(renderer, dirt_texture, NULL, NULL);
	font_set_color(fonts[0], sdl_palette[1]);
	loading_text_rect.x = 150;
	loading_text_rect.y = 90;
	loading_text_rect.h = fonts[0].height;
	font_render_text("Loading  .  . .", fonts[0], renderer, loading_text_rect);
}

void state_game_map_render_level() {
	state_game_map_previous_state = state_id;
	state_id = 3;
	state_game_map_loading_screen();
	state_game_map_frame_counter = 0;
}

void state_map_render_loading_frame() {
	if (state_game_map_frame_counter == 3) {
		printf("renderating level %d texture\n", player_level);
		map_view_texture_update(player_level);
		map_playfield_render(player_level);
		state_id = state_game_map_previous_state;
		ents[player_level][0].dir = 0xff;
	}
	else state_game_map_frame_counter++;
	state_game_map_loading_screen();
}

void state_game_map_new() {
	map_gen_new(player_level);
	state_game_map_render_level();
}


void state_game_map_init() {
	map_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, map_texture_rect.w, map_texture_rect.h);
	SDL_SetTextureBlendMode(map_texture, SDL_BLENDMODE_BLEND);
	map_view_texture = texture_create_generic(renderer, map_width * 2, map_height * 2);
}

SDL_Rect map_view_rect = { 32, 20, 256, 160 };

void state_game_map_frame() {

	// copy map view to screen
	SDL_RenderCopy(renderer, map_view_texture, NULL, &map_view_rect);

	// show player position
	SDL_Rect player_pixel = { 
		map_view_rect.x + ents[player_level][0].xt * 2, 
		map_view_rect.y + ents[player_level][0].yt * 2,
		2, 2 };
	grafx_set_color(2);
	SDL_RenderDrawRect(renderer, &player_pixel);
	if (keys[SDL_SCANCODE_SPACE] == 1 || keys[SDL_SCANCODE_RETURN] == 1) {
		state_game_map_new();
	}
}


