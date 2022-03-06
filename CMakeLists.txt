cmake_minimum_required(VERSION 3.14)

project(
    sgc
    VERSION 0.0.1
    DESCRIPTION "Static split parser"
    HOMEPAGE_URL "https://github.com/red0124/sgc"
    LANGUAGES C
)

# ---- Warning guard ----

# Protect dependents from this project's warnings if the guard isn't disabled
set(sgc_warning_guard SYSTEM)
if(sgc_INCLUDE_WITHOUT_SYSTEM)
  set(sgc_warning_guard "")
endif()

# ---- Declare library ----

add_library(sgc INTERFACE)
add_library(sgc::sgc ALIAS sgc)

target_include_directories(
    sgc
    ${sgc_warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(sgc INTERFACE)

target_link_libraries(
    sgc
    INTERFACE
)

# ---- Install ----

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(sgc_directory "sgc-${PROJECT_VERSION}")
set(sgc_include_directory "${CMAKE_INSTALL_INCLUDEDIR}")

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION "${sgc_include_directory}"
    COMPONENT sgc_Development
)

install(
    TARGETS sgc
    EXPORT sgcTargets
    INCLUDES DESTINATION "${sgc_include_directory}"
)

write_basic_package_version_file(
    sgc-config-version.cmake
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

set(sgc_install_cmakedir "${CMAKE_INSTALL_LIBDIR}/cmake/${sgc_directory}")

install(
    FILES "${PROJECT_BINARY_DIR}/sgc-config-version.cmake"
    DESTINATION "${sgc_install_cmakedir}"
    COMPONENT sgc_Development
)

install(
    EXPORT sgcTargets
    FILE sgc-config.cmake
    NAMESPACE sgc::
    DESTINATION "${sgc_install_cmakedir}"
    COMPONENT sgc_Development
)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  include(CPack)
endif()
