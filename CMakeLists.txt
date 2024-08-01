cmake_minimum_required(VERSION 3.19)

project(openglwindow LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-no-pie -fwasm-exceptions -msimd128 -pthread -sFULL_ES3 -sUSE_SDL=2  -sASSERTIONS --bind -sEXPORTED_FUNCTIONS=_main -sEXPORTED_RUNTIME_METHODS=ccall,cwrap,UTF16ToString,stringToUTF16,JSEvents,specialHTMLTargets,FS -sMAX_WEBGL_VERSION=2 -sFETCH=1 -sWASM_BIGINT=1 -sSTACK_SIZE=5MB -sMODULARIZE=1 -sPTHREAD_POOL_SIZE=100 -sEXPORT_NAME=createQtAppInstance -sALLOW_MEMORY_GROWTH -fnon-call-exceptions -fno-strict-aliasing  -fexceptions")

# Detect if we're building with Emscripten
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    message(STATUS "Building for Emscripten")
    set(EMSCRIPTEN TRUE)

    # Copy files from html folder to the build directory
    file(COPY ${CMAKE_SOURCE_DIR}/html/index.html DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CMAKE_SOURCE_DIR}/html/qtloader.js DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${CMAKE_SOURCE_DIR}/html/qtlogo.svg DESTINATION ${CMAKE_BINARY_DIR})

    # Ensure the data directory exists
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

    else()
    message(STATUS "Building for native platform")
endif()

# Add compile definitions
add_compile_definitions(
    QT_CORE_LIB
    QT_GUI_LIB
    QT_WIDGETS_LIB
    QT_NO_DEBUG
    QT_NO_KEYWORDS
)

add_library(Qt6.6 INTERFACE)

# Import Qt executables
add_executable(Qt6::moc IMPORTED)
add_executable(Qt6::rcc IMPORTED)

set_target_properties(Qt6::moc PROPERTIES IMPORTED_LOCATION "D:/sd3d/engine/3rdparty/Qt/6.6/msvc2022_64/Debug/bin/moc.exe")
set_target_properties(Qt6::rcc PROPERTIES IMPORTED_LOCATION "D:/sd3d/engine/3rdparty/Qt/6.6/msvc2022_64/Debug/bin/rcc.exe")


set(Qt6Core_VERSION_MAJOR 6)
set(Qt6Core_VERSION_MINOR 6)

# Link Qt libraries
target_link_libraries(Qt6.6 INTERFACE
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/plugins/platforms/libqwasm.a
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/lib/libQt6OpenGLWidgets.a
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/lib/libQt6OpenGL.a
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/lib/libQt6Widgets.a
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/lib/libQt6Gui.a
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/lib/libQt6Core.a
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/lib/libQt6BundledPcre2.a
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/lib/libQt6BundledFreetype.a
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/lib/libQt6BundledLibpng.a
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/lib/libQt6BundledZLIB.a
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/lib/libQt6BundledHarfbuzz.a
)

# Add the executable
add_executable(openglwindow
    main.cpp
    openglwindow.cpp
    openglwindow.h
)

# Set target properties for desktop builds
if(NOT EMSCRIPTEN)
    set_target_properties(openglwindow PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
    )
endif()

# Link the libraries and set include directories
target_link_libraries(openglwindow PUBLIC
    Qt6.6
)

target_include_directories(openglwindow PRIVATE
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/include
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/include/QtCore
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/include/QtGui
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/include/QtWidgets
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/include/QtOpenGLWidgets
    D:/sd3d/engine/3rdparty/Qt/6.6/wasm_64/Debug/include/QtOpenGL
)

# Add Emscripten-specific configurations
if(EMSCRIPTEN)
    target_link_options(openglwindow PRIVATE -s FULL_ES2=1)
endif()

set_target_properties(openglwindow PROPERTIES AUTOMOC ON)
set_target_properties(openglwindow PROPERTIES AUTORCC ON)
set_property(TARGET openglwindow PROPERTY AUTORCC_OPTIONS "--no-zstd")
