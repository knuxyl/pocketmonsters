void change_theme(uint8_t theme) {
	config.theme = theme;
	update_state();
}

void change_mode(uint8_t mode) {
	config.mode = mode;
	update_state();
}

Color get_color(uint8_t color) {
	return themes[config.theme][config.mode][color];
}

Color transparent_color(uint8_t color, uint8_t alpha) {
	Color new_color = themes[config.theme][config.mode][color];
	new_color.a = alpha;
	return new_color;
}
