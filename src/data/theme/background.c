#include "theme_charizard_png.c"
#include "theme_blastoise_png.c"
#include "theme_venusaur_png.c"
#include "theme_dragonite_png.c"
#include "theme_mew_png.c"
#include "theme_scyther_png.c"
#include "theme_aerodactyl_png.c"
#include "theme_alakazam_png.c"

struct embedded backgrounds[THEMES] = {
	[THEME_MONO] = {.data = theme_alakazam_png, .len = theme_alakazam_png_len},
	[THEME_CHARIZARD] = {.data = theme_charizard_png, .len = theme_charizard_png_len},
	[THEME_VENUSAUR] = {.data = theme_venusaur_png, .len = theme_venusaur_png_len},
	[THEME_BLASTOISE] = {.data = theme_blastoise_png, .len = theme_venusaur_png_len},
	[THEME_DRAGONITE] = {.data = theme_dragonite_png, .len = theme_dragonite_png_len},
	[THEME_MEW] = {.data = theme_mew_png, .len = theme_mew_png_len},
	[THEME_SCYTHER] = {.data = theme_scyther_png, .len = theme_scyther_png_len},
	[THEME_AERODACTYL] = {.data = theme_aerodactyl_png, .len = theme_aerodactyl_png_len},
};
