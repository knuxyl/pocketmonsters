// ---------------------------------- //
// International
// Wizards of the Coast
// Base Set
// 1
// Alakazam
// ---------------------------------- //

// Function to check if move can be used
bool intern_wotc_bs_44_move1_condition(const struct database_move* move) {
	printf("Checked %s\n", move->name[ENGLISH]);
	return true;
};

// Function to run when move is used
void intern_wotc_bs_44_move1_execute(const struct database_move* move) {
    printf("Used %s\n", move->name[ENGLISH]);
};

// Struct of move
const struct database_move intern_wotc_bs_44_move1 = {
    // Char because sometimes has + or x, calculation is done in execute()
    .damage = "30",
	.name = (const char* [LANGUAGE]) {
		[ENGLISH] = "Confuse Ray",
        [JAPANESE] = "",
        [GERMAN] = "",
        [FRENCH] = "",
        [ITALIAN] = "",
        [SPANISH] = "",
        [KOREAN] = "",
        [CHINESE_SIMPLIFIED] = "",
        [CHINESE] = ""
	},
	.description = (const char* [LANGUAGE]) {
		[ENGLISH] = "Flip a coin. If heads, the Defending Pokémon is now Confused.",
        [JAPANESE] = "",
        [GERMAN] = "",
        [FRENCH] = "",
        [ITALIAN] = "",
        [SPANISH] = "",
        [KOREAN] = "",
        [CHINESE_SIMPLIFIED] = "",
        [CHINESE] = ""
	},
	.energy_cost = (const uint8_t [TYPE]) {
        [GRASS] = 0,
        [FIRE] = 0,
        [WATER] = 0,
        [LIGHTNING] = 0,
        [PSYCHIC] = 3,
        [FIGHTING] = 0,
        [DARKNESS] = 0,
        [METAL] = 0,
        [FAIRY] = 0,
        [COLORLESS] = 0,
        [NO_TYPE] = 0
	},
	.condition = &intern_wotc_bs_44_move1_condition,
	.execute = &intern_wotc_bs_44_move1_execute,
};

// Array of all move structs
const struct database_move* intern_wotc_bs_44_moves[] = {
	&intern_wotc_bs_44_move1,
};

// Function to check if ability can be used
bool intern_wotc_bs_44_ability_condition(const struct database_ability* ability) {
	printf("Checked %s\n", ability->name[ENGLISH]);
	return true;
};

// Function to run for ability
void intern_wotc_bs_44_ability_execute(const struct database_ability* ability) {
    printf("Used %s\n", ability->name[ENGLISH]);
};

// Struct of ability
const struct database_ability intern_wotc_bs_44_ability = {
	.name = (const char* [LANGUAGE]) {
		[ENGLISH] = "Damage Swap",
        [JAPANESE] = "",
        [GERMAN] = "",
        [FRENCH] = "",
        [ITALIAN] = "",
        [SPANISH] = "",
        [KOREAN] = "",
        [CHINESE_SIMPLIFIED] = "",
        [CHINESE] = ""
	},
	.description = (const char* [LANGUAGE]) {
		[ENGLISH] = "As often as you like during your turn (before your attack), you may move 1 damage counter from 1 of your Pokémon to another as long as you don't Knock Out that Pokémon. This power can't be used if Alakazam is Asleep, Confused, or Paralyzed.",
        [JAPANESE] = "",
        [GERMAN] = "",
        [FRENCH] = "",
        [ITALIAN] = "",
        [SPANISH] = "",
        [KOREAN] = "",
        [CHINESE_SIMPLIFIED] = "",
        [CHINESE] = ""
	},
	.condition = &intern_wotc_bs_44_ability_condition,
	.execute = &intern_wotc_bs_44_ability_execute,
};

// Struct to contain everything about the card
const struct database_card intern_wotc_bs_44= {
	.region = INTERNATIONAL,
	.series = INTERN_WOTC,
	.set = WOTC_BS,
	.number = 1,
	.pokemon = ALAKAZAM,
    // These are just for special evolution requirements (Dark Charmeleon, Raichu EX)
	.name_prefix = NO_PREFIX,
	.name_suffix = NO_SUFFIX,
	//.pokemon = ALAKAZAM,
	.evolve_from = KADABRA,
    // These are just for special evolution requirements (Dark Charmeleon, Raichu EX)
	.evolve_prefix = NO_PREFIX,
	.evolve_suffix = NO_SUFFIX,
	.weakness = (const struct database_damage_modifier) {
		.type = PSYCHIC,
        .mod = MOD_MULTIPLY,
        .value = 2,
	},
	.information = (const char* [LANGUAGE]) {
		[ENGLISH] = "Its brain can outperform a supercomputer. Its intelligence quotient is said to be 5000.",
        [JAPANESE] = "",
        [GERMAN] = "",
        [FRENCH] = "",
        [ITALIAN] = "",
        [SPANISH] = "",
        [KOREAN] = "",
        [CHINESE_SIMPLIFIED] = "",
        [CHINESE] = ""
	},
	.description = (const char* [LANGUAGE]) {
		[ENGLISH] = "Psi Pokémon",
        [JAPANESE] = "",
        [GERMAN] = "",
        [FRENCH] = "",
        [ITALIAN] = "",
        [SPANISH] = "",
        [KOREAN] = "",
        [CHINESE_SIMPLIFIED] = "",
        [CHINESE] = ""
	},
	.type = PSYCHIC,
	.rarity = HOLOFOIL,
	.stage = STAGE2,
	.hp = 80,
	// This isn't automatically set by card language, it's read by app setting
    .height = (const char* [MEASUREMENT]) {
    		[IMPERIAL] = "4' 11\"",
            [METRIC] = "1.5m",
    	},
    // This isn't automatically set by card language, it's read by app setting
    .weight = (const char* [MEASUREMENT]) {
    		[IMPERIAL] = "106 lbs.",
            [METRIC] = "48Kg",
    	},
	.resistance = (const struct database_damage_modifier) {
		.type = NO_TYPE,
	},
	.retreat_cost = (const uint8_t[TYPE]) {
		[GRASS] = 0,
        [FIRE] = 0,
        [WATER] = 0,
        [LIGHTNING] = 0,
        [PSYCHIC] = 0,
        [FIGHTING] = 0,
        [DARKNESS] = 0,
        [METAL] = 0,
        [FAIRY] = 0,
        [COLORLESS] = 3,
        [NO_TYPE] = 0
	},
	.moves = intern_wotc_bs_44_moves,
	.move_count = sizeof(intern_wotc_bs_44_moves)/sizeof(intern_wotc_bs_44_moves[0]),
	.ability = &intern_wotc_bs_44_ability,
    .prize = 1,
    // Even Japanese cards use english letters for names
    .illustrator = "Ken Sugimori",
	.images = (const struct embedded*[LANGUAGE]) {
		[ENGLISH] = &(const struct embedded) {
			.data = intern_wotc_bs_44_en_png,
			.len = intern_wotc_bs_44_en_png_len,
		},
	},
	// Sometimes card will have like 80A/70 so cant store as int
	.printed_number = "1/102"
};
