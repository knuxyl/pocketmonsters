#--------------------------------------#
#
#	opusfile
#
#--------------------------------------#
# opusfile build setup
add_library(opusfile STATIC IMPORTED GLOBAL)
set(OPUSFILE_LIB "${DEP_INSTALL_DIR}/lib64/libopusfile.a")
set_target_properties(opusfile PROPERTIES
	IMPORTED_LOCATION "${OPUSFILE_LIB}"
	INTERFACE_LINK_LIBRARIES "opus;ogg"
)
set(OPUS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/opusfile")
if(NOT EXISTS "${OPUS_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/xiph/opusfile.git "${OPUS_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone opusfile")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${OPUS_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update opusfile")
    endif()
endif()
if(NOT EXISTS "${OPUSFILE_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libopusfile
		SOURCE_DIR "${OPUS_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/opusfile"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${OPUSFILE_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DOP_DISABLE_HTTP:BOOL=ON
			-DOP_DISABLE_EXAMPLES:BOOL=ON
			-DOP_DISABLE_DOCS:BOOL=ON
	)
	add_dependencies(opusfile libopusfile)
else()
	message(STATUS "opusfile found at ${OPUSFILE_LIB} - skipping build")
endif()
