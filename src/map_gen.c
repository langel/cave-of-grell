
// XXX some levels should have variations
// 1 : 3 rooms
// 2 : normal
// 3 : normal
// 4 : some water
// 5 : tiny rooms
// 6 : giant lake
// 7 : normal many grell
// 8 : giant rooms full of grell
// 9 : 3 rooms with invisibility ring

void map_gen_new(int map_level) {
	
	// fill map with rocks
	printf("drawing level %d map\n", map_level);
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			map_data[map_level][x][y] = 1;
		}
	}

	// make a lake
//	if (map_level == 6) {
	for (int x = 50; x < map_width - 50; x++) {
		for (int y = 30; y < map_height - 30; y++) {
			map_data[map_level][x][y] = 2;
		}
	}

	// make 9 rooms
	for (int i = 0; i < 9; i++) {
		SDL_Rect cavity;
		cavity.w = (rand() % (map_width / 5)) + 4;
		cavity.x = 2 + (rand() % (map_width - cavity.w - 4)); 
		cavity.h = (rand() % (map_height / 5)) + 4;
		cavity.y = 2 + (rand() % (map_height - cavity.h - 4)); 
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

	// add debris
	for (int i = 0; i < 512; i++) {
		int x = rand() % map_width;
		int y = rand() % map_height;
		if (map_data[map_level][x][y] == 0) {
			map_data[map_level][x][y] = 1;
		}
	}
	
	// ENTITY PLOTTING!!!
	ents_init(map_level);
	// up ladder
	ents[2].type = ent_ladder_up;
	ents[2].xt = cavity_centers[0][0];
	ents[2].yt = cavity_centers[0][1];
	// down ladder
	ents[1].type = ent_ladder_down;
	ents[1].xt = cavity_centers[8][0];
	ents[1].yt = cavity_centers[8][1];
	// player
	ents[0].type = ent_player;
	ents[0].xt = cavity_centers[0][0] + 1;
	ents[0].yt = cavity_centers[0][1];
	ents[0].state = ent_state_player_controlled;
	ents[0].hp = 100;
	ents[0].dir = rand() % 4;

	// XXX add more empty tiles around room here
	// this will keep chests from blocking corridoros

	for (int i = 1; i < 9; i++) {

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
