
typedef struct {
	int type;
	int dir; // right, up, left, down
	int xt; // tile positions
	int yt;
	int state;
	int hp;
	int collisions;
} ent;

#define ENTS_COUNT 99
ent ents[map_levels][ENTS_COUNT];


#define ent_state_dead 0
#define ent_state_wandering 1
#define ent_state_blocked 2
#define ent_state_dormant 3
#define ent_state_pursuit 4
#define ent_state_flee 5
#define ent_state_player_controlled 6

#define ent_nan 0
#define ent_gnome 1
#define ent_owlbear 2
#define ent_rat 3
#define ent_snake 4
#define ent_key 5
#define ent_coin 6
#define ent_coins 7
#define ent_chest 8
#define ent_chest_emptied 9
#define ent_mimic 10
#define ent_grell 11
#define ent_ladder_up 12
#define ent_ladder_down 13
#define ent_player 14
#define ent_herb 15
#define ent_crown 16
#define ent_player_with_crown 17
#define ent_cockatrice 18
#define ent_crab 19
#define ent_duck 20
#define ent_jackalope 21
#define ent_yonk 22
#define ent_ronk 23
#define ent_gonk 24
#define ent_bonk 25
#define ent_snerv 26

// number of types per level
int map_ent_type_count[9] = { 3, 6, 9,  13, 11, 15,  12, 10, 4 };
// number of ents per level
int map_ents_count[9] = { 5, 24, 28,  32, 16, 24,  56, 88, 1 };
// ent types per level
int map_ent_types[9][16]  = {
	// level 1
	{ ent_rat, ent_rat, ent_herb },
	{ ent_rat, ent_snake, ent_owlbear, ent_herb, ent_coin, ent_herb, ent_jackalope },
	{ ent_rat, ent_snake, ent_owlbear, ent_herb, ent_coin, ent_coins, ent_chest, ent_jackalope, ent_gnome },
	// level 4
	{ ent_rat, ent_snake, ent_gnome, ent_gnome, ent_gnome, ent_herb, ent_herb, ent_coin, ent_coins, ent_chest, ent_key, ent_cockatrice, ent_jackalope },
	{ ent_rat, ent_snake, ent_gnome, ent_herb, ent_coin, ent_coins, ent_cockatrice, ent_cockatrice, ent_jackalope, ent_snerv, ent_snerv },
	{ ent_rat, ent_snake, ent_duck, ent_duck, ent_duck, ent_crab, ent_crab, ent_crab, ent_herb, ent_coin, ent_coins, ent_chest, ent_key, ent_herb, ent_snerv },
	// level 7
	{ ent_rat, ent_grell, ent_grell, ent_grell, ent_grell, ent_coins, ent_chest, ent_yonk, ent_ronk, ent_gonk, ent_bonk, ent_duck },
	{ ent_grell, ent_grell, ent_grell, ent_grell, ent_grell, ent_grell, ent_yonk, ent_ronk, ent_gonk, ent_bonk },
	{ ent_yonk, ent_ronk, ent_gonk, ent_bonk },
};

typedef struct {
	int ent_types_count;
	int ent_types[16];
} map_ents_data_struct;

/*
map_ents_data_struct map_ents_data[map_levels] = {
	{ 2, { ent_rat, ent_snake } },
	{ 8, { ent_coin, ent_rat, ent_snake, ent_owlbear } },
};
*/

typedef struct {
	char name[16];
	int state;
	int hp;
	int speed;
	int dexterity;
	int damage_base;
	int damage_rand;
	char verb[16];
	SDL_Rect sprite;
	int xp;
} ent_type;


ent_type ent_types[42] = {
	{ "nan", ent_state_dead, 0, 0, 0, 0, 0, "does not exist", 
		{ 0, 0, 20, 40 }, 0 },
	{ "gnome", 
		1, 25, 8, 10, 
		3, 5, "cunnings", { 20, 0, 13, 40 }, 56
	},
	{ "owlbear",
		1, 59, 14, 7, 
		5, 11, "claws", { 60, 0, 20, 40 }, 777
	},
	{ "rat",
		1, 4, 16, 8, 
		1, 3, "bites", { 0, 40, 4, 4 }, 22
	},
	{ "snake",
		1, 6, 11, 15, 2, 4, "sproings", 
		{ 10, 40, 10, 10}, 33
	},
	{ "key", ent_state_dormant, 
		0, 0, 0, 0, 0, "unlocks",
		{ 0, 45, 10, 4 }, 0 },
	{ "coin",
		ent_state_dormant, 0, 0, 0, 0, 0, "plinks",
		{ 0, 52, 7, 3 }, 0 },
	{ "coins",
		ent_state_dormant, 0, 0, 0, 0, 0, "changles",
		{ 10, 51, 7, 7 }, 0 },
	{ "chest",
		ent_state_dormant, 0, 0, 0, 0, 0, "opens",
		{ 20, 40, 20, 20 }, 0 },
	{ "empty chest", ent_state_dead, 0, 0, 0, 0, 0, "sits",
		{ 40, 40, 20, 20 }, 0 },
	{ "mimic", ent_state_wandering, 
		43, 12, 12, 3, 8, "mawls",
		{ 60, 40, 20, 20 }, 120 },
	{ "grell", ent_state_wandering, 
		111, 13, 15, 7, 23, "pecks",
		{ 100, 0, 40, 41 }, 1225 },
	{ "ladder_up", ent_state_dormant, 
		0, 0, 0, 0, 0, "ascends",
		{ 80, 40, 20, 20 }, 13 },
	{ "ladder_down", ent_state_dormant, 
		0, 0, 0, 0, 0, "descends",
		{ 100, 42, 20, 18 }, 13 },
	{ "player", ent_state_wandering,	42, 10, 10, 2, 9, "quacks", 
		{ 100, 60, 20, 20 }, 0
	},
	{ "herb", ent_state_dormant, 0, 0, 0, 0, 0, "heals", 
		{ 0, 60, 20, 9 }, 0
	},
	{ "crown", ent_state_dormant, 0, 0, 0, 0, 0, "elevates", 
		{ 20, 60, 20, 20 }, 0
	},
	{ "player_w_crown", ent_state_wandering, 42, 10, 10, 2, 9, "quacks", 
		{ 100, 80, 20, 40 }, 0
	},
	{ "cockatrice", 1, 27, 8, 10, 
		4, 4, "breathes", { 60, 60, 20, 20 }, 111
	},
	{ "crab", 1, 5, 8, 10, 
		1, 5, "pincers", { 80, 60, 20, 20 }, 23
	},
	{ "homunculus", 1, 13, 8, 10, 
		3, 25, "fists", { 0, 0, 20, 40 }, 37
	},
	{ "jackalope", 1, 33, 8, 10, 
		1, 6, "gores", { 120, 50, 20, 30 }, 56
	},
	{ "yonk", 1, 3, 8, 10, 
		1, 3, "yonks", { 140, 40, 20, 20 }, 11
	},
	{ "ronk", 1, 3, 8, 10, 
		1, 3, "ronks", { 160, 40, 20, 20 }, 11
	},
	{ "gonk", 1, 3, 8, 10, 
		1, 3, "gonks", { 140, 60, 20, 20 }, 11
	},
	{ "bonk", 1, 3, 8, 10, 
		1, 3, "bonks", { 160, 60, 20, 20 }, 11
	},
	{ "snerv", 1, 11, 8, 10, 
		1, 7, "swerves", { 0, 80, 10, 20 }, 27
	},
};




