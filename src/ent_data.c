
typedef struct {
	int type;
	int dir; // right, up, left, down
	int xt; // tile positions
	int yt;
	int state;
	int hp;
	int collisions;
} ent;

#define ENTS_COUNT 64
ent ents[ENTS_COUNT];


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
		{ 0, 0, 0, 0 }, 0 },
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
	{ "empty chest",
		ent_state_dormant, 0, 0, 0, 0, 0, "sits",
		{ 40, 40, 20, 20 }, 0 },
	{ "mimic", ent_state_wandering, 
		43, 12, 12, 3, 8, "mawls",
		{ 60, 40, 20, 20 }, 120 },
	{ "grell", ent_state_wandering, 
		111, 13, 15, 7, 23, "pecks",
		{ 100, 0, 40, 40 }, 1225 },
	{ "ladder_up", ent_state_dormant, 
		0, 0, 0, 0, 0, "ascends",
		{ 80, 40, 20, 20 }, 13 },
	{ "ladder_down", ent_state_dormant, 
		0, 0, 0, 0, 0, "descends",
		{ 100, 40, 20, 20 }, 13 },
	{ "player", ent_state_wandering,
		42, 10, 10, 2, 9, "fists", 
		{ 0, 0, 20, 40 }, 0
	},
};




