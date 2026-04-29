#--------------------------------------#
#
#	game-music-emu
#
#--------------------------------------#
# game-music-emu build setup
# Create a target to hold the external project
add_library(gme STATIC IMPORTED GLOBAL)
set(GME_LIB "${DEP_INSTALL_DIR}/lib64/libgme.a")
set_target_properties(gme PROPERTIES
	IMPORTED_LOCATION "${GME_LIB}"
)
set(GME_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/game-music-emu")
if(NOT EXISTS "${GME_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/libgme/game-music-emu "${GME_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone game-music-emu")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${GME_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update game-music-emu")
    endif()
endif()
if(NOT EXISTS "${GME_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(game-music-emu
		SOURCE_DIR "${GME_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/game-music-emu"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${GME_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DUSE_GME_AY:BOOL=OFF
			-DUSE_GME_GBS:BOOL=ON
			-DUSE_GME_GYM:BOOL=ON
			-DUSE_GME_HES:BOOL=OFF
			-DUSE_GME_KSS:BOOL=OFF
			-DUSE_GME_NFS:BOOL=ON
			-DUSE_GME_NSFE:BOOL=ON
			-DUSE_GME_SAP:BOOL=OFF
			-DUSE_GME_SPC:BOOL=ON
			-DUSE_GME_VGM:BOOL=ON
			-DGME_BUILD_SHARED:BOOL=OFF
			-DGME_BUILD_STATIC:BOOL=ON
			-DGME_BUILD_TESTING:BOOL=OFF
			-DGME_ZLIB:BOOL=OFF
	)
	add_dependencies(gme game-music-emu)
else()
	message(STATUS "gme found at ${GME_LIB} - skipping build")
endif()
