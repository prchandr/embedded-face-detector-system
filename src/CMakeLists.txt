CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(EmbeddedFaceDetectorSystem)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_EXPORT_COMPILE_COMMANDS on)

INCLUDE_DIRECTORIES(
		actors
        graph
        $ENV{UXWELTERC}/src/gems/actors/basic
        $ENV{UXWELTERC}/src/gems/actors/common
        $ENV{UXWELTERC}/src/gems/edges
        $ENV{UXWELTERC}/src/tools/runtime
        $ENV{UXWELTERC}/src/tools/graph

        $ENV{UXWELTER}/lang/cpp/src/gems/actors/common
        $ENV{UXWELTER}/lang/cpp/src/gems/actors/basic
        $ENV{UXWELTER}/lang/cpp/src/tools/graph
        $ENV{UXWELTER}/lang/cpp/src/tools/runtime
        $ENV{UXWELTER}/lang/cpp/src/apps/basic

)

add_library(efds_src
		)

INSTALL(TARGETS efds_src DESTINATION
        $ENV{UXTMP})


