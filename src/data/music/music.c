#include "gbc/blue_gbs.c"
#include "gbc/card2_gbs.c"
#include "gbc/card_gbs.c"
#include "gbc/crystal1_gbs.c"
#include "gbc/crystal2_gbs.c"
#include "gbc/crystal_gbs.c"
#include "gbc/gold1_gbs.c"
#include "gbc/gold_gbs.c"
#include "gbc/green_gbs.c"
#include "gbc/pinball_gbs.c"
#include "gbc/puzzle_gbs.c"
#include "gbc/red_gbs.c"
#include "gbc/silver1_gbs.c"
#include "gbc/silver_gbs.c"
#include "gbc/yellow_gbs.c"
const struct embedded embedded_music[] = {
	(const struct embedded) {
		.data = blue_gbs,
		.len = blue_gbs_len,
	},
	(const struct embedded) {
		.data = card2_gbs,
		.len = card2_gbs_len,
	},
	(const struct embedded) {
		.data = card_gbs,
		.len = card_gbs_len,
	},
	(const struct embedded) {
		.data = crystal1_gbs,
		.len = crystal1_gbs_len,
	},
	(const struct embedded) {
		.data = crystal2_gbs,
		.len = crystal2_gbs_len,
	},
	(const struct embedded) {
		.data = crystal_gbs,
		.len = crystal_gbs_len,
	},
	(const struct embedded) {
		.data = gold1_gbs,
		.len = gold1_gbs_len,
	},
	(const struct embedded) {
		.data = gold_gbs,
		.len = gold_gbs_len,
	},
	(const struct embedded) {
		.data = green_gbs,
		.len = green_gbs_len,
	},
	(const struct embedded) {
		.data = pinball_gbs,
		.len = pinball_gbs_len,
	},
	(const struct embedded) {
		.data = puzzle_gbs,
		.len = puzzle_gbs_len,
	},
	(const struct embedded) {
		.data = red_gbs,
		.len = red_gbs_len,
	},
	(const struct embedded) {
		.data = silver1_gbs,
		.len = silver1_gbs_len,
	},
	(const struct embedded) {
		.data = silver_gbs,
		.len = silver_gbs_len,
	},
	(const struct embedded) {
		.data = yellow_gbs,
		.len = yellow_gbs_len,
	},
};
const uint8_t music_count = sizeof(embedded_music)/sizeof(embedded_music[0]);
