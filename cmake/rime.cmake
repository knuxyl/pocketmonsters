#--------------------------------------#
#
#	rime
#
#--------------------------------------#
# rime build setup
add_library(rime STATIC IMPORTED GLOBAL)
set(RIME_LIB "${DEP_INSTALL_DIR}/lib64/librime.a")
set_target_properties(rime PROPERTIES
	IMPORTED_LOCATION "${RIME_LIB}"
	INTERFACE_LINK_LIBRARIES "boost"
)
set(RIME_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/rime")
if(NOT EXISTS "${RIME_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/rime/librime.git "${RIME_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone rime")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${RIME_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update rime")
    endif()
endif()
if(NOT EXISTS "${RIME_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(librime
		SOURCE_DIR "${RIME_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/rime"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${RIME_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=Release
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DBUILD_STATIC:BOOL=ON
			-DBUILD_TEST:BOOL=OFF
			-DBUILD_DATA:BOOL=ON
			-DENABLE_LOGGING:BOOL=OFF
			-DENABLE_ASAN:BOOL=ON
		    -DBoost_USE_STATIC_LIBS=ON
		    -DBoost_DIR:STRING=${DEP_INSTALL_DIR}/lib64/cmake
	)
	add_dependencies(librime libboost)
else()
	message(STATUS "rime found at ${RIME_LIB} - skipping build")
endif()
