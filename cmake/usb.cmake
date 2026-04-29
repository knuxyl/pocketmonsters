#--------------------------------------#
#
#	libusb
#
#--------------------------------------#
# libusb build setup
add_library(usb STATIC IMPORTED GLOBAL)
set(USB_LIB "${DEP_INSTALL_DIR}/lib/libusb-1.0.a")
set_target_properties(usb PROPERTIES
	IMPORTED_LOCATION "${USB_LIB}"
)
set(LIBUSB_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/libusb")
if(NOT EXISTS "${LIBUSB_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/libusb/libusb.git "${LIBUSB_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone libusb")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${LIBUSB_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update libusb")
    endif()
endif()
if(NOT EXISTS "${USB_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libusb
		SOURCE_DIR "${LIBUSB_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/libusb"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${USB_LIB}"
		CONFIGURE_COMMAND
			bash -c "cd \"<SOURCE_DIR>\" && autoreconf -fi"
		BUILD_COMMAND
			bash -c "cd \"<BINARY_DIR>\" && bash \"<SOURCE_DIR>/configure\" --prefix=\"${DEP_INSTALL_DIR}\" --disable-udev --disable-tests --disable-shared --enable-static && make -j`nproc`"
		INSTALL_COMMAND
			bash -c "cd \"<BINARY_DIR>\" && make install"
	)
	add_dependencies(usb libusb)
else()
	message(STATUS "usb found at ${USB_LIB} - skipping build")
endif()
