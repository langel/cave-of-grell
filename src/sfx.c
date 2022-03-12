

void sfx_attack() {
	audio_bend = 1.0001;
	audio_fade = 0.9996;
	audio_amp = 0.25;
	audio_hertz = (double) (50 + rand() % 400) / 32000.0;
	//printf("%lf %lf %lf \n", audio_hertz, audio_bend, audio_amp);
}

void sfx_death() {
	audio_amp = 0.3;
	audio_fade = 0.999996;
	audio_hertz = 420.0 / 32000.0;
	audio_bend = 0.99991;
	//printf("%lf %lf %lf \n", audio_hertz, audio_bend, audio_amp);
}

void sfx_gold() {
	audio_hertz = 2000.0 / 32000.0;
	audio_amp = 0.2;
	audio_bend = 1.0;
	audio_fade = 0.99989;
}
