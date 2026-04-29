#!/bin/bash
for d in */; do
	cd "${d}"
	main_file="${d%/*}.c"
	if [[ -f "${main_file}" ]]; then
		rm "${main_file}"
	fi
	font_main=""
	for i in *.ttf; do
		if [[ -f "${i}" ]]; then
			echo "Doing ${i}"
			font_type="${d%/*}"
			if [[ "${1}" ]] && [[ -f "${i%.ttf}.c" ]]; then
				rm "${i%.ttf}.c"
			fi
			if [[ ! -f "${i%.ttf}.c" ]]; then
				xxd -n "${i%.ttf}" -i "${i}" | sed 's/unsigned char/const char/g' | sed 's/unsigned int/const uint/g' > "${i%.ttf}.c"
				language=$(echo "${i}" | cut -f 2 -d "_")
				if [[ "${language}" == "en" ]]; then
					biglanguage="ENGLISH"
				elif [[ "${language}" == "jp" ]]; then
					biglanguage="JAPANESE"
				elif [[ "${language}" == "kr" ]]; then
					biglanguage="KOREAN"
				elif [[ "${language}" == "sc" ]]; then
					biglanguage="CHINESE_SIMPLIFIED"
				elif [[ "${language}" == "ch" ]]; then
					biglanguage="CHINESE"
				fi
				if [[ "${font_main}" == "" ]]; then
					font_main=$(echo -e "const struct embedded* fonts[LANGUAGE] = {")
				fi
				output="${language}.c"
				echo -e "#include \"${i%.ttf}.c\"\nconst struct embedded font_${language} = {\n\t.data = ${i%.ttf},\n\t.len = ${i%.ttf}_len\n};" > "${output}"
				font_main=$(echo -e "#include \"${output}\"\n${font_main}\n\t[${biglanguage}] = &font_${language},")
			fi
		else
			continue
		fi
	done
	font_main=$(echo -e "${font_main}\n\t[GERMAN] = &font_en,")
	font_main=$(echo -e "${font_main}\n\t[FRENCH] = &font_en,")
	font_main=$(echo -e "${font_main}\n\t[ITALIAN] = &font_en,")
	font_main=$(echo -e "${font_main}\n\t[SPANISH] = &font_en,")
	font_main=$(echo -e "${font_main}\n};")
	echo "${font_main}" >> "${main_file}"
	cd ../
done
