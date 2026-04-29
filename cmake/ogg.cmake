#--------------------------------------#
#
#	ogg
#
#--------------------------------------#
# ogg build setup
add_library(ogg STATIC IMPORTED GLOBAL)
set(OGG_LIB "${DEP_INSTALL_DIR}/lib64/libogg.a")
set_target_properties(ogg PROPERTIES
	IMPORTED_LOCATION "${OGG_LIB}"
)
set(OPUS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/ogg")
if(NOT EXISTS "${OPUS_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/xiph/ogg.git "${OPUS_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone ogg")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${OPUS_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update ogg")
    endif()
endif()
if(NOT EXISTS "${OGG_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libogg
		SOURCE_DIR "${OPUS_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/ogg"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${OGG_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DINSTALL_DOCS:BOOL=OFF
	)
	add_dependencies(ogg libogg)
else()
	message(STATUS "libogg found at ${OGG_LIB} - skipping build")
endif()
