#--------------------------------------#
#
#	gsf
#	Not adding to project yet, it pulls in zlib and mgba
#
#--------------------------------------#
add_library(gsf STATIC IMPORTED GLOBAL)
set(GSF_LIB "${DEP_INSTALL_DIR}/lib64/libgsf.a")
set_target_properties(gsf PROPERTIES
	IMPORTED_LOCATION "${GSF_LIB}"
)
set(GSF_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/libgsf")
if(NOT EXISTS "${GSF_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://codeberg.org/chrg/libgsf.git "${GSF_SOURCE_DIR}"
        COMMAND sed -i "s/\n\tSHARED/\n\tSTATIC/g" "${GSF_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone gsf")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${GSF_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update gsf")
    endif()
endif()
if(NOT EXISTS "${GSF_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libgsf
		SOURCE_DIR "${GSF_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/gsf"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${GSF_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=Release
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DGSF_BUILD_STATIC:BOOL=ON
	)
	add_dependencies(gsf libgsf)
else()
	message(STATUS "gsf found at ${GSF_LIB} - skipping build")
endif()
