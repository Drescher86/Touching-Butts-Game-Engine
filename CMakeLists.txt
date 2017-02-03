cmake_minimum_required(VERSION 3.6)
project(Touching_Butts)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

file(GLOB 
	COMPONENT_SOURCE
	"src/Components/*.cpp"
)
		
file(GLOB 
	COMPONENT_HEADER
	"src/Components/*.h"
	"src/Components/*.hpp"
)		

file(GLOB
	LUAHANDLER_HEADER
	"src/LuaHandlers/*.h"
	"src/LuaHandlers/*.hpp"
)

file(GLOB
	LUAHANDLER_SOURCE
	"src/LuaHandlers/*.cpp"
)

file(GLOB 
	SOURCE_FILES
    "src/*.cpp"
)
		
file(GLOB 
	HEADER_FILES
	"src/*.hpp"
    "src/*.h"
)		
file(GLOB 
	PARTICLE_SOURCE
	"src/ParticleSystem/*.cpp"
)
	
file(GLOB 
	PARTICLE_HEADER
	"src/ParticleSystem/*.h"
	"src/ParticleSystem/*.hpp"
)

file(GLOB
	DEMO_GAME
	"src/Demo Game/*.h"
	"src/Demo Game/*.hpp"
	"src/Demo Game/*.cpp"
	)
	
file(GLOB
	PARTICLE_DEMO
	"src/Particle Demo/*.h"
	"src/Particle Demo/*.hpp"
	"src/Particle Demo/*.cpp"
)
file(GLOB
	PHYSICS_TECH_DEMO
	"src/Physics Demo/*.h"
	"src/Physics Demo/*.hpp"
	"src/Physics Demo/*.cpp"
)
file(GLOB
	SCRIPTING_TECH_DEMO
	"src/Scripting Demo/*.h"
	"src/Scripting Demo/*.hpp"
	"src/Scripting Demo/*.cpp"
)
add_library(Touching_Butts STATIC ${SOURCE_FILES} ${HEADER_FILES} ${COMPONENT_SOURCE} ${COMPONENT_HEADER} ${PARTICLE_SOURCE} ${PARTICLE_HEADER} ${LUAHANDLER_HEADER} ${LUAHANDLER_SOURCE})
add_executable(Demo_Game ${DEMO_GAME})
add_executable(Particle_Demo ${PARTICLE_DEMO})
add_executable(Physics_Demo ${PHYSICS_TECH_DEMO})
add_executable(Scripting_Demo ${SCRIPTING_TECH_DEMO})

source_group("Source Files\\Components" FILES ${COMPONENT_SOURCE})
source_group("Header Files\\Components" FILES ${COMPONENT_HEADER})

source_group("Source Files\\ParticleSystem" FILES ${PARTICLE_SOURCE})
source_group("Header Files\\ParticleSystem" FILES ${PARTICLE_HEADER})

source_group("Source Files\\LuaHandlers" FILES ${LUAHANDLER_SOURCE})
source_group("Header Files\\LuaHandlers" FILES ${LUAHANDLER_HEADER})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})



#########################################################
# FIND OPENGL
#########################################################
IF(APPLE)
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    MARK_AS_ADVANCED (OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${OpenGL_LIBRARY})
ELSE (APPLE)
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    IF(UNIX)
        find_package(GLEW REQUIRED)
    ELSE(UNIX)
        find_package(glew REQUIRED)
    ENDIF(UNIX)
    include_directories(${GLEW_INCLUDE_DIR})
    SET(EXTRA_LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARY})
ENDIF (APPLE)

find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(.)

# Box2D
find_package(Box2D REQUIRED)
include_directories(${BOX2D_INCLUDE_DIR})

# GLM -- on Windows: depends on env var: GLM_ROOT_DIR
find_package (glm REQUIRED)

IF(UNIX AND NOT APPLE)
    IF( glm_FOUND )
        INCLUDE_DIRECTORIES( ${GLM_INCLUDE_DIR} )
    ELSE( glm_FOUND )
        MESSAGE( STATUS "Failed to find GLM ----------------------")
    ENDIF( glm_FOUND )
ELSE(UNIX AND NOT APPLE)
    IF( GLM_FOUND )
        INCLUDE_DIRECTORIES( ${GLM_INCLUDE_DIR} )
    ELSE( GLM_FOUND )
        MESSAGE( STATUS "Failed to find GLM ----------------------")
    ENDIF( GLM_FOUND )
ENDIF(UNIX AND NOT APPLE)

find_package(SRE REQUIRED)
if (SRE_FOUND)
    include_directories(${SRE_INCLUDE_DIR})
ELSE (SRE_FOUND)
    MESSAGE( STATUS "Failed to find Simple Render Engine")
endif(SRE_FOUND)

find_package(LUA REQUIRED)
if (LUA_FOUND)
	include_directories(${LUA_INCLUDE_DIR})
ELSE (LUA_FOUND)
	MESSAGE(STATUS "Failed to find LUA")
endif(LUA_FOUND)

find_package(LUABridge REQUIRED)
if(LUABRIDGE_FOUND)
	include_directories(${LUABRIDGE_INCLUDE_DIR})
ELSE(LUABRIDGE_FOUND)
	MESSAGE(STATUS "Failed to find LUABridge")
endif(LUABRIDGE_FOUND)

target_link_libraries(Touching_Butts ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SRE_LIBRARY} ${BOX2D_LIBRARY} ${LUA_LIBRARY})
target_link_libraries(Demo_Game Touching_Butts)
target_link_libraries(Particle_Demo Touching_Butts)
target_link_libraries(Physics_Demo Touching_Butts)
target_link_libraries(Scripting_Demo Touching_Butts)

IF (WIN32)
    SET(SDL2_dll "" CACHE STRING "Where the SDL2.dll can be found")
    SET(SDL2_image_dll "" CACHE STRING "Where the SDL2_image.dll can be found")
    SET(libjpeg-9_dll "" CACHE STRING "Where the libjpeg-9.dll can be found")
    SET(libpng16-16_dll "" CACHE STRING "Where the libpng16-16.dll can be found")
    SET(libtiff-5_dll "" CACHE STRING "Where the libtiff-5.dll can be found")
    SET(libwebp-4_dll "" CACHE STRING "Where the libwebp-4.dll can be found")
    SET(zlib1_dll "" CACHE STRING "Where the zlib1.dll can be found")
    SET(DLLFileList ${libjpeg-9_dll} ${libpng16-16_dll} ${SDL2_dll} ${SDL2_image_dll} ${zlib1_dll} ${libtiff-5_dll} ${libwebp-4_dll})
    file(COPY ${DLLFileList} DESTINATION Debug)
    file(COPY ${DLLFileList} DESTINATION Release)
ENDIF(WIN32)