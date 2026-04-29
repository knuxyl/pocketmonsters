# BUILDING
- Cross platform building is not yet supported. I don't have a windows or mac machine to test nor have I started android.

- build.sh is for me, you can look at it for how things are done but it probably won't work on your system and I wouldn't recommend it

- Build system is still a WIP. There may be libraries and recursive dependencies not needed pulled in by cmake. 

- All binary files (images, music, fonts) must be generated as .c files first. I can't upload to remote because the files can get too big. On Linux you can use xxd. I wrote a script xxd.sh to automate this, the first argument is the file extension without the .. This will need to be done for all .gbs, .png, and .ttf files. What it outpus
	- filename.c
	- `const char filename = {};`
	- `const uint filename_len = {};`
- To build
	- `mkdir build`
	- `cd build`
	- `cmake ../`
	- `make`
- Software Rendering
	- `cmake ../ -DPMCG_SOFTWARE=ON`
