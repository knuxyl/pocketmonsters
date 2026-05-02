//#include "images/logo_dark_png.c"
//#include "images/logo_light_png.c"
#include "images/logo_png.c"
#include "images/title_background_png.c"

static function_void* current_state;
static Image logo_image;
static uint8_t state = 0;
function_void continue_game;
function_void new_game;
function_void options;
function_void exit_game;
function_void network;
struct ui_child logo_child = {.type = UI_IMAGE, .pw = 0.95f, .ph = 0.25f};
static struct ui_child pushstart_child = {.type = UI_TEXT, .ph = 0.075f, .pw = 0.6f, .string = str_title_pushstart};
static struct ui_child continue_child = {.type = UI_MENU_TEXT, .v = UI_DISABLED, .pw = 0.6f, .click = continue_game, .string = str_title_continue};
static struct ui_child newgame_child = {.type = UI_MENU_TEXT, .pw = 0.6f, .click = new_game, .string = str_title_newgame};
static struct ui_child network_child = {.type = UI_MENU_TEXT, .v = UI_DISABLED, .pw = 0.6f, .click = network, .string = str_title_network};
static struct ui_child options_child = {.type = UI_MENU_TEXT, .pw = 0.6f, .click = options, .string = str_title_options};
static struct ui_child exit_child = {.type = UI_MENU_TEXT, .click = exit_game, .string = str_title_exit};
struct ui_element titlemenu_element = {.index = UI_NOSELECTION, .py = 0.5f, .child_pgap = 0.04f, .padding_pb = 0.1f, .padding_pt = 0.05f, .ph = 0.5f, .align_x = UI_CENTER, .align_y = UI_CENTER, .child_count = 5, .children = {&continue_child, &newgame_child, &network_child, &options_child, &exit_child}};
struct ui_element pushstart_element = {.py = 0.65f, .ph = 0.35f, .align_x = UI_CENTER, .align_y = UI_TOP, .child_count = 1, .children = {&pushstart_child}};
struct ui_element logo_element = {.ph = 0.5f, .padding_pt = 0.15f, .align_x = UI_CENTER, .align_y = UI_CENTER, .child_count = 1, .children = {&logo_child}};
// not used like a regular element
static struct onscreen_keyboard onscreen_keyboard;
static float pushstart_timer;
static struct ui_child* current_element;
static Image background_image;
static Texture2D background_texture;
static float background_x = 0;
static float background_y = 0;
static float background_scale = 1;
bool show_keyboard;


void continue_game() {
	printf("Continue game\n");
}

void new_game() {
	printf("New game\n");
}

void network() {
	printf("Network\n");
}

void options() {
	if (config.language + 1 == LANGUAGE) {
		config.language = 0;
	} else {
		config.language++;
	}
	//update_element(&titlemenu_element);
	update_state();
}

void exit_game() {
	printf("Exit game\n");
	exit(0);
}

void update_title() {
	if (IsImageValid(background_image)) {
		UnloadImage(background_image);
	}
	if (IsTextureValid(background_texture)) {
		UnloadTexture(background_texture);
	}
	background_image = LoadImageFromMemory(".png", title_background_png, title_background_png_len);
	background_scale = window.height / background_image.height;
	ImageResize(&background_image, (int)(background_image.width * background_scale), (int)(background_image.height * background_scale));
	background_texture = LoadTextureFromImage(background_image);
	SetTextureFilter(background_texture, TEXTURE_FILTER_POINT);
	update_element(&logo_element);
	if (state == 0) {
		update_element(&pushstart_element);
	} else if (state == 1) {
		update_element(&titlemenu_element);
	}
	update_keyboard(&onscreen_keyboard);
}

void loop_title() {
	background_x = background_x - (background_texture.width * 0.0001f);
	if (background_x + background_texture.width > -1) {
		DrawTextureEx(background_texture, (Vector2) {background_x, background_y}, 0.0f, 1.0f, (Color) {255,255,255,64});
	}
	uint8_t i = 1;
	while (background_x + (background_texture.width * i) < window.width) {
		DrawTextureEx(background_texture, (Vector2) {background_x + (background_texture.width * i), background_y}, 0.0f, 1.0f, (Color) {255,255,255,64});
		i++;
	}
	if (background_x + background_texture.width < 0) {
		background_x = background_x + ((uint)background_x * -1);
	}
	
	
	draw_element(&logo_element);
	if (state == 0) {
		pushstart_timer = pushstart_timer + dt;		
		if (pushstart_timer >= 0.75 && pushstart_timer < 1.5) {
			pushstart_child.v = UI_HIDDEN;
		} else if (pushstart_timer > 1.5) {
			pushstart_timer = 0;
			pushstart_child.v = UI_ACTIVE;
		}
		draw_element(&pushstart_element);
		if (is_pressed(INPUT_START)) {
			play_sound(SOUND_SELECT);
			play_music(MUSIC_TITLE_MENU);
			state++;
			reset_element(&pushstart_element);
			update_title();
		}
		if (is_pressed(INPUT_B)) {
			play_sound(SOUND_INVALID);
		}
	} else if (state == 1) {
		input_element(&titlemenu_element);
		draw_element(&titlemenu_element);
		if (is_pressed(INPUT_B)) {
			play_sound(SOUND_BACK);
			play_music(MUSIC_TITLE);
			state--;
			reset_element(&titlemenu_element);
			update_title();
		}
	}
	//onscreen_keyboard();
	if (is_pressed(INPUT_SELECT)) {
		show_keyboard = !show_keyboard;
		if (show_keyboard) {
			update_keyboard(&onscreen_keyboard);
		}
	}
	if (show_keyboard) {
		input_keyboard(&onscreen_keyboard);
		draw_keyboard(&onscreen_keyboard);
	}
}

void init_title() {
	logo_image = LoadImageFromMemory(".png", logo_png, logo_png_len);
	logo_child.image = LoadTextureFromImage(logo_image);
	GenTextureMipmaps(&logo_child.image);
	SetTextureFilter(logo_child.image, config.filter);
	background_image = LoadImageFromMemory(".png", title_background_png, title_background_png_len);
	background_scale = window.height / background_image.height;
	ImageResize(&background_image, (int)(background_image.width * background_scale), (int)(background_image.height * background_scale));
	background_texture = LoadTextureFromImage(background_image);
	SetTextureFilter(background_texture, TEXTURE_FILTER_POINT);
	current_state = init_title;
	play_music(MUSIC_TITLE);
	loop_state = loop_title;
	update_state = update_title;
	onscreen_keyboard.page = 0;
	update_state();
}

