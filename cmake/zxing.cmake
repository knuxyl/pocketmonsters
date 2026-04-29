#--------------------------------------#
#
#	zxing-cpp
#
#--------------------------------------#
add_library(zxing STATIC IMPORTED GLOBAL)
set(ZXING_LIB "${DEP_INSTALL_DIR}/lib64/libZXing.a")
set_target_properties(zxing PROPERTIES
	IMPORTED_LOCATION "${ZXING_LIB}"
	INTERFACE_LINK_LIBRARIES "zint"
)
set(ZXING_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/zxing-cpp")
if(NOT EXISTS "${ZXING_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/zxing-cpp/zxing-cpp.git "${ZXING_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone zxing")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${ZXING_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update zxing")
    endif()
endif()
if(NOT EXISTS "${ZXING_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libzxing
		SOURCE_DIR "${ZXING_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/zxing"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${ZXING_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=Release
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DZXING_C_API:BOOL=ON
			-DZXING_ENABLED_1D:BOOL=OFF
			-DZXING_ENABLE_AZTECT:BOOL=ON
			-DZXING_ENABLE_DATAMATRIX:BOOL=ON
			-DZXING_ENABLE_MAXICODE:BOOL=OFF
			-DZXING_ENABLE_PDF417:BOOL=OFF
			-DZXING_ENABLE_QRCODE:BOOL=ON
			-DZXING_EXAMPLES:BOOL=OFF
			-DZXING_PYTHON_MODULES:BOOL=OFF
			-DZXING_USE_BUNDLED_ZINT:BOOL=OFF
	)
	add_dependencies(zxing libzxing)
else()
	message(STATUS "zxing found at ${ZXING_LIB} - skipping build")
endif()
