
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
	
	// background refresh
	SDL_RenderCopy(renderer, map_texture[0], &camera_rect, &playfield_rect);

	// sprites
	ents_render(ents, renderer);

}


