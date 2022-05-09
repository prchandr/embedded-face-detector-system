CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

PROJECT(EmbeddedFaceDetectorSystemTraining)

SET(CMAKE_CXX_STANDARD 14)

SET(CMAKE_EXPORT_COMPILE_COMMANDS on)

ADD_EXECUTABLE(
        efds_train.exe
        efds_train.cpp
)

TARGET_LINK_LIBRARIES(
        efds_train.exe
)

INSTALL(TARGETS efds_train.exe DESTINATION
        ${PROJECT_SOURCE_DIR})

