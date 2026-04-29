#include "sc.c"
#include "kr.c"
#include "jp.c"
#include "en.c"
#include "ch.c"
const struct embedded* fonts[LANGUAGE] = {
	[CHINESE] = &font_ch,
	[ENGLISH] = &font_en,
	[JAPANESE] = &font_jp,
	[KOREAN] = &font_kr,
	[CHINESE_SIMPLIFIED] = &font_sc,
	[GERMAN] = &font_en,
	[FRENCH] = &font_en,
	[ITALIAN] = &font_en,
	[SPANISH] = &font_en,
};
