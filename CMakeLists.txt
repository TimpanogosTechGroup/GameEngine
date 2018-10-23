cmake_minimum_required(VERSION 3.8)
project(GameEngine)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED ${PROJECT_SOURCE_DIR}/lib/SDL/linux)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

include_directories(include/bullet)
include_directories(include)
#include_directories(${SDL2_INCLUDE_DIRS})

#link_directories(${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/lib)


file(GLOB SOURCE_FILES
        "GameEngine/*.h"
        "GameEngine/*.cpp")

add_executable(GameEngine ${SOURCE_FILES} GameEngine/FileSystemManager.cpp GameEngine/Cube.cpp GameEngine/Cube.h)

# adding all the libraries
target_link_libraries( GameEngine ${OPENGL_LIBRARY} ${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/linux/libGLEW.so ${SDL2_LIBRARIES}
        ${PROJECT_SOURCE_DIR}/lib/bullet3/linux/libBulletDynamics_gmake_x64_release.a
        ${PROJECT_SOURCE_DIR}/lib/bullet3/linux/libBulletCollision_gmake_x64_release.a
        ${PROJECT_SOURCE_DIR}/lib/bullet3/linux/libLinearMath_gmake_x64_release.a
        ${PROJECT_SOURCE_DIR}/lib/bullet3/linux/libBulletSoftBody_gmake_x64_release.a
        ${PROJECT_SOURCE_DIR}/lib/assimp-4.0.1/linux/libassimp.so)