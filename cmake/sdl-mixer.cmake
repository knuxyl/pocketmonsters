#--------------------------------------#
#
#	SDL_mixer
#
#--------------------------------------#
# SDL_mixer build setup
add_library(sdl-mixer STATIC IMPORTED GLOBAL)
set(SDLMIXER_LIB "${DEP_INSTALL_DIR}/lib64/libSDL3_mixer.a")
set_target_properties(sdl-mixer PROPERTIES
	IMPORTED_LOCATION "${SDLMIXER_LIB}"
	INTERFACE_LINK_LIBRARIES "opusfile;gme;flac;sdl"
)
set(SDL_MIXER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/SDL_mixer")
if(NOT EXISTS "${SDL_MIXER_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/libsdl-org/SDL_mixer.git "${SDL_MIXER_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone sdl-mixer")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${SDL_MIXER_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update sdl-mixer")
    endif()
endif()
if(NOT EXISTS "${SDLMIXER_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libsdl-mixer
		SOURCE_DIR "${SDL_MIXER_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/sdl-mixer"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${SDLMIXER_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DSDLMIXER_AIFF:BOOL=OFF
			-DSDLMIXER_DEPS_SHARED:BOOL=OFF
			-DSDLMIXER_EXAMPLES:BOOL=OFF
			-DSDLMIXER_FLAC:BOOL=ON
			-DSDLMIXER_FLAC_LIBFLAC:BOOL=ON
			-DSDLMIXER_FLAC_LIBFLAC_SHARED:BOOL=OFF
			-DSDLMIXER_GME:BOOL=ON
			-DSDLMIXER_GME_SHARED:BOOL=OFF
			-DSDLMIXER_MIDI:BOOL=OFF
			-DSDLMIXER_MOD:BOOL=OFF
			-DSDLMIXER_MP3:BOOL=OFF
			-DSDLMIXER_OPUS:BOOL=ON
			-DSDLMIXER_OPUS_SHARED:BOOL=OFF
			-DSDLMIXER_RELOCATABLE:BOOL=ON
			-DSDLMIXER_TESTS:BOOL=OFF
			-DSDLMIXER_VOC:BOOL=OFF
			-DSDLMIXER_VORBIS_STB:BOOL=OFF
			-DSDLMIXER_VORBIS_VORBISFILE:BOOL=OFF
			-DSDLMIXER_WAVE:BOOL=OFF
			-DSDLMIXER_WAVPACK:BOOL=OFF
	)
	add_dependencies(sdl-mixer libflac libsdl-mixer)
else()
	message(STATUS "sdl-mixer found at ${SDLMIXER_LIB} - skipping build")
endif()
