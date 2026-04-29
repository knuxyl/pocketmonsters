#--------------------------------------#
#
#	boost
#
#--------------------------------------#
# boost build setup
add_library(boost STATIC IMPORTED GLOBAL)
set(BOOST_LIB "${DEP_INSTALL_DIR}/lib64/libboost_filesystem.a")
set_target_properties(boost PROPERTIES
	IMPORTED_LOCATION "${BOOST_LIB}"
)
set(BOOST_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/boost")
if(NOT EXISTS "${BOOST_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://github.com/boostorg/boost.git "${BOOST_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone boost")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${BOOST_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update boost")
    endif()
endif()
#if(NOT EXISTS "${BOOST_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libboost
		SOURCE_DIR "${BOOST_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/boost"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${BOOST_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
	)
	add_dependencies(boost libboost)
#else()
	#message(STATUS "boost found at ${BOOST_LIB} - skipping build")
#endif()
