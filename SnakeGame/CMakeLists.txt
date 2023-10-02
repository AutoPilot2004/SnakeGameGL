file(GLOB_RECURSE SRC_FILES ./*.cpp)

add_executable(SnakeGame ${SRC_FILES})
target_include_directories(SnakeGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(SnakeGame PRIVATE engine)

add_custom_command(TARGET SnakeGame POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:SnakeGame>/assets
  COMMAND_EXPAND_LISTS
  )