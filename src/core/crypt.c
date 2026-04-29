#define NEED_LIBGCRYPT_VERSION "1.12.1"
void init_crypt() {
	if (!gcry_check_version(NEED_LIBGCRYPT_VERSION)) {
		fprintf(stderr, "libgcrypt is too old (need %s, have %s)\n", NEED_LIBGCRYPT_VERSION, gcry_check_version(NULL));
		exit(2);
	};
	gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
	gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
	if (sodium_init() < 0) {
		fprintf(stderr, "libsodium was unable to start\n");
		exit(2);
	};
    printf("Cryptography and Encryption has been initialized successfully!\n");
};
