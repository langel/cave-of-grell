
typedef struct {
	int ent_type;
	int dir; // right, up, left, down
	int xt; // tile positions
	int yt;
	int state;
	int collisions;
} ent;

#define ENTS_COUNT 32

#define ent_state_dormant 0
#define ent_state_wandering 1
#define ent_state_blocked 2

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

float ents_rnd_direction() {
	return (float) ((rand() % 200) - 100) * 0.005f;
}

void ents_init(ent ents[], SDL_Renderer * renderer, SDL_Rect rect) {
	for (int i = 0; i < ENTS_COUNT; i++) {
		printf("init ent %d \n", i);
		ents[i].ent_type = (i < ENTS_COUNT / 2) ? ent_giantgnome : ent_owlbear;
		ents[i].dir = rand() % 4;
		ents[i].xt = ents[i].yt = 0;
		while (map_data[0][ents[i].xt][ents[i].yt] != 0) {
			ents[i].xt = rand() % 32;
			ents[i].yt = rand() % 20;
			printf("%d , %d \n", ents[i].xt, ents[i].yt);
		}
		ents[i].state = ent_state_wandering;
		ents[i].collisions = 0;
		char coll[10];
		sprintf(coll, "%d", ents[i].collisions);
	}
}


void ents_update(ent ents[], SDL_Rect rect) {

	for (int i = 0; i < ENTS_COUNT; i++) {
		ent e = ents[i];
		SDL_Rect spr = ent_sprites[e.ent_type];

		if (e.state == ent_state_blocked) {
			e.state = ent_state_wandering;
			e.dir = rand() % 4;
		}
		else if (e.state == ent_state_wandering && frame_counter % 10 == 0) {
			if (e.dir == 0) { // right
				if (map_data[0][e.xt+1][e.yt] == 0) e.xt++;
				else e.state = ent_state_blocked;
			}
			if (e.dir == 1) { // up
				if (map_data[0][e.xt][e.yt-1] == 0) e.yt--;
				else e.state = ent_state_blocked;
			}
			if (e.dir == 2) { //left
				if (map_data[0][e.xt-1][e.yt] == 0) e.xt--;
				else e.state = ent_state_blocked;
			}
			if (e.dir == 3) { // right
				if (map_data[0][e.xt][e.yt+1] == 0) e.yt++;
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
		SDL_Rect spr_rect = ent_sprites[e.ent_type];
		SDL_Rect rect = { 
			(int) (e.xt * 10 + 5 - spr_rect.w / 2),
			(int) (e.yt * 10 + 8 - spr_rect.h),
			spr_rect.w, spr_rect.h
		};
		SDL_RenderCopy(renderer, spriteshit, &spr_rect, &rect);
	}
}





