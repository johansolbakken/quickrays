cmake_minimum_required(VERSION 3.16)

project(QuickRays3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickActionStore)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appQuickRays3
    src/main.cpp
)

target_include_directories(appQuickRays3
    PRIVATE src
    PUBLIC vendor/glm)

qt_add_qml_module(appQuickRays3
    URI QuickRays3
    VERSION 1.0
    QML_FILES src/Main.qml 
    SOURCES src/johanrenderer.h src/johanrenderer.cpp
            src/renderer.h src/renderer.cpp
            src/camera.h src/camera.cpp
            src/ray.h src/ray.cpp
            src/scene.h src/scene.cpp
)

set_target_properties(appQuickRays3 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQuickRays3
    PRIVATE Qt6::Quick
            Qt6::QuickActionStore
)

install(TARGETS appQuickRays3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
