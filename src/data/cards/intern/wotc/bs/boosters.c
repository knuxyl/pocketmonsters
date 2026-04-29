const struct database_card* intern_wotc_bs_energies[] = {
};
const struct database_card* intern_wotc_bs_trainers[] = {
};
const struct database_booster intern_wotc_bs_booster1 = {
    .common = {
        &intern_wotc_bs_1,
        &intern_wotc_bs_1,
    },
    .uncommon = {},
    .rare = {},
    .energy = {
        &intern_wotc_bs_1,
    },
    .image = &(const struct database_image) {
		.image_data = intern_wotc_bs_booster1_img,
		.image_len = intern_wotc_bs_booster1_img_len,
    },
};
const struct database_booster* intern_wotc_bs_boosters[] = {
    &intern_wotc_bs_booster1,
};
