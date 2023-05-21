cmake_minimum_required(VERSION 3.5)

project(1st_with_ffmpeg VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_LIBS
  Core
  Gui
  OpenGL
  OpenGLWidgets
  Widgets
)

#find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS ${QT_LIBS})
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${QT_LIBS})

set(PROJECT_SOURCES
  mylog.h
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  avframes_manager.h avframes_manager.cpp
  decoder_thread.h decoder_thread.cpp
  glwidget.h glwidget.cpp
  images_panel.h images_panel.cpp
  resource.qrc
)

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(1st_with_ffmpeg
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 1st_with_ffmpeg APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
#else()
#    if(ANDROID)
#        add_library(1st_with_ffmpeg SHARED
#            ${PROJECT_SOURCES}
#        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    else()
#        add_executable(1st_with_ffmpeg
#            ${PROJECT_SOURCES}
#        )
#    endif()
#endif()

set_target_properties(1st_with_ffmpeg PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

#设置ffmpeg头文件和库路径
set(FFMPEG_PREFIX_PATH D:/softwares/coding/ffmpeg-5.1.2-full_build-shared)
include_directories( ${FFMPEG_PREFIX_PATH}/include )
#find_library(AVUTIL_LIBRARY avutil)

FIND_LIBRARY(AVFILTER_LIBRARY avfilter  ${FFMPEG_PREFIX_PATH}/lib)
FIND_LIBRARY(AVFORMAT_LIBRARY avformat  ${FFMPEG_PREFIX_PATH}/lib)
FIND_LIBRARY(AVCODEC_LIBRARY avcodec ${FFMPEG_PREFIX_PATH}/lib)
FIND_LIBRARY(AVUTIL_LIBRARY avutil  ${FFMPEG_PREFIX_PATH}/lib)
FIND_LIBRARY(AVDEVICE_LIBRARY avdevice  ${FFMPEG_PREFIX_PATH}/lib)
FIND_LIBRARY(POSTPROC_LIBRARY postproc  ${FFMPEG_PREFIX_PATH}/lib)
FIND_LIBRARY(SWRESAMPLE_LIBRARY swresample  ${FFMPEG_PREFIX_PATH}/lib)
FIND_LIBRARY(SWSCALE_LIBRARY swscale  ${FFMPEG_PREFIX_PATH}/lib)

message(STATUS "AVCODEC_LIBRARY:"  ${AVCODEC_LIBRARY})
list(APPEND FFMPEG_LIBS
  ${AVFILTER_LIBRARY} ${AVFORMAT_LIBRARY} ${AVCODEC_LIBRARY}
  ${AVUTIL_LIBRARY} ${AVDEVICE_LIBRARY} ${POSTPROC_LIBRARY}
  ${SWRESAMPLE_LIBRARY} ${SWSCALE_LIBRARY}
)
set(LINK_QT_LIBS "")
foreach(lib ${QT_LIBS})
  list(APPEND LINK_QT_LIBS "Qt${QT_VERSION_MAJOR}::${lib}")
endforeach()
message(STATUS ${LINK_QT_LIBS})
#Qt${QT_VERSION_MAJOR}::Widgets
target_link_libraries(1st_with_ffmpeg PUBLIC ${LINK_QT_LIBS} ${FFMPEG_LIBS})

#target_link_libraries(1st_with_ffmpeg )

set_target_properties(1st_with_ffmpeg PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS 1st_with_ffmpeg
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(1st_with_ffmpeg)
endif()
