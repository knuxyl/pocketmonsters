#!/bin/bash
if [[ ! "${1}" ]] || [[ ! -f "${1}" ]]; then
	echo "Need base image!"
	exit
fi
sizes=("16" "24" "32" "48" "56" "64")
for i in "${sizes[@]}"; do
	output=$(echo "${1}" | sed "s/full/${i}/g")
	magick "${1}" -trim +repage -filter lanczos -resize "${i}"x"${i}" -trim +repage "${output}"
	image "${output}"
done
