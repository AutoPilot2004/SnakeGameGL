cmake_minimum_required(VERSION 3.27.0)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Snake_Game_GL")

find_package(glfw3 CONFIG REQUIRED)
find_package(glew REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory ("engine")
add_subdirectory ("SnakeGame")