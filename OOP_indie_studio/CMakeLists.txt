# Minimum Cmake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(bomberman)

IF (NOT Irrlicht_INCLUDE_DIRS OR NOT Irrlicht_LIBRARIES)
  FIND_PATH(Irrlicht_INCLUDE_DIRS
    NAMES
      irrlicht.h
    PATHS
      /usr/include/irrlicht/        # Default Fedora28 system include path
      /usr/include/irr/             # Include path for Ubuntu
      /usr/local/include/irrlicht/  # Default Fedora28 local include path
      ${CMAKE_MODULE_PATH}/include/ # Expected to contain the path to this file for Windows10
      ${Irrlicht_DIR}/include/      # Irrlicht root directory (if provided)
  )

  IF (MSVC)     # Windows
    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  ELSE (MSVC)   # Linux
    SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
  ENDIF(MSVC)

  FIND_LIBRARY(Irrlicht_LIBRARIES
    NAMES
      Irrlicht
    PATHS
      /usr/lib64/                   # Default Fedora28 library path
      /usr/lib/                     # Some more Linux library path
      /usr/lib/x86_64-linux-gnu/    # Some more Linux library path
      /usr/local/lib/               # Some more Linux library path
      /usr/local/lib64/             # Some more Linux library path
      ${CMAKE_MODULE_PATH}/         # Expected to contain the path to this file for Windows10
      ${Irrlicht_DIR}/              # Irrlicht root directory (if provided)
  )
ENDIF (NOT Irrlicht_INCLUDE_DIRS OR NOT Irrlicht_LIBRARIES)

IF (Irrlicht_INCLUDE_DIRS AND Irrlicht_LIBRARIES)
  SET(Irrlicht_FOUND TRUE)
ELSE (Irrlicht_INCLUDE_DIRS AND Irrlicht_LIBRARIES)
  SET(Irrlicht_FOUND FALSE)
ENDIF (Irrlicht_INCLUDE_DIRS AND Irrlicht_LIBRARIES)

IF (Irrlicht_FIND_REQUIRED AND NOT Irrlicht_FOUND)
  MESSAGE(FATAL_ERROR
    "  Irrlicht not found.\n"
    "      Windows: Fill CMake variable CMAKE_MODULE_PATH to the provided directory.\n"
    "      Linux: Install Irrlicht using your package manager ($> sudo dnf install irrlicht-devel).\n"
  )
ENDIF (Irrlicht_FIND_REQUIRED AND NOT Irrlicht_FOUND)

# # C++11
# if (UNIX)
# 	SET(CMAKE_CXX_COMPILER g++)
# 	add_compile_options(-std=c++11)
# 	add_compile_options(-Wall)
# 	add_compile_options(-Wextra)
# elseif(WIN32)
# 	# SET(CMAKE_CXX_COMPILER visualc++)
# endif(UNIX)

# # #  Flags
# # SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
# SET(CMAKE_CXX_FLAGS_DEBUG  "g")

# set(CMAKE_MODULE_PATH "cmake_modules" ${CMAKE_MODULE_PATH})
# # SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
# # # SET(GCC_COVERAGE_LINK_FLAGES "-lgl")

# # IF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
# #    SET(CMAKE_BUILD_TYPE RelWithDebInfo)
# # ENDIF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

# # IF(CMAKE_CXX_FLAGS_DEBUG)
# #    SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/debug)
# # ELSE(CMAKE_CXX_FLAGS_DEBUG)
# #    SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release)
# # ENDIF(CMAKE_CXX_FLAGS_DEBUG)

# # Irrlicht
# FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem)
# FIND_PACKAGE(X11 REQUIRED)
# FIND_PACKAGE(OpenGL REQUIRED)
# FIND_PACKAGE(GLUT REQUIRED)
# FIND_PACKAGE(ZLIB REQUIRED)
# FIND_PACKAGE(IRRLICHT REQUIRED)
# FIND_PACKAGE(SFML 2 REQUIRED COMPONENTS audio)
# find_package(Threads REQUIRED)


# INCLUDE_DIRECTORIES(
# 	${Boost_INCLUDE_DIR}
# 	${IRRLICHT_INCLUDE_DIR}
# 	${SFML_INCLUDE_DIR}
# 	${OPENGL_INCLUDE_DIRS}
# 	${GLUT_INCLUDE_DIR}
# 	${ZLIB_INCLUDE_DIR}
# 	${X11_INCLUDE_DIR}
# 	${PROJECT_SOURCE_DIR}/include
# 	${PROJECT_SOURCE_DIR}/include/entities
# )

# FILE(GLOB SRCS src/*.cpp)
# FILE(GLOB HDRS include/*.hpp include/entities/*.hpp)
FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR})


include_directories(include include/entities)

set(SRCS
	src/Board.cpp
	src/AEntity.cpp
	src/AMovable.cpp
	src/ATimed.cpp
	src/BoardGenerator.cpp
	src/main.cpp
	src/Timer.cpp
	src/Display.cpp	
	src/Sound.cpp
	src/entities/Bomb.cpp
	src/entities/Player.cpp
	src/entities/Monster.cpp
	src/entities/Floor.cpp
	src/entities/Wall.cpp
	src/entities/Soft.cpp
	src/entities/PowerUp.cpp
  src/Directories.cpp
  src/Explosion.cpp)
# set(HDRS
# 	include/Board.hpp
# 	include/AEntity.hpp
# 	include/AMovable.hpp
# 	include/ATimed.hpp
# 	include/ARunnable.hpp
# 	include/BoardGenerator.hpp
# 	include/bomberman.hpp
# 	include/Timer.hpp
# 	include/Sound.hpp
# 	include/entities/Bomb.hpp
# 	include/entities/Player.hpp
# 	include/entities/Monster.hpp
# 	include/entities/Floor.hpp
# 	include/entities/Wall.hpp
# 	include/entities/Soft.hpp
# 	include/entities/PowerUp.hpp
#     include/MyEventReceiver.hpp
#     include/Colision.hpp)

# Executable name
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Weffc++ -O3")
add_executable(bomberman ${SRCS})

# dependancy
target_link_libraries(bomberman ${Boost_LIBRARIES})
target_link_libraries(bomberman Irrlicht)
target_link_libraries(bomberman sfml-audio)
target_link_libraries(bomberman GL)
target_link_libraries(bomberman Xxf86vm)
target_link_libraries(bomberman Xext)
target_link_libraries(bomberman X11)
target_link_libraries(bomberman Xcursor)
# TARGET_LINK_LIBRARIES(bomberman
# 	${Boost_LIBRARIES}
# 	${X11_LIBRARIES}
# 	${IRRLICHT_LIBRARY}
# 	# "/usr/lib/libIrrlicht.a"
# 	"/usr/lib/x86_64-linux-gnu/libX11.so"
# 	"/usr/lib/x86_64-linux-gnu/libXxf86vm.so.1"
# 	${OPENGL_LIBRARIES}
# 	${GLUT_LIBRARIES}
# 	${ZLIB_LIBRARIES}
# 	${SFML_LIBRARIES}
# 	${SFML_DEPENDENCIES}
# 	${CMAKE_THREAD_LIBS_INIT}
# )
