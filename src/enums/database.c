typedef enum {
    MOD_ADD,
    MOD_SUBTRACT,
    MOD_MULTIPLY,
    MOD_DIVIDE,
    MOD_DAMAGE
} ModDamage;

typedef enum {
    DARK,
    NO_PREFIX,
    PREFIX,
} Prefix;

typedef enum {
    EX,
    NO_SUFFIX,
    SUFFIX,
} Suffix;

typedef enum {
    INTERN_WOTC,
    INTERN_NEO,
    INTERN_ECARD,
    INTERN_EX,
    INTERN_SERIES // Total Count
} SeriesIntern;

typedef enum {
    WOTC_BS,
    WOTC_JU,
    WOTC_FO,
    WOTC_TR,
    WOTC_GH,
    WOTC_GC,
    WOTC_SETS // Total Count
} SetWOTC;

typedef enum {
    INTERNATIONAL,
    JAPAN,
    KOREA,
    CHINA,
    REGION
} Region;

typedef enum {
    COMMON, // ● C
    UNCOMMON, // ◆ U
    RARE, // 🟊 R
    HOLOFOIL, // 🟊 R
    SHINY, // 🟊SH, ☆SH
    DOUBLE, // 🟊🟊 RR
    ULTRA, // ☆, 🟊P, 🟊A, 🟊B, ☆X, V☆, ☆RAD, 🟊🟊, ☆☆
    SECRET, // 🟊H, 🟊🟊🟊H, ☆H
    ACE_SPEC, // 🟊 (pink)
    ILLUSTRATION, // 🟊, AR
    SPECIAL_ILLUSTRATION, // 🟊🟊, SAR
    MEGA_ATTACK, // ☆☆, MA
    HYPER, // 🟊🟊🟊, UR
    MEGA_HYPER, // ✧, MUR
    DECK,
    PROMO,
    RARITY // Total number
} Rarity;

typedef enum {
    OK,
    ASLEEP,
    CONFUSED,
    PARALYZED,
    POISONED,
    BURNED,
    STATUS // Total number
} Status;

typedef enum {
    GRASS,
    FIRE,
    WATER,
    LIGHTNING,
    PSYCHIC,
    FIGHTING,
    DARKNESS,
    METAL,
    FAIRY,
    COLORLESS,
    NO_TYPE,
    TYPE // Total number
} Type;

typedef enum {
    BASIC,
    STAGE1,
    STAGE2,
    STAGE //Total number
} Stage;
