#--------------------------------------#
#
#	libhidapi
#
#--------------------------------------#
# libhidapi build setup

# Create a target to hold the external project
add_library(hidapi-libusb STATIC IMPORTED GLOBAL)
set(HIDAPIUSB_LIB "${DEP_INSTALL_DIR}/lib64/libhidapi-libusb.a")
set_target_properties(hidapi-libusb PROPERTIES
	IMPORTED_LOCATION "${HIDAPIUSB_LIB}"
	INTERFACE_LINK_LIBRARIES "usb"
)
add_library(hidapi-hidraw STATIC IMPORTED GLOBAL)
set(HIDAPIDRAW_LIB "${DEP_INSTALL_DIR}/lib64/libhidapi-hidraw.a")
set_target_properties(hidapi-hidraw PROPERTIES
	IMPORTED_LOCATION "${HIDAPIDRAW_LIB}"
)
set(HIDAPI_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/libhidapi")
if(NOT EXISTS "${HIDAPI_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/libusb/hidapi.git "${HIDAPI_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone hidapi")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${HIDAPI_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update hidapi")
    endif()
endif()
if(NOT EXISTS "${HIDAPIDRAW_LIB}" OR NOT EXISTS "${HIDAPIUSB_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libhidapi
		SOURCE_DIR "${HIDAPI_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/libhidapi"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS
			"${HIDAPIUSB_LIB}"
			"${HIDAPIDRAW_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DHIDAPI_WIDTH_HIDRAW:BOOL=ON
			-DHIDAPI_WITH_LIBUSB:BOOL=ON
	)
	add_dependencies(hidapi-libusb libhidapi)
	add_dependencies(hidapi-hidraw libhidapi)
else()
	message(STATUS "hidapi-hidraw found at ${HIDAPIDRAW_LIB} - skipping build")
	message(STATUS "hidapi-libusb found at ${HIDAPIUSB_LIB} - skipping build")
endif()
