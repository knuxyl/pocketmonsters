#include "sets.c"

const struct database_set* intern_wotc_sets[] = {
	[WOTC_BS] = &intern_wotc_bs,
	//[WOTC_JU] = &intern_wotc_ju,
	//[WOTC_FO] = &intern_wotc_fo,
	//[WOTC_TR] = &intern_wotc_tr,
	//[WOTC_GH] = &intern_wotc_gh,
	//[WOTC_GC] = &intern_wotc_gc,
};

const struct database_serie intern_wotc = {
	.name = (const char* [LANGUAGE]) {
        [ENGLISH] = "Original",
    },
	.released = 0,
    .sets = intern_wotc_sets,
    .set_count = sizeof(intern_wotc_sets)/sizeof(intern_wotc_sets[0]),
};
