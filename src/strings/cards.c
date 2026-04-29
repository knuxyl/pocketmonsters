const char* str_energy[TYPE][LANGUAGE] = {
    [GRASS] = {
        [ENGLISH] = "Grass",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [FIRE] = {
        [ENGLISH] = "Fire",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [WATER] = {
        [ENGLISH] = "Water",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [LIGHTNING] = {
        [ENGLISH] = "Lightning",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [PSYCHIC] = {
        [ENGLISH] = "Psychic",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [FIGHTING] = {
        [ENGLISH] = "Fighting",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [DARKNESS] = {
        [ENGLISH] = "Darkness",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [METAL] = {
        [ENGLISH] = "Metal",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [FAIRY] = {
        [ENGLISH] = "Fairy",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [COLORLESS] = {
        [ENGLISH] = "Colorless",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [NO_TYPE] = {
        [ENGLISH] = "None",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    }
};
const char* str_rarity[RARITY][LANGUAGE] = {
    [COMMON] = {
        [ENGLISH] = "Common ●",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [UNCOMMON] = {
        [ENGLISH] = "Uncommon ◆",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [RARE] = {
        [ENGLISH] = "Rare 🟊",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [HOLOFOIL] = {
        [ENGLISH] = "Holofoil 🟊",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [SHINY] = {
        [ENGLISH] = "Shiny 🟊SH",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [DOUBLE] = {
        [ENGLISH] = "Double Rare 🟊🟊",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [ULTRA] = {
        [ENGLISH] = "Ultra Rare ☆",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [SECRET] = {
        [ENGLISH] = "Secret Rare 🟊H",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [ACE_SPEC] = {
        [ENGLISH] = "Ace-Spec 🟊",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [ILLUSTRATION] = {
        [ENGLISH] = "Illustration 🟊",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [SPECIAL_ILLUSTRATION] = {
        [ENGLISH] = "Special Illustration 🟊🟊",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [MEGA_ATTACK] = {
        [ENGLISH] = "Mega Attack ☆☆",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [HYPER] = {
        [ENGLISH] = "Hyper Rare 🟊🟊🟊",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [MEGA_HYPER] = {
        [ENGLISH] = "Mega Hyper Rare ✧",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [DECK] = {
        [ENGLISH] = "Deck Box",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [PROMO] = {
        [ENGLISH] = "Promotional",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
};

const char* str_stage[STAGE][LANGUAGE] = {
    [BASIC] = {
        [ENGLISH] = "Basic",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [STAGE1] = {
        [ENGLISH] = "Stage 1",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
    [STAGE2] = {
        [ENGLISH] = "Stage 2",
        [JAPANESE] = "",
		[GERMAN] = "",
		[FRENCH] = "",
		[ITALIAN] = "",
		[SPANISH] = "",
		[KOREAN] = "",
		[CHINESE_SIMPLIFIED] = "",
		[CHINESE] = ""
    },
};
