#--------------------------------------#
#
#	libgpg-error
#
#--------------------------------------#
# libgpg-error build setup
add_library(gpg-error STATIC IMPORTED GLOBAL)
set(GPGERROR_LIB "${DEP_INSTALL_DIR}/lib/libgpg-error.a")
set_target_properties(gpg-error PROPERTIES
	IMPORTED_LOCATION "${GPGERROR_LIB}"
)
set(LIBGPG_ERROR_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/libgpg-error")
if(NOT EXISTS "${LIBGPG_ERROR_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/gpg/libgpg-error.git "${LIBGPG_ERROR_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone libgpg-error")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${LIBGPG_ERROR_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update libgpg-error")
    endif()
endif()
if(NOT EXISTS "${GPGERROR_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libgpg-error
		SOURCE_DIR "${LIBGPG_ERROR_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/libgpg-error"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${GPGERROR_LIB}"
		CONFIGURE_COMMAND
			bash -c "cd \"<SOURCE_DIR>\" && bash autogen.sh"
		BUILD_COMMAND
			bash -c "cd \"<BINARY_DIR>\" && bash \"<SOURCE_DIR>/configure\" --prefix=\"${DEP_INSTALL_DIR}\" --disable-doc --disable-tests --disable-shared --enable-static && make -j`nproc`"
		INSTALL_COMMAND
			bash -c "cd \"<BINARY_DIR>\" && make install"
	)
	add_dependencies(gpg-error libgpg-error)
else()
	message(STATUS "gpg-error found at ${GPGERROR_LIB} - skipping build")
endif()
