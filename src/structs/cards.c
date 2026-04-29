struct database_move;
struct database_ability;
struct database_card;

// Notes
// using char** vs char*[] seems counter intuitive but it allows for significant space saving when dealing with hundreds of thousands of cards, i think. i'll need to revisit this idea, but i believe i have to do it this way is a couple of scenarios because the array size is dynamic.

typedef void (*function_move)(const struct database_move*);
typedef void (*function_ability)(const struct database_ability*);
typedef bool (*function_move_condition)(const struct database_move*);
typedef bool (*function_ability_condition)(const struct database_ability*);

struct database_booster {
    const struct database_card* common;
    const struct database_card* uncommon;
    const struct database_card* rare;
    const struct database_card* energy;
    const struct embedded* image;
};

struct database_damage_modifier {
    const uint8_t type;
    const uint8_t mod;
    const uint8_t value;
};

struct database_region {
	const char** name;
	const struct database_serie** series;
	const uint series_count;
};

struct database_serie {
	const char** name;
    const uint8_t generation;
	const int64_t released;
	const struct database_set** sets;
	const uint set_count;
};

struct database_set {
	const char** name;
	const int64_t released;
	const struct database_card** cards;
	const uint card_count;
    const struct database_booster** boosters;
    const uint booster_count;
    const struct database_card** energies;
    const struct embedded* logo;
    const struct embedded* icon;
};

struct database_card {
	const uint8_t region;
	const uint16_t series;
	const uint16_t set;
	const uint number;
	const uint16_t pokemon;
    const uint8_t name_prefix;
    const uint8_t name_suffix;
    	const uint16_t evolve_from;
    const uint8_t evolve_prefix;
    const uint8_t evolve_suffix;
	const char** information;
	const char** description;
	const uint8_t type;
	const uint8_t rarity;
	const uint8_t stage;
	const uint16_t hp;
	// this is called length on older cards
	const char** height;
    const char** weight;
	const struct database_damage_modifier weakness;
	const struct database_damage_modifier resistance;
	const uint8_t* retreat_cost;
	const struct database_move** moves;
	const uint move_count;
	const struct database_ability* ability;
    const uint8_t prize;
    const char* illustrator;
	const struct embedded** images;
	const char* printed_number;
};
struct database_move {
    const char* damage;
	const char** name;
    const char** description;
	const uint8_t* energy_cost;
	const function_move_condition condition;
	const function_move execute;
};
struct database_ability {
	const char** name;
	const char** description;
    const function_ability_condition condition;
	const function_ability execute;
};
