#--------------------------------------#
#
#	tmx
#
#--------------------------------------#
add_library(tmx STATIC IMPORTED GLOBAL)
set(TMX_LIB "${DEP_INSTALL_DIR}/lib64/libtmx.a")
set_target_properties(tmx PROPERTIES
	IMPORTED_LOCATION "${TMX_LIB}"
	INTERFACE_LINK_LIBRARIES "xml2"
)
set(TMX_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/tmx")
if(NOT EXISTS "${TMX_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/baylej/tmx.git "${TMX_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone tmx")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${TMX_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update tmx")
    endif()
endif()
if(NOT EXISTS "${TMX_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libtmx
		SOURCE_DIR "${TMX_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/tmx"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${TMX_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=Release
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DDOC_HTML:BOOL=OFF
			-DWANT_ZSTD:BOOL=OFF
			-DWANT_ZLIB:BOOL=OFF
	)
	add_dependencies(tmx libtmx)
else()
	message(STATUS "tmx found at ${TMX_LIB} - skipping build")
endif()
