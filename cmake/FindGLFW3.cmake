# Find GLFW3 development libraries

find_package(PkgConfig)
pkg_check_modules(GLFW3 REQUIRED IMPORTED_TARGET
    glfw3
)

if (GLFW3_FOUND)
    message(STATUS "GLFW3 libraries found.")
    message(STATUS "GLFW3 include directories: ${GLFW3_INCLUDE_DIRS}")
    message(STATUS "GLFW3 libraries: ${GLFW3_LIBRARIES}")
else()
    message(FATAL_ERROR "GLFW3 libraries not found")
endif()
