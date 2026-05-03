const Color TRANSPARENT = (Color) {0,0,0,0};
const struct theme themes[THEME] = {
	[LIGHT_THEME] = {
		.dark = false,
		.colors = {
			[COLOR_BACKGROUND] = (Color) {255,255,255,255},
			[COLOR_TR_BACKGROUND] = (Color) {255,255,255,128},
			[COLOR_TEXT] = (Color) {0,0,0,255},
			[COLOR_TR_TEXT] = (Color) {0,0,0,128},
			[COLOR_DISABLED] = (Color) {128,128,128,255},
			[COLOR_HOVER] = (Color) {139,197,205,255},
			[COLOR_INVALID] = (Color) {246,164,0,255},
			[COLOR_OK] = (Color) {115,172,49,255},
			[COLOR_BUTTON] = (Color) {139,197,205,255}
		}
	},
	[DARK_THEME] = {
		.dark = true,
		.colors = {
			[COLOR_BACKGROUND] = (Color) {16,16,16,255},
			[COLOR_TR_BACKGROUND] = (Color) {16,16,16,128},
			[COLOR_TEXT] = (Color) {255,255,255,255},
			[COLOR_TR_TEXT] = (Color) {255,255,255,128},
			[COLOR_DISABLED] = (Color) {128,128,128,255},
			[COLOR_HOVER] = (Color) {41,115,131,255},
			[COLOR_INVALID] = (Color) {139,41,0,255},
			[COLOR_OK] = (Color) {82,98,41,255},
			[COLOR_BUTTON] = (Color) {41,115,131,255}
		}
	},
	[GB_LIGHT_THEME] = {
		.dark = false,
		.colors = {
			[COLOR_BACKGROUND] = (Color) {224,248,207,255},
			[COLOR_TR_BACKGROUND] = (Color) {224,248,207,128},
			[COLOR_TEXT] = (Color) {48,104,80,255},
			[COLOR_TR_TEXT] = (Color) {48,104,80,128},
			[COLOR_DISABLED] = (Color) {136,176,143,255},
			[COLOR_HOVER] = (Color) {139,197,205,255},
			[COLOR_INVALID] = (Color) {246,164,0,255},
			[COLOR_OK] =(Color) {115,172,49,255},
			[COLOR_BUTTON]= (Color) {139,197,205,255}
		}
	},
	[GB_DARK_THEME] = {
		.dark = true,
		.colors = {
			[COLOR_BACKGROUND] = (Color) {48,104,80,255},
			[COLOR_TR_BACKGROUND] = (Color) {48,104,80,128},
			[COLOR_TEXT] = (Color) {224,248,207,255},
			[COLOR_TR_TEXT] = (Color) {224,248,207,128},
			[COLOR_DISABLED] = (Color) {136,176,143,255},
			[COLOR_HOVER] = (Color) {41,115,131,255},
			[COLOR_INVALID] = (Color) {139,41,0,255},
			[COLOR_OK] = (Color) {82,98,41,255},
			[COLOR_BUTTON] = (Color) {41,115,131,255}
		}
	},
};
