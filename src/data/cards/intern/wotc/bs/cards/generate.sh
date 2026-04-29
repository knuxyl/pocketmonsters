#!/bin/bash
template=$(cat 1.c)
for i in $(seq 2 102); do
	echo "${template}" | sed "s/bs_1_/bs_${i}_/g" | sed "s/bs_1 /bs_${i}/g" > "${i}.c"
done
if [[ -f cards.c ]]; then
	rm cards.c
fi
for i in $(seq 1 102); do
	echo "#include \"${i}.c\"" >> cards.c
done
echo "const struct database_card* intern_wotc_bs_cards[] = {" >> cards.c
for i in $(seq 1 102); do
	echo -e "\t&intern_wotc_bs_${i}," >> cards.c
done
echo "};" >> cards.c
