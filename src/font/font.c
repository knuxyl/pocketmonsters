//#include "sans/sans.c"
#include "fonts/fonts.c"

void unload_font(Font font) {
	if (IsFontValid(font)) {
		UnloadFont(font);
	}
}

Font load_font(uint16_t font_size, uint8_t language) {
	int codepoints_count;
	int *language_codepoints = LoadCodepoints(codepoints[language], &codepoints_count);
	Font loaded_font = LoadFontFromMemory(".ttf", fonts[language]->data, fonts[language]->len, font_size, language_codepoints, codepoints_count);
	SetTextureFilter(loaded_font.texture, TEXTURE_FILTER_BILINEAR);
	return loaded_font;
}

void init_font() {
//	change_language(config.language);
};
