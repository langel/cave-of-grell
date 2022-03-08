
#define FONT_MAX_LEN 512

typedef struct {
	int size;
	int width;
	int height;
	SDL_Rect char_rect[FONT_MAX_LEN];
	SDL_Rect shit_rect;
	SDL_Texture * texture;
} font;

typedef struct {
	SDL_Rect rect;
	SDL_Texture * texture;
} font_text_rendered;


font fonts_load(char *name, int size, SDL_Renderer * renderer) {
	font f;
	f.size = size;
	char filename[] = "fonts/";
	strcat(filename, name);
	printf("loading : %s\n", filename);
	// load graphic
	char font_filename[32];
	strcpy(font_filename, filename);
	strcat(font_filename, ".bmp");
	SDL_Surface * image = SDL_LoadBMP(font_filename);
	f.shit_rect.x = 0;
	f.shit_rect.y = 0;
	f.shit_rect.w = image->w;
	f.shit_rect.h = image->h;
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0, 0)); 
	f.texture = SDL_CreateTextureFromSurface(renderer, image);
	printf("%s\n", SDL_GetError());
	SDL_FreeSurface(image);
	// load data
	char data_filename[32];
	strcpy(data_filename, filename);
	strcat(data_filename, ".dat");
	FILE * data_file = fopen(data_filename, "r");
	if (data_file == NULL) {
		printf("failed access to : %s\n", data_filename);
	}
	unsigned char buffer[FONT_MAX_LEN];
	/* Read in 8-bit numbers into the buffer */
	size_t bytes_read = 0;
	bytes_read = fread(buffer, sizeof(unsigned char), FONT_MAX_LEN, data_file);
	printf("bytes read : %zu\n", bytes_read);
	// Note: sizeof(unsigned char) is for emphasis
	int x = 0;
	int y = 0;
	f.width = buffer[8];
	f.height = buffer[12];
	int first_char = buffer[16];
	int header_length = 17;
	for (int i = first_char; i < bytes_read - header_length; i++) {
		int width = buffer[i + header_length];
//		width = size;
		if (x + f.width > 255) {
			x = 0;
			y += f.height;
		}
		if (i % 8 == 0) printf("\n");
		printf("%d\t", width);
		f.char_rect[i].x = x;
		f.char_rect[i].y = y;
		f.char_rect[i].w = width;
		f.char_rect[i].h = size;
		x += f.width;
	}
	fclose(data_file);
	printf("\n\nx, y, 1st_char : %d, %d, %d\n", f.width, f.height, first_char);
	return f;
}

font_text_rendered fonts_render_text(char *text, font f, SDL_Renderer * renderer) {
	int length = strlen(text);
	SDL_Texture * output = texture_create_generic(renderer, length * f.width, f.height);
	SDL_SetRenderTarget(renderer, output);
	SDL_Rect char_buff = { 0, 0, f.width, f.height };
	for (int i = 0; i < length; i++) {
		int char_id = (int) text[i];
		printf(" %3d ", char_id);
		int width = f.char_rect[char_id].w;
		char_buff.w = width;
		SDL_RenderCopy(renderer, f.texture, &f.char_rect[char_id], &char_buff);
		char_buff.x += width;
	}
	font_text_rendered render;
	render.texture = output;
	SDL_QueryTexture(render.texture, NULL, NULL, &render.rect.w, &render.rect.h);
	printf("\n render w, h : %d, %d\n", render.rect.w, render.rect.h);
	render.rect.x = render.rect.y = 0;
	return render;
}
