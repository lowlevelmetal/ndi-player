# Find glew

find_package(PkgConfig)
pkg_check_modules(GLEW REQUIRED IMPORTED_TARGET
    glew
)

if (GLEW_FOUND)
    message(STATUS "GLEW libraries found.")
    message(STATUS "GLEW include directories: ${GLEW_INCLUDE_DIRS}")
    message(STATUS "GLEW libraries: ${GLEW_LIBRARIES}")
else()
    message(FATAL_ERROR "GLEW libraries not found")
endif()
