const struct theme themes[THEME] = {
	[LIGHT_THEME] = {
		.dark = false,
		.background = (Color) {255,255,255,255},
		.tr_background = (Color) {255,255,255,128},
		.text = (Color) {0,0,0,255},
		.tr_text = (Color) {0,0,0,128},
		.disabled = (Color) {128,128,128,255},
		.hover = (Color) {139,197,205,255},
		.invalid = (Color) {246,164,0,255},
		.ok = (Color) {115,172,49,255}
	},
	[DARK_THEME] = {
		.dark = true,
		.background = (Color) {16,16,16,255},
		.tr_background = (Color) {16,16,16,128},
		.text = (Color) {255,255,255,255},
		.tr_text = (Color) {255,255,255,128},
		.disabled = (Color) {128,128,128,255},
		.hover = (Color) {41,115,131,255},
		.invalid = (Color) {139,41,0,255},
		.ok = (Color) {82,98,41,255}
	},
	[GB_LIGHT_THEME] = {
		.dark = false,
		.background = (Color) {224,248,207,255},
		.tr_background = (Color) {224,248,207,128},
		.text = (Color) {48,104,80,255},
		.tr_text = (Color) {48,104,80,128},
		.disabled = (Color) {136,176,143,255},
		.hover = (Color) {139,197,205,255},
		.invalid = (Color) {246,164,0,255},
		.ok = (Color) {115,172,49,255}
	},
	[GB_DARK_THEME] = {
		.dark = true,
		.background = (Color) {48,104,80,255},
		.tr_background = (Color) {48,104,80,128},
		.text = (Color) {224,248,207,255},
		.tr_text = (Color) {224,248,207,128},
		.disabled = (Color) {136,176,143,255},
		.hover = (Color) {41,115,131,255},
		.invalid = (Color) {139,41,0,255},
		.ok = (Color) {82,98,41,255}
	},
};
