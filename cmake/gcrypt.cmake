#--------------------------------------#
#
#	libgcrypt
#
#--------------------------------------#
# libgcrypt build setup
# Create a target to hold the external project
add_library(gcrypt STATIC IMPORTED GLOBAL)
set(GCRYPT_LIB "${DEP_INSTALL_DIR}/lib/libgcrypt.a")
set_target_properties(gcrypt PROPERTIES
	IMPORTED_LOCATION "${GCRYPT_LIB}"
	INTERFACE_LINK_LIBRARIES "gpg-error"
)
set(LIBGCRYPT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/libgcrypt")
if(NOT EXISTS "${LIBGCRYPT_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/gpg/libgcrypt.git "${LIBGCRYPT_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone libgcrypt")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${LIBGCRYPT_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update libgcrypt")
    endif()
endif()
if(NOT EXISTS "${GCRYPT_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libgcrypt
		SOURCE_DIR "${LIBGCRYPT_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/libgcrypt"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${GCRYPT_LIB}"
		CONFIGURE_COMMAND
			bash -c "cd \"<SOURCE_DIR>\" && bash autogen.sh"
		BUILD_COMMAND
			bash -c "cd \"<BINARY_DIR>\" && bash \"<SOURCE_DIR>/configure\" --prefix=\"${DEP_INSTALL_DIR}\" --disable-doc --disable-shared --enable-static && make -j`nproc`"
		INSTALL_COMMAND
			bash -c "cd \"<BINARY_DIR>\" && make install"
	)
	add_dependencies(gcrypt libgcrypt)
else()
	message(STATUS "gcrypt found at ${GCRYPT_LIB} - skipping build")
endif()
