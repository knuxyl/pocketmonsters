#--------------------------------------#
#
#	sdl-image
#
#--------------------------------------#
# sdl-image build setup
add_library(sdl-image STATIC IMPORTED GLOBAL)
set(SDLIMAGE_LIB "${DEP_INSTALL_DIR}/lib64/libSDL3_image.a")
set_target_properties(sdl-image PROPERTIES
	IMPORTED_LOCATION "${SDLIMAGE_LIB}"
)
set(SDLIMAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/SDL_image")
if(NOT EXISTS "${SDLIMAGE_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/libsdl-org/SDL_image.git "${SDLIMAGE_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone sdl-image")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${SDLIMAGE_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update sdl-image")
    endif()
endif()
if(NOT EXISTS "${SDLIMAGE_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libsdl-image
		SOURCE_DIR "${SDLIMAGE_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/sdl-image"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${SDLIMAGE_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=Release
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DSDLIMAGE_ANI:BOOL=OFF
			-DSDLIMAGE_AVIF:BOOL=OFF
			-DSDLIMAGE_GIF:BOOL=OFF
			-DSDLIMAGE_JPG:BOOL=OFF
			-DSDLIMAGE_JXL:BOOL=OFF
			-DSDLIMAGE_LBM:BOOL=OFF
			-DSDLIMAGE_PNG:BOOL=ON
			-DSDLIMAGE_PNM:BOOL=OFF
			-DSDLIMAGE_QOI:BOOL=ON
			-DSDLIMAGE_SVG:BOOL=OFF
			-DSDLIMAGE_TGA:BOOL=OFF
			-DSDLIMAGE_TIF:BOOL=OFF
			-DSDLIMAGE_WEBP:BOOL=ON
			-DSDLIMAGE_XCF:BOOL=OFF
			-DSDLIMAGE_XPM:BOOL=OFF
			-DSDLIMAGE_XPM:BOOL=OFF
			-DSDLIMAGE_XV:BOOL=OFF
	)
	add_dependencies(sdl-image libsdl-image)
else()
	message(STATUS "sdl-image found at ${SDLIMAGE_LIB} - skipping build")
endif()
