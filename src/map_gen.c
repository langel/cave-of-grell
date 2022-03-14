
// MAPS ARE 128 x 80 tiles
// 1 : 3 rooms
// 2 : normal
// 3 : normal
// 4 : some water
// 5 : tiny rooms
// 6 : giant lake
// 7 : normal many grell
// 8 : giant rooms full of grell
// 9 : 3 rooms - 1 crown

int map_gen_room_count[9] = { 3, 9, 9, 5, 9, 9, 9, 15, 3 };
int map_gen_rock_debris[9] = { 128, 256, 512, 512, 128, 1024, 512, 1024, 256 };
int map_gen_water_debris[9] = { 0,  16,  62, 256, 128, 1024, 128, 512, 0 };

int map_room_min_x = 4;
int map_room_min_y = 5;
int map_gen_room_max[9][2] = { // level id / x, y
	{ 3, 4 }, { 28, 14 }, { 32, 20 },
	{ 40, 24 }, { 3, 2 }, { 20, 8 },
	{ 32, 20 }, { 48, 32 }, { 3, 4 },
};
int map_gen_map_size[9][2] = { // level id / x, y max
	{ 32, 20 }, { 80, 50 }, { 126, 78 },
	{ 80, 50 }, { 126, 78 }, { 126, 78 },
	{ 80, 50 }, { 126, 78 }, { 32, 20 },
};

void map_gen_new(int map_level) {
	
	// cavity id / x,y
	int cavity_centers[map_cavities_max][2]; 

	// fill map with rocks
	printf("generating level %d map\n", map_level);
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			map_data[map_level][x][y] = 1;
		}
	}

	// make a lake
	if (map_level == 5) {
		for (int i = 0; i < 27; i++) {
			int pondx = rand() % 80;
			int pondy = rand() % 60;
			int pondw = rand() % 50 + 8;
			int pondh = rand() % 40 + 5;
			for (int x = pondx; x < pondx + pondw; x++) {
				for (int y = pondy; y < pondy + pondh; y++) {
					map_data[map_level][x][y] = 2;
				}
			}
		}
	}

	// make 9 rooms
	for (int i = 0; i < map_gen_room_count[map_level]; i++) {
		SDL_Rect cavity;
		cavity.w = rand() % map_gen_room_max[map_level][0] + map_room_min_x;
		cavity.x = (map_width - map_gen_map_size[map_level][0]) / 2 + (rand() % (map_gen_map_size[map_level][0] - cavity.w - 4)); 
		cavity.h = rand() % map_gen_room_max[map_level][1] + map_room_min_x;
		cavity.y = (map_height - map_gen_map_size[map_level][1]) / 2 + (rand() % (map_gen_map_size[map_level][1] - cavity.h - 4)); 
		//printf("%d %d %d %d  ..  ", cavity.x, cavity.y, cavity.w, cavity.h);
		for (int x = cavity.x; x < cavity.x + cavity.w; x++) {
			for (int y = cavity.y; y < cavity.y + cavity.h; y++) {
				map_data[map_level][x][y] = 0;
			}
		}

		// cache cavity center position
		cavity_centers[i][0] = cavity.x + cavity.w / 2;
		cavity_centers[i][1] = cavity.y + cavity.h / 2;
		//printf("\nlevel %d cavity %d center x, y : %d, %d\n", map_level, map_drawing_stage, cavity_centers[i][0], cavity_centers[i][1]);
	}

	// add water debris
	for (int i = 0; i < map_gen_water_debris[map_level]; i++) {
		int x = rand() % map_width;
		int y = rand() % map_height;
		if (map_data[map_level][x][y] == 0) {
			map_data[map_level][x][y] = 2;
		}
	}
	// add rock debris
	for (int i = 0; i < map_gen_rock_debris[map_level]; i++) {
		int x = rand() % map_width;
		int y = rand() % map_height;
		if (map_data[map_level][x][y] == 0) {
			map_data[map_level][x][y] = 1;
		}
	}
	
	// ENTITY PLOTTING!!!
	// up ladder
	ent_load_type(map_level, 2, ent_ladder_up);
	ents[map_level][2].xt = cavity_centers[0][0];
	ents[map_level][2].yt = cavity_centers[0][1];
	int last_room = map_gen_room_count[map_level] - 1;
	if (map_level < 8) {
		// down ladder
		ent_load_type(map_level, 1, ent_ladder_down);
		ents[map_level][1].xt = cavity_centers[last_room][0];
		ents[map_level][1].yt = cavity_centers[last_room][1];
	}
	else {
		// crown to win!!
		ent_load_type(map_level, 1, ent_crown);
		ents[map_level][1].xt = cavity_centers[last_room][0];
		ents[map_level][1].yt = cavity_centers[last_room][1];
	}
	// player
	ents[map_level][0].type = ent_player;
	ents[map_level][0].xt = cavity_centers[0][0] + 1;
	ents[map_level][0].yt = cavity_centers[0][1];
	ents[map_level][0].state = ent_state_player_controlled;
	// Everything Else!!
	ents_init(map_level);

	// carve corridors between rooms
	for (int i = 1; i < map_gen_room_count[map_level]; i++) {

		// corridor cut outs between cavities
		int target = rand() % (i);
		//printf("attaching cavity %d to cavity %d\n", i, target);
		// current cavity
		int ccx = cavity_centers[i][0];
		int ccy = cavity_centers[i][1];
		// target cavity
		int tcx = cavity_centers[target][0];
		int tcy = cavity_centers[target][1];
		//printf("target cavity center x, y : %d, %d\n", tcx, tcy);
		if (ccx >= tcx) for (int x = tcx; x <= ccx; x++) {
			map_data[map_level][x][ccy] = 0;		
		}
		else for (int x =  ccx; x <= tcx; x++) {
			map_data[map_level][x][ccy] = 0;
		}
		if (ccy >= tcy) for (int y = tcy; y <= ccy; y++) {
			map_data[map_level][tcx][y] = 0;
		}
		else for (int y =  ccy; y <= tcy; y++) {
			map_data[map_level][tcx][y] = 0;
		}
	}

}
