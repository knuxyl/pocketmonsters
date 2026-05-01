Image test_image;
Texture2D test_texture;
static uint8_t test_region;
static uint8_t test_series;
static uint8_t test_set;
static uint16_t test_number;
static uint8_t test_language;
static uint8_t test_image_language;
static uint8_t test_measurement;
static const struct database_card* test_card;
static bool show_card;
static uint8_t track;
static uint8_t game;
static bool pause;
uint8_t temp_language;


function_void fun1;
function_void fun2;
function_void fun3;
function_void fun4;
function_void fun5;
function_void fun6;
static struct ui_child fun1_child = {.type = UI_MENU_TEXT, .pw = 0.6f, .click = fun1, .string = str_pokemon[SCYTHER]};
static struct ui_child fun2_child = {.type = UI_MENU_TEXT, .pw = 0.6f, .click = fun2, .string = str_pokemon[LAPRAS]};
static struct ui_child fun3_child = {.type = UI_MENU_TEXT, .pw = 0.6f, .click = fun3, .string = str_pokemon[LUGIA]};
static struct ui_child fun4_child = {.type = UI_MENU_TEXT, .pw = 0.6f, .click = fun4, .string = str_pokemon[MEW]};
static struct ui_child fun5_child = {.type = UI_MENU_TEXT, .pw = 0.6f, .click = fun5, .string = str_pokemon[RAYQUAZA]};
static struct ui_child fun6_child = {.type = UI_MENU_TEXT, .pw = 0.6f, .click = fun6, .string = str_pokemon[ZAPDOS]};
struct ui_element test_element = {.ph = 0.5f, .padding_pt = 0.15f, .v = UI_HIDDEN, .align_x = UI_CENTER, .align_y = UI_CENTER, .child_count = 6, .children = {&fun1_child, &fun2_child, &fun3_child, &fun4_child, &fun5_child, &fun6_child}};

void fun1() {
	printf("fun1\n");
}
void fun2() {
	printf("fun2\n");
}
void fun3() {
	printf("fun3\n");
}
void fun4() {
	printf("fun4\n");
}
void fun5() {
	printf("fun5\n");
}
void fun6() {
	printf("fun6\n");
}


void play_test_sound(uint16_t track) {
	stop_sound();
	gme_open_data(embedded_music[game].data, embedded_music[game].len, &sound_player, SAMPLE_RATE);
	gme_start_track(sound_player, track);
	sound_stream = LoadAudioStream(SAMPLE_RATE, 16, 2);
	PlayAudioStream(sound_stream);
	sound_playing = true;
	printf("Playing Game: %i, Track: %i\n", game, track);
}

void play_test_music(uint16_t track) {
	stop_music();
	gme_open_data(embedded_music[game].data, embedded_music[game].len, &music_player, SAMPLE_RATE);
	gme_start_track(music_player, track);
	music_stream = LoadAudioStream(SAMPLE_RATE, 16, 2);
	PlayAudioStream(music_stream);
	music_playing = true;
	printf("Playing Game: %i, Track: %i\n", game, track);
}



void print_card_info() {
    printf("----------------------------------------\n");
    printf("test_region: %i, test_series: %i, test_set: %i, test_number: %i/%i, test_language: %i, test_measurement: %i\n", test_region, test_series, test_set, test_number, db[test_region]->series[test_series]->sets[test_set]->card_count, test_language, test_measurement);
    printf("Card Name: %s\n", str_pokemon[test_card->pokemon][test_language]);
    printf("Printed Number: %s\n", test_card->printed_number);
    printf("Number: %i\n", test_card->number);
    printf("Pokedex Number: %i\n", test_card->pokemon);
    printf("Information: %s\n", test_card->information[test_language]);
    printf("Description: %s\n", test_card->description[test_language]);
    printf("Type: %s\n", str_energy[test_card->type][test_language]);
    printf("Rarity: %s\n", str_rarity[test_card->rarity][test_language]);
    printf("Stage: %s\n", str_stage[test_card->stage][test_language]);
    if (test_card->evolve_from) {
        printf("Evolves From: %s\n", str_pokemon[test_card->evolve_from][test_language]);
    };
    printf("HP: %i\n", test_card->hp);
    if (test_card->ability) {
        printf("Ability: %s\n", test_card->ability->name[test_language]);
        printf("\tDescription: %s\n", test_card->ability->description[test_language]);
    };
    printf("Moves: %i\n", test_card->move_count);
    for (uint8_t i = 0; i < test_card->move_count; i++) {
        printf("Move %i: %s\n", i+1, test_card->moves[i]->name[test_language]);
        printf("\tDescription: %s\n", test_card->moves[i]->description[test_language]);
    };
    printf("Height: %s\n", test_card->height[test_measurement]);
    printf("Weight: %s\n", test_card->weight[test_measurement]);
    printf("Weakness: %s\n", str_energy[test_card->weakness.type][test_language]);
    printf("Resistance: %s\n", str_energy[test_card->resistance.type][test_language]);
    printf("Illustrator: %s\n", test_card->illustrator);
    printf("----------------------------------------\n");
};

void change_card() {
    UnloadTexture(test_texture);
    UnloadImage(test_image);
    printf("Changing to: %i\n", test_number);
    test_card = db[test_region]->series[test_series]->sets[test_set]->cards[test_number];
    //test_card = database[test_region]->series[test_series]->sets[test_set]->cards[test_number];
    //test_image = );

    test_image = LoadImageFromMemory(".png", test_card->images[test_image_language]->data, test_card->images[test_image_language]->len);
    test_texture = LoadTextureFromImage(test_image);
    //UnloadImage(test_image);
    print_card_info();
}

void update_test() {
	update_element(&test_element);
}


void draw_test() {
    //ClearBackground((Color){208,208,153,0});
    //DrawTextureEx(test_texture, (Vector2) {(window.width / 2)-((test_texture.width*0.5f)/2), 16}, 0.0f, 4.0f, WHITE);
    if (show_card) {
    		DrawTextureEx(test_texture, (Vector2) {(window.width - (test_texture.width*1.0f)), 0}, 0.0f, 1.0f, WHITE);
    	};
    	
    //DrawTextEx(fonts[current_font], test_card->information[test_language], (Vector2) {0, window.height-496}, 36, 0, BLACK);
};

void loop_test() {
	if (temp_language != config.language) {
		update_test();
		temp_language = config.language;
	}
	if (IsKeyReleased(KEY_ONE)) {
		if (test_card->move_count >= 1) {
			test_card->moves[0]->execute(test_card->moves[0]);
		};
	};
    if (IsKeyReleased(KEY_Q)) {
		if (test_card->move_count >= 1) {
			test_card->moves[0]->condition(test_card->moves[0]);
		};
	};
    if (IsKeyReleased(KEY_TWO)) {
        if (test_card->move_count >= 2) {
            test_card->moves[1]->execute(test_card->moves[1]);
        };
	};
    if (IsKeyReleased(KEY_W)) {
        if (test_card->move_count >= 2) {
            test_card->moves[1]->condition(test_card->moves[1]);
        };
	};
	if (IsKeyReleased(KEY_C)) {
		show_card = !show_card;
		//clear_color = (Color) { 16,16,16,255 };
	};
    if (IsKeyReleased(KEY_I)) {
        print_card_info();
	};
    if (IsKeyReleased(KEY_L)) {
        if (test_language + 1 >= LANGUAGE) {
            test_language = 0;
        } else {
            test_language++;
        };
        if (config.language + 1 >= LANGUAGE) {
            config.language = 0;
        } else {
            config.language++;
        };
        printf("Changed language: %i\n", config.language);
        print_card_info();
	};
	if (IsKeyReleased(KEY_N)) {
		if (game - 1 < 0) {
			game = music_count - 1;
		} else {
			game--;
		};
		track = 0;
		play_test_music(track);
	};
	if (IsKeyReleased(KEY_M)) {
		if (game + 1 == music_count) {
			game = 0;
		} else {
			game++;
		};
		track = 0;
		play_test_music(track);
	};
	if (IsKeyReleased(KEY_J)) {
		//config.game_audio = GAME_PMCG2;
	};
	if (IsKeyReleased(KEY_K)) {
		//config.game_audio = GAME_YELLOW;
	};
	if (IsKeyReleased(KEY_COMMA)) {
		if (music_playing) {
			uint8_t track_count = gme_track_count(music_player);
			if (track - 1 < 0) {
				track = track_count - 1;
			} else {
				track--;
			}
		}
		play_test_music(track);
	};
	if (IsKeyReleased(KEY_PERIOD)) {
		if (music_playing) {
			uint8_t track_count = gme_track_count(music_player);
			printf("Track count: %i\n", track_count);
			if (track + 1 == track_count) {
				track = 0;
			} else {
				track++;
			}
		}
		play_test_music(track);
	};
	if (is_pressed(INPUT_START)) {
		if (pause) {
			resume_music();
		} else {
			pause_music();
		};
		pause = !pause;
	}
	if (IsKeyReleased(KEY_T)) {
		mute();
	}
	if (IsKeyReleased(KEY_D)) {
		change_theme(DARK_THEME);
	};
	if (IsKeyReleased(KEY_F)) {
		change_theme(LIGHT_THEME);
	};
	if (IsKeyReleased(KEY_G)) {
		change_theme(GB_DARK_THEME);
	};
	if (IsKeyReleased(KEY_H)) {
		change_theme(GB_LIGHT_THEME);
	};
	if (IsKeyReleased(KEY_O)) {
		stop_music();
	};
	if (is_pressed(INPUT_RIGHT)) {
        uint16_t prev = test_number;
		if ((test_number + 1) == db[test_region]->series[test_series]->sets[test_set]->card_count) {
			test_number = 0;
		} else {
			test_number++;
		};
        if (prev != test_number) {
            change_card();
        };
	};
	if (is_pressed(INPUT_LEFT)) {
        uint16_t prev = test_number;
		if ((test_number - 1) < 0) {
			test_number = db[test_region]->series[test_series]->sets[test_set]->card_count - 1;
		} else {
			test_number--;
		};
        if (prev != test_number) {
		    change_card();
        };
	};
	if (is_pressed(INPUT_X)) {
        if (logo_element.v == UI_ACTIVE) {
        		//logo_child.v = UI_HIDDEN;
        		//for (uint8_t i = 0; i < test_element.child_count; i++) {
        			//test_element.children[i]->v = UI_ACTIVE;
        		//}
        		logo_element.v = UI_HIDDEN;
        		titlemenu_element.v = UI_DISABLED;
        		//pushstart_element.v = UI_DISABLED;
        		//titlemenu_element.v = UI_DISABLED;
        		test_element.v = UI_ACTIVE;
        	} else {
        		//logo_child.v = UI_ACTIVE;
        		//for (uint8_t i = 0; i < test_element.child_count; i++) {
        			//test_element.children[i]->v = UI_HIDDEN;
        		//}
        		logo_element.v = UI_ACTIVE;
        		titlemenu_element.v = UI_ACTIVE;
        		//pushstart_element.v = UI_ACTIVE;
        		//titlemenu_element.v = UI_ACTIVE;
        		test_element.v = UI_HIDDEN;
        	}
        	update_element(&test_element);
	};
	if (is_pressed(INPUT_Y)) {
        uint8_t prev = test_set;
		if ((test_set + 1) >= db[test_region]->series[test_series]->set_count) {
			test_set = 0;
		} else {
			test_set++;
		};
		//test_number = 0;
		if (prev != test_set) {
            change_card();
        };
	};
	input_element(&test_element);
    	draw_element(&test_element);
    draw_test();
};

void init_test() {
	test_region = INTERNATIONAL;
    test_series = INTERN_WOTC;
    test_set = WOTC_BS;
    test_number = 0;
    test_image_language = ENGLISH;
    test_language = ENGLISH;
    test_measurement = config.measurement;
    show_card = false;
    change_card();
    track = 0;
    game = 0;
    pause = false;
    update_element(&test_element);
    temp_language = config.language;
};
