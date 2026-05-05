struct keyboard_letter {
	Vector2 letter_position, letter_size;
	Vector2 slot_position, background_position;
	//Vector2 box_position;
	bool hover;
	bool clicked;
};
struct keyboard_button {
	const char* letter;
	uint8_t align, relation;
	uint16_t index;
	uint8_t space_width;
	Vector2 letter_position, letter_size;
	Vector2 slot_position, slot_size;
	Vector2 background_position, background_size;
	//uint8_t color_background, color_click;
	bool hover;
	bool clicked;
	function_void* click;
};
const char* keyboard_letters[] = {
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
	"k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
	"u", "v", "w", "x", "y", "z", ",", ".", ";", "'",
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",

	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
	"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
	"U", "V", "W", "X", "Y", "Z", "<", ">", ":", "\"",
	"!", "@", "#", "$", "%", "^", "&", "*", "(", ")",

	"à", "â", "ä", "æ", "é", "è", "ê", "ë", "í", "ì",
	"î", "ï", "ô", "ö", "œ", "ù", "û", "ü", "ÿ", "ç",
	"À", "Â", "Ä", "Æ", "É", "È", "Ê", "Ë", "Í", "Ì",
	"Î", "Ï", "Ô", "Ö", "Œ", "Ù", "Û", "Ü", "Ÿ", "Ç",
	
	"ñ", "ß", "-", "=", "?", "`", "「", "」", "[", "]",
	"Ñ", "ẞ", "_", "+", "¿", "~", "『", "』", "{", "}",
	"。", "゜", "・", "゛", "〜", "ー", "«", "»", "【", "】",
	"*", "🎴", "◓", "◒", "🏰", "🏯", "《", "》", "♀", "♂",
	
	"あ", "ぁ", "い", "ぃ", "う", "ぅ", "え", "ぇ", "お", "ぉ",
	"か", "き", "く", "け", "こ", "さ", "し", "す", "せ", "そ",
	"た", "ち", "つ", "て", "と", "な", "に", "ぬ", "ね", "の",
	"は", "ひ", "ふ", "へ", "ほ", "ま", "み", "む", "め", "も",
	
	"や", "ゃ", "ゆ", "ゅ", "よ", "ょ", "ら", "り", "る", "れ",
	"ろ", "わ", "を", "ん", "っ", "が", "ぎ", "ぐ", "げ", "ご",
	"ざ", "じ", "ず", "ぜ", "ぞ", "だ", "ぢ", "づ", "で", "ど",
	"ば", "び", "ぶ", "べ", "ぼ", "ぱ", "ぴ", "ぷ", "ぺ", "ぽ",

	"ア", "ァ", "イ", "ィ", "ウ", "ゥ", "エ", "ェ", "オ", "ォ",
	"カ", "キ", "ク", "ケ", "コ", "サ", "シ", "ス", "セ", "ソ",
	"タ", "チ", "ツ", "テ", "ト", "ナ", "ニ", "ヌ", "ネ", "ノ",
	"ハ", "ヒ", "フ", "ヘ", "ホ", "マ", "ミ", "ム", "メ", "モ",

	"ヤ", "ャ", "ユ", "ュ", "ヨ", "ョ", "ラ", "リ", "ル", "レ",
	"ロ", "ワ", "ヲ", "ン", "ッ", "ガ", "ギ", "グ", "ゲ", "ゴ",
	"ザ", "ジ", "ズ", "ゼ", "ゾ", "ダ", "ヂ", "ヅ", "デ", "ド",
	"バ", "ビ", "ブ", "ベ", "ボ", "パ", "ピ", "プ", "ペ", "ポ",

	"α", "β", "γ", "δ", "ε", "ζ", "η", "θ", "ι", "κ",
	"λ", "μ", "ν", "ξ", "ο", "π", "ρ", "σ", "τ", "υ",
	"φ", "χ", "ψ", "ω", "ς", "💢", "💧", "🌀", "💤", "✨",
	"🌿", "🔥", "🌊", "⚡", "👊", "👁️", "✪", "🌙", "⚙️", "🐲",
	
	"Α", "Β", "Γ", "Δ", "Ε", "Ζ", "Η", "Θ", "Ι", "Κ",
	"Λ", "Μ", "Ν", "Ξ", "Ο", "Π", "Ρ", "Σ", "Τ", "Υ",
	"Φ", "Χ", "Ψ", "Ω", "♛", "♚", "♜", "♝", "♞", "♟",
	"¤", "¢", "£", "€", "₽", "₩", "¥", "卍", "≛", "⍣",

	"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и",
	"й", "к", "л", "м", "н", "о", "п", "р", "с", "т",
	"у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь",
	"э", "ю", "я", "○", "◇", "☆", "♤", "♡", "♧", "♢",
	
	"А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И",
	"Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т",
	"У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь",
	"Э", "Ю", "Я", "●", "◆", "★", "♠", "♥", "♣", "♦",
};

#define KEYBOARD_LETTER_COUNT (sizeof(keyboard_letters)/sizeof(keyboard_letters[0]))
#define KEYBOARD_ROWS 4
#define KEYBOARD_COLUMNS 10
#define KEYBOARD_PAGES ((KEYBOARD_LETTER_COUNT + (KEYBOARD_ROWS * KEYBOARD_COLUMNS) - 1) / (KEYBOARD_ROWS * KEYBOARD_COLUMNS))
#define KEYBOARD_KEYS_PER_PAGE (KEYBOARD_ROWS * KEYBOARD_COLUMNS)

struct keyboard_button keyboard_buttons[] = {
	{.letter = "← 🅛", .align = UI_TOP, .relation = 0, .space_width = 2, .index = KEYBOARD_LETTER_COUNT},
	{.letter = "→ 🅡", .align = UI_TOP, .relation = 2, .space_width = 2, .index = KEYBOARD_LETTER_COUNT + 1},
	{.letter = "⌧ 🅨", .align = UI_TOP, .relation = 4, .space_width = 3, .index = KEYBOARD_LETTER_COUNT + 2},
	{.letter = "⌫ 🅧", .align = UI_TOP, .relation = 7, .space_width = 3, .index = KEYBOARD_LETTER_COUNT + 3},
	{.letter = "❌ 🅑", .align = UI_BOTTOM, .relation = 30, .space_width = 3, .index = KEYBOARD_LETTER_COUNT + 4},
	{.letter = "␣", .align = UI_BOTTOM, .relation = 33, .space_width = 4, .index = KEYBOARD_LETTER_COUNT + 5},
	{.letter = "↩ 🅢", .align = UI_BOTTOM, .relation = 37, .space_width = 3, .index = KEYBOARD_LETTER_COUNT + 6}
};

#define KEYBOARD_BUTTON_COUNT (sizeof(keyboard_buttons)/sizeof(keyboard_buttons[0]))

struct keyboard {
	struct keyboard_letter letters[KEYBOARD_LETTER_COUNT];
	struct keyboard_button* buttons;
	const uint16_t letter_count;
	uint16_t button_count;
	float x, y;
	float padding;
	float width, height;
	float key_width, key_height, key_padding;
	float border;
	//Vector2 border_size;
	int input[MAX_NAME_LENGTH];
	uint8_t input_count;
	char input_string[MAX_NAME_BYTES];
	Vector2 inputbox_size, inputbox_position, input_size, input_position, cursor_size, cursor_position;
	Vector2 background_size, box_offset;
	uint8_t keys_per_page, rows, columns, pages, page;
	uint16_t page_index, index;
	float font_size;
	bool done;
	bool hover;
	bool click;
	char* message;
	Vector2 message_size, message_position;
	Font font;
};

struct keyboard osk = {
	.buttons = keyboard_buttons,
	.letter_count = KEYBOARD_LETTER_COUNT,
	.button_count = KEYBOARD_BUTTON_COUNT,
	.rows = KEYBOARD_ROWS,
	.columns = KEYBOARD_COLUMNS,
	.pages = KEYBOARD_PAGES,
	.keys_per_page = KEYBOARD_KEYS_PER_PAGE,
	.input[MAX_NAME_LENGTH - 1] = '\0',
	.input_count = 0,
	.message = "What is your name?\0",
	.index = UI_NOSELECTION,
};

