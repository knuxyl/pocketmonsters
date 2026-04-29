#--------------------------------------#
#
#	clay
#
#--------------------------------------#
# clay build setup
set(CLAY_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/clay")
if(NOT EXISTS "${CLAY_SOURCE_DIR}/renderers/raylib/clay_renderer_raylib.c")
    execute_process(
        COMMAND git clone --recursive https://github.com/nicbarker/clay.git "${CLAY_SOURCE_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone clay")
    endif()
elseif(UPDATE_DEPS)
    execute_process(
        WORKING_DIRECTORY "${CLAY_SOURCE_DIR}"
        COMMAND git pull
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to update clay")
    endif()
endif()
