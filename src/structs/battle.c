struct battle_field {
    struct player_card* active;
    struct player_card** bench;
};

struct battle_player {
    struct player_public* player;
    struct player_card* hand;
    struct player_deck* deck;
    struct player_card* discard;
    uint8_t prizes;
    struct battle_field field;
};

struct battle_scene {
    uint16_t theme;
    unsigned char* uid[32];
    struct battle_player** players;
};