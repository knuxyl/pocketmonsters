#include "theme/background.c"
const Color TRANSPARENT = (Color) {0,0,0,0};
const Color themes[THEMES][THEME_MODES][THEME_COLORS] = {
	[THEME_MONO] = {
		[THEME_DARK] = {
			[COLOR_BACKGROUND] = (Color) {0,0,0,255},
			[COLOR_TEXT] = (Color) {255,255,255,255},

			[COLOR_SELECT] = (Color) {192,192,192,255},
			[COLOR_INVALID] = (Color) {64,64,64,255},
		},
		[THEME_LIGHT] = {
			[COLOR_BACKGROUND] = (Color) {255,255,255,255},
			[COLOR_TEXT] = (Color) {0,0,0,255},

			[COLOR_SELECT] = (Color) {64,64,64,255},
			[COLOR_INVALID] = (Color) {192,192,192,255},
		}
	},
	[THEME_CHARIZARD] = {
		[THEME_DARK] = {
			[COLOR_BACKGROUND] = (Color) {131,49,24,255},
			[COLOR_TEXT] = (Color) {238,222,123,255},

			[COLOR_SELECT] = (Color) {205,82,65,255},
			[COLOR_INVALID] = (Color) {238,131,41,255},
		},
		[THEME_LIGHT] = {
			[COLOR_BACKGROUND] = (Color) {238,222,123,255},
			[COLOR_TEXT] = (Color) {131,49,24,255},

			[COLOR_SELECT] = (Color) {238,131,41,255},
			[COLOR_INVALID] = (Color) {205,82,65,255},
		}
	},
	[THEME_BLASTOISE] = {
		[THEME_DARK] = {
			[COLOR_BACKGROUND] = (Color) {8,57,98,255},
			[COLOR_TEXT] = (Color) {148,172,230,255},

			[COLOR_SELECT] = (Color) {32,98,172,255},  //darkest on dark
			[COLOR_INVALID] = (Color) {90,139,205,255},
		},
		[THEME_LIGHT] = {
			[COLOR_BACKGROUND] = (Color) {148,172,230,255},
			[COLOR_TEXT] = (Color) {8,57,98,255},

			[COLOR_SELECT] = (Color) {90,139,205,255},
			[COLOR_INVALID] = (Color) {32,98,172,255},
		}
	},
	[THEME_VENUSAUR] = {
		[THEME_DARK] = {
			[COLOR_BACKGROUND] = (Color) {16,82,65,255},
			[COLOR_TEXT] = (Color) {90,213,197,255},

			[COLOR_SELECT] = (Color) {16,123,106,255},
			[COLOR_INVALID] = (Color) {32,180,156,255},
		},
		[THEME_LIGHT] = {
			[COLOR_BACKGROUND] = (Color) {90,213,197,255},
			[COLOR_TEXT] = (Color) {16,82,65,255},

			[COLOR_SELECT] = (Color) {32,180,156,255},
			[COLOR_INVALID] = (Color) {16,123,106,255},
		}
	},
	[THEME_AERODACTYL] = {
		[THEME_DARK] = {
			[COLOR_BACKGROUND] = (Color) {49,24,106,255},
			[COLOR_TEXT] = (Color) {172,131,222,255},

			[COLOR_SELECT] = (Color) {115,82,148,255},
			[COLOR_INVALID] = (Color) {148,98,205,255},
		},
		[THEME_LIGHT] = {
			[COLOR_BACKGROUND] = (Color) {172,131,222,255},
			[COLOR_TEXT] = (Color) {49,24,106,255},

			[COLOR_SELECT] = (Color) {148,98,205,255},
			[COLOR_INVALID] = (Color) {115,82,148,255},
		}
	},
	[THEME_DRAGONITE] = {
		[THEME_DARK] = {
			[COLOR_BACKGROUND] = (Color) {90,57,32,255},
			[COLOR_TEXT] = (Color) {246,189,90,255},

			[COLOR_SELECT] = (Color) {222,115,57,255},
			[COLOR_INVALID] = (Color) {238,156,57,255},
		},
		[THEME_LIGHT] = {
			[COLOR_BACKGROUND] = (Color) {246,189,90,255},
			[COLOR_TEXT] = (Color) {90,57,32,255},

			[COLOR_SELECT] = (Color) {238,156,57,255},
			[COLOR_INVALID] = (Color) {222,115,57,255},
		}
	},
	[THEME_MEW] = {
		[THEME_DARK] = {
			[COLOR_BACKGROUND] = (Color) {90,41,82,255},
			[COLOR_TEXT] = (Color) {255,180,213,255},

			[COLOR_SELECT] = (Color) {180,98,148,255},
			[COLOR_INVALID] = (Color) {238,131,180,255},
		},
		[THEME_LIGHT] = {
			[COLOR_BACKGROUND] = (Color) {255,180,213,255},
			[COLOR_TEXT] = (Color) {90,41,82,255},

			[COLOR_SELECT] = (Color) {238,131,180,255},
			[COLOR_INVALID] = (Color) {180,98,148,255},
		}
	},
	[THEME_SCYTHER] = {
		[THEME_DARK] = {
			[COLOR_BACKGROUND] = (Color) {65,90,32,255},
			[COLOR_TEXT] = (Color) {189,230,115,255},

			[COLOR_SELECT] = (Color) {90,156,74,255},
			[COLOR_INVALID] = (Color) {139,205,115,255},
		},
		[THEME_LIGHT] = {
			[COLOR_BACKGROUND] = (Color) {189,230,115,255},
			[COLOR_TEXT] = (Color) {65,90,32,255},

			[COLOR_SELECT] = (Color) {139,205,115,255},
			[COLOR_INVALID] = (Color) {90,156,74,255},
		}
	},
};

/*
[COLOR_BACKGROUND] = (Color) {,,,},
[COLOR_TEXT] = (Color) {,,,},
[COLOR_BUTTON] = (Color) {,,,},
[COLOR_INVALID] = (Color) {,,,},
[COLOR_OK] = (Color) {,,,},
[COLOR_DISABLED] = (Color) {,,,},
*/
