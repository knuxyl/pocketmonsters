#--------------------------------------#
#
#	SDL
#
#--------------------------------------#
# SDL3 build setup
add_library(sdl STATIC IMPORTED GLOBAL)
set(SDL_LIB "${DEP_INSTALL_DIR}/lib64/libSDL3.a")
set_target_properties(sdl PROPERTIES
	IMPORTED_LOCATION "${SDL_LIB}"
	INTERFACE_LINK_LIBRARIES "hidapi-hidraw;hidapi-libusb;drm"
)
set(SDL_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/SDL")
if(NOT EXISTS "${SDL_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/libsdl-org/SDL.git "${SDL_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone sdl")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${SDL_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update sdl")
    endif()
endif()
if(NOT EXISTS "${SDL_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libsdl
		SOURCE_DIR "${SDL_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/sdl"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${SDL_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=Release
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DSDL_ALSA:BOOL=ON
			#-DSDL_ALSA_SHARED:BOOL=OFF
			#-DSDL_DBUS:BOOL=OFF
			# have to setup building entire stack
			#-DSDL_DEPS_SHARED:BOOL=OFF
			-DSDL_GPU_OPENXR:BOOL=OFF
			-DSDL_HIDAPI_LIBUSB:BOOL=ON
			-DSDL_HIDAPI_LIBUSB_SHARED:BOOL=OFF
			-DSDL_JACK:BOOL=ON
			# dont care
			#-DSDL_JACK_SHARED:BOOL=OFF
			-DSDL_KMDSDRM:BOOL=ON
			# Need GBM from mesa
			#-DSDL_KMSDRM_SHARED:BOOL=OFF
			-DSDL_LIBUDEV:BOOL=OFF
			-DSDL_PIPEWIRE:BOOL=ON
			# wireplumber fucks this up
			#-DSDL_PIPEWIRE_SHARED:BOOL=OFF
			-DSDL_PULSEAUDIO:BOOL=ON
			# dont care
			#-DSDL_PULSEAUDIO_SHARED:BOOL=OFF
			-DSDL_SNDIO:BOOL=OFF
			-DSDL_TESTS:BOOL=OFF
			-DSDL_TRAY:BOOL=OFF
			-DSDL_WAYLAND:BOOL=ON
			# needs some weird config files
			#-DSDL_WAYLAND_SHARED:BOOL=OFF
			-DSDL_X11:BOOL=ON
			# trivial, will probably do in future
			#-DSDL_X11_SHARED:BOOL=OFF
	)
	add_dependencies(sdl libsdl)
else()
	message(STATUS "sdl found at ${SDL_LIB} - skipping build")
endif()
