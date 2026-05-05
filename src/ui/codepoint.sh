#!/bin/bash
echo "const char* keyboard_codepoints = \"$(cat keyboard.c | grep -i "\"," | sed 's/^.*[^ ,"]\+ "//g' | sed 's/", [^"].*//g' | sed 's/", "//g' | sed 's/",//g' | sed 's/^[[:space:]]\+"//g' | sed 's/[[:space:]]\+//g' | sed -z 's/\n//g')\\\"\";" > ../strings/keyboard.c

