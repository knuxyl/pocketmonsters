//#include "images/logo_png.c"
//#include "images/icon_png.c"
#include "card_images/card_images.c"
#include "cards/cards.c"
//#include "boosters/boosters.c"

const struct database_set intern_wotc_bs = {
	.name = (const char* [LANGUAGE]) {
        [ENGLISH] = "Base Set",
        [JAPANESE] = "拡張パック",
        [GERMAN] = "",
        [FRENCH] = "",
        [ITALIAN] = "",
        [SPANISH] = "",
        [KOREAN] = "",
        [CHINESE_SIMPLIFIED] = "",
        [CHINESE] = ""
    },
	.released = 0,
	.cards = intern_wotc_bs_cards,
	.card_count = sizeof(intern_wotc_bs_cards)/sizeof(intern_wotc_bs_cards[0]),
};
