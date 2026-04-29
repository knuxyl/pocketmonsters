struct keyboard {
	const char* symbol[6][4];
	uint8_t x, y, shift; // shift is how many different collection of symbols the shift key will cycle through (up to 6 pages total)
};

// i'll need to seperate this out into a seperate file so i can automate the codepoint parsing for each language

struct keyboard keyboard_en = {
	.symbol = {
		{"1234567890", "abcdefghij", "klmnopqrst", "uvwxyz,.-="},
		{"!@#$%^&*()", "ABCDEFGHIJ", "KLMNOPQRST", "UVWXYZ<>_+"},
	},
	.x = 0, .y = 0, .shift = 2
};

// fin hell i have no idea how to layout japanese with hiragana and katakana
// much less chinese....

struct keyboard* keyboards[LANGUAGE] = {
	[ENGLISH] = &keyboard_en,
};
