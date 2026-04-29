#!/bin/bash
root="${PWD}"
if [[ -f music.c ]]; then
	rm "music.c"
fi
cd gbc
for i in *.gbs; do
	var_name="${i%.*}"
	xxd -n "${var_name}" -i "${i}" | sed 's/unsigned char/const char/g' | sed 's/unsigned int/const uint/g' > "${var_name}.c"
	echo "#include \"gbc/${var_name}.c\"" >> "${root}/music.c"
done
echo "const struct embedded embedded_music[] = {" >> "${root}/music.c"
for i in *.c; do
	name="${i%.c}"
	echo -e "\t(const struct embedded) {\n\t\t.data = ${name},\n\t\t.len = ${name}_len,\n\t}," >> "${root}/music.c"
done
echo -e "};\nconst uint8_t music_count = sizeof(embedded_music)/sizeof(embedded_music[0]);" >> "${root}/music.c"
