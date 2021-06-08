cmake_minimum_required(VERSION 3.5)

project(repose VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools WebEngineWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools WebEngineWidgets REQUIRED)
find_package(KF5TextEditor REQUIRED)

set(TS_FILES repose_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        src/widgets/mainwindow.h        src/widgets/mainwindow.cpp        src/widgets/mainwindow.ui
        src/widgets/requesttree.h       src/widgets/requesttree.cpp       src/widgets/requesttree.ui
        src/widgets/requesteditor.h     src/widgets/requesteditor.cpp     src/widgets/requesteditor.ui
        src/widgets/requestcontainer.h  src/widgets/requestcontainer.cpp  src/widgets/requestcontainer.ui
        src/widgets/responsecontainer.h src/widgets/responsecontainer.cpp src/widgets/responsecontainer.ui
        src/widgets/paramtable.h        src/widgets/paramtable.cpp        src/widgets/paramtable.ui
        src/models/paramtablemodel.h    src/models/paramtablemodel.cpp
        src/models/paramtablerow.h      src/models/paramtablerow.cpp
        src/models/request.h            src/models/request.cpp
        src/models/response.h           src/models/response.cpp
        src/models/rootstate.h          src/models/rootstate.cpp
        src/services/httpclient.h       src/services/httpclient.cpp
        src/utils/mimemapper.h          src/utils/mimemapper.cpp
        vendor/QtWaitingSpinner/waitingspinnerwidget.h vendor/QtWaitingSpinner/waitingspinnerwidget.cpp
        vendor/hexdump/Hexdump.hpp
        ${TS_FILES}
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(repose
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(repose SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(repose
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(repose PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebEngineWidgets KF5::TextEditor)

set_target_properties(repose PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(repose)
endif()
