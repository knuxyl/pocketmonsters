#define UI_NOSELECTION UINT16_MAX

typedef enum {
	UI_ACTIVE,
	UI_DISABLED,
	UI_HIDDEN,
	UI_VISIBILITY
} UiVisibility;

typedef enum {
	UI_BLANK,
	UI_TEXT,
	UI_MENU_TEXT,
	UI_IMAGE,
	UI_MENU_IMAGE,
	UI_DIALOG,
	UI_CONTENT
} UiContent;

typedef enum {
	UI_CENTER,
	UI_LEFT,
	UI_RIGHT,
	UI_TOP,
	UI_BOTTOM,
	UI_ALIGNMENT
} UiAlignment;

typedef enum {
	UI_TOP_BOTTOM,
	UI_LEFT_RIGHT,
	UI_DIRECTION
} UiDirection;

