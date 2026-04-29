#--------------------------------------#
#
#	opus
#
#--------------------------------------#
# opus build setup
add_library(opus STATIC IMPORTED GLOBAL)
set(OPUS_LIB "${DEP_INSTALL_DIR}/lib64/libopus.a")
set_target_properties(opus PROPERTIES
	IMPORTED_LOCATION "${OPUS_LIB}"
)
set(OPUS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/opus")
if(NOT EXISTS "${OPUS_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/xiph/opus.git "${OPUS_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone opus")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${OPUS_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update opus")
    endif()
endif()
if(NOT EXISTS "${OPUS_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libopus
		SOURCE_DIR "${OPUS_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/opus"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${OPUS_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DOPUS_BUILD_TESTING:BOOL=OFF
			-DOPUS_CUSTOM_MODES:BOOL=ON
			-DOPUS_BUILD_PROGRAMS:BOOL=OFF
			-DOPUS_STATIC_RUNTIME:BOOL=ON
	)
	add_dependencies(opus libopus)
else()
	message(STATUS "libopus found at ${OPUS_LIB} - skipping build")
endif()
