cmake_minimum_required(VERSION 3.16)

project(smp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS  Widgets  Sql   REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Network Widgets)



set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(smp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        dialog.h dialog.cpp dialog.ui
        secwin.h secwin.cpp secwin.ui
        resource.qrc
        admin.h admin.cpp admin.ui
        adminpanel.h adminpanel.cpp
        adminpanel.ui
        regform.h regform.cpp regform.ui
        hashpass.h
        hashpass.cpp
        schlserver.h schlserver.cpp
        regform_1.h regform_1.cpp regform_1.ui
        formreg.h formreg.cpp formreg.ui





    )






# Define target properties for Android with Qt 6 as:
#    set_property(TARGET smp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(smp SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(smp
            ${PROJECT_SOURCES}
        )
    endif()
endif()



target_link_libraries(smp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(smp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt6::Network)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.smp)
endif()
set_target_properties(smp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


include(GNUInstallDirs)
install(TARGETS smp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(smp)
endif()
