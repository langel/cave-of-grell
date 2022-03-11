


// map matrix
// map_data[level][row/x][col/y]

#define map_levels 9
#define map_width 128
#define map_height 80

int map_data[map_levels][map_width][map_height];

int map_drawing_new = 0;
int map_drawing_stage = 0;


int cavity_centers[9][2]; // cavity id / x,y
