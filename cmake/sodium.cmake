#--------------------------------------#
#
#	libsodium
#
#--------------------------------------#
# libsodium build setup
add_library(sodium STATIC IMPORTED GLOBAL)
set(SODIUM_LIB "${DEP_INSTALL_DIR}/lib/libsodium.a")
set_target_properties(sodium PROPERTIES
	IMPORTED_LOCATION "${SODIUM_LIB}"
)
set(LIBSODIUM_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/libsodium")
if(NOT EXISTS "${LIBSODIUM_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/jedisct1/libsodium.git "${LIBSODIUM_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone libsodium")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${LIBSODIUM_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update libsodium")
    endif()
endif()
if(NOT EXISTS "${SODIUM_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libsodium
		SOURCE_DIR "${LIBSODIUM_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/libsodium"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${SODIUM_LIB}"
		CONFIGURE_COMMAND
			bash -c "cd \"<SOURCE_DIR>\" && bash autogen.sh -s"
		BUILD_COMMAND
			bash -c "cd \"<BINARY_DIR>\" && bash \"<SOURCE_DIR>/configure\" --prefix=\"${DEP_INSTALL_DIR}\" --disable-shared --enable-static && make -j`nproc`"
		INSTALL_COMMAND
			bash -c "cd \"<BINARY_DIR>\" && make install"
	)
	add_dependencies(sodium libsodium)
else()
	message(STATUS "sodium found at ${SODIUM_LIB} - skipping build")
endif()
