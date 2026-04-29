#--------------------------------------#
#
#	alsa-lib
#
#--------------------------------------#
# alsa-lib build setup
add_library(alsa STATIC IMPORTED GLOBAL)
set(ALSA_LIB "${DEP_INSTALL_DIR}/lib/libasound.a")
set_target_properties(alsa PROPERTIES
	IMPORTED_LOCATION "${ALSA_LIB}"
)
set(ALSA_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/alsa-lib")
if(NOT EXISTS "${ALSA_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/alsa-project/alsa-lib.git "${ALSA_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone alsa-lib")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${ALSA_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update alsa-lib")
    endif()
endif()
if(NOT EXISTS "${ALSA_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(alsa-lib
		SOURCE_DIR "${ALSA_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/alsa"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${ALSA_LIB}"
		CONFIGURE_COMMAND
			bash -c "cd \"<SOURCE_DIR>\" && autoreconf -fi && rm -f \"${ALSA_SOURCE_DIR}/include/asoundlib.h\" && rm -f \"${ALSA_SOURCE_DIR}/include/version.h\""
		BUILD_COMMAND
			bash -c "cd \"<BINARY_DIR>\" && bash \"<SOURCE_DIR>/configure\" --prefix=\"${DEP_INSTALL_DIR}\" --with-pic --with-libdl=no --disable-tests --disable-shared --enable-static && make all -j`nproc`"
		INSTALL_COMMAND
			bash -c "cd \"<BINARY_DIR>\" && make install"
	)
	add_dependencies(alsa alsa-lib)
else()
	message(STATUS "alsa found at ${ALSA_LIB} - skipping build")
endif()
