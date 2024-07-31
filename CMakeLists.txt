cmake_minimum_required(VERSION 3.19)

project(openglwindow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect if we're building with Emscripten
if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    message(STATUS "Build for Emscripten" )
    set(EMSCRIPTEN TRUE)
endif()

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGL)

# Set up the standard project
qt_standard_project_setup()

# Add the executable
qt_add_executable(openglwindow
    main.cpp
    openglwindow.cpp openglwindow.h
)

# Set target properties for desktop builds
if(NOT EMSCRIPTEN)
    set_target_properties(openglwindow PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
    )
endif()

# Link Qt libraries
target_link_libraries(openglwindow PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGL
)

# Add Emscripten-specific configurations
if(EMSCRIPTEN)
    # Specify the minimum WebAssembly memory
    # set_target_properties(openglwindow PROPERTIES
    #     QT_WASM_INITIAL_MEMORY "150MB"
    # )

    # # Link options for WebGL and asyncify
    # target_link_options(openglwindow PRIVATE
    #     -s FULL_ES2=1
    #     -s ASYNCIFY
    # )
    target_link_options(openglwindow PRIVATE -s FULL_ES2=1)

endif()

# # Installation instructions
# install(TARGETS openglwindow
#     BUNDLE  DESTINATION .
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )

# # Generate deployment script for non-Emscripten builds
# if(NOT EMSCRIPTEN)
#     qt_generate_deploy_app_script(
#         TARGET openglwindow
#         OUTPUT_SCRIPT deploy_script
#         NO_UNSUPPORTED_PLATFORM_ERROR
#     )
#     install(SCRIPT ${deploy_script})
# endif()
