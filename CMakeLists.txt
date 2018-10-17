cmake_minimum_required(VERSION 3.8)
project(GameEngine)

set(CMAKE_CXX_STANDARD 11)

include_directories(include/bullet)
include_directories(include)

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