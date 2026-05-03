#include "keyboard.c"

void reset_element(struct ui_element* element) {
	if (element->index != UI_NOSELECTION) {
		element->children[element->index]->hover = false;
		element->index = UI_NOSELECTION;
	}
}


void draw_keyboard() {
	DrawRectangle(0, 0, window.width, window.height, config.theme->tr_background);
	for (uint16_t i = osk.page_index; i < osk.page_index + osk.keys_per_page && i < osk.letter_count; i++) {
		if (osk.letters[i].click) {
			DrawRectangleRounded((Rectangle) {osk.letters[i].slot_position.x, osk.letters[i].slot_position.y, osk.key_width, osk.key_height}, 0.5f, 8, config.theme->text);
			DrawRectangleRounded((Rectangle) {osk.letters[i].background_position.x, osk.letters[i].background_position.y, osk.background_size.x, osk.background_size.y}, 0.5f, 8, config.theme->ok);
			DrawTextEx(osk.font, keyboard_letters[i], osk.letters[i].letter_position, osk.font_size, 0.0f, config.theme->text);
		} else if (osk.letters[i].hover) {
			DrawRectangleRounded((Rectangle) {osk.letters[i].slot_position.x, osk.letters[i].slot_position.y, osk.key_width, osk.key_height}, 0.5f, 8, config.theme->background);
			DrawRectangleRounded((Rectangle) {osk.letters[i].background_position.x, osk.letters[i].background_position.y, osk.background_size.x, osk.background_size.y}, 0.5f, 8, config.theme->text);
			DrawTextEx(osk.font, keyboard_letters[i], osk.letters[i].letter_position, osk.font_size, 0.0f, config.theme->background);
		} else {
			DrawRectangleRounded((Rectangle) {osk.letters[i].slot_position.x, osk.letters[i].slot_position.y, osk.key_width, osk.key_height}, 0.5f, 8, config.theme->text);
			DrawRectangleRounded((Rectangle) {osk.letters[i].background_position.x, osk.letters[i].background_position.y, osk.background_size.x, osk.background_size.y}, 0.5f, 8, config.theme->background);
			DrawTextEx(osk.font, keyboard_letters[i], osk.letters[i].letter_position, osk.font_size, 0.0f, config.theme->text);
		}
		
	}
	for (uint8_t i = 0; i < osk.button_count; i++) {
		if (osk.buttons[i].click) {
			DrawRectangleRounded((Rectangle) {osk.buttons[i].slot_position.x, osk.buttons[i].slot_position.y, osk.buttons[i].slot_size.x, osk.buttons[i].slot_size.y}, 0.5f, 8, config.theme->text);
			DrawRectangleRounded((Rectangle) {osk.buttons[i].background_position.x, osk.buttons[i].background_position.y, osk.buttons[i].background_size.x, osk.buttons[i].background_size.y}, 0.5f, 8, config.theme->ok);
			DrawTextEx(osk.font, osk.buttons[i].letter, osk.buttons[i].letter_position, osk.font_size, 0.0f, config.theme->text);
		} else if (osk.buttons[i].hover) {
			DrawRectangleRounded((Rectangle) {osk.buttons[i].slot_position.x, osk.buttons[i].slot_position.y, osk.buttons[i].slot_size.x, osk.buttons[i].slot_size.y}, 0.5f, 8, config.theme->background);
			DrawRectangleRounded((Rectangle) {osk.buttons[i].background_position.x, osk.buttons[i].background_position.y, osk.buttons[i].background_size.x, osk.buttons[i].background_size.y}, 0.5f, 8, config.theme->text);
			DrawTextEx(osk.font, osk.buttons[i].letter, osk.buttons[i].letter_position, osk.font_size, 0.0f, config.theme->background);
		} else {
			DrawRectangleRounded((Rectangle) {osk.buttons[i].slot_position.x, osk.buttons[i].slot_position.y, osk.buttons[i].slot_size.x, osk.buttons[i].slot_size.y}, 0.5f, 8, config.theme->text);
			DrawRectangleRounded((Rectangle) {osk.buttons[i].background_position.x, osk.buttons[i].background_position.y, osk.buttons[i].background_size.x, osk.buttons[i].background_size.y}, 0.5f, 8, config.theme->background);
			DrawTextEx(osk.font, osk.buttons[i].letter, osk.buttons[i].letter_position, osk.font_size, 0.0f, config.theme->text);
		}
		//DrawRectangleRounded((Rectangle) {osk.buttons[i].box_position.x, osk.buttons[i].box_position.y, osk.buttons[i].box_size.x, osk.buttons[i].box_size.y}, 0.5f, 8, config.theme->hover);
	
	
	
		//DrawRectangleRounded((Rectangle) {osk.buttons[i].box_position.x, osk.buttons[i].box_position.y, osk.buttons[i].box_size.x, osk.key_height}, 0.5f, 8, config.theme->text);
	}
}

void update_keyboard() {
	/*
	----------------------------------------------------------------------------
	----------------------------------------------------------------------------
		THERE IS A SMALL MEMORY LEAK SOMEWHERE IN HERE
	----------------------------------------------------------------------------
	----------------------------------------------------------------------------
	*/
	if (osk.page >= osk.pages || osk.page < 0) {
		osk.page = 0;
	}
	osk.page_index = osk.page * osk.keys_per_page;
	
	float max_width = window.width * 0.98f;
	float max_height = window.height * 0.5f;
	osk.width = max_width;
	osk.height = max_height;
	osk.key_width = osk.width / osk.columns;
	osk.key_height = osk.height / (osk.rows + 2);
	unload_font(osk.font);
	int codepoints_count;
	int* codepoints = LoadCodepoints(keyboard_codepoints, &codepoints_count);
	osk.font = LoadFontFromMemory(".otf", unifont_otf, unifont_otf_len, osk.key_height, codepoints, codepoints_count);
	SetTextureFilter(osk.font.texture, TEXTURE_FILTER_BILINEAR);
	const char* biggest_char;
	float width = 0;
	for (uint16_t c = 0; c < osk.letter_count; c++) {
		float check_width = MeasureTextEx(osk.font, keyboard_letters[c], osk.key_height, 0.0f).x;
		if (check_width > width) {
			width = check_width;
			biggest_char = keyboard_letters[c];
		}
	}
	osk.width = width * osk.columns;
	while (osk.width > max_width || osk.height > max_height) {
		osk.key_height--;
		osk.height = osk.key_height * (osk.rows + 2);
		width = MeasureTextEx(osk.font, biggest_char, osk.key_height, 0.0f).x;
		osk.width = width * osk.columns;
	}
	osk.key_width = width;
	osk.x = (window.width / 2) - (osk.width / 2);
	osk.y = window.height - osk.height;
	osk.font_size = osk.key_height * 0.7f;
	float border = osk.key_width * 0.05f;
	osk.background_size.x = osk.key_width - (border * 2);
	osk.background_size.y = osk.key_height - (border * 2);
	unload_font(osk.font);
	codepoints = LoadCodepoints(keyboard_codepoints, &codepoints_count);
	osk.font = LoadFontFromMemory(".otf", unifont_otf, unifont_otf_len, osk.font_size, codepoints, codepoints_count);
	SetTextureFilter(osk.font.texture, TEXTURE_FILTER_BILINEAR);
	int row_index, index;
	for (uint8_t r = 0; r < osk.rows; r++) {
		row_index = r * osk.columns;
		for (uint8_t c = 0; c < osk.columns; c++) {
			index = osk.page_index + row_index + c;
			if (index > osk.letter_count) {
				break;
			}
			osk.letters[index].letter_size = MeasureTextEx(osk.font, keyboard_letters[index], osk.font_size, 0.0f);
			float x_offset = (osk.key_width - osk.letters[index].letter_size.x) / 2;
			float y_offset = (osk.key_height - osk.letters[index].letter_size.y) / 2;
			osk.letters[index].slot_position.x = osk.x + (osk.key_width * c);
			osk.letters[index].slot_position.y = osk.y + (osk.key_height * (r +1));
			osk.letters[index].background_position.x = osk.letters[index].slot_position.x + border;
			osk.letters[index].background_position.y = osk.letters[index].slot_position.y + border;
			osk.letters[index].letter_position.x = osk.letters[index].slot_position.x + x_offset;
			osk.letters[index].letter_position.y = osk.letters[index].slot_position.y + y_offset;
		}
	}
	for (uint8_t i = 0; i < osk.button_count; i++) {
		osk.buttons[i].slot_size.x = (osk.key_width * osk.buttons[i].space_width);
		osk.buttons[i].slot_size.y = osk.key_height;
		osk.buttons[i].slot_position.x = osk.letters[osk.page_index + osk.buttons[i].relation].slot_position.x;
		if (osk.buttons[i].align == UI_TOP) {
			osk.buttons[i].slot_position.y = osk.letters[osk.page_index + osk.buttons[i].relation].slot_position.y - osk.key_height;
		} else if (osk.buttons[i].align == UI_BOTTOM) {
			osk.buttons[i].slot_position.y = osk.letters[osk.page_index + osk.buttons[i].relation].slot_position.y + osk.key_height;
		}
		osk.buttons[i].background_size.x = osk.buttons[i].slot_size.x - (border * 2);
		osk.buttons[i].background_size.y = osk.background_size.y;		
		osk.buttons[i].background_position.x = osk.buttons[i].slot_position.x + border;
		osk.buttons[i].background_position.y = osk.buttons[i].slot_position.y + border;
		osk.buttons[i].letter_size = MeasureTextEx(osk.font, osk.buttons[i].letter, osk.font_size, 0.0f);
		osk.buttons[i].letter_position.x = (osk.buttons[i].slot_position.x + (osk.buttons[i].slot_size.x / 2)) - (osk.buttons[i].letter_size.x / 2);
		osk.buttons[i].letter_position.y = (osk.buttons[i].slot_position.y + (osk.buttons[i].slot_size.y / 2)) - (osk.buttons[i].letter_size.y / 2);
	}
}


void input_keyboard() {
	//if (osk.index != UI_NOSELECTION && (osk.index < osk.page_index || osk.index > osk.page_index + osk.keys_per_page)) {
		//osk.index = 0;
	//}
	if (mouse_moving) {
		if (mouse_x >= osk.x && mouse_x <= osk.x + osk.width && mouse_y >= osk.y && mouse_y <= osk.y + osk.height) {
			bool hover = false;
			for (uint16_t i = osk.page_index; i < osk.page_index + osk.keys_per_page && i < osk.letter_count; i++) {
				if (mouse_x >= osk.letters[i].slot_position.x && mouse_x <= osk.letters[i].slot_position.x + osk.key_width &&
					mouse_y >= osk.letters[i].slot_position.y && mouse_y <= osk.letters[i].slot_position.y + osk.key_height) {
					if (!osk.letters[i].hover) {
						osk.letters[i].hover = true;
					}
					hover = true;
					osk.hover = true;
					osk.index = i;
					change_cursor(CURSOR_HAND);
					break;
				}
			}
			if (!hover) {
				for (uint16_t i = 0; i < osk.button_count; i++) {
					if (mouse_x >= osk.buttons[i].slot_position.x && mouse_x <= osk.buttons[i].slot_position.x + osk.buttons[i].slot_size.x &&
						mouse_y >= osk.buttons[i].slot_position.y && mouse_y <= osk.buttons[i].slot_position.y + osk.buttons[i].slot_size.y) {
						if (!osk.buttons[i].hover) {
							osk.buttons[i].hover = true;
						}
						hover = true;
						osk.hover = true;
						osk.index = osk.buttons[i].index;
						change_cursor(CURSOR_HAND);
						break;
					}
				}
			}
			if (!hover) {
				osk.hover = false;
			}
		} else {
			osk.hover = false;
		}
		if (!osk.hover) {
			if (osk.index != UI_NOSELECTION) {
				osk.index = UI_NOSELECTION;
			}
			change_cursor(CURSOR_POINTER);
		}
		for (uint16_t i = osk.page_index; i < osk.page_index + osk.keys_per_page && i < osk.letter_count; i++) {
			if (osk.index != i && osk.letters[i].hover) {
				osk.letters[i].hover = false;
			}
		}
		for (uint16_t i = 0; i < osk.button_count; i++) {
			if (osk.index != osk.buttons[i].index && osk.buttons[i].hover) {
				osk.buttons[i].hover = false;
			}
		}
		
	}
	if (input_device == DEVICE_GAMEPAD || input_device == DEVICE_KEYBOARD) {
		if (!osk.hover) {
			osk.hover = true;
		}
		if (osk.index == UI_NOSELECTION || osk.index > osk.letter_count + osk.buttons - 1) {
			osk.index = osk.page_index;
		}
		if (osk.index < osk.letter_count) {
			if (!osk.letters[osk.index].hover) {
				osk.letters[osk.index].hover = true;
			}
		} else {
			if (!osk.buttons[osk.index - osk.letter_count].hover) {
				osk.buttons[osk.index - osk.letter_count].hover = true;
			}
		}
		for (uint16_t i = osk.page_index; i < osk.page_index + osk.keys_per_page && i < osk.letter_count; i++) {
			if (osk.index != i && osk.letters[i].hover) {
				osk.letters[i].hover = false;
			}
		}
		for (uint16_t i = 0; i < osk.button_count; i++) {
			if (osk.index != osk.buttons[i].index && osk.buttons[i].hover) {
				osk.buttons[i].hover = false;
			}
		}
	}
	
	
	
	if (osk.hover && osk.index != UI_NOSELECTION && is_pressed(INPUT_A)) {
		if (osk.index < osk.letter_count) {
			osk.letters[osk.index].click = true;
		} else {
			osk.buttons[osk.index - osk.letter_count].click = true;
		}
	}
	
	
	if (is_pressed(INPUT_DOWN)) {
		uint8_t index = osk.index % osk.keys_per_page;
		if (index + osk.columns >= osk.keys_per_page) {
			osk.index -= osk.columns * (osk.rows - 1);
		} else {
			osk.index += osk.columns;
		}
	}
	if (is_pressed(INPUT_UP)) {
		uint8_t index = osk.index % osk.keys_per_page;
		if (index - osk.columns < 0) {
			osk.index += osk.columns * (osk.rows - 1);
		} else {
			osk.index -= osk.columns;
		}
	}
	if (is_pressed(INPUT_LEFT)) {
		if (osk.index % osk.columns == 0) {
			osk.index += osk.columns - 1;
		} else {
			osk.index -= 1;
		}
	}
	if (is_pressed(INPUT_RIGHT)) {
		if ((osk.index + 1) % osk.columns == 0) {
			osk.index -= osk.columns - 1;
		} else {
			osk.index += 1;
		}
	}
	if (is_pressed(INPUT_X)) {
		osk.buttons[0].click = true;
		if (osk.page - 1 == -1) {
			osk.page = osk.pages - 1;
			osk.index += osk.page * osk.keys_per_page;
			//osk.index = osk.index % osk.keys_per_page;
		} else {
			osk.page--;
			osk.index -= osk.keys_per_page;
		}
		update_keyboard();
	}
	if (is_released(INPUT_X)) {
		if (osk.buttons[0].click) {
			osk.buttons[0].click = false;
		}
	}
	if (is_pressed(INPUT_Y)) {
		osk.buttons[1].click = true;
		if (osk.page + 1 == osk.pages) {
			osk.page = 0;
			osk.index = osk.index % osk.keys_per_page;
		} else {
			osk.page++;
			osk.index += osk.keys_per_page;
		}
		update_keyboard();
	}
	if (is_released(INPUT_Y)) {
		if (osk.buttons[1].click) {
			osk.buttons[1].click = false;
		}
	}
	if (is_pressed(INPUT_START)) {
		osk.buttons[6].click = true;
	}
	if (is_released(INPUT_START)) {
		if (osk.buttons[6].click) {
			osk.buttons[6].click = false;
		}
	}
	if (is_pressed(INPUT_B)) {
		osk.buttons[3].click = true;
	}
	if (is_released(INPUT_B)) {
		if (osk.buttons[3].click) {
			osk.buttons[3].click = false;
		}
	}
	if (is_released(INPUT_A)) {
		for (uint16_t i = osk.page_index; i < osk.page_index + osk.keys_per_page && i < osk.letter_count; i++) {
			if (osk.letters[i].click) {
				osk.letters[i].click = false;
			}
		}
		for (uint16_t i = 0; i < osk.button_count; i++) {
			if (osk.buttons[i].click) {
				osk.buttons[i].click = false;
			}
		}
	}
	if (is_pressed(INPUT_Y)) {
		
	}
	
	
}


void input_element(struct ui_element* element) {
	if (element->v == UI_ACTIVE) {
		if (mouse_moving && input_device == DEVICE_MOUSE) {
			bool hover_element = false;
			for (uint8_t i = 0; i < element->child_count; i++) {
				if (element->children[i]->type == UI_MENU_TEXT && element->children[i]->v == UI_ACTIVE) {
					float max_x = element->children[i]->w + element->children[i]->x;
					float max_y = element->children[i]->h + element->children[i]->y;
					if (mouse_x >= element->children[i]->x &&
						mouse_y >= element->children[i]->y &&
						mouse_x <= max_x &&
						mouse_y <= max_y) {
						if (element->index != i) {
							play_sound(SOUND_MOVE);
							if (element->index < element->child_count) {
								if (element->children[element->index]->hover) {
									element->children[element->index]->hover = false;
								}
							}
							element->index = i;
						}
						element->children[element->index]->hover = true;
						hover_element = true;
						if (current_cursor != CURSOR_HAND) {
							change_cursor(CURSOR_HAND);
							//SetMouseCursor(mouse_cursor);
						}
					}
				}
			}
			// i hate the code below but i need it to reset cursor and menu item highlighting. at least its only done on mouse_moving
			if (!hover_element) {
				if (element->index != UI_NOSELECTION) {
					element->index = UI_NOSELECTION;
				}
				for (uint8_t i = 0; i < element->child_count; i++) {
					if (element->index != i && element->children[i]->hover) {
						element->children[i]->hover = false;
					}
				}
				if (current_cursor != CURSOR_POINTER) {
					change_cursor(CURSOR_POINTER);
					//SetMouseCursor(mouse_cursor);
				}
			}
		} else if (num_controllers > 0 && input_device == DEVICE_GAMEPAD) {
			if (element->index == UI_NOSELECTION) {
				for (uint8_t i = 0; i < element->child_count; i++) {
					if (element->children[i]->type == UI_MENU_TEXT && element->children[i]->v == UI_ACTIVE) {
						element->index = i;
						element->children[i]->hover = true;
						break;
					}
				}
			}
		} // maybe add touch into this block later, idk if handled the same as mouse
		if (is_pressed(INPUT_DOWN)) {
			uint8_t previous_index = element->index;
			if (element->index != UI_NOSELECTION) {
				element->children[element->index]->hover = false;
				if (element->index + 1 == element->child_count) {
					element->index = 0;
				} else {
					element->index++;
				}
			} else {
				element->index = 0;
			}
			while (element->index + 1 < element->child_count && element->children[element->index]->v != UI_ACTIVE) {
				element->index++;
			}
			if (element->children[element->index]->v != UI_ACTIVE) {
				element->index = 0;
				if (element->children[element->index]->v != UI_ACTIVE) {
					while (element->index + 1 < element->child_count && element->children[element->index]->v != UI_ACTIVE) {
						element->index++;
					}
				}
			}
			if (previous_index != element->index) {
				play_sound(SOUND_MOVE);
			}
			if (element->children[element->index]->v == UI_ACTIVE) {
				element->children[element->index]->hover = true;
			}
		}
		if (is_pressed(INPUT_UP)) {
			uint8_t previous_index = element->index;
			if (element->index != UI_NOSELECTION) {
				element->children[element->index]->hover = false;
				if (element->index - 1 < 0) {
					element->index = element->child_count - 1;
				} else {
					element->index--;
				}
			} else {
				element->index = 0;
			}
			while (element->index - 1 >= 0 && element->children[element->index]->v != UI_ACTIVE) {
				element->index--;
			}
			if (element->children[element->index]->v != UI_ACTIVE) {
				element->index = element->child_count - 1;
				if (element->children[element->index]->v != UI_ACTIVE) {
					while (element->index - 1 >= 0 && element->children[element->index]->v != UI_ACTIVE) {
						element->index--;
					}
				}
			}
			if (previous_index != element->index) {
				play_sound(SOUND_MOVE);
			}
			if (element->children[element->index]->v == UI_ACTIVE) {
				element->children[element->index]->hover = true;
			}
		}
		if (element->index != UI_NOSELECTION && element->children[element->index]->v == UI_ACTIVE && is_pressed(INPUT_A) && element->children[element->index]->click) {
			play_sound(SOUND_SELECT);
			element->children[element->index]->click();
		}
	}
}


void draw_element(struct ui_element* element) {
	if (element->v != UI_HIDDEN) {
		for (uint8_t i = 0; i < element->child_count; i++) {
			if (element->children[i]->v != UI_HIDDEN) {
				Color color;
				if (element->children[i]->type == UI_IMAGE && IsTextureValid(element->children[i]->image)) {
					DrawTextureEx(element->children[i]->image, (Vector2) {element->children[i]->x, element->children[i]->y}, 0.0f, element->children[i]->s, WHITE);
				} else if (element->children[i]->type == UI_TEXT || element->children[i]->type == UI_MENU_TEXT) {
					DrawTextEx(element->font, element->children[i]->string[config.language], (Vector2) {(int)roundf(element->children[i]->x + (element->children[i]->h * 0.05f)), (int)roundf(element->children[i]->y + (element->children[i]->h * 0.05f))}, element->children[i]->s, 0.0f, config.theme->background);
					if (element->children[i]->hover && element->children[i]->v == UI_ACTIVE) {
						DrawTextEx(element->font, element->children[i]->string[config.language], (Vector2) {element->children[i]->x, element->children[i]->y}, element->children[i]->s, 0.0f, config.theme->hover);
					} else if (element->children[i]->v == UI_ACTIVE) {
						DrawTextEx(element->font, element->children[i]->string[config.language], (Vector2) {element->children[i]->x, element->children[i]->y}, element->children[i]->s, 0.0f, config.theme->text);
					} else if (element->children[i]->v == UI_DISABLED) {
						DrawTextEx(element->font, element->children[i]->string[config.language], (Vector2) {element->children[i]->x, element->children[i]->y}, element->children[i]->s, 0.0f, config.theme->disabled);
					}
					if (element->index == i && element->children[i]->type == UI_MENU_TEXT) {
						float cursor_size = element->children[i]->h * 0.3f;
						float cursor_padding = cursor_size / 2;
						float cursor_top_x = element->children[i]->x - cursor_padding - cursor_size;
						float cursor_top_y = element->children[i]->y + ((element->children[i]->h - cursor_size) / 2);
						float cursor_bottom_x = cursor_top_x;
						float cursor_bottom_y = cursor_top_y + cursor_size;
						float cursor_right_x = cursor_top_x + cursor_size;
						float cursor_right_y = cursor_top_y + (cursor_size / 2);
						DrawTriangle((Vector2) {cursor_top_x, cursor_top_y}, (Vector2) {cursor_bottom_x + (int)roundf(element->children[i]->h * 0.05f), cursor_bottom_y + (int)roundf(element->children[i]->h * 0.05f)}, (Vector2) {cursor_right_x, cursor_right_y}, config.theme->background);
						DrawTriangle((Vector2) {cursor_top_x, cursor_top_y}, (Vector2) {cursor_bottom_x, cursor_bottom_y}, (Vector2) {cursor_right_x, cursor_right_y}, config.theme->text);
					}
				}
			}
		}
	}
}

void update_element(struct ui_element* element) {
	if (element->padding_pt) {
		element->padding_t = (int)roundf(window.height * element->padding_pt);
	}
	if (element->padding_pb) {
		element->padding_b = (int)roundf(window.height * element->padding_pb);
	}
	if (element->padding_pl) {
		element->padding_l = (int)roundf(window.width * element->padding_pl);
	}
	if (element->padding_pr) {
		element->padding_r = (int)roundf(window.width * element->padding_pr);
	}
	if (element->pw) {
		element->w = (int)roundf((window.width * element->pw) - element->padding_l - element->padding_r);
	} else {
		element->w = (int)roundf(window.width - element->padding_l - element->padding_r);
	}
	if (element->ph) {
		element->h = (int)roundf((window.height * element->ph) - element->padding_t - element->padding_b);
	} else {
		element->h = (int)roundf(window.height - element->padding_t - element->padding_b);
	}
	if (element->px) {
		element->x = (int)roundf((window.width * element->px) + element->padding_l);
	} else {
		element->x = (int)roundf(element->padding_l);
	}
	if (element->py) {
		element->y = (int)roundf((window.height * element->py) + element->padding_t);
	} else {
		element->y = (int)roundf(element->padding_t);
	}
	if (element->direction == UI_TOP_BOTTOM) {
		if (element->child_pgap) {
			element->child_gap = element->h * element->child_pgap;
		}
		element->child_w = element->w;
		int child_h = element->child_h;
		element->child_h = (int)roundf((element->h - (element->child_gap * (element->child_count - 1))) / element->child_count);
		if (!IsFontValid(element->font)) {
			element->font = load_font(element->child_h);
		}
		for (uint8_t i = 0; i < element->child_count; i++) {
			if (element->children[i]->type == UI_TEXT || element->children[i]->type == UI_MENU_TEXT) {
				float max_width;
				float max_height;
				if (element->children[i]->pw) {
					max_width = element->children[i]->pw * window.width;
				} else {
					max_width = element->child_w;
				}
				if (element->children[i]->ph) {
					max_height = element->children[i]->ph * window.height;
				} else {
					max_height = element->child_h;
				}
				float font_height = element->child_h;
				float font_width = MeasureTextEx(element->font, element->children[i]->string[config.language], font_height, 0.0f).x;
				while (font_width > element->child_w || font_width > max_width || font_height > max_height) {
					font_height--;
					font_width = MeasureTextEx(element->font, element->children[i]->string[config.language], font_height, 0.0f).x;
				}
				if (font_height < element->child_h) {
					element->child_h = font_height;
				}
			}
		}
		if (element->child_h != child_h || element->language != config.language) {
			if (IsFontValid(element->font)) {
				unload_font(element->font);
			}
			element->language = config.language;
			element->font = load_font(element->child_h);
		}
		
		// Positioning
		float offset_x = element->x;
		float longest_width = 0;
		int longest_element = -1;
		for (uint16_t i = 0; i < element->child_count; i++) {
			float offset_y = element->y + (element->child_gap * i) + (element->child_h * i);
			if (element->children[i]->type == UI_IMAGE) {
				float max_width;
				float max_height;
				if (element->children[i]->pw) {
					max_width = element->children[i]->pw * window.width;
					if (max_width > element->child_w) {
						max_width = element->child_w;
					}
				} else {
					max_width = element->child_w;
				}
				if (element->children[i]->ph) {
					max_height = element->children[i]->ph * window.height;
					if (max_height > element->child_h) {
						max_height = element->child_h;
					}
				} else {
					max_height = element->child_h;
				}
				float width_scale = max_width / element->children[i]->image.width;
				float height_scale = max_height / element->children[i]->image.height;
				float max_width_height = element->children[i]->image.height * width_scale;
				float max_height_width = element->children[i]->image.width * height_scale;
				if (max_width_height > max_height) {
					element->children[i]->s = height_scale;
					element->children[i]->w = element->children[i]->image.width * height_scale;
					element->children[i]->h = element->children[i]->image.height * height_scale;
				} else {
					element->children[i]->s = width_scale;
					element->children[i]->w = element->children[i]->image.width * width_scale;
					element->children[i]->h = element->children[i]->image.height * width_scale;
				}
			} else if (element->children[i]->type == UI_TEXT || element->children[i]->type == UI_MENU_TEXT) {
				element->children[i]->s = element->child_h;
				element->children[i]->w = MeasureTextEx(element->font, element->children[i]->string[config.language], element->child_h, 0.0f).x;
				element->children[i]->h = MeasureTextEx(element->font, element->children[i]->string[config.language], element->child_h, 0.0f).y;
			}
			if (element->children[i]->w > longest_width) {
				longest_width = element->children[i]->w;
				longest_element = i;
			}
		}
		// Sloppyness, testing how to go about this. will need this for popup menus
		if (longest_element > -1) {
			float offset_y = element->y + (element->child_gap * longest_element) + (element->child_h * longest_element);
			if (element->align_x == UI_LEFT) {
				element->children[longest_element]->x = offset_x;
			} else if (element->align_x == UI_RIGHT) {
				element->children[longest_element]->x = offset_x + element->child_w - element->children[longest_element]->w;
			} else { // UI_CENTER
				element->children[longest_element]->x = offset_x + (element->child_w / 2) - (element->children[longest_element]->w / 2);
			}
			if (element->align_y == UI_TOP) {
				element->children[longest_element]->y = offset_y;
			} else if (element->align_y == UI_BOTTOM) {
				element->children[longest_element]->y = offset_y + element->child_h - element->children[longest_element]->h;
			} else { // UI_CENTER
				element->children[longest_element]->y = offset_y + (element->child_h / 2) - (element->children[longest_element]->h / 2);
			}
		}
		for (uint16_t i = 0; i < element->child_count; i++) {
			float offset_y = element->y + (element->child_gap * i) + (element->child_h * i);
			if (i != longest_element) {
				if (element->children[i]->salign == UI_LEFT) {
					element->children[i]->x = element->children[longest_element]->x;
					if (element->align_y == UI_TOP) {
						element->children[i]->y = offset_y;
					} else if (element->align_y == UI_BOTTOM) {
						element->children[i]->y = offset_y + element->child_h - element->children[i]->h;
					} else { // UI_CENTER
						element->children[i]->y = offset_y + (element->child_h / 2) - (element->children[i]->h / 2);
					}
				} else if (element->children[i]->salign == UI_RIGHT) {
					element->children[i]->x = element->children[longest_element]->x + element->children[longest_element]->w - element->children[i]->w;
					if (element->align_y == UI_TOP) {
						element->children[i]->y = offset_y;
					} else if (element->align_y == UI_BOTTOM) {
						element->children[i]->y = offset_y + element->child_h - element->children[i]->h;
					} else { // UI_CENTER
						element->children[i]->y = offset_y + (element->child_h / 2) - (element->children[i]->h / 2);
					}
				} else {
					if (element->align_x == UI_LEFT) {
						element->children[i]->x = offset_x;
					} else if (element->align_x == UI_RIGHT) {
						element->children[i]->x = offset_x + element->child_w - element->children[i]->w;
					} else { // UI_CENTER
						element->children[i]->x = offset_x + (element->child_w / 2) - (element->children[i]->w / 2);
					}
					if (element->align_y == UI_TOP) {
						element->children[i]->y = offset_y;
					} else if (element->align_y == UI_BOTTOM) {
						element->children[i]->y = offset_y + element->child_h - element->children[i]->h;
					} else { // UI_CENTER
						element->children[i]->y = offset_y + (element->child_h / 2) - (element->children[i]->h / 2);
					}
				}
			}
		}
		// I can't seem to fin compare element->child_h in an if statement, it just returns 0
		//if (!IsFontValid(element->font) || element->child_h != child_h || ) {
			//printf("%f != %f\n", element->child_h, child_h);
			//unload_font(element->font);
			//element->font = load_font(element->child_h);
			
		//}
	} else if (element->direction == UI_LEFT_RIGHT) {
	}
}
