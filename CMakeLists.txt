cmake_minimum_required(VERSION 3.16)

project(AutoSetting VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES AutoSetting_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AutoSetting
        WIN32 icon.rc

        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        MainResource.qrc
        mainwindow_MenuBT.cpp
        fadeqstackedwidget.h fadeqstackedwidget.cpp



        mainwindow_update.cpp
        qmessagewidget.h qmessagewidget.cpp
        qpopmessage.h qpopmessage.cpp
        qkeepbutton.h qkeepbutton.cpp
        quniquebuttongroup.h quniquebuttongroup.cpp
        qqsschanger.h qqsschanger.cpp
        mainwindow_Frameless.cpp
        qstylewidget.h qstylewidget.cpp
        mainwindow_Drag.cpp
        mainwindow_customnade.cpp

        # qwindowkit/




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AutoSetting APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(AutoSetting SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AutoSetting
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(AutoSetting PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AutoSetting)
endif()
set_target_properties(AutoSetting PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

set(QWINDOWKIT_BUILD_EXAMPLES OFF CACHE BOOL "")
set(QWINDOWKIT_BUILD_STATIC ON CACHE BOOL "")

find_package(Qt6 COMPONENTS Network REQUIRED)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Svg)
find_package(Qt6 REQUIRED COMPONENTS Svg)
target_link_libraries(AutoSetting PUBLIC Qt6::Network)
target_link_libraries(AutoSetting PUBLIC Qt6::Svg)


include_directories("D:\\CFGAutoSettingsFramework\\AutoSettings")
set(CMAKE_EXE_LINKER_FLAGS "-static")

install(TARGETS AutoSetting
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AutoSetting)
endif()
