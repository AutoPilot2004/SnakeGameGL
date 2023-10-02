file(GLOB_RECURSE SRC_FILES ./*.cpp)

add_library(engine ${SRC_FILES})
target_link_libraries(engine PUBLIC glfw GLEW::GLEW glm::glm)