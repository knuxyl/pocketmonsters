#!/bin/bash
for d in */; do
	cd "${d}"
	if [[ -d "boosters" ]]; then
		cd "boosters"
		for i in *.png; do
			name="$(echo "${i%.png}" | sed 's/_png//g')_png.png"
			if [[ -f "${i%.png}.c" ]]; then	
				rm "${i%.png}.c"
			fi
			mv "${i}" "${name}"
		done
		cd ../
	fi
	cd ../
done
