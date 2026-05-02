struct keyboard {
	const char* symbols[6][4];
	uint8_t x, y, pages; // shift is how many different collection of symbols the shift key will cycle through (up to 6 pages total)
	Font font;
};

// i'll need to seperate this out into a seperate file so i can automate the codepoint parsing for each language

struct keyboard keyboard_en = {
	.symbols = {
		{"abcdefghij", "klmnopqrst", "uvwxyz,.-=", "1234567890"},
		{"ABCDEFGHIJ", "KLMNOPQRST", "UVWXYZ<>_+", "!@#$%^&*()"},
	},
	.x = 0, .y = 0, .pages = 2,
};
struct keyboard keyboard_jp = {
	.symbols = {
		{"abcdefghij", "klmnopqrst", "uvwxyz,.-=", "1234567890"},
		{"ABCDEFGHIJ", "KLMNOPQRST", "UVWXYZ。゜_+", "!@#$%^&*¥ー"},
		{"あぁいぃうぅえぇおぉ", "かきくけこさしすせそ", "たちつてとなにぬねの", "はひふへほまみむめも"},
		{"やゃゆゅよょらりるれ", "ろわをんっがぎぐげご", "ざじずぜぞだぢづでど", "ばびぶべぼぱぴぷぺぽ"},
		{"アァイィウゥエェオォ", "カキクケコサシスセソ", "タチツテトナニヌネノ", "ハヒフヘホマミムメモ"},
		{"ヤャユュヨョラリルレ", "ロワヲンッガギグゲゴ", "ザジズゼゾダヂヅデド", "バビブベボパピプペポ"}
	},
	.x = 0, .y = 0, .pages = 6,
};

// fin hell i have no idea how to layout japanese with hiragana and katakana
// much less chinese....

struct keyboard* keyboards[LANGUAGE] = {
	[ENGLISH] = &keyboard_en,
	[JAPANESE] = &keyboard_jp,
	[GERMAN] = &keyboard_en,
	[FRENCH] = &keyboard_en,
	[ITALIAN] = &keyboard_en,
	[SPANISH] = &keyboard_en,
	[KOREAN] = &keyboard_en,
	[CHINESE_SIMPLIFIED] = &keyboard_en,
	[CHINESE] = &keyboard_en
};
