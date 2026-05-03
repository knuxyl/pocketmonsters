	for (uint8_t y = 0; y < keyboard.rows; y++) {
		const char *str = keyboard.symbols[osk.page][y];
		for (int i = 0, x = 0; str[i] != '\0' && x < keyboard.columns; x++) {
			uint16_t number = (uint16_t)((y * 10) + x);
			int advance = 0;
			osk.keys[number].codepoint = GetCodepoint(&keyboard.symbols[osk.page][y][i], &advance);
			printf("Codepoint: %i\n", osk.keys[number].codepoint);
			osk.keys[number].key_size = MeasureTextCodepoints(osk.font, &osk.keys[number].codepoint, 1, osk.key_height, 0.0f);
			osk.keys[number].box.x = osk.x + (osk.key_width * x);
			osk.keys[number].box.y = osk.y + (osk.key_height * (y + 1)) + (osk.key_padding * (y + 1));
			osk.keys[number].key.x = osk.keys[number].box.x + (osk.key_width / 2) - (osk.keys[number].key_size.x / 2);
			osk.keys[number].key.y = osk.keys[number].box.y + (osk.key_height / 2) - (osk.keys[number].key_size.y / 2);
			i += advance;
		}
	}
	osk.line_padding = window.height * 0.001f;
	for (uint8_t i = 0; i < osk.button_count; i++) {
		
	
	
	
	
	osk.submit.box_size.x = osk.key_width * 3;
	osk.submit.box_size.y = osk.key_height;
	osk.submit.box.x = osk.x + osk.width - osk.submit.box_size.x;
	osk.submit.box.y = osk.keys[39].key.y + osk.submit.box_size.y + osk.key_padding;
	int advance = 0;
	//osk.keys[number].codepoint = GetCodepoint(&keyboard.symbols[p][y][i], &advance);
	osk.submit.codepoint = GetCodepoint("⮐", &advance);
	osk.submit.key_size = MeasureTextCodepoints(osk.font, &osk.submit.codepoint, 1, osk.key_height, 0.0f);
	osk.submit.key.x = osk.submit.box.x + (osk.submit.box_size.x / 2) - (osk.submit.key_size.x / 2);
	osk.submit.key.y = osk.submit.box.y + (osk.submit.box_size.y / 2) - (osk.submit.key_size.y / 2);
	
	osk.cancel.box_size.x = osk.key_width * 3;
	osk.cancel.box_size.y = osk.key_height;
	osk.cancel.box.x = osk.x;
	osk.cancel.box.y = osk.keys[39].key.y + osk.cancel.box_size.y + osk.key_padding;
	advance = 0;
	//osk.keys[number].codepoint = GetCodepoint(&keyboard.symbols[p][y][i], &advance);
	osk.cancel.codepoint = GetCodepoint("×", &advance);
	osk.cancel.key_size = MeasureTextCodepoints(osk.font, &osk.cancel.codepoint, 1, osk.key_height, 0.0f);
	osk.cancel.key.x = osk.cancel.box.x + (osk.cancel.box_size.x / 2) - (osk.cancel.key_size.x / 2);
	osk.cancel.key.y = osk.cancel.box.y + (osk.cancel.box_size.y / 2) - (osk.cancel.key_size.y / 2);
	
	
	osk.space.box_size.x = osk.key_width * 4;
	osk.space.box_size.y = osk.key_height;
	osk.space.box.x = osk.x + osk.key_width * 3;
	osk.space.box.y = osk.keys[39].key.y + osk.space.box_size.y + osk.key_padding;
	advance = 0;
	//osk.keys[number].codepoint = GetCodepoint(&keyboard.symbols[p][y][i], &advance);
	osk.space.codepoint = GetCodepoint("␣", &advance);
	osk.space.key_size = MeasureTextCodepoints(osk.font, &osk.space.codepoint, 1, osk.key_height, 0.0f);
	osk.space.key.x = osk.space.box.x + (osk.space.box_size.x / 2) - (osk.space.key_size.x / 2);
	osk.space.key.y = osk.space.box.y + (osk.space.box_size.y / 2) - (osk.space.key_size.y / 2);
	
	
	osk.backspace.box_size.x = osk.key_width * 3;
	osk.backspace.box_size.y = osk.key_height;
	osk.backspace.box.x = osk.x + osk.width - (osk.key_width * 3);
	osk.backspace.box.y = osk.y;
	advance = 0;
	//osk.keys[number].codepoint = GetCodepoint(&keyboard.symbols[p][y][i], &advance);
	osk.backspace.codepoint = GetCodepoint("⌫", &advance);
	osk.backspace.key_size = MeasureTextCodepoints(osk.font, &osk.backspace.codepoint, 1, osk.key_height, 0.0f);
	osk.backspace.key.x = osk.backspace.box.x + (osk.backspace.box_size.x / 2) - (osk.backspace.key_size.x / 2);
	osk.backspace.key.y = osk.backspace.box.y + (osk.backspace.box_size.y / 2) - (osk.backspace.key_size.y / 2);
	
	
	
	
	
	
	
	
	DrawRectangle(0, 0, window.width, window.height, (Color) {0,0,0,128});
	for (uint8_t y = 0; y < 4; y++) {
		const char *str = keyboard.symbols[osk.page][y];
		for (int i = 0, x = 0; str[i] != '\0' && x < 10; x++) {
			uint16_t number = (uint16_t)((y * 10) + x);
			// this is a stupid way of getting advance index but it works, hopefully ill find better
			int advance = 0;
			int codepoint = GetCodepoint(&keyboard.symbols[osk.page][y][i], &advance);
			Color border;
			Color background;
			Color text;
			if (osk.keys[number].clicked) {
				background = config.theme->ok;
				border = config.theme->background;
			} else if (osk.keys[number].hover) {
				background = config.theme->hover;
				border = config.theme->text;
			} else {
				DrawRectangleRounded((Rectangle) {osk.keys[number].box.x, osk.keys[number].box.y, osk.key_width - (osk.line_padding * 2), osk.key_height - (osk.line_padding * 2)}, 0.5, 256, config.theme->background);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.keys[number].box.x, osk.keys[number].box.y, osk.key_width - (osk.line_padding * 2), osk.key_height - (osk.line_padding * 2)}, 0.5, 256, osk.line_padding, config.theme->text);
			}
			DrawRectangleRounded((Rectangle) {osk.keys[number].box.x, osk.keys[number].box.y, osk.key_width - (osk.line_padding * 2), osk.key_height - (osk.line_padding * 2)}, 0.5, 256, config.theme->background);
			DrawRectangleRoundedLinesEx((Rectangle) {osk.keys[number].box.x, osk.keys[number].box.y, osk.key_width - (osk.line_padding * 2), osk.key_height - (osk.line_padding * 2)}, 0.5, 256, osk.line_padding, config.theme->text);
			DrawTextCodepoint(osk.font, osk.keys[number].codepoint, osk.keys[number].key, osk.key_height, config.theme->text);
			i += advance;
			if (osk.submit.clicked) {
				DrawRectangleRounded((Rectangle) {osk.submit.box.x, osk.submit.box.y, osk.submit.box_size.x, osk.submit.box_size.y}, 0.5, 256, config.theme->ok);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.submit.box.x, osk.submit.box.y, osk.submit.box_size.x, osk.submit.box_size.y}, 0.5, 256, osk.line_padding, config.theme->background);
				
			} else if (osk.submit.hover) {
				DrawRectangleRounded((Rectangle) {osk.submit.box.x, osk.submit.box.y, osk.submit.box_size.x, osk.submit.box_size.y}, 0.5, 256, config.theme->hover);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.submit.box.x, osk.submit.box.y, osk.submit.box_size.x, osk.submit.box_size.y}, 0.5, 256, osk.line_padding, config.theme->text);
			} else {
				DrawRectangleRounded((Rectangle) {osk.submit.box.x, osk.submit.box.y, osk.submit.box_size.x, osk.submit.box_size.y}, 0.5, 256, config.theme->ok);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.submit.box.x, osk.submit.box.y, osk.submit.box_size.x, osk.submit.box_size.y}, 0.5, 256, osk.line_padding, config.theme->text);
			}
			DrawTextCodepoint(osk.font, osk.submit.codepoint, osk.submit.key, osk.key_height, config.theme->text);
			if (osk.cancel.clicked) {
				DrawRectangleRounded((Rectangle) {osk.cancel.box.x, osk.cancel.box.y, osk.cancel.box_size.x, osk.cancel.box_size.y}, 0.5, 256, config.theme->disabled);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.cancel.box.x, osk.cancel.box.y, osk.cancel.box_size.x, osk.cancel.box_size.y}, 0.5, 256, osk.line_padding, config.theme->background);
				
			} else if (osk.cancel.hover) {
				DrawRectangleRounded((Rectangle) {osk.cancel.box.x, osk.cancel.box.y, osk.cancel.box_size.x, osk.cancel.box_size.y}, 0.5, 256, config.theme->hover);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.cancel.box.x, osk.cancel.box.y, osk.cancel.box_size.x, osk.cancel.box_size.y}, 0.5, 256, osk.line_padding, config.theme->text);
			} else {
				DrawRectangleRounded((Rectangle) {osk.cancel.box.x, osk.cancel.box.y, osk.cancel.box_size.x, osk.cancel.box_size.y}, 0.5, 256, config.theme->disabled);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.cancel.box.x, osk.cancel.box.y, osk.cancel.box_size.x, osk.cancel.box_size.y}, 0.5, 256, osk.line_padding, config.theme->text);
			}
			DrawTextCodepoint(osk.font, osk.cancel.codepoint, osk.cancel.key, osk.key_height, config.theme->text);
			
			if (osk.space.clicked) {
				DrawRectangleRounded((Rectangle) {osk.space.box.x, osk.space.box.y, osk.space.box_size.x, osk.space.box_size.y}, 0.5, 256, config.theme->ok);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.space.box.x, osk.space.box.y, osk.space.box_size.x, osk.space.box_size.y}, 0.5, 256, osk.line_padding, config.theme->background);
				
			} else if (osk.space.hover) {
				DrawRectangleRounded((Rectangle) {osk.space.box.x, osk.space.box.y, osk.space.box_size.x, osk.space.box_size.y}, 0.5, 256, config.theme->hover);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.space.box.x, osk.space.box.y, osk.space.box_size.x, osk.space.box_size.y}, 0.5, 256, osk.line_padding, config.theme->text);
			} else {
				DrawRectangleRounded((Rectangle) {osk.space.box.x, osk.space.box.y, osk.space.box_size.x, osk.space.box_size.y}, 0.5, 256, config.theme->background);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.space.box.x, osk.space.box.y, osk.space.box_size.x, osk.space.box_size.y}, 0.5, 256, osk.line_padding, config.theme->text);
			}
			DrawTextCodepoint(osk.font, osk.space.codepoint, osk.space.key, osk.key_height, config.theme->text);
			
			if (osk.backspace.clicked) {
				DrawRectangleRounded((Rectangle) {osk.backspace.box.x, osk.backspace.box.y, osk.backspace.box_size.x, osk.backspace.box_size.y}, 0.5, 256, config.theme->invalid);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.backspace.box.x, osk.backspace.box.y, osk.backspace.box_size.x, osk.backspace.box_size.y}, 0.5, 256, osk.line_padding, config.theme->background);
				
			} else if (osk.backspace.hover) {
				DrawRectangleRounded((Rectangle) {osk.backspace.box.x, osk.backspace.box.y, osk.backspace.box_size.x, osk.backspace.box_size.y}, 0.5, 256, config.theme->hover);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.backspace.box.x, osk.backspace.box.y, osk.backspace.box_size.x, osk.backspace.box_size.y}, 0.5, 256, osk.line_padding, config.theme->text);
			} else {
				DrawRectangleRounded((Rectangle) {osk.backspace.box.x, osk.backspace.box.y, osk.backspace.box_size.x, osk.backspace.box_size.y}, 0.5, 256, config.theme->invalid);
				DrawRectangleRoundedLinesEx((Rectangle) {osk.backspace.box.x, osk.backspace.box.y, osk.backspace.box_size.x, osk.backspace.box_size.y}, 0.5, 256, osk.line_padding, config.theme->text);
			}
			DrawTextCodepoint(osk.font, osk.backspace.codepoint, osk.backspace.key, osk.key_height, config.theme->text);
			
		}
	}
	
	
	
	
	
	
	
	float line_padding;
	float height;
	float width;
	float key_height;
	float key_width;
	float key_padding;
	float x;
	float y;
	uint8_t page;
	struct key keys[40];
	struct key buttons[6];
	uint8_t row_count;
	uint8_t column_count;
	uint8_t key_count;
	uint8_t button_count;
	uint16_t index;

struct keyboard keyboard = {
	.symbols = {
		{"abcdefghij", "klmnopqrst", "uvwxyz,.-'", "1234567890"},
		{"ABCDEFGHIJ", "KLMNOPQRST", "UVWXYZ<>_\"", "!@#$%^&*()"},
		{"àâäæéèêëíì", "îïôöœùûüÿç", "ÀÂÄÆÉÈÊËÍÌ", "ÎÏÔÖŒÙÛÜŸÇ"},
		{"ñß~{}《》□=|+", "Ñẞ[]【】「」『』", "?¿♂♀«»⁂∴⌘܀", "〜ー。・゜;:…，゛"},
		{"あぁいぃうぅえぇおぉ", "かきくけこさしすせそ", "たちつてとなにぬねの", "はひふへほまみむめも"},
		{"やゃゆゅよょらりるれ", "ろわをんっがぎぐげご", "ざじずぜぞだぢづでど", "ばびぶべぼぱぴぷぺぽ"},
		{"アァイィウゥエェオォ", "カキクケコサシスセソ", "タチツテトナニヌネノ", "ハヒフヘホマミムメモ"},
		{"ヤャユュヨョラリルレ", "ロワヲンッガギグゲゴ", "ザジズゼゾダヂヅデド", "バビブベボパピプペポ"},
		{"ㄱㄲㄴㄷㄸㄹㅁㅂㅃㅅ", "ㅆㅇㅈㅉㅊㅋㅌㅍㅎㅏ", "ㅐㅑㅒㅓㅔㅕㅖㅗㅘㅙ", "ㅚㅛㅜㅝㅞㅟㅠㅡㅢㅣ"},
		{"∅ㄱㄲㄳㄴㄵㄶㄷㄹㄺ", "ㄻㄼㄽㄾㄿㅀㅁㅂㅄㅅ", "ㅆㅇㅈㅊㅋㅌㅍㅎ©™", "¤¢£₤€₣₽₱₩¥"},
		{"абвгдеёжзи", "йклмнопрст", "уфхцчшщъыь", "эюя✦✧≛⓵✪▯⛩"},
		{"АБВГДЕЁЖЗИ", "ЙКЛМНОПРСТ", "УФХЦЧШЩЪЫЬ", "ЭЮЯ●○◆◇⭑⭒⍟"}
	},
	.x = 0, .y = 0, .pages = 12, .rows = 6, .columns = 10
};









if (is_pressed(INPUT_Y)) {
		if (osk.page + 1 >= keyboard.pages) {
			osk.page = 0;
		} else {
			osk.page++;
		}
		update_keyboard(osk);
	}
	if (mouse_moving && input_device == DEVICE_MOUSE) {
		bool hover = false;
		for (uint16_t i = 0; i < 40; i++) {
			if (mouse_x > osk.keys[i].box.x &&
				mouse_x < osk.keys[i].box.x + osk.key_width &&
				mouse_y > osk.keys[i].box.y &&
				mouse_y < osk.keys[i].box.y + osk.key_height) {
				if (!osk.keys[i].hover) {
					osk.keys[i].hover = true;
				}
				if (osk.index != i) {
					osk.index = i;
				}
				hover = true;
				break;
			}
		}
		if (mouse_x > osk.submit.box.x &&
			mouse_x < osk.submit.box.x + osk.submit.box_size.x &&
			mouse_y > osk.submit.box.y &&
			mouse_y < osk.submit.box.y + osk.submit.box_size.y) {
			if (!osk.submit.hover) {
				osk.submit.hover = true;
			}
			if (osk.index != 43) {
				osk.index = 43;
			}
			hover = true;
		} else {
			if (osk.submit.hover) {
				osk.submit.hover = false;
			}
			if (osk.index == 43) {
				osk.index = UI_NOSELECTION;
			}
		}
		if (mouse_x > osk.cancel.box.x &&
			mouse_x < osk.cancel.box.x + osk.cancel.box_size.x &&
			mouse_y > osk.cancel.box.y &&
			mouse_y < osk.cancel.box.y + osk.cancel.box_size.y) {
			if (!osk.cancel.hover) {
				osk.cancel.hover = true;
			}
			if (osk.index != 42) {
				osk.index = 42;
			}
			hover = true;
		} else {
			if (osk.cancel.hover) {
				osk.cancel.hover = false;
			}
			if (osk.index == 42) {
				osk.index = UI_NOSELECTION;
			}
		}
		if (mouse_x > osk.space.box.x &&
			mouse_x < osk.space.box.x + osk.space.box_size.x &&
			mouse_y > osk.space.box.y &&
			mouse_y < osk.space.box.y + osk.space.box_size.y) {
			if (!osk.space.hover) {
				osk.space.hover = true;
			}
			if (osk.index != 40) {
				osk.index = 40;
			}
			hover = true;
		} else {
			if (osk.space.hover) {
				osk.space.hover = false;
			}
			if (osk.index == 40) {
				osk.index = UI_NOSELECTION;
			}
		}
		if (mouse_x > osk.backspace.box.x &&
			mouse_x < osk.backspace.box.x + osk.backspace.box_size.x &&
			mouse_y > osk.backspace.box.y &&
			mouse_y < osk.backspace.box.y + osk.backspace.box_size.y) {
			if (!osk.backspace.hover) {
				osk.backspace.hover = true;
			}
			if (osk.index != 41) {
				osk.index = 41;
			}
			hover = true;
		} else {
			if (osk.backspace.hover) {
				osk.backspace.hover = false;
			}
			if (osk.index == 41) {
				osk.index = UI_NOSELECTION;
			}
		}
		if (!hover) {
			if (osk.index != UI_NOSELECTION) {
				osk.index = UI_NOSELECTION;
			}
			if (current_cursor != CURSOR_POINTER) {
				change_cursor(CURSOR_POINTER);
			}
			for (uint16_t i = 0; i < 40; i++) {
				if (osk.keys[i].hover) {
					osk.keys[i].hover = false;
				}
			}
		} else {
			if (current_cursor != CURSOR_HAND) {
				change_cursor(CURSOR_HAND);
			}
			for (uint16_t i = 0; i < 40; i++) {
				if (i != osk.index) {
					if (osk.keys[i].hover) {
						osk.keys[i].hover = false;
					}
				}
			}
		}
	}
	if (is_pressed(INPUT_A)) {
		if (osk.index != UI_NOSELECTION) {
			if (osk.index < 40) {
				if (!osk.keys[osk.index].clicked) {
					osk.keys[osk.index].clicked = true;
				}
			} else {
				if (osk.index == 43) {
					osk.submit.clicked = true;
				}
				if (osk.index == 42) {
					osk.cancel.clicked = true;
				}
				if (osk.index == 40) {
					osk.space.clicked = true;
				}
				if (osk.index == 41) {
					osk.backspace.clicked = true;
				}
			}
		}
	}
	if (is_released(INPUT_A)) {
		for (uint16_t i = 0; i < 40; i++) {
			if (osk.keys[i].clicked) {
				osk.keys[i].clicked = false;
			}
		}
		if (osk.submit.clicked) {
			osk.submit.clicked = false;
		}
		if (osk.cancel.clicked) {
			osk.cancel.clicked = false;
		}
		if (osk.space.clicked) {
			osk.space.clicked = false;
		}
		if (osk.backspace.clicked) {
			osk.backspace.clicked = false;
		}
	}
