
typedef struct {
	int ent_type;
	float x; // bottom middle of sprite
	float y; // bottom middle of sprite
	float x_dir;
	float y_dir;
	SDL_Rect base;
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
	return (float) ((rand() % 200) - 100) * 0.005f;
}

void ents_init(ent ents[], SDL_Renderer * renderer, SDL_Rect rect) {
	for (int i = 0; i < ENTS_COUNT; i++) {
		ents[i].x = 10 + (rand() % (rect.w - 30));
		ents[i].y = 10 + (rand() % (rect.h - 30));
		ents[i].x_dir = ents_rnd_direction();
		ents[i].y_dir = ents_rnd_direction();
		ents[i].ent_type = (i < ENTS_COUNT / 2) ? ent_giantgnome : ent_owlbear;

		//ents[i].base_rect.x = ents[i].sprite_rect.x;
		//ents[i].base_rect.y = ents[i].sprite_rect.y + 15;
		ents[i].base.w = 20;
		ents[i].base.h = 5;
		ents[i].collisions = 0;
		char coll[10];
		sprintf(coll, "%d", ents[i].collisions);
	}
}


void ents_update(ent ents[], SDL_Rect rect) {

	for (int i = 0; i < ENTS_COUNT; i++) {
		ent e = ents[i];
		SDL_Rect spr = ent_sprites[e.ent_type];
		SDL_Rect base = {
			(int) (e.x - spr.w / 2),
			(int) e.y - 5,
			spr.w, 5
		};
		int wall_collide = 0;
		for (int x = e.base.x; x < e.base.x + e.base.w; x += 10) {
			for (int y = e.base.y; y < e.base.y + e.base.h; y += 10) {
				if (x > 0 && y > 0) {
				/*
					if (map_data[0][x/10][y/10] != 0) {
						wall_collide++;
					}
					*/
				}
			}
		}
		if (e.x < 10) e.x_dir = -e.x_dir;
		if (e.x > 300) e.x_dir = -e.x_dir;
		if (e.y < 10) e.y_dir = -e.y_dir;
		if (e.y > 180) e.y_dir = -e.y_dir;
		if (wall_collide) {
			e.x_dir = -e.x_dir;
			e.y_dir = -e.y_dir;
		}
		e.x += e.x_dir;
		e.y += e.y_dir;
		e.base = base;
		ents[i] = e;
	}
}


void ents_render(ent ents[], SDL_Renderer * renderer) {
	int ents_sorted[ENTS_COUNT];
	for (int i = 0; i < ENTS_COUNT; i++) ents_sorted[i] = i;
	ents_bubble_sort(ents, ents_sorted);
	for (int i = 0; i < ENTS_COUNT; i++) {
//		SDL_RenderCopy(renderer, ents[ents_sorted[i]].texture, NULL, &ents[ents_sorted[i]].sprite_rect);
		ent e = ents[ents_sorted[i]];
		SDL_Rect spr_rect = ent_sprites[e.ent_type];
		SDL_Rect rect = { 
			(int) (e.x - spr_rect.w / 2),
			(int) (e.y - spr_rect.h),
			spr_rect.w, spr_rect.h
		};
		set_render_color(renderer, 1);
		SDL_Rect tile;
		tile = (SDL_Rect) { 
			(e.base.x / 10) * 10,
			(e.base.y / 10) * 10,
			10, 10 };
		SDL_RenderDrawRect(renderer, &tile);
		tile = (SDL_Rect) { 
			((e.base.x + e.base.w) / 10) * 10,
			(e.base.y / 10) * 10,
			10, 10 };
		SDL_RenderDrawRect(renderer, &tile);
		tile = (SDL_Rect) { 
			(e.base.x / 10) * 10,
			((e.base.y + e.base.h) / 10) * 10,
			10, 10 };
		SDL_RenderDrawRect(renderer, &tile);
		tile = (SDL_Rect) { 
			((e.base.x + e.base.w) / 10) * 10,
			((e.base.y + e.base.h) / 10) * 10,
			10, 10 };
		SDL_RenderDrawRect(renderer, &tile);
		SDL_RenderCopy(renderer, spriteshit, &spr_rect, &rect);
	}
}





