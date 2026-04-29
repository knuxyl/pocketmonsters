#include "intern/intern.c"

const struct database_region* db[REGION] = {
    [INTERNATIONAL] = &intern,
    //[JAPAN] = &japan,
    //[RUSSIA] = &russia,
    //[KOREA] = &korea,
};

