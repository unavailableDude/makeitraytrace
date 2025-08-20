cmake_minimum_required(VERSION 3.10)
project(Raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O0 -g")

# set path to SDL2 and get it
set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/SDL2/cmake/)
find_package(SDL2 REQUIRED)

# Use GLM as header-only library
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/glm)

find_package(OpenGL REQUIRED)

file(GLOB IMGUI_SOURCES
    "lib/imgui/*.cpp"
    "lib/imgui/backends/imgui_impl_sdl2.cpp"
    "lib/imgui/backends/imgui_impl_opengl3.cpp"
)

file(GLOB GLAD_SOURCES
    "lib/glad/glad.c"
)

# set source files for the library
set(LIB_SOURCES src/Vec4.cpp src/Ray.cpp src/Color4.cpp src/Canvas.cpp src/Sphere.cpp src/RayHit.cpp src/Renderer.cpp src/Window.cpp ${GLAD_SOURCES})

# define library raytracer_core and add its sources, and include directories
add_library(raytracer_core STATIC ${LIB_SOURCES})
target_include_directories(raytracer_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends
    ${SDL2_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIR}
)

# add target, and link libraries
add_executable(raytracer src/main.cpp)
target_sources(raytracer PRIVATE ${IMGUI_SOURCES})
target_link_libraries(raytracer raytracer_core SDL2::SDL2main SDL2::SDL2 OpenGL::GL)
target_include_directories(raytracer PRIVATE ${SDL2_INCLUDE_DIRS} ${GLM_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends)


#### for testing ####
enable_testing()
#create test programs from the test sources
file(GLOB TEST_SOURCES "test/test_*.cpp")

# Create executable for each test file
foreach(test_file ${TEST_SOURCES})
    # Get filename without extension
    get_filename_component(test_name ${test_file} NAME_WE)
    # Create executable
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} raytracer_core)
	# Set output directory to build/tests
    set_target_properties(${test_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
    
    # Add to test framework
    add_test(NAME ${test_name} COMMAND ${CMAKE_BINARY_DIR}/tests/${test_name})
endforeach()

# Custom target to build all tests
add_custom_target(build_tests)
foreach(test_file ${TEST_SOURCES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_dependencies(build_tests ${test_name})
endforeach()