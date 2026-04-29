#!/bin/bash
if [[ ! "${1}" ]]; then
	find_extension="vgm"
else
	find_extension="${1}"
fi
cd "src"
list=$(find -iname "*.${find_extension}" | sed 's/^\.\///g')
while read line; do
	name=$(basename "${line%.${find_extension}}")
	dire=$(dirname "${line}")
	output="${dire}/${name}.c"
	if [[ "${output}" != *"hires"* ]]; then
		if [[ ! -f "${output}" ]]; then
			xxd -n "${name}" -i "${line}" | sed 's/unsigned char/const char/g' | sed 's/unsigned int/const uint/g' > "${output}"
		fi
	fi
done <<< "${list}"
