#include "images/window_icon_png.c"
#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720
#define SOFTWARE_FPS 75
TextureFilter scale_filter = TEXTURE_FILTER_POINT;

struct window {
    float width;
    float height;
    float half_width;
    float half_height;
    float aspect;
};
struct window window;

void update_window() {
	window.width = GetScreenWidth();
    window.height = GetScreenHeight();
}

void init_window() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
	InitWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, GAME_TITLE);
    SetWindowIcon(LoadImageFromMemory(".png", window_icon_png, window_icon_png_len));
    update_window();
	#ifdef RLSW_IMPLEMENTATION
	SetTargetFPS(SOFTWARE_FPS);
	#endif
}

