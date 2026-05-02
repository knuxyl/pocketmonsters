root="${PWD}"
cd src/strings
if [[ -f "codepoints.c" ]]; then
	rm "codepoints.c"
fi

cd "${root}/src/ui"
keyboard=""
letters=$(cat "keyboard.c" | grep "{\"" | sed 's/^.*{"//g' | sed 's/"}.*//g' | sed 's/","//g')
upper=$(echo "${letters}" | tr "[[:lower:]]" "[[:upper:]]")
lower=$(echo "${letters}" | tr "[[:upper:]]" "[[:lower:]]")
keyboard="${keyboard}${upper}${lower}"
keyboard=$(echo "${keyboard}" | fold -w1 | sort -u | tr -d '\n')
#echo -e "const char* codepoints[LANGUAGE] = {\n\t[ENGLISH] = \"${string}\"," > "codepoints.c"
cd "${root}/src/strings"

string="${keyboard}"
for i in *.c; do
	letters=$(cat "${i}" | grep "\[ENGLISH\]" | sed 's/^.*= "//g' | sed 's/".*//g')
	upper=$(echo "${letters}" | tr "[[:lower:]]" "[[:upper:]]")
	lower=$(echo "${letters}" | tr "[[:upper:]]" "[[:lower:]]")
	string="${string}${upper}${lower}"
done
string=$(echo "${string}" | fold -w1 | sort -u | tr -d '\n' | sed 's/"/\\"/g')
echo -e "const char* codepoints[LANGUAGE] = {\n\t[ENGLISH] = \"${string}\"," > "codepoints.c"

string="${keyboard}"
for i in *.c; do
	letters=$(cat "${i}" | grep "\[JAPANESE\]" | sed 's/^.*= "//g' | sed 's/".*//g')
	upper=$(echo "${letters}" | tr "[[:lower:]]" "[[:upper:]]")
	lower=$(echo "${letters}" | tr "[[:upper:]]" "[[:lower:]]")
	string="${string}${upper}${lower}"
done
string=$(echo "${string}" | fold -w1 | sort -u | tr -d '\n' | sed 's/"/\\"/g')
echo -e "\t[JAPANESE] = \"${string}\"," >> "codepoints.c"

string="${keyboard}"
for i in *.c; do
	letters=$(cat "${i}" | grep "\[GERMAN\]" | sed 's/^.*= "//g' | sed 's/".*//g')
	upper=$(echo "${letters}" | tr "[[:lower:]]" "[[:upper:]]")
	lower=$(echo "${letters}" | tr "[[:upper:]]" "[[:lower:]]")
	string="${string}${upper}${lower}"
done
string=$(echo "${string}" | fold -w1 | sort -u | tr -d '\n' | sed 's/"/\\"/g')
echo -e "\t[GERMAN] = \"${string}\"," >> "codepoints.c"

string="${keyboard}"
for i in *.c; do
	letters=$(cat "${i}" | grep "\[FRENCH\]" | sed 's/^.*= "//g' | sed 's/".*//g')
	upper=$(echo "${letters}" | tr "[[:lower:]]" "[[:upper:]]")
	lower=$(echo "${letters}" | tr "[[:upper:]]" "[[:lower:]]")
	string="${string}${upper}${lower}"
done
string=$(echo "${string}" | fold -w1 | sort -u | tr -d '\n' | sed 's/"/\\"/g')
echo -e "\t[FRENCH] = \"${string}\"," >> "codepoints.c"

string="${keyboard}"
for i in *.c; do
	letters=$(cat "${i}" | grep "\[ITALIAN\]" | sed 's/^.*= "//g' | sed 's/".*//g')
	upper=$(echo "${letters}" | tr "[[:lower:]]" "[[:upper:]]")
	lower=$(echo "${letters}" | tr "[[:upper:]]" "[[:lower:]]")
	string="${string}${upper}${lower}"
done
string=$(echo "${string}" | fold -w1 | sort -u | tr -d '\n' | sed 's/"/\\"/g')
echo -e "\t[ITALIAN] = \"${string}\"," >> "codepoints.c"

string="${keyboard}"
for i in *.c; do
	letters=$(cat "${i}" | grep "\[SPANISH\]" | sed 's/^.*= "//g' | sed 's/".*//g')
	upper=$(echo "${letters}" | tr "[[:lower:]]" "[[:upper:]]")
	lower=$(echo "${letters}" | tr "[[:upper:]]" "[[:lower:]]")
	string="${string}${upper}${lower}"
done
string=$(echo "${string}" | fold -w1 | sort -u | tr -d '\n' | sed 's/"/\\"/g')
echo -e "\t[SPANISH] = \"${string}\"," >> "codepoints.c"

string="${keyboard}"
for i in *.c; do
	letters=$(cat "${i}" | grep "\[KOREAN\]" | sed 's/^.*= "//g' | sed 's/".*//g')
	upper=$(echo "${letters}" | tr "[[:lower:]]" "[[:upper:]]")
	lower=$(echo "${letters}" | tr "[[:upper:]]" "[[:lower:]]")
	string="${string}${upper}${lower}"
done
string=$(echo "${string}" | fold -w1 | sort -u | tr -d '\n' | sed 's/"/\\"/g')
echo -e "\t[KOREAN] = \"${string}\"," >> "codepoints.c"

string="${keyboard}"
for i in *.c; do
	letters=$(cat "${i}" | grep "\[CHINESE_SIMPLIFIED\]" | sed 's/^.*= "//g' | sed 's/".*//g')
	upper=$(echo "${letters}" | tr "[[:lower:]]" "[[:upper:]]")
	lower=$(echo "${letters}" | tr "[[:upper:]]" "[[:lower:]]")
	string="${string}${upper}${lower}"
done
string=$(echo "${string}" | fold -w1 | sort -u | tr -d '\n' | sed 's/"/\\"/g')
echo -e "\t[CHINESE_SIMPLIFIED] = \"${string}\"," >> "codepoints.c"

string="${keyboard}"
for i in *.c; do
	letters=$(cat "${i}" | grep "\[CHINESE\]" | sed 's/^.*= "//g' | sed 's/".*//g')
	upper=$(echo "${letters}" | tr "[[:lower:]]" "[[:upper:]]")
	lower=$(echo "${letters}" | tr "[[:upper:]]" "[[:lower:]]")
	string="${string}${upper}${lower}"
done
string=$(echo "${string}" | fold -w1 | sort -u | tr -d '\n' | sed 's/"/\\"/g')
echo -e "\t[CHINESE] = \"${string}\"" >> "codepoints.c"
echo "};" >> "codepoints.c"











