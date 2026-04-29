#--------------------------------------#
#
#	libcbor
#
#--------------------------------------#
# libcbor build setup
# Create a target to hold the external project
add_library(cbor STATIC IMPORTED GLOBAL)
set(CBOR_LIB "${DEP_INSTALL_DIR}/lib64/libcbor.a")
set_target_properties(cbor PROPERTIES
	IMPORTED_LOCATION "${CBOR_LIB}"
)
set(LIBCBOR_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/libcbor")
if(NOT EXISTS "${LIBCBOR_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/PJK/libcbor.git "${LIBCBOR_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone libcbor")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${LIBCBOR_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update libcbor")
    endif()
endif()
if(NOT EXISTS "${CBOR_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libcbor
		SOURCE_DIR "${LIBCBOR_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/libcbor"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${CBOR_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
	)
	add_dependencies(cbor libcbor)
else()
	message(STATUS "libcbor found at ${CBOR_LIB} - skipping build")
endif()
