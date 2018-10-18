cmake_minimum_required(VERSION 3.8)
project(GameEngine)

set(CMAKE_CXX_STANDARD 11)

#find_package(SDL2 REQUIRED /users/guest/b/bbrenk/Documents/GitHub/Repositories/SDL/libraries)
find_package(SDL2 REQUIRED ${PROJECT_SOURCE_DIR}/lib/SDL)
find_package(OpenGL REQUIRED)

include_directories(include/bullet)
include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS})

link_directories(${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/lib)

#add_subdirectory( ${PROJECT_SOURCE_DIR}/glew-2.1.0/build/cmake )

#set(SOURCE_FILES
#        GameEngine/AssetManager.cpp
#        GameEngine/AssetManager.h
#        GameEngine/Camera.cpp
#        GameEngine/Camera.h
#        GameEngine/FrameBuffer.cpp
#        GameEngine/FrameBuffer.h
#        GameEngine/main.cpp
#        GameEngine/Material.h
#        GameEngine/Object.cpp
#        GameEngine/Object.h
#        GameEngine/OpenGlRenderer.cpp
#        GameEngine/OpenGlRenderer.h
#        GameEngine/PrimitiveShape.cpp
#        GameEngine/PrimitiveShape.h
#        GameEngine/Registry.cpp
#        GameEngine/Registry.h
#        GameEngine/RenderEngine.h
#        GameEngine/RenderItem.h
#        GameEngine/Shader.cpp
#        GameEngine/Shader.h
#        GameEngine/Source.cpp
#        GameEngine/Texture.h
#        GameEngine/Verticies.cpp
#        GameEngine/Verticies.h)

file(GLOB SOURCE_FILES
        "GameEngine/*.h"
        "GameEngine/*.cpp")

add_executable(GameEngine ${SOURCE_FILES})
target_link_libraries( GameEngine ${OPENGL_LIBRARY} ${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/lib/libGLEW.so ${SDL2_LIBRARIES})
#target_include_directories(GameEngine PRIVATE ${PROJECT_SOURCE_DIR}/glew-2.1.0/include/)