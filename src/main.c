#define GAME_TITLE "Pocket Monsters | ポケットモンスター"
//カードゲーム
const char *exe_path;
const char *save_path;
const char *asset_path;
#include "external.c"
float dt;
//typedef void (function_state)(void);
typedef void (function_void)(void);
function_void* loop_state;
function_void* update_state;
#include "includes.c"

void init() {
	srand(time(NULL));
    init_window();
    init_crypt();
	init_audio();
    init_input();
    init_test();
    init_title();
    init_font();
    init_mouse();
    init_keyboard();
};

void main(void)
{
    init();
	while (!WindowShouldClose()) {
		dt = GetFrameTime();
		if (IsWindowResized()) {
			update_window();
			update_state();
			update_test();
			//update_mouse();
		};
		loop_input();
        loop_audio();
       
		BeginDrawing();
		ClearBackground(config.theme->colors[COLOR_BACKGROUND]);
		
        loop_state();
        loop_test();
        
        loop_mouse();
		EndDrawing();
	};
	CloseWindow();
};
