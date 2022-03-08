
typedef struct {
	float x;
	float y;
	float x_dir;
	float y_dir;
	SDL_Texture * texture;
	SDL_Rect base_rect;
	SDL_Rect sprite_rect;
	int collisions;
} ent;

#define ENTS_COUNT 8


void ents_bubble_sort(ent ents[], int ents_sort[]) {
	// draw lower y axis ents first
	int size = ENTS_COUNT;
	for (int step = 0; step < size - 1; ++step) {
		for (int i = 0; i < size - step - 1; ++i) {
			if (ents[ents_sort[i]].y > ents[ents_sort[i + 1]].y) {
				int temp = ents_sort[i];
				ents_sort[i] = ents_sort[i + 1];
				ents_sort[i + 1] = temp;
			}
		}
	}
}

float ents_rnd_direction() {
	return (float) ((rand() % 200) - 100) * 0.025f;
}

void ents_init(ent ents[], SDL_Renderer * renderer, SDL_Rect rect) {
	for (int i = 0; i < ENTS_COUNT; i++) {
		ents[i].x = 10 + (rand() % (rect.w - 30));
		ents[i].y = 10 + (rand() % (rect.h - 30));
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
		ents[i].collisions = 0;
		char coll[10];
		sprintf(coll, "%d", ents[i].collisions);
	}
}

void ents_update(ent ents[], SDL_Rect rect) {

	for (int i = 0; i < ENTS_COUNT; i++) {
		if (ents[i].base_rect.x < 11) ents[i].x_dir = abs(ents_rnd_direction());
		if (ents[i].base_rect.x > rect.w - 31) ents[i].x_dir = -abs(ents_rnd_direction());
		if (ents[i].base_rect.y < 11) ents[i].y_dir = abs(ents_rnd_direction());
		if (ents[i].base_rect.y > rect.h - 16) ents[i].y_dir = -abs(ents_rnd_direction());
		for (int j = 0; j < 8; j++) {
			if (i != j) {
				if (collision_detection(ents[i].base_rect, ents[j].base_rect)) {
					audio_amp = 0.01f;
					audio_hertz = (float) ((rand() % 420) + 80) / 32000.f;
					ents[i].x_dir = -ents[i].x_dir;
					ents[i].y_dir = -ents[i].y_dir;
					ents[i].collisions++;
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
	int ents_sorted[ENTS_COUNT];
	for (int i = 0; i < ENTS_COUNT; i++) ents_sorted[i] = i;
	ents_bubble_sort(ents, ents_sorted);
	for (int i = 0; i < ENTS_COUNT; i++) {
		SDL_RenderCopy(renderer, ents[ents_sorted[i]].texture, NULL, &ents[ents_sorted[i]].sprite_rect);
	}
	/*
					SDL_DestroyTexture(ents[i].collision_text.texture);
					char coll[10];
					sprintf(coll, "%d", ents[i].collisions);
					ents[i].collision_text = fonts_render_text(coll, f, renderer);
					*/
}
