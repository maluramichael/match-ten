CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
SET(EXECUTABLE_NAME "match-ten")
PROJECT(${EXECUTABLE_NAME})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES
		src/main.cpp
		src/Scene.cpp
		src/Scenes/Menu.cpp
		src/Scenes/Game.cpp
		src/Application.cpp
		)
ADD_EXECUTABLE(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Detect and add SFML
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
FIND_PACKAGE(SFML 2.3 REQUIRED system window graphics network audio)
IF (SFML_FOUND)
	INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
ENDIF ()

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} tinyxml2)

# Install target
INSTALL(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
INCLUDE(InstallRequiredSystemLibraries)
INCLUDE(CPack)