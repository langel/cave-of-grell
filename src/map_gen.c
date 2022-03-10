

int map_drawing_new = 0;
int map_drawing_stage = 0;

int cavity_centers[9][2]; // cavity id / x,y

void map_draw_new(int map_level) {
	
	// fill map with rocks
	if (map_drawing_stage == 0) {
		printf("drawing level %d map\n", map_level);
		for (int x = 0; x < map_width; x++) {
			for (int y = 0; y < map_height; y++) {
				map_data[map_level][x][y] = 1;
			}
		}
	}

	if (map_drawing_stage > 0 && map_drawing_stage <= 9) {
		SDL_Rect cavity;
		cavity.w = (rand() % (map_width / 4)) + 4;
		cavity.x = 2 + (rand() % (map_width - cavity.w - 4)); 
		cavity.h = (rand() % (map_height / 4)) + 4;
		cavity.y = 2 + (rand() % (map_height - cavity.h - 4)); 
		//printf("%d %d %d %d  ..  ", cavity.x, cavity.y, cavity.w, cavity.h);
		for (int x = cavity.x; x < cavity.x + cavity.w; x++) {
			for (int y = cavity.y; y < cavity.y + cavity.h; y++) {
				map_data[map_level][x][y] = 0;
			}
		}

		// cache cavity center position
		cavity_centers[map_drawing_stage - 1][0] = cavity.x + cavity.w / 2;
		cavity_centers[map_drawing_stage - 1][1] = cavity.y + cavity.h / 2;
		//printf("\nlevel %d cavity %d center x, y : %d, %d\n", map_level, map_drawing_stage, cavity_centers[map_drawing_stage - 1][0], cavity_centers[map_drawing_stage - 1][1]);

		// corridor cut outs between cavities
		if (map_drawing_stage > 1) {
			int target = rand() % (map_drawing_stage - 1);
			//printf("attaching cavity %d to cavity %d\n", map_drawing_stage - 1, target);
			// current cavity
			int ccx = cavity_centers[map_drawing_stage - 1][0];
			int ccy = cavity_centers[map_drawing_stage - 1][1];
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

	map_drawing_stage++;

	if (map_drawing_stage > 10) {
		map_drawing_new = 0;
		map_playfield_render();
		ents_init();
	}
	
	map_view_texture_update(map_level);
}
