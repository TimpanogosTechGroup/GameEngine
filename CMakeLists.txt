cmake_minimum_required(VERSION 3.8)
project(GameEngine)

# sets the C++ version
set(CMAKE_CXX_STANDARD 11)

# creates new variable LINUX
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

# checks the operating system
if (LINUX)
    message("Compiling for Linux :)")
elseif(WIN32)
    message("Comiling for Windows")
elseif(UNIX)
    message("Compiling on Apple")
else()
    message("Unkown compiler or OS")
endif(LINUX)

# this finds the SDL library, TODO replace with a more versatile option as not all computers have SDL installed
#find_package(SDL2 REQUIRED ${PROJECT_SOURCE_DIR}/lib/SDL/linux)

# this gets the opengl stuff, should be installed on all computers
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

#including all the include files
include_directories(include/bullet)
include_directories(include)

# adding all the source files
file(GLOB SOURCE_FILES
        "GameEngine/*.h"
        "GameEngine/*.cpp")

# this creates our executable
# cool feature latter on might be to add multiple executables
add_executable(GameEngine ${SOURCE_FILES})

# adding all the libraries
if (LINUX)

    set(ENGINE_LIBRARIES ${OPENGL_LIBRARY}
            ${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/linux/libGLEW.so #${SDL2_LIBRARIES}
            ${PROJECT_SOURCE_DIR}/lib/SDL/linux/lib/libSDL2.so
            ${PROJECT_SOURCE_DIR}/lib/bullet3/linux/libBulletDynamics_gmake_x64_release.a
            ${PROJECT_SOURCE_DIR}/lib/bullet3/linux/libBulletCollision_gmake_x64_release.a
            ${PROJECT_SOURCE_DIR}/lib/bullet3/linux/libLinearMath_gmake_x64_release.a
            ${PROJECT_SOURCE_DIR}/lib/bullet3/linux/libBulletSoftBody_gmake_x64_release.a
            ${PROJECT_SOURCE_DIR}/lib/assimp-4.0.1/linux/libassimp.so)

elseif(WIN32)
    set(ENGINE_LIBRARIES ${OPENGL_LIBRARY}
            ${PROJECT_SOURCE_DIR}/lib/GLEW/glew32.lib
            ${PROJECT_SOURCE_DIR}/lib/bullet/BulletCollision_Debug.lib
            ${PROJECT_SOURCE_DIR}/lib/bullet/BulletDynamics_Debug.lib
            ${PROJECT_SOURCE_DIR}/lib/bullet/BulletSoftBody_Debug.lib
            ${PROJECT_SOURCE_DIR}/lib/bullet/LinearMath_Debug.lib
            ${PROJECT_SOURCE_DIR}/lib/assimp/assimp-vc140-mt.lib
            ${PROJECT_SOURCE_DIR}/lib/win32/freetype271.lib
            ${PROJECT_SOURCE_DIR}/lib/win32/freetype271MT.lib)
endif(LINUX)

target_link_libraries(GameEngine ${ENGINE_LIBRARIES})
target_compile_options(GameEngine PRIVATE -Werror)