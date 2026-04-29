void change_theme(uint8_t theme) {
	config.theme = &themes[theme];
	update_state();
}


