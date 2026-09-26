cmake_minimum_required(VERSION 3.19)
project(PuzzleGame LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# Qt 6 只默认开启 AUTOMOC / AUTOUIC，不会自动处理 .qrc；
# 必须显式开启 AUTORCC，resources.qrc 里的图片才会被编译进可执行文件。
set(CMAKE_AUTORCC ON)

qt_add_executable(PuzzleGame
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc
)

target_link_libraries(PuzzleGame
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS PuzzleGame
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET PuzzleGame
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
