struct key {
	Vector2 key;
	Vector2 box;
	Vector2 box_size;
	Vector2 key_size;
	int codepoint;
	bool hover;
	bool clicked;
};

struct onscreen_keyboard {
	float height;
	float width;
	float key_height;
	float key_width;
	float key_padding;
	float x;
	float y;
	uint8_t page;
	struct key keys[40];
	struct key submit;
	uint8_t language;
	Font font;
};


struct ui_child {
	uint8_t type; // UI_TEXT, UI_IMAGE, UI_MENU
	union {
		Texture2D image;
		const char** string;
	};
	float s; // calculated - font size or image scale
	float x; // calculated
	float y; // calculated
	float w; // calculated
	float h; // calculated
	float pw; // percentage of width of the window, max width of child
	float ph; // percentage of height of the window, max height of child
	float salign; // UI_LEFT, UI_RIGHT, UI_TOP, UI_BOTTOM, UI_CENTER (sibling alignment to tallest/widest sibling)
	function_void* click; // function to call when clicked
	bool hover; // set if hovering
	uint8_t v; // visibility/interaction (UI_ACTIVE, UI_DISABLED, UI_HIDDEN, UI_HOVER, UI_CLICK)
};

struct ui_element {
	uint8_t language;
	float px; // percentage of the width of the window
	float py; // percentage of the height of the window
	float pw; // percentage of the width of the window, max width of element
	float ph; // percentage of the height of the window, max height of element
	int x; // calculated
	int y; // calculated
	int w; // calculated
	int h; // calculated
	uint8_t direction; // UI_TOP_BOTTOM UI_BOTTOM_TOP UI_LEFT_RIGHT UI_RIGHT_LEFT
	uint8_t align_x; // UI_LEFT UI_CENTER UI_RIGHT (where to align child inside element's allocated geometry for child)
	uint8_t align_y; // UI_TOP UI_CENTER UI_BOTTOM (where to align child inside elements's allocated geometry for child)
	
	float padding_pt;
	float padding_pb;
	float padding_pl;
	float padding_pr;
	int padding_t; // calculated
	int padding_b; // calculated
	int padding_l; // calculated
	int padding_r; // calculated
	//float padding_px; // padding for left and right sides inside window
	//float padding_py; // padding for top and bottom sides inside window
	float child_pgap; // percentage of elements width/height for padding between children
	float child_gap; //calculated
	//float child_padding_py; // percentage of elements height for padding
	//float padding_x; // calculated
	//float padding_y; // calculated
	//float child_padding_x; // calculated
	//float child_padding_y; // calculated
	uint16_t index; // current highlighted menu option
	uint8_t v; // used for menus (will probably remove, input() will be dictated by state)
	int child_w; // calculated
	int child_h; // calculated
	Font font;
	uint16_t child_count; // need to provide number of elements
	struct ui_child* children[]; // array of pointers to chilren elements
};
