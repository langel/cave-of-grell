
typedef struct {
	float x;
	float y;
	float x_dir;
	float y_dir;
	SDL_Texture * texture;
	SDL_Rect base_rect;
	SDL_Rect sprite_rect;
} ent;

#define ENTS_COUNT 8


void ents_bubble_sort(ent ents[]) {
	// draw lower y axis ents first
	int size = ENTS_COUNT;
	for (int step = 0; step < size - 1; ++step) {
		for (int i = 0; i < size - step - 1; ++i) {
			if (ents[i].y > ents[i + 1].y) {
				ent temp = ents[i];
				ents[i] = ents[i + 1];
				ents[i + 1] = temp;
			}
		}
	}
}

float ents_rnd_direction() {
	return (float) ((rand() % 200) - 100) * 0.025f;
}

void ents_init(ent ents[], SDL_Renderer * renderer) {
	for (int i = 0; i < ENTS_COUNT; i++) {
		ents[i].x = rand() % 320 + 50;
		ents[i].y = rand() % 100 + 50;
		ents[i].x_dir = ents_rnd_direction();
		ents[i].y_dir = ents_rnd_direction();
		// XXX maybe move textures to another function
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		ents[i].texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 20, 20);
		SDL_SetRenderTarget(renderer, ents[i].texture);
		SDL_RenderFillRect(renderer, NULL);
		SDL_SetTextureColorMod(ents[i].texture, sdl_palette[i].r, sdl_palette[i].g, sdl_palette[i].b);
		ents[i].sprite_rect.x = (int) ents[i].x;
		ents[i].sprite_rect.y = (int) ents[i].y;
		ents[i].sprite_rect.w = 20;
		ents[i].sprite_rect.h = 20;
		ents[i].base_rect.x = ents[i].sprite_rect.x;
		ents[i].base_rect.y = ents[i].sprite_rect.y + 15;
		ents[i].base_rect.w = 20;
		ents[i].base_rect.h = 5;
	}
}

void ents_update(ent ents[]) {
	ents_bubble_sort(ents);
	for (int i = 0; i < ENTS_COUNT; i++) {
		if (ents[i].base_rect.x < 11) ents[i].x_dir = abs(ents_rnd_direction());
		if (ents[i].base_rect.x > 389) ents[i].x_dir = -abs(ents_rnd_direction());
		if (ents[i].base_rect.y < 11) ents[i].y_dir = abs(ents_rnd_direction());
		if (ents[i].base_rect.y > 184) ents[i].y_dir = -abs(ents_rnd_direction());
		for (int j = 0; j < 8; j++) {
			if (i != j) {
				if (collision_detection(ents[i].base_rect, ents[j].base_rect)) {
					audio_amp = 0.1f;
					audio_hertz = (float) ((rand() % 420) + 80) / 32000.f;
					ents[i].x_dir = -ents[i].x_dir;
					ents[i].y_dir = -ents[i].y_dir;
				}
			}
		}
		ents[i].x += ents[i].x_dir;
		ents[i].sprite_rect.x = (int) ents[i].x;
		ents[i].y += ents[i].y_dir;
		ents[i].sprite_rect.y = (int) ents[i].y;
		ents[i].base_rect.x = ents[i].sprite_rect.x;
		ents[i].base_rect.y = ents[i].sprite_rect.y + 15;
	}
}

void ents_render(ent ents[], SDL_Renderer * renderer) {
	for (int i = 0; i < ENTS_COUNT; i++) {
		SDL_RenderCopy(renderer, ents[i].texture, NULL, &ents[i].sprite_rect);
	}
}
