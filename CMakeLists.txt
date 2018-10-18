cmake_minimum_required(VERSION 3.8)
project(GameEngine)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED ${PROJECT_SOURCE_DIR}/lib/SDL)
find_package(OpenGL REQUIRED)
#find_package(Bullet REQUIRED ${PROJECT_SOURCE_DIR}/lib/bullet3 )
#set ( BULLET_USE_FILE     "@BULLET_USE_FILE@" )
#set ( BULLET_DEFINITIONS  "@BULLET_DEFINITIONS@" )
#set ( BULLET_INCLUDE_DIR  "@INCLUDE_INSTALL_DIR@" )
#set ( BULLET_INCLUDE_DIRS "@INCLUDE_INSTALL_DIR@" )
#set ( BULLET_LIBRARIES    "@BULLET_LIBRARIES@" )
#set ( BULLET_LIBRARY_DIRS "@LIB_DESTINATION@" )
#set ( BULLET_ROOT_DIR     "@CMAKE_INSTALL_PREFIX@" )
#set ( BULLET_VERSION_STRING "@BULLET_VERSION@" )

include_directories(include/bullet)
include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS})

link_directories(${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/lib)


file(GLOB SOURCE_FILES
        "GameEngine/*.h"
        "GameEngine/*.cpp")

add_executable(GameEngine ${SOURCE_FILES})
target_link_libraries( GameEngine ${OPENGL_LIBRARY} ${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/lib/libGLEW.so ${SDL2_LIBRARIES}
        ${PROJECT_SOURCE_DIR}/lib/bullet3/bin/libBulletDynamics_gmake_x64_release.a
        ${PROJECT_SOURCE_DIR}/lib/bullet3/bin/libBulletCollision_gmake_x64_release.a
        ${PROJECT_SOURCE_DIR}/lib/bullet3/bin/libLinearMath_gmake_x64_release.a
        ${PROJECT_SOURCE_DIR}/lib/bullet3/bin/libBulletSoftBody_gmake_x64_release.a)