#--------------------------------------#
#
#	zint
#
#--------------------------------------#
add_library(zint STATIC IMPORTED GLOBAL)
set(ZINT_LIB "${DEP_INSTALL_DIR}/lib64/libzint.a")
set_target_properties(zint PROPERTIES
	IMPORTED_LOCATION "${ZINT_LIB}"
	INTERFACE_LINK_LIBRARIES "zint"
)
set(ZINT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/zint")
if(NOT EXISTS "${ZINT_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/zint/zint.git "${ZINT_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone zint")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${ZINT_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update zint")
    endif()
endif()
if(NOT EXISTS "${ZINT_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libzint
		SOURCE_DIR "${ZINT_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/zint"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${ZINT_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=Release
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DZINT_FRONTEND:BOOL=OFF
			-DZINT_SHARED:BOOL=OFF
			-DZINT_STATIC:BOOL=ON
			-DZINT_USE_QT:BOOL=OFF
			-DZINT_USE_GS1SE:BOOL=OFF
	)
	add_dependencies(zint libzint)
else()
	message(STATUS "zint found at ${ZINT_LIB} - skipping build")
endif()
