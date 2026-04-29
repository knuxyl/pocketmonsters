Image load_image(const struct embedded* embedded) {
	return LoadImageFromMemory(".png", embedded->data, embedded->len);
}
