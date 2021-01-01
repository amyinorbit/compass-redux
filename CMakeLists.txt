cmake_minimum_required(VERSION 3.12)
project(compass
    VERSION 1.0.0
    DESCRIPTION "Lightweight interactive fiction engine"
    HOMEPAGE_URL "https://github.com/amyinorbit/compass"
    LANGUAGES C
)

option(COMPASS_BUILD_DEMO "Build the parser/running demo" ON)
option(COMPASS_BUILD_CLI "Build the deafult command line interface" ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(packages/unic)
add_subdirectory(packages/ccore)

add_definitions(
    "-DCOMPASS_VERSION=\"${PROJECT_VERSION}\""
    "-DCOMPASS_VERSION_MAJOR=${PROJECT_MAJOR_VERSION}"
    "-DCOMPASS_VERSION_MINOR=${PROJECT_MINOR_VERSION}"
    "-DCOMPASS_VERSION_PATCH=${PROJECT_PATCH_VERSION}"
)

find_package(ccore REQUIRED)
add_library(${PROJECT_NAME} STATIC src/vm.c src/parser.c src/tokens.c)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC ccore::ccore unic::unic)
target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(${PROJECT_NAME}
    PUBLIC  $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

if(COMPASS_BUILD_DEMO)
    add_executable(compass-demo demo/main.c)
    target_link_libraries(compass-demo ${PROJECT_NAME})
endif()


