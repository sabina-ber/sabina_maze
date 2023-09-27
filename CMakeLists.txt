cmake_minimum_required(VERSION 3.5)

project(Maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

set(MODEL_SOURCES
    model/maze.cc
    model/mazegenerator.cc
    model/cell.cc
)

set(PROJECT_SOURCES
        main.cc
        view/mainwindow.cc
        view/mainwindow.h
        controller/mazecontroller.cc
        controller/mazecontroller.h
        model/mazemodel.cc
        model/mazemodel.h
        view/mazewidget.cc
        view/mazewidget.h
        model/maze.h
        model/maze.cc
        model/cell.h
        model/cell.cc
        model/mazegenerator.h
        model/mazegenerator.cc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Maze
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Maze SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Maze
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Maze PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

# Google Test Support
enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

#add_executable(Maze_test tests/test.cc)
add_executable(Maze_test tests/test.cc ${MODEL_SOURCES})
target_link_libraries(Maze_test PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(Maze_test)

# Further customization and installation
set_target_properties(Maze PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Maze
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Maze)
endif()

#Добавляем цель 'coverage'
#add_custom_target(coverage
#   COMMAND gcov -r -o . CMakeFiles/SmartCalc_v2_test.dir/tests/test.cc.gcno
#    COMMAND lcov --capture --directory . --output-file coverage.info
#    COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info
#    COMMAND genhtml coverage.info --output-directory out
#)
#add_dependencies(coverage Maze_test)

add_custom_target(coverage
    COMMAND gcov -r -o . CMakeFiles/Maze_test.dir/tests/test.cc.gcno
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' '*/_deps/*' '*/tests/*' '*/Applications/Xcode.app/*' '*/v1/*' --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory out
)
add_dependencies(coverage Maze_test)

