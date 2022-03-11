
void ents_bubble_sort(ent ents[], int ents_sort[]) {
	// draw lower y axis ents first
	int size = ENTS_COUNT;
	for (int step = 0; step < size - 1; ++step) {
		for (int i = 0; i < size - step - 1; ++i) {
			if (ents[ents_sort[i]].yt > ents[ents_sort[i + 1]].yt) {
				int temp = ents_sort[i];
				ents_sort[i] = ents_sort[i + 1];
				ents_sort[i + 1] = temp;
			}
		}
	}
}

int ents_rand() {
	return (rand() % 11) + 1;
}

int ents_space_free(int x, int y) {
	for (int i = 0; i < ENTS_COUNT; i++) {
		if (ents[i].xt == x && ents[i].yt == y) return 0;
	}
	return 1;
}

// finds and sets empty map tile for spawning
ent ent_find_spawn_position(ent e, int map_level) {
	e.xt = e.yt = 0;
	while (map_data[map_level][e.xt][e.yt] != 0 || !ents_space_free(e.xt, e.yt)) {
		e.xt = rand() % map_width;
		e.yt = rand() % map_height;
	}
	return e;
}


void ents_init(int map_level) {
	for (int i = 3; i < ENTS_COUNT; i++) {
//		printf("\nent_id %d\n", i);
		ent e = ents[i];
		e.type = ents_rand();
		e = ent_find_spawn_position(e, map_level);
//		printf("spawning %s @ %d, %d\n", ent_types[e.type].name, e.xt, e.yt);
		e.hp = ent_types[e.type].hp;
		e.state = ent_types[e.type].state;
		e.collisions = 0;
		e.dir = rand() % 4;
		ents[i] = e;
	}
}


void ents_update(ent ents[], SDL_Rect rect) {

	for (int i = 0; i < ENTS_COUNT; i++) {
		ent e = ents[i];

		if (e.state == ent_state_blocked) {
			e.state = ent_state_wandering;
			e.dir = rand() % 4;
		}
		else if (e.state == ent_state_wandering && frame_counter % 10 == 0) {
			if (rand() % 11 == 0) e.state = ent_state_blocked;
			else if (e.dir == 0) { // right
				if (map_data[0][e.xt + 1][e.yt] == 0) {
					if (ents_space_free(e.xt+1, e.yt)) e.xt++;
					else e.collisions++;
				}
				else e.state = ent_state_blocked;
			}
			else if (e.dir == 1) { // up
				if (map_data[0][e.xt][e.yt - 1] == 0) {
					if (ents_space_free(e.xt, e.yt - 1)) e.yt--;
					else e.collisions++;
				}
				else e.state = ent_state_blocked;
			}
			else if (e.dir == 2) { //left
				if (map_data[0][e.xt-1][e.yt] == 0) {
					if (ents_space_free(e.xt - 1, e.yt)) e.xt--;
					else e.collisions++;
				}
				else e.state = ent_state_blocked;
			}
			else if (e.dir == 3) { // down
				if (map_data[0][e.xt][e.yt + 1] == 0) {
					if (ents_space_free(e.xt, e.yt + 1)) e.yt++;
					else e.collisions++;
				}
				else e.state = ent_state_blocked;
			}
		}

		ents[i] = e;
	}
}


void ents_render(ent ents[], SDL_Renderer * renderer) {
	int ents_sorted[ENTS_COUNT];
	for (int i = 0; i < ENTS_COUNT; i++) ents_sorted[i] = i;
	ents_bubble_sort(ents, ents_sorted);
	for (int i = 0; i < ENTS_COUNT; i++) {
		ent e = ents[ents_sorted[i]];
		SDL_Rect spr_rect = ent_types[e.type].sprite;
		SDL_Rect rect = { 
			(int) (e.xt * 10 + 5 - spr_rect.w / 2) - camera_rect.x,
			(int) (e.yt * 10 + 8 - spr_rect.h) - camera_rect.y,
			spr_rect.w, spr_rect.h
		};
		SDL_RenderCopy(renderer, spriteshit, &spr_rect, &rect);
	}
}





