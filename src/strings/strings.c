#include "cards.c"
#include "pokemon_names.c"
#include "title.c"
#include "codepoints.c"
#include "keyboard.c"

// test strings

const char* str_test_fun1[LANGUAGE] = {
	[ENGLISH] = "FUN1",
	[JAPANESE] = "FUN1",
	[GERMAN] = "FUN1",
	[FRENCH] = "FUN1",
	[ITALIAN] = "FUN1",
	[SPANISH] = "FUN1",
	[KOREAN] = "FUN1",
	[CHINESE_SIMPLIFIED] = "FUN1",
	[CHINESE] = "FUN1"
};
const char* str_test_fun2[LANGUAGE] = {
	[ENGLISH] = "FUN2",
	[JAPANESE] = "FUN2",
	[GERMAN] = "FUN2",
	[FRENCH] = "FUN2",
	[ITALIAN] = "FUN2",
	[SPANISH] = "FUN2",
	[KOREAN] = "FUN2",
	[CHINESE_SIMPLIFIED] = "FUN2",
	[CHINESE] = "FUN2"
};
const char* str_test_fun3[LANGUAGE] = {
	[ENGLISH] = "FUN3",
	[JAPANESE] = "FUN3",
	[GERMAN] = "FUN3",
	[FRENCH] = "FUN3",
	[ITALIAN] = "FUN3",
	[SPANISH] = "FUN3",
	[KOREAN] = "FUN3",
	[CHINESE_SIMPLIFIED] = "FUN3",
	[CHINESE] = "FUN3"
};
const char* str_test_fun4[LANGUAGE] = {
	[ENGLISH] = "FUN4",
	[JAPANESE] = "FUN4",
	[GERMAN] = "FUN4",
	[FRENCH] = "FUN4",
	[ITALIAN] = "FUN4",
	[SPANISH] = "FUN4",
	[KOREAN] = "FUN4",
	[CHINESE_SIMPLIFIED] = "FUN4",
	[CHINESE] = "FUN4"
};
const char* str_test_fun5[LANGUAGE] = {
	[ENGLISH] = "FUN5",
	[JAPANESE] = "FUN5",
	[GERMAN] = "FUN5",
	[FRENCH] = "FUN5",
	[ITALIAN] = "FUN5",
	[SPANISH] = "FUN5",
	[KOREAN] = "FUN5",
	[CHINESE_SIMPLIFIED] = "FUN5",
	[CHINESE] = "FUN5"
};
const char* str_test_fun6[LANGUAGE] = {
	[ENGLISH] = "FUN6",
	[JAPANESE] = "FUN6",
	[GERMAN] = "FUN6",
	[FRENCH] = "FUN6",
	[ITALIAN] = "FUN6",
	[SPANISH] = "FUN6",
	[KOREAN] = "FUN6",
	[CHINESE_SIMPLIFIED] = "FUN6",
	[CHINESE] = "FUN6"
};

/*

	♚♛↷↶↺↻↪↩

	"ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ", "ㅂ", "ㅃ", "ㅅ",
	"ㅆ", "ㅇ", "ㅈ", "ㅉ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ", "ㅏ",
	"ㅐ", "ㅑ", "ㅒ", "ㅓ", "ㅔ", "ㅕ", "ㅖ", "ㅗ", "ㅘ", "ㅙ",
	"ㅚ", "ㅛ", "ㅜ", "ㅝ", "ㅞ", "ㅟ", "ㅠ", "ㅡ", "ㅢ", "ㅣ",
	
	"∅", "ㄱ", "ㄲ", "ㄳ", "ㄴ", "ㄵ", "ㄶ", "ㄷ", "ㄹ", "ㄺ",
	"ㄻ", "ㄼ", "ㄽ", "ㄾ", "ㄿ", "ㅀ", "ㅁ", "ㅂ", "ㅄ", "ㅅ",
	"ㅆ", "ㅇ", "ㅈ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ", " ", " ",
	" ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
	
	"𝔞", "𝔟", "𝔠", "𝔡", "𝔢", "𝔣", "𝔤", "𝔥", "𝔦", "𝔧",
	"𝔨", "𝔩", "𝔪", "𝔫", "𝔬", "𝔭", "𝔮", "𝔯", "𝔰", "𝔱",
	"𝔲", "𝔳", "𝔴", "𝔵", "𝔶", "𝔷", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "",
	
	"𝔄", "𝔅", "ℭ", "𝔇", "𝔈", "𝔉", "𝔊", "ℌ", "ℑ", "𝔍",
	"𝔎", "𝔏", "𝔐", "𝔑", "𝔒", "𝔓", "𝔔", "ℜ", "𝔖", "𝔗",
	"𝔘", "𝔙", "𝔚", "𝔛", "𝔜", "ℨ", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "",
	
	"𝒶", "𝒷", "𝒸", "𝒹", "ℯ", "𝒻", "ℊ", "𝒽", "𝒾", "𝒿",
	"𝓀", "𝓁", "𝓂", "𝓃", "ℴ", "𝓅", "𝓆", "𝓇", "𝓈", "𝓉",
	"𝓊", "𝓋", "𝓌", "𝓍", "𝓎", "𝓏", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "",
	
	"𝒜", "ℬ", "𝒞", "𝒟", "ℰ", "ℱ", "𝒢", "ℋ", "ℐ", "𝒥",
	"𝒦", "ℒ", "ℳ", "𝒩", "𝒪", "𝒫", "𝒬", "ℛ", "𝒮", "𝒯",
	"𝒰", "𝒱", "𝒲", "𝒳", "𝒴", "𝒵", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "",
	
	"🎴", "🌐", "💾", "🕹️", "📱", "🎮", "⌨️", "🖱️", "🖥️", "💻",
	"🌿", "🔥", "🌊", "⚡", "👊", "👁️", "✪", "🌙", "⚙️", "🐲",
	"✨", "💢", "💧", "🌀", "💤", "❌", "☠️", "💥", "📜", "⭐",
	"", "", "", "", "", "", "", "", "", "",
	
	"▲", "▼", "◀", "▶", "▴", "▾", "◂", "▸", "¤", "¢",
	"△", "▽", "◁", "▷", "▵", "▿", "◃", "▹", "£", "₤",
	"⬆", "⬇", "⬅", "➡", "⌫", "⌧", "↩", "␣", "€", "₽",
	"↑", "↓", "←", "→", "⟲", "☰", "⏻", "✈", "₩", "¥",
	
	"◓", "●", "🅐", "🅑", "🅧", "🅨", "🅛", "🅡", "🅢", "🅔",
	"◒", "○", "Ⓐ", "Ⓑ", "Ⓧ", "Ⓨ", "Ⓛ", "Ⓡ", "Ⓢ", "Ⓔ",
	"◆", "⭑", "✦", "♠", "♥", "♣", "♦", "❶", "■",  "⍟",
	"◇", "⭒", "✧", "♤", "♡", "♧", "♢", "⓵", "☐", "≛", "⍣"
🏴‍☠️️卍
*/
