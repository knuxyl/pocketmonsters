unsigned char sign_public[crypto_sign_PUBLICKEYBYTES];
unsigned char sign_private[crypto_sign_SECRETKEYBYTES];
unsigned char public[crypto_sign_PUBLICKEYBYTES];
unsigned char private[crypto_sign_SECRETKEYBYTES];

struct save_game save_game;

void init_player() {
    save_game.player.name = "knuxyl";
    memcpy(save_game.player.public, (unsigned char[]) {
            0x76, 0xe5, 0xa2, 0xfc, 0x24, 0x96, 0xbf, 0x17, 0x13, 0xcd, 0x6b, 0xaa, 0xa7, 0xbc, 0x4b, 0xd9, 0x21, 0x6e, 0xbf, 0x08, 0xcd, 0xe4, 0x9e, 0xb4, 0xa2, 0x04, 0x34, 0x1d, 0x4a, 0x1d, 0x48, 0xd4,
        }, crypto_sign_PUBLICKEYBYTES
    );
    memcpy(save_game.player.private, (unsigned char[]) {
            0x11, 0xa7, 0x62, 0x3b, 0x48, 0x22, 0x8a, 0xaf, 0x54, 0xaf, 0x8a, 0x5d, 0x9f, 0x2b, 0xe4, 0x56, 0xbd, 0x3f, 0x7e, 0x92, 0x80, 0x1f, 0x9c, 0x49, 0x55, 0xfd, 0x8f, 0x4a, 0xda, 0xd1, 0xff, 0x60, 0x76, 0xe5, 0xa2, 0xfc, 0x24, 0x96, 0xbf, 0x17, 0x13, 0xcd, 0x6b, 0xaa, 0xa7, 0xbc, 0x4b, 0xd9, 0x21, 0x6e, 0xbf, 0x08, 0xcd, 0xe4, 0x9e, 0xb4, 0xa2, 0x04, 0x34, 0x1d, 0x4a, 0x1d, 0x48, 0xd4,
        }, crypto_sign_SECRETKEYBYTES
    );
    //current_save.player.sign_private = "";
	//crypto_sign_ed25519_keypair(current_save.player.sign_public, current_save.player.sign_private);
	crypto_sign_ed25519_pk_to_curve25519(save_game.player.encrypt_public, save_game.player.public);
	crypto_sign_ed25519_sk_to_curve25519(save_game.player.encrypt_private, save_game.player.private);
    //crypto_box_curve25519_pk_to_ed25519(public, current_save.player.public);
    //crypto_box_curve25519_sk_to_ed25519(private, current_save.player.private);

    printf("Player: %s\n", save_game.player.name);
	printf("Public key: ");
	for (size_t i = 0; i < crypto_sign_PUBLICKEYBYTES; i++) {
		printf("%02x", save_game.player.public[i]);
	}
	printf("\n");
   
	printf("Private key: ");
    for (size_t i = 0; i < crypto_sign_SECRETKEYBYTES; i++) {
        printf("%02x", save_game.player.private[i]);
    }
    printf("\n");
    printf("Sign Public key: ");
	for (size_t i = 0; i < crypto_box_PUBLICKEYBYTES; i++) {
		printf("%02x", save_game.player.encrypt_public[i]);
	}
	printf("\n");
	printf("Sign Private key: ");
	for (size_t i = 0; i < crypto_box_SECRETKEYBYTES; i++) {
		printf("%02x", save_game.player.encrypt_private[i]);
	}
	printf("\n");
};

