#define MAX_NAME_LENGTH 14
#define MAX_NAME_BYTES (MAX_NAME_LENGTH * 4 + 1)

struct player_progress {
	uint8_t stage;
	// ...
};

struct player_public {
    char* name; // 24 characters or 96 bytes
	unsigned char public[crypto_sign_PUBLICKEYBYTES];
	unsigned char encrypt_public[crypto_box_PUBLICKEYBYTES];
};

struct player_private {
    char* name; // 24 characters or 96 bytes
	unsigned char public[crypto_sign_PUBLICKEYBYTES];
	unsigned char private[crypto_sign_SECRETKEYBYTES];
	unsigned char encrypt_public[crypto_box_PUBLICKEYBYTES];
	unsigned char encrypt_private[crypto_box_SECRETKEYBYTES];
};

struct player_obtained {
    time_t date; // value
	uint8_t method; // value
	struct player_public player; // 128 bytes
};


struct player_card {
    uint32_t owners; // value
	struct player_public owner; // 128 bytes
	struct player_obtained owner_obtained; // 137 bytes
	struct player_public last_owner; // 128 bytes
	struct player_obtained last_obtained; // 137 bytes
	struct player_public original_owner; // 128 bytes
	struct player_obtained original_obtained; // 137 bytes
	struct database_card* card;
	uint64_t variant; // flags
	uint64_t extra; // value or flags
	uint8_t condition; // value
	uint16_t won; // value
	uint16_t lost; // value
	uint16_t knockouts; // value
	uint16_t knockedout; // value
	uint64_t achievements; // flags
	struct player_public signature; // 192 bytes
};

struct player_deck {
    char* name;
    struct player_card** cards;
    uint card_count;
};

struct save_game {
	struct player_progress progress;
    struct player_private player;
    struct player_public* friends;
    uint friend_count;
    struct player_card *cards;
    uint card_count;
    struct player_deck* decks;
    uint deck_count;
    time_t date_created;
    time_t time_played;
    time_t date_saved;
};

//struct player_slot player_slots[3];
