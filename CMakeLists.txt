cmake_minimum_required(VERSION 3.10)

set(CMAKE_SIZEOF_VOID_P 8)
set(CMAKE_C_COMPILER "gcc.exe")
set(CMAKE_CXX_COMPILER "g++.exe")

project(Raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O0 -g -static-libgcc -static-libstdc++ -mconsole")

# SDL2
set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/SDL2/cmake/)
find_package(SDL2 REQUIRED)

# GLM as header-only library
add_library(glm_lib INTERFACE)
target_include_directories(glm_lib INTERFACE ${CMAKE_CURRENT_LIST_DIR}/lib/glm)

find_package(OpenGL REQUIRED)

# GLAD
file(GLOB GLAD_SOURCES
"lib/glad/src/glad.c"
)
add_library(glad_lib STATIC ${GLAD_SOURCES})
target_include_directories(glad_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include)

# ImGui
file(GLOB IMGUI_SOURCES
    "lib/imgui/*.cpp"
    "lib/imgui/backends/imgui_impl_sdl2.cpp"
    "lib/imgui/backends/imgui_impl_opengl3.cpp"
)
add_library(imgui_lib STATIC ${IMGUI_SOURCES})
target_include_directories(imgui_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends
    ${SDL2_INCLUDE_DIRS} # imgui needs to see SDL2 includes
)
target_link_libraries(imgui_lib PUBLIC glad_lib)

# MIRT core library
set(MIRT_CORE_SOURCES 
    src/Canvas.cpp 
    src/Color4.cpp 
    src/Material.cpp
    src/OpenGLLayer.cpp
    src/Ray.cpp 
    src/RayHit.cpp 
    src/Renderer.cpp 
    src/Sphere.cpp 
    src/PointLight.cpp
    src/Vec4.cpp 
    src/Window.cpp
    src/ShaderProgram.cpp
    src/ShaderLoader.cpp
)

add_library(MIRT_CORE STATIC ${MIRT_CORE_SOURCES})
# add imgui's includes so make doesn't complain about them in Window.cpp
target_include_directories(MIRT_CORE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
                                            ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui 
                                            ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends 
                                            ${SDL2_INCLUDE_DIRS}
                                            ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include)


add_library(MIRT_DEPS INTERFACE)
target_link_libraries(MIRT_DEPS INTERFACE
    glm_lib 
    imgui_lib 
    SDL2::SDL2main 
    SDL2::SDL2 
    OpenGL::GL
    glad_lib 
)

# this is for the test binaries, they do not use SDL, so no sdl linking
add_library(MIRT_TEST_DEPS STATIC ${MIRT_CORE_SOURCES})
target_include_directories(MIRT_TEST_DEPS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(MIRT_TEST_DEPS PUBLIC 
    glad_lib 
    glm_lib 
    imgui_lib 
    OpenGL::GL
)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer MIRT_CORE MIRT_DEPS)
set_target_properties(raytracer PROPERTIES LINK_FLAGS "-mconsole")

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
    target_link_libraries(${test_name} MIRT_TEST_DEPS)
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