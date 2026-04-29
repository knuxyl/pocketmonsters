#define INPUT_NOBIND 255
#include "keyboard.c"
#include "gamepad.c"
#include "mouse.c"

float mouse_x;
float mouse_y;
bool mouse_moving;
uint8_t input_device;
struct controller* controllers[10] = { NULL };
uint8_t num_controllers = 0;

void current_device(uint8_t device) {
	if (input_device != device) {
		input_device = device;
	}
}

bool is_up(uint8_t key) {
	if (keyboard_input[key] != INPUT_NOBIND) {
		if (IsKeyUp(keyboard_input[key])) {
			current_device(DEVICE_KEYBOARD);
			return true;
		}
	}
	for (uint8_t i = 0; i < 10; i++) {
		if (gamepad_input[key] != INPUT_NOBIND) {
			if (IsGamepadButtonUp(i, gamepad_input[key])) {
				current_device(DEVICE_GAMEPAD);
				return true;
			}
		}
	}
	if (mouse_input[key] != INPUT_NOBIND) {
		if (IsMouseButtonUp(mouse_input[key])) {
			current_device(DEVICE_MOUSE);
			return true;
		}
	}
	return false;
}

bool is_released(uint8_t key) {
	if (keyboard_input[key] != INPUT_NOBIND) {
		if (IsKeyReleased(keyboard_input[key])) {
			current_device(DEVICE_KEYBOARD);
			return true;
		}
	}
	for (uint8_t i = 0; i < 10; i++) {
		if (gamepad_input[key] != INPUT_NOBIND) {
			if (IsGamepadButtonReleased(i, gamepad_input[key])) {
				current_device(DEVICE_GAMEPAD);
				return true;
			}
		}
	}
	if (mouse_input[key] != INPUT_NOBIND) {
		if (IsMouseButtonReleased(mouse_input[key])) {
			current_device(DEVICE_MOUSE);
			return true;
		}
	}
	return false;
}

bool is_down(uint8_t key) {
	if (keyboard_input[key] != INPUT_NOBIND) {
		if (IsKeyDown(keyboard_input[key])) {
			current_device(DEVICE_KEYBOARD);
			return true;
		}
	}
	for (uint8_t i = 0; i < 10; i++) {
		if (gamepad_input[key] != INPUT_NOBIND) {
			if (IsGamepadButtonDown(i, gamepad_input[key])) {
				current_device(DEVICE_GAMEPAD);
				return true;
			}
		}
	}
	if (mouse_input[key] != INPUT_NOBIND) {
		if (IsMouseButtonDown(mouse_input[key])) {
			current_device(DEVICE_MOUSE);
			return true;
		}
	}
	return false;
}

bool is_pressed(uint8_t key) {
	if (keyboard_input[key] != INPUT_NOBIND) {
		if (IsKeyPressed(keyboard_input[key])) {
			current_device(DEVICE_KEYBOARD);
			return true;
		}
	}
	for (uint8_t i = 0; i < 10; i++) {
		if (gamepad_input[key] != INPUT_NOBIND) {
			if (IsGamepadButtonPressed(i, gamepad_input[key])) {
				current_device(DEVICE_GAMEPAD);
				return true;
			}
		}
	}
	if (mouse_input[key] != INPUT_NOBIND) {
		if (IsMouseButtonPressed(mouse_input[key])) {
			current_device(DEVICE_MOUSE);
			return true;
		}
	}
	return false;
}

void init_input() {
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
}

void loop_input() {
	for (uint8_t i = 0; i <10; i++) {
		if (!controllers[i]) {
			if (IsGamepadAvailable(i)) {
				controllers[i] = malloc(sizeof(struct controller));
				const char* name = GetGamepadName(i);
				controllers[i]->name = malloc(strlen(name) + 1);
				strcpy(controllers[i]->name, name);
				controllers[i]->index = i;
				num_controllers++;
				printf("%s connected.\n", controllers[i]->name);
			}
		} else	{
			if (!IsGamepadAvailable(i)) {
				printf("%s disconnected.\n", controllers[i]->name);
				free(controllers[i]);
				num_controllers--;
				controllers[i] = NULL;
			}
		}
	}
	mouse_x = GetMouseX();
	mouse_y = GetMouseY();
	Vector2 mouse_delta = GetMouseDelta();
	if (mouse_delta.x || mouse_delta.y) {
		mouse_moving = true;
		current_device(DEVICE_MOUSE);
	} else if (mouse_moving) {
		mouse_moving = false;
	}
}

