
#define action_log_len 32

char action_log_0[3][action_log_len];
char action_log_1[3][action_log_len];
char action_log_2[3][action_log_len];

char action_log_temp[3][action_log_len];

void action_log_update() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < action_log_len; j++) { 
			action_log_2[i][j] = action_log_1[i][j];
			action_log_1[i][j] = action_log_0[i][j];
			action_log_0[i][j] = action_log_temp[i][j];
		}
		sprintf(action_log_temp[i], "");
	}
};
