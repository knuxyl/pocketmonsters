#--------------------------------------#
#
#	flac
#
#--------------------------------------#
# flac build setup
add_library(flac STATIC IMPORTED GLOBAL)
set(FLAC_LIB "${DEP_INSTALL_DIR}/lib64/libFLAC.a")
set_target_properties(flac PROPERTIES
	IMPORTED_LOCATION "${FLAC_LIB}"
)
set(FLAC_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/flac")
if(NOT EXISTS "${FLAC_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/xiph/flac.git "${FLAC_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone flac")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${FLAC_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update flac")
    endif()
endif()
if(NOT EXISTS "${FLAC_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libflac
		SOURCE_DIR "${FLAC_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/flac"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${FLAC_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DBUILD_CXXLIBS:BOOL=OFF
			-DBUILD_PROGRAMS:BOOL=OFF
			-DBUILD_EXAMPLES:BOOL=OFF
			-DBUILD_DOCS:BOOL=OFF
			-DINSTALL_MANPAGES:BOOL=OFF
			-DWITH_OGG:BOOL=OFF
	)
	add_dependencies(flac libflac)
else()
	message(STATUS "flac found at ${FLAC_LIB} - skipping build")
endif()
