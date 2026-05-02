#!/bin/bash
export BUILD_TYPE="Debug"
export CFLAGS="-O3 -pipe -flto=auto -fuse-linker-plugin --exec-charset=utf8"
export CXXFLAGS="${CFLAGS}"
#if [[ "${1}" ]]; then
	#export CFLAGS="-g -O0"
	#export CXXFLAGS="${CFLAGS}"
#fi
if [[ -d build ]]; then
	rm -R build
fi
mkdir build
cmd="cmake -S . -B build -G Ninja -DCMAKE_COLOR_DIAGNOSTICS=ON -DCMAKE_BUILD_TYPE=${BUILD_TYPE}"
if [[ "${1}" == *"u"* ]]; then
	cmd="${cmd} -DUPDATE_DEPS=ON"
fi
if [[ "${1}" == *"b"* ]] || [[ "${1}" == *"d"* ]]; then
	cmd="${cmd} -DBUILD_DEPS=ON"
fi
if [[ "${1}" == *"s"* ]]; then
	cmd="${cmd} -DPMCG_SOFTWARE_RENDERER=ON"
fi
if [[ "${1}" == *"r"* ]]; then
	cmd="${cmd} -DPMCG_RAYLIB=ON"
fi
eval "${cmd} -L"
cmake --build build
cd build
if [[ -f pmcg ]]; then
	cp pmcg ../
	cd ../
	ldd pmcg
	./pmcg
fi
