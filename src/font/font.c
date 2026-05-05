//#include "sans/sans.c"
//#include "fonts/fonts.c"
#include "font_unito_jp_ttf.c"
//#include "font_unito_sc_ttf.c"
//#include "font_unito_ch_ttf.c"
//#include "font_unito_kr_ttf.c"
void unload_font(Font font) {
	if (IsFontValid(font)) {
		UnloadFont(font);
	}
}

struct embedded fonts[LANGUAGE] = {
	[ENGLISH] = {.data = font_unito_jp_ttf, .len = font_unito_jp_ttf_len},
	[JAPANESE] = {.data = font_unito_jp_ttf, .len = font_unito_jp_ttf_len},
	[GERMAN] = {.data = font_unito_jp_ttf, .len = font_unito_jp_ttf_len},
	[FRENCH] = {.data = font_unito_jp_ttf, .len = font_unito_jp_ttf_len},
	[ITALIAN] = {.data = font_unito_jp_ttf, .len = font_unito_jp_ttf_len},
	[SPANISH] = {.data = font_unito_jp_ttf, .len = font_unito_jp_ttf_len},
	[KOREAN] = {.data = font_unito_jp_ttf, .len = font_unito_jp_ttf_len},
	[CHINESE_SIMPLIFIED] = {.data = font_unito_jp_ttf, .len = font_unito_jp_ttf_len},
	[CHINESE] = {.data = font_unito_jp_ttf, .len = font_unito_jp_ttf_len},
};

Font load_font(uint16_t font_size) {
	int codepoints_count;
	int *language_codepoints = LoadCodepoints(codepoints[config.language], &codepoints_count);
	Font loaded_font = LoadFontFromMemory(".ttf", fonts[config.language].data, fonts[config.language].len, font_size, language_codepoints, codepoints_count);
	UnloadCodepoints(language_codepoints);
	return loaded_font;
}

void init_font() {

};
