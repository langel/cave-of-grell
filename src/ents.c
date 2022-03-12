
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


int ents_at_position(int map_id, int x, int y) {
	for (int i = 0; i < ENTS_COUNT; i++) {
		if (ents[i].xt == x && ents[i].yt == y) return i;
	}
	return 0xff;
}

// finds and sets empty map tile for spawning
ent ent_find_spawn_position(ent e, int map_level) {
	e.xt = e.yt = 0;
	while (map_data[map_level][e.xt][e.yt] != 0 || ents_at_position(0, e.xt, e.yt) != 0xff) {
		e.xt = rand() % map_width;
		e.yt = rand() % map_height;
	}
	return e;
}

void ent_load_type(int ent_id, int ent_type) {
	ents[ent_id].type = ent_type;
	ents[ent_id].state = ent_types[ent_type].state;
	ents[ent_id].hp = ent_types[ent_type].hp;
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

	// XXX need to make this turn based but throttled?!?!

	if (frame_counter % 6 == 0) {

		for (int i = 0; i < ENTS_COUNT; i++) {
			ent e = ents[i];

			int target_x = e.xt;
			int target_y = e.yt;

			if (e.state == ent_state_blocked) {
				e.state = ent_state_wandering;
				e.dir = rand() % 4;
			}
			else if (e.state == ent_state_wandering || e.state == ent_state_player_controlled) {
				int blocked = 0;
				if (e.state == ent_state_wandering && rand() % 11 == 0) e.state = ent_state_blocked;
				else if (e.dir == 0) { // right
					if (map_data[0][e.xt + 1][e.yt] == 0) target_x++;
					else blocked++;
				}
				else if (e.dir == 1) { // up
					if (map_data[0][e.xt][e.yt - 1] == 0) target_y--;
					else blocked++;
				}
				else if (e.dir == 2) { //left
					if (map_data[0][e.xt-1][e.yt] == 0) target_x--;
					else blocked++;
				}
				else if (e.dir == 3) { // down
					if (map_data[0][e.xt][e.yt + 1] == 0) target_y++;
					else blocked++;
				}
				if (blocked && i != 0) e.state = ent_state_blocked;
				int target_id = ents_at_position(0, target_x, target_y);
				// direction hit a target
				if (target_id != i && target_id != 0xff && ents[target_id].state != ent_state_dead) {
					ent ent_target = ents[target_id];
					ent_type ent_target_type = ent_types[ent_target.type];
					// IS PLAYER
					if (i == 0) {
						if (ent_target.type == ent_chest) {
							// is it gold or is it a mimic?
							if (rand() % 10 < player_level) {
								ent_load_type(target_id, ent_mimic);
							}
							else {
								player_gp += rand() % 100;
								ent_load_type(target_id, ent_chest_emptied);
								sfx_gold();
							}
						}
						if (ent_target.type == ent_coin) {
							player_gp++;
							ent_load_type(target_id, ent_nan);
							sfx_gold();
						}
						if (ent_target.type == ent_coins) {
							player_gp += rand() % 7 + 5;
							ent_load_type(target_id, ent_nan);
							sfx_gold();
						}
					}
					// don't attack dormant or same types
					if (ent_target.state != ent_state_dormant && e.type != ent_target.type) {
						int damage = ent_target_type.damage_base + rand() %  ent_target_type.damage_rand;
					//	printf("%s %s %s for %d damage\n", ent_types[e.type].name, ent_types[e.type].verb, ent_types[ents[target_ent_id].type].name, damage);
						ents[target_id].hp -= damage;
						if (ents[target_id].hp < 0) {
							printf("%s dies\n", ent_target_type.name);
							ents[target_id].state = ent_state_dead;
							ents[target_id].type = 0;
							// player bonuses
							if (i == 0) {
								player_xp += ent_target_type.xp;
								player_hp++;
								ents[0].hp++;
							}
							if (i == 0 || target_id == 0) sfx_death();
						}
						// not a death
						else if (i == 0 || target_id == 0) sfx_attack();
					}
				}
				else {
					e.xt = target_x;
					e.yt = target_y;
				}
			}

			ents[i] = e;
		}
	}
}


void ents_render(ent ents[], SDL_Renderer * renderer) {
	int ents_sorted[ENTS_COUNT];
	for (int i = 0; i < ENTS_COUNT; i++) ents_sorted[i] = i;
	ents_bubble_sort(ents, ents_sorted);
	for (int i = 0; i < ENTS_COUNT; i++) {
		ent e = ents[ents_sorted[i]];
		// XXX some kind of death check
		if (e.type != 0) {
			SDL_Rect spr_rect = ent_types[e.type].sprite;
			SDL_Rect rect = { 
				(int) (e.xt * 10 + 5 - spr_rect.w / 2) - camera_rect.x,
				(int) (e.yt * 10 + 8 - spr_rect.h) - camera_rect.y,
				spr_rect.w, spr_rect.h
			};
			SDL_RenderCopy(renderer, spriteshit, &spr_rect, &rect);
		}
	}
}





