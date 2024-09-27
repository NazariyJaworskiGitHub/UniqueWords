set(ut_build_target ${PROJECT_NAME}_ut)

file( GLOB ut_srcfiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.hpp *.c *.cpp)
# message(${ut_srcfiles})

# Add the executable target
add_executable(${ut_build_target} ${ut_srcfiles})

target_link_libraries(
    ${ut_build_target}
    ${PROJECT_NAME}_lib
    )

add_custom_command(
  TARGET ${ut_build_target}
  POST_BUILD
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${ut_build_target}  # Specify full path to executable
  DEPENDS ${ut_build_target})  # Ensure executable is built first
