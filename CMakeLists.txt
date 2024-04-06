cmake_minimum_required(VERSION 3.16)

project(OpenSesame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Core Network)

qt_standard_project_setup()

qt_add_executable(appOpenSesame
    main.cpp
)

qt_add_qml_module(appOpenSesame
    URI OpenSesame
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES Resources.qrc
        SOURCES sslclient.cpp
        SOURCES sslclient.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appOpenSesame PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appOpenSesame
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appOpenSesame
    PRIVATE Qt6::Quick Qt6::Core Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appOpenSesame
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
