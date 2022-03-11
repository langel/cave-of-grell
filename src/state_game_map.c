

void state_game_map_new() {
	map_gen_new(0);
	map_view_texture_update(0);
	map_playfield_render(0);
}


void state_game_map_init() {
	map_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, map_texture_rect.w, map_texture_rect.h);
	SDL_SetTextureBlendMode(map_texture, SDL_BLENDMODE_BLEND);
	map_view_texture = texture_create_generic(renderer, map_width * 2, map_height * 2);
	state_game_map_new();
}

SDL_Rect map_view_rect = { 32, 20, 256, 160 };

void state_game_map_frame() {
	if (map_drawing_new == 1) { 
		state_game_map_new();
		map_drawing_new = 0;
	}

	// copy map view to screen
	SDL_RenderCopy(renderer, map_view_texture, NULL, &map_view_rect);

	// show player position
	SDL_Rect player_pixel = { 
		map_view_rect.x + ents[0].xt * 2, 
		map_view_rect.y + ents[0].yt * 2,
		2, 2 };
	grafx_set_color(2);
	SDL_RenderDrawRect(renderer, &player_pixel);
}


