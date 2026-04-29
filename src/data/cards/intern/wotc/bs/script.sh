#!/bin/bash
cd card_images
if [[ -f card_images.c ]]; then
	rm card_images.c
fi
for i in *.png; do
	echo "#include \"${i%.png}.c\"" >> /tmp/tmp.txt
done
cat /tmp/tmp.txt | sort -d > card_images.c
if [[ -f /tmp/tmp.txt ]]; then
	rm /tmp/tmp.txt
fi
