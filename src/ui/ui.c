#include "keyboard.c"

void reset_element(struct ui_element* element) {
	if (element->index != UI_NOSELECTION) {
		element->children[element->index]->hover = false;
		element->index = UI_NOSELECTION;
	}
}



void draw_keyboard(struct onscreen_keyboard* osk) {
	DrawRectangle(0, 0, window.width, window.height, (Color) {0,0,0,128});
	for (uint8_t y = 0; y < 4; y++) {
		const char *str = keyboards[osk->language]->symbols[osk->page][y];
		for (int i = 0, x = 0; str[i] != '\0' && x < 10; x++) {
			uint16_t number = (uint16_t)((y * 10) + x);
			// this is a stupid way of getting advance index but it works, hopefully ill find better
			int advance = 0;
			int codepoint = GetCodepoint(&keyboards[osk->language]->symbols[osk->page][y][i], &advance);
			if (osk->keys[number].clicked) {
				DrawRectangleRounded((Rectangle) {osk->keys[number].box.x, osk->keys[number].box.y, osk->key_width - (osk->line_padding * 2), osk->key_height - (osk->line_padding * 2)}, 0.5, 256, config.theme->background);
				DrawRectangleRoundedLinesEx((Rectangle) {osk->keys[number].box.x, osk->keys[number].box.y, osk->key_width - (osk->line_padding * 2), osk->key_height - (osk->line_padding * 2)}, 0.5, 256, osk->line_padding, config.theme->text);
				DrawTextCodepoint(osk->font, osk->keys[number].codepoint, osk->keys[number].key, osk->key_height, config.theme->tr_background);
			} else if (osk->keys[number].hover) {
				DrawRectangleRounded((Rectangle) {osk->keys[number].box.x, osk->keys[number].box.y, osk->key_width - (osk->line_padding * 2), osk->key_height - (osk->line_padding * 2)}, 0.5, 256, config.theme->text);
				DrawRectangleRoundedLinesEx((Rectangle) {osk->keys[number].box.x, osk->keys[number].box.y, osk->key_width - ((window.height * 0.001f) * 2), osk->key_height - (osk->line_padding * 2)}, 0.5, 256, osk->line_padding, config.theme->background);
				DrawTextCodepoint(osk->font, osk->keys[number].codepoint, osk->keys[number].key, osk->key_height, config.theme->background);
			} else {
				DrawRectangleRounded((Rectangle) {osk->keys[number].box.x, osk->keys[number].box.y, osk->key_width - (osk->line_padding * 2), osk->key_height - (osk->line_padding * 2)}, 0.5, 256, config.theme->background);
				DrawRectangleRoundedLinesEx((Rectangle) {osk->keys[number].box.x, osk->keys[number].box.y, osk->key_width - (osk->line_padding * 2), osk->key_height - (osk->line_padding * 2)}, 0.5, 256, osk->line_padding, config.theme->text);
				DrawTextCodepoint(osk->font, osk->keys[number].codepoint, osk->keys[number].key, osk->key_height, config.theme->text);
			}
			i += advance;
			DrawRectangleRounded((Rectangle) {osk->submit.box.x, osk->submit.box.y, osk->submit.box_size.x, osk->submit.box_size.y}, 0.5, 256, config.theme->background);
			DrawRectangleRoundedLinesEx((Rectangle) {osk->submit.box.x, osk->submit.box.y, osk->submit.box_size.x, osk->submit.box_size.y}, 0.5, 256, window.height * 0.001f, config.theme->text);
			DrawTextCodepoint(osk->font, osk->submit.codepoint, osk->submit.key, osk->key_height, config.theme->text);
		}
	}
}

void update_keyboard(struct onscreen_keyboard* osk) {
	osk->key_width = (window.width * 0.98f) / 10;
	osk->key_padding = (window.height / 2) * 0.025f;
	osk->key_height = ((window.height / 2) - (osk->key_padding * 7)) / 6;
	uint8_t language;
	if (keyboards[config.language] == NULL) {
		osk->language = ENGLISH;
	} else {
		osk->language = config.language;
	}
	if (IsFontValid(osk->font)) {
		UnloadFont(osk->font);
	}
	osk->font = load_font(osk->key_height, osk->language);
	int largest_char = 0;
	float largest_width = 0;
	for (uint8_t p = 0; p < keyboards[osk->language]->pages; p++) {
		for (uint8_t y = 0; y < 4; y++) {
			const char *str = keyboards[osk->language]->symbols[p][y];
			for (int i = 0, x = 0; str[i] != '\0' && x < 10; x++) {
				uint16_t number = (uint16_t)((y * 10) + x);
				int advance = 0;
				osk->keys[number].codepoint = GetCodepoint(&keyboards[osk->language]->symbols[p][y][i], &advance);
				float current_width = MeasureTextCodepoints(osk->font, &osk->keys[number].codepoint, 1, osk->key_height, 0.0f).x;
				if (current_width > largest_width) {
					largest_width = current_width;
					largest_char = osk->keys[number].codepoint;
				}
				i += advance;
			}
		}
	}
	osk->width = largest_width * 10;
	while (osk->width > (window.width * 0.98f)) {
		osk->key_height--;
		largest_width = MeasureTextCodepoints(osk->font, &largest_char, 1, osk->key_height, 0.0f).x;
		osk->width = largest_width * 10;
	}
	osk->key_width = largest_width;
	osk->height = osk->key_height * 6;
	osk->key_padding = osk->height * 0.025f;
	osk->height = osk->height + (osk->key_padding * 7);
	osk->width = largest_width * 10;
	osk->x = (window.width / 2) - (osk->width / 2);
	osk->y = window.height - osk->height;
	for (uint8_t y = 0; y < 4; y++) {
		const char *str = keyboards[osk->language]->symbols[osk->page][y];
		for (int i = 0, x = 0; str[i] != '\0' && x < 10; x++) {
			uint16_t number = (uint16_t)((y * 10) + x);
			int advance = 0;
			osk->keys[number].codepoint = GetCodepoint(&keyboards[osk->language]->symbols[osk->page][y][i], &advance);
			osk->keys[number].key_size = MeasureTextCodepoints(osk->font, &osk->keys[number].codepoint, 1, osk->key_height, 0.0f);
			osk->keys[number].box.x = osk->x + (osk->key_width * x);
			osk->keys[number].box.y = osk->y + (osk->key_height * (y + 1)) + (osk->key_padding * (y + 1));
			osk->keys[number].key.x = osk->keys[number].box.x + (osk->key_width / 2) - (osk->keys[number].key_size.x / 2);
			osk->keys[number].key.y = osk->keys[number].box.y + (osk->key_height / 2) - (osk->keys[number].key_size.y / 2);
			i += advance;
		}
	}
	osk->line_padding = window.height * 0.001f;
	
	osk->submit.box_size.x = osk->key_width * 3;
	osk->submit.box_size.y = osk->key_height;
	osk->submit.box.x = osk->x + osk->width - osk->submit.box_size.x;
	osk->submit.box.y = osk->keys[39].key.y + osk->submit.box_size.y + osk->key_padding;
	int advance = 0;
	//osk->keys[number].codepoint = GetCodepoint(&keyboards[osk->language]->symbols[p][y][i], &advance);
	osk->submit.codepoint = GetCodepoint("⏎", &advance);
	osk->submit.key_size = MeasureTextCodepoints(osk->font, &osk->submit.codepoint, 1, osk->key_height, 0.0f);
	osk->submit.key.x = osk->submit.box.x + (osk->submit.box_size.x / 2) - (osk->submit.key_size.x / 2);
	osk->submit.key.y = osk->submit.box.y + (osk->submit.box_size.y / 2) - (osk->submit.key_size.y / 2);
	// 🗏
	// ⏎ ↵
	printf("updating\n");
}


void input_keyboard(struct onscreen_keyboard* osk) {
	if (is_pressed(INPUT_Y)) {
		if (osk->page + 1 >= keyboards[osk->language]->pages) {
			osk->page = 0;
		} else {
			osk->page++;
		}
		update_keyboard(osk);
	}
	if (mouse_moving && input_device == DEVICE_MOUSE) {
		bool hover = false;
		for (uint16_t i = 0; i < 40; i++) {
			if (mouse_x > osk->keys[i].box.x &&
				mouse_x < osk->keys[i].box.x + osk->key_width &&
				mouse_y > osk->keys[i].box.y &&
				mouse_y < osk->keys[i].box.y + osk->key_height) {
				if (!osk->keys[i].hover) {
					osk->keys[i].hover = true;
				}
				if (current_cursor != CURSOR_HAND) {
					change_cursor(CURSOR_HAND);
				}
				if (osk->index != i) {
					osk->index = i;
					printf("Set index: %i:%i\n", i, osk->index);
				}
				hover = true;
				break;
			}
		}
		if (!hover) {
			for (uint16_t i = 0; i < 40; i++) {
				if (osk->index != UI_NOSELECTION) {
					osk->index = UI_NOSELECTION;
				}
				if (osk->keys[i].hover) {
					osk->keys[i].hover = false;
					if (current_cursor != CURSOR_POINTER) {
						change_cursor(CURSOR_POINTER);
					}
				}
			}
		} else {
			for (uint16_t i = 0; i < 40; i++) {
				if (i != osk->index) {
					if (osk->keys[i].hover) {
						osk->keys[i].hover = false;
						if (current_cursor != CURSOR_POINTER) {
							change_cursor(CURSOR_POINTER);
						}
					}
				}
			}
		}
	}
	if (is_pressed(INPUT_A)) {
		printf("Clicked: %i\n", osk->index);
		if (osk->index != UI_NOSELECTION) {
			if (!osk->keys[osk->index].clicked) {
				osk->keys[osk->index].clicked = true;
			}
		}
	}
	if (is_released(INPUT_A)) {
		for (uint16_t i = 0; i < 40; i++) {
			if (osk->keys[i].clicked) {
				osk->keys[i].clicked = false;
			}
		}
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
							printf("changing\n");
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
					printf("resetting\n");
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
			element->font = load_font(element->child_h, config.language);
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
			element->font = load_font(element->child_h, config.language);
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
