#include "series.c"

const struct database_serie* intern_series[] = {
	[INTERN_WOTC] = &intern_wotc,
};

const struct database_region intern = {
	.name = (const char*[LANGUAGE]) {
		[ENGLISH] = "International",
		[JAPANESE] = "拡張パック",
        [GERMAN] = "",
        [FRENCH] = "",
        [ITALIAN] = "",
        [SPANISH] = "",
        [KOREAN] = "",
        [CHINESE_SIMPLIFIED] = "",
        [CHINESE] = ""
    },
	.series = intern_series,
	.series_count = sizeof(intern_series)/sizeof(intern_series[0]),
};
