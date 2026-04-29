#--------------------------------------#
#
# libdrm
#
#--------------------------------------#
# libdrm build setup
add_library(drm STATIC IMPORTED GLOBAL)
set(DRM_LIB "${DEP_INSTALL_DIR}/lib64/libdrm.a")
set_target_properties(drm PROPERTIES
	IMPORTED_LOCATION "${DRM_LIB}"
)
set(DRM_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/drm")
if(NOT EXISTS "${DRM_SOURCE_DIR}")
    execute_process(
        COMMAND git clone https://gitlab.freedesktop.org/mesa/drm.git "${DRM_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone drm")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${DRM_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update drm")
    endif()
endif()
if(NOT EXISTS "${DRM_LIB}" OR BUILD_DEPS)
	ExternalProject_Add(libdrm
		SOURCE_DIR "${DRM_SOURCE_DIR}"
		PREFIX "${DEP_BUILD_DIR}/drm"
		BUILD_ALWAYS ${BUILD_DEPS}
		BUILD_BYPRODUCTS "${DRM_LIB}"
		CONFIGURE_COMMAND bash -c "meson setup \"<BINARY_DIR>\" \
			--prefix=\"${DEP_INSTALL_DIR}\" \
			--buildtype=release \
			-Ddefault_library=static \
			-Dintel=enabled \
			-Dradeon=enabled \
			-Damdgpu=enabled \
			-Dnouveau=enabled \
			-Dvmwgfx=enabled \
			-Domap=enabled \
			-Dexynos=enabled \
			-Dfreedreno=enabled \
			-Dtegra=enabled \
			-Dvc4=enabled \
			-Detnaviv=enabled \
			-Dcairo-tests=disabled \
			-Dman-pages=disabled \
			-Dvalgrind=disabled \
			-Dfreedreno-kgsl=true \
			-Dinstall-test-programs=false \
			-Dudev=false \
			-Dtests=false \
			\"<SOURCE_DIR>\""
		BUILD_COMMAND bash -c "ninja -C \"<BINARY_DIR>\""
		INSTALL_COMMAND bash -c "ninja -C \"<BINARY_DIR>\" install"
	)
	add_dependencies(drm libdrm)
else()
	message(STATUS "drm found at ${DRM_LIB} - skipping build")
endif()
