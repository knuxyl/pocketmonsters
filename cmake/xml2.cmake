#--------------------------------------#
#
#	xml2
#
#--------------------------------------#
add_library(xml2 STATIC IMPORTED GLOBAL)
set(XML2_LIB "${DEP_INSTALL_DIR}/lib64/libxml2.a")
set_target_properties(xml2 PROPERTIES
	IMPORTED_LOCATION "${XML2_LIB}"
)
set(XML2_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/libxml2")
if(NOT EXISTS "${XML2_SOURCE_DIR}")
    execute_process(
        COMMAND git clone --recursive https://gitlab.gnome.org/GNOME/libxml2.git "${XML2_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone xml2")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${XML2_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update xml2")
    endif()
endif()
if(NOT EXISTS "${XML2_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libxml2
		SOURCE_DIR "${XML2_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/xml2"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${XML2_LIB}"
		CMAKE_CACHE_ARGS
			-DCMAKE_BUILD_TYPE:STRING=Release
			-DCMAKE_INSTALL_PREFIX:STRING=${DEP_INSTALL_DIR}
			-DBUILD_SHARED_LIBS:BOOL=OFF
			-DBUILD_TESTING:BOOL=OFF
			-DLIBXML2_WITH_DEBUG:BOOL=OFF
			-DLIBXML2_WITH_HTML:BOOL=OFF
			-DLIBXML2_WITH_PYTHON:BOOL=OFF
			-DLIBXML2_WITH_TESTS:BOOL=OFF
			-DLIBXML2_WITH_ZLIB:BOOL=OFF
			-DLIBXML2_WITH_PROGRAMS:BOOL=OFF
	)
	add_dependencies(xml2 libxml2)
else()
	message(STATUS "xml2 found at ${XML2_LIB} - skipping build")
endif()
