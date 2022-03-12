
SDL_Rect playfield_rect = { 0, 0, 320, 200 };

SDL_Texture * dirt_texture;

void state_game_playfield_init() {
	// dirt floor
	printf("creating dirt floor\n");
	uint32_t * dirt_pixels = malloc(playfield_rect.w * playfield_rect.h * 4);
	dirt_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, playfield_rect.w, playfield_rect.h);
	for (int x = 0; x < playfield_rect.w; x++) {
		for (int y = 0; y < playfield_rect.h; y++) {
			int color_id = (rng8() & rng8() & rng8() & rng8() & rng8() & 13) ? 5 : 7;
			uint32_t dirt = 0;
			if (color_id == 7) {
				dirt += (sdl_palette[color_id].r + (rand() % 16) - 8) << 24;
				dirt += (sdl_palette[color_id].g + (rand() % 16) - 8) << 16;
				dirt += (sdl_palette[color_id].b + (rand() % 16) - 8) << 8;
			}
			dirt_pixels[x + y * playfield_rect.w] = dirt;
		}
	}
	SDL_UpdateTexture(dirt_texture, NULL, dirt_pixels, playfield_rect.w * 4);
	free(dirt_pixels);
}


void state_game_playfield_frame() {

	ents_update(ents, playfield_rect);

	camera_rect.x = (ents[0].xt - 16) * 10;
	camera_rect.y = (ents[0].yt - 10) * 10;

	// handle out of bounds camera positions
	int map_px_w = map_width * 10;
	int map_px_h = map_height * 10;
	SDL_Rect oob_cam = { 0, 0, camera_rect.w, camera_rect.h };
	SDL_Rect oob_field = { 0, 0, playfield_rect.w, playfield_rect.h };
	if (camera_rect.x < 0) {
		oob_cam.x = 0;
		oob_field.x = abs(camera_rect.x);
		oob_field.w = playfield_rect.w - oob_cam.x;
	}
	else if (camera_rect.x + camera_rect.w > map_px_w) {
		oob_cam.x = camera_rect.x;
		oob_cam.w = map_px_w - camera_rect.x;
		oob_field.w = oob_cam.w;
	}
	else {
		oob_cam.x = camera_rect.x;
	}
	if (camera_rect.y < 0) {
		oob_cam.y = 0;
		oob_field.y = abs(camera_rect.y);
		oob_field.h = playfield_rect.h - oob_cam.y;
	}
	else if (camera_rect.y + camera_rect.h > map_px_h) {
		oob_cam.y = camera_rect.y;
		oob_cam.h = map_px_h - camera_rect.y;
		oob_field.h = oob_cam.h;
	}
	else {
		oob_cam.y = camera_rect.y;
	}
	
	// background refresh
	SDL_RenderCopy(renderer, map_texture, &oob_cam, &oob_field);

	// sprites
	ents_render(ents, renderer);
	
	if (ents[0].state == ent_state_player_controlled) {
		ents[0].dir = 0xff;
		if (keys[SDL_SCANCODE_RIGHT]) ents[0].dir = 0;
		if (keys[SDL_SCANCODE_UP]) ents[0].dir = 1;
		if (keys[SDL_SCANCODE_LEFT]) ents[0].dir = 2;
		if (keys[SDL_SCANCODE_DOWN]) ents[0].dir = 3;
	}
	if (keys[SDL_SCANCODE_C] == 1) {
		printf("c pressed\n");
		if (ents[0].state == ent_state_player_controlled) {
			ents[0].state = ent_state_blocked;
		}
		else ents[0].state = ent_state_player_controlled;
	}

}


