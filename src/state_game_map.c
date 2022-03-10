


void state_game_map_init() {
	map_view_texture = texture_create_generic(renderer, map_width * 2, map_height * 2);
	map_view_texture_update(0);
}

SDL_Rect map_view_rect = { 32, 20, 256, 160 };

void state_game_map_frame() {
	if (map_drawing_new == 1) map_draw_new(0);
	SDL_RenderCopy(renderer, map_view_texture, NULL, &map_view_rect);
}


