//#include "sans/sans.c"
//#include "fonts/fonts.c"
#include "unifont_otf.c"
void unload_font(Font font) {
	if (IsFontValid(font)) {
		UnloadFont(font);
	}
}

Font load_font(uint16_t font_size) {
	printf("Loading font: %i\n", font_size);
	int codepoints_count;
	int *language_codepoints = LoadCodepoints(codepoints[config.language], &codepoints_count);
	printf("Codepoints: %s\n", codepoints[config.language]);
	Font loaded_font = LoadFontFromMemory(".otf", unifont_otf, unifont_otf_len, font_size, language_codepoints, codepoints_count);
	SetTextureFilter(loaded_font.texture, TEXTURE_FILTER_BILINEAR);
	return loaded_font;
}

void init_font() {
//	change_language(config.language);
};
