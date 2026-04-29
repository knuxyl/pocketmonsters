const struct theme themes[THEME] = {
	[LIGHT_THEME] = {
		.dark = false,
		.background = (Color) {255,255,255,255},
		.tr_background = (Color) {255,255,255,51},
		.text = (Color) {0,0,0,255},
		.disabled = (Color) {128,128,128,255},
		.hover = (Color) {0,0,0,255},
		//.hover = (Color) {184,3,0,255}
	},
	[DARK_THEME] = {
		.dark = true,
		.background = (Color) {16,16,16,255},
		.tr_background = (Color) {16,16,16,51},
		.text = (Color) {255,255,255,255},
		.disabled = (Color) {128,128,128,255},
		//.hover = (Color) {184,3,0,255}
		.hover = (Color) {255,255,255,255},
	},
	[GB_LIGHT_THEME] = {
		.dark = false,
		.background = (Color) {224,248,207,255},
		.tr_background = (Color) {224,248,207,85},
		.text = (Color) {48,104,80,255},
		.disabled = (Color) {136,176,143,255},
		//.hover = (Color) {184,3,0,255}
		.hover = (Color) {48,104,80,255},
	},
	[GB_DARK_THEME] = {
		.dark = true,
		.background = (Color) {48,104,80,255},
		.tr_background = (Color) {48,104,80,85},
		.text = (Color) {224,248,207,255},
		.disabled = (Color) {136,176,143,255},
		//.hover = (Color) {184,3,0,255}
		.hover = (Color) {224,248,207,255},
	},
};
