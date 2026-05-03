#include "images/pointer_png.c"
#include "images/hand_png.c"

struct cursor {
	Image image;
	Texture2D texture;
	float s;
};
struct cursor cursors[CURSOR];
struct cursor* mouse_cursor;
uint8_t current_cursor = CURSOR_POINTER;



void update_mouse() {
	//mouse_cursor->s = (GetScreenHeight() * 0.03f) / mouse_cursor->texture.height;
}

void change_cursor(uint8_t cursor) {
	if (current_cursor != cursor) {
		mouse_cursor = &cursors[cursor];
		current_cursor = cursor;
	}
	//update_mouse();
}

void loop_mouse() {
	DrawTextureEx(mouse_cursor->texture, (Vector2) {GetMouseX(), GetMouseY()}, 0.0f, 1.0f, WHITE);
}

void init_mouse() {
	HideCursor();
	cursors[CURSOR_POINTER].image = LoadImageFromMemory(".png", pointer_png, pointer_png_len);
	cursors[CURSOR_POINTER].texture = LoadTextureFromImage(cursors[CURSOR_POINTER].image);
	cursors[CURSOR_HAND].image = LoadImageFromMemory(".png", hand_png, hand_png_len);
	cursors[CURSOR_HAND].texture = LoadTextureFromImage(cursors[CURSOR_HAND].image);
	mouse_cursor = &cursors[CURSOR_POINTER];
}
