
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

int ents_rand(int map_level) {
	return (rand() % 8) + 1;
}


int ents_at_position(int map_level, int x, int y) {
	for (int i = 0; i < ENTS_COUNT; i++) {
		if (ents[map_level][i].xt == x && ents[map_level][i].yt == y) return i;
	}
	return 0xff;
}

// finds and sets empty map tile for spawning
ent ent_find_spawn_position(ent e, int map_level) {
	e.xt = e.yt = 0;
	while (map_data[map_level][e.xt][e.yt] != 0 || ents_at_position(map_level, e.xt, e.yt) != 0xff) {
		e.xt = rand() % map_width;
		e.yt = rand() % map_height;
	}
	return e;
}

void ent_load_type(int map_level, int ent_id, int ent_type) {
	ents[map_level][ent_id].type = ent_type;
	ents[map_level][ent_id].state = ent_types[ent_type].state;
	ents[map_level][ent_id].hp = ent_types[ent_type].hp;
}


void ents_init(int map_level) {
	for (int i = 3; i < map_ents_count[map_level] + 3; i++) {
//		printf("\nent_id %d\n", i);
		ent e = ents[map_level][i];
		e.type = map_ent_types[map_level][rand() % map_ent_type_count[map_level]];
		e = ent_find_spawn_position(e, map_level);
//		printf("spawning %s @ %d, %d\n", ent_types[e.type].name, e.xt, e.yt);
		e.hp = ent_types[e.type].hp;
		e.state = ent_types[e.type].state;
		e.collisions = 0;
		e.dir = rand() % 4;
		ents[map_level][i] = e;
	}
}


void ents_update(int map_level, ent ents[], SDL_Rect rect) {

	// XXX need to make this turn based but throttled?!?!

	if (frame_counter % 6 == 0) {

		for (int i = 0; i < ENTS_COUNT; i++) {
			ent e = ents[i];

			int target_x = e.xt;
			int target_y = e.yt;
			int blocked = 0;

			if (e.state == ent_state_blocked) {
				e.state = ent_state_wandering;
				e.dir = rand() % 4;
			}
			else if (e.state == ent_state_wandering || e.state == ent_state_player_controlled) {
				if (e.state == ent_state_wandering && rand() % 11 == 0) e.state = ent_state_blocked;
				else if (e.dir == 0) { // right
					if (map_data[map_level][e.xt + 1][e.yt] == 0) target_x++;
					else blocked++;
				}
				else if (e.dir == 1) { // up
					if (map_data[map_level][e.xt][e.yt - 1] == 0) target_y--;
					else blocked++;
				}
				else if (e.dir == 2) { //left
					if (map_data[map_level][e.xt-1][e.yt] == 0) target_x--;
					else blocked++;
				}
				else if (e.dir == 3) { // down
					if (map_data[map_level][e.xt][e.yt + 1] == 0) target_y++;
					else blocked++;
				}
				if (blocked && i != 0) e.state = ent_state_blocked;
				if (!blocked && i == 0 && e.dir != 0xff) player_steps++;
				int target_id = ents_at_position(map_level, target_x, target_y);
				// direction hit a target
				if (target_id != i && target_id != 0xff && ents[target_id].state != ent_state_dead) {
					ent ent_target = ents[target_id];
					ent_type ent_target_type = ent_types[ent_target.type];
					// IS PLAYER
					if (i == 0) {
						if (ent_target.type == ent_crown) {
							player_gp += 1777;
							player_xp += 1777;
							ent_load_type(map_level, target_id, ent_nan);
							// this triggers crown sfx
							player_has_crown = 1;
						}
						if (ent_target.type == ent_ladder_down) {
							player_update_level = 1;
						}
						if (ent_target.type == ent_ladder_up) {
							player_update_level = -1;
						}
						int amount = 0;
						if (ent_target.type == ent_chest) {
							// is it gold or is it a mimic?
							if (rand() % 10 < player_level) {
								ent_load_type(map_level, target_id, ent_mimic);
							}
							else {
								amount = rand() % 100;
								sprintf(action_log_temp[0], "%s %s ", ent_target_type.name, ent_target_type.verb);
								sprintf(action_log_temp[1], "  %d gp", amount);
								action_log_update();
								player_gp += amount;
								ent_load_type(map_level, target_id, ent_chest_emptied);
								sfx_gold();
							}
						}
						if (ent_target.type == ent_coin) {
							amount = 1;
							sprintf(action_log_temp[0], "%s %s", ent_target_type.name, ent_target_type.verb);
							sprintf(action_log_temp[1], "  %d gp", amount);
							action_log_update();
							player_gp += amount;
							ent_load_type(map_level, target_id, ent_nan);
							sfx_gold();
						}
						if (ent_target.type == ent_coins) {
							amount = 5 + rand() % 7;
							sprintf(action_log_temp[0], "%s %s", ent_target_type.name, ent_target_type.verb);
							sprintf(action_log_temp[1], "  %d gp", amount);
							action_log_update();
							player_gp += amount;
							ent_load_type(map_level, target_id, ent_nan);
							sfx_gold();
						}
						if (ent_target.type == ent_key) {
							amount = 7 + rand() % 17;
							sprintf(action_log_temp[0], "%s %s ", ent_target_type.name, ent_target_type.verb);
							sprintf(action_log_temp[1], "  %d gp", amount);
							action_log_update();
							player_gp += amount;
							ent_load_type(map_level, target_id, ent_nan);
							sfx_gold();
						}
						if (ent_target.type == ent_herb) {
							amount = 20 + rand() % 15;
							sprintf(action_log_temp[0], "%s %s ", ent_target_type.name, ent_target_type.verb);
							sprintf(action_log_temp[1], "  %d HP", amount);
							action_log_update();
							e.hp += amount;
							if (e.hp > player_hp_max) e.hp = player_hp_max;
							player_hp = e.hp;
							ent_load_type(map_level, target_id, ent_nan);
							sfx_heal();
						}
					}
					// don't attack dormant or same types
					if (ent_target.state != ent_state_dormant && e.type != ent_target.type) {
						int damage = ent_target_type.damage_base + rand() %  ent_target_type.damage_rand;
						if (e.type == ent_player || e.type == ent_player_with_crown || ent_target.type == ent_player || ent_target.type == ent_player_with_crown) {
							sprintf(action_log_temp[0], "%s %s", ent_types[e.type].name, ent_types[e.type].verb);
							sprintf(action_log_temp[1], " %s for", ent_target_type.name);
							sprintf(action_log_temp[2], "  %d damage", damage);
							action_log_update();
							printf("%s %s %s for %d damage\n", ent_types[e.type].name, ent_types[e.type].verb, ent_target_type.name, damage);
						}
						ents[target_id].hp -= damage;
						if (ents[target_id].hp < 0) {
							sprintf(action_log_temp[0], "%s ", ent_types[e.type].name);
							sprintf(action_log_temp[1], " murders");
							sprintf(action_log_temp[2], "  %s", ent_target_type.name);
							action_log_update();
							printf("%s dies\n", ent_target_type.name);
							ents[target_id].state = ent_state_dead;
							ents[target_id].type = 0;
							// player bonuses
							if (i == 0) {
								sprintf(action_log_temp[0], "player bills");
								sprintf(action_log_temp[1], " %s for", ent_target_type.name);
								sprintf(action_log_temp[2], "  %d xp", ent_target_type.xp);
								action_log_update();
								player_xp += ent_target_type.xp;
								player_hp_max += player_level + 1;
								player_hp += (int) ceilf((float) (player_level + 1) * 0.6f);
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
					if (i == 0 && e.dir < 4) {
						if (!blocked) sfx_footstep();
						// XXX blocked sound?
					}
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
		if (e.type != 0) {
			SDL_Rect spr_rect;
			if (e.type == ent_player) {
				int step_offset = (player_steps % 4) * 20;
				spr_rect = (!player_has_crown) ?
					ent_types[ent_player].sprite :
					ent_types[ent_player_with_crown].sprite;
				spr_rect.x += step_offset;
			}
			else spr_rect = ent_types[e.type].sprite;
			SDL_Rect rect = { 
				(int) (e.xt * 10 + 5 - spr_rect.w / 2) - camera_rect.x,
				(int) (e.yt * 10 + 8 - spr_rect.h) - camera_rect.y,
				spr_rect.w, spr_rect.h
			};
			SDL_RenderCopy(renderer, spriteshit, &spr_rect, &rect);
		}
	}
}





