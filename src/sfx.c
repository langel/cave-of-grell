

void sfx_attack() {
	audio_bend = 1.0001;
	audio_fade = 0.9996;
	audio_amp = 0.25;
	audio_hertz = (double) (50 + rand() % 400) / 32000.0;
	//printf("%lf %lf %lf \n", audio_hertz, audio_bend, audio_amp);
}

void sfx_death() {
	audio_amp = 0.3;
	audio_fade = 0.99996;
	audio_hertz = 420.0 / 32000.0;
	audio_bend = 0.99991;
	//printf("%lf %lf %lf \n", audio_hertz, audio_bend, audio_amp);
}

void sfx_footstep() {
	if (audio_amp < 0.1) {
		audio_amp = 0.33;
		audio_fade = 0.995;
		audio_bend = 1;
		audio_hertz = (double) (80 + rand() % 20) / 32000.0;
	}
}

void sfx_gold() {
	audio_hertz = (float) (2000 + rand() % 22) / 32000.0;
	audio_amp = 0.25;
	audio_bend = 1.0;
	audio_fade = 0.99989;
}

void sfx_heal() {
	audio_hertz = 42.0 / 32000.0;
	audio_amp = 0.25;
	audio_bend = 1.003;
	audio_fade = 0.99977;
}

void sfx_crown() {
	audio_hertz = (float) (1777 - rand() % 22) / 32000.0;
	audio_amp = 0.3;
	audio_bend = 1.000001;
	audio_fade = 0.9997;
}

void sfx_congration() {
	audio_hertz = (float) (420 + rand() % 22) / 32000.0;
	audio_amp = 0.3333;
	audio_bend = 1.0000025;
	audio_fade = 0.99989;
}
