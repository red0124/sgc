cmake_minimum_required(VERSION 3.14)

project(
    sgc
    VERSION 1.0.0
    DESCRIPTION "generic algorithms and data structures"
    HOMEPAGE_URL "https://github.com/red0124/sgc"
    LANGUAGES C
)

# ---- Warning guard ----

# Protect dependents from this project's warnings if the guard isn't disabled
set(SGC_WARNING_GUARD SYSTEM)
if(sgc_INCLUDE_WITHOUT_SYSTEM)
    set(SGC_WARNING_GUARD "")
endif()

# ---- Declare library ----

add_library(sgc INTERFACE)
add_library(sgc::sgc ALIAS sgc)

target_include_directories(
    sgc
    ${SGC_WARNING_GUARD}
    INTERFACE "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(sgc INTERFACE)

target_link_libraries(sgc INTERFACE)

# ---- Install ----

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(SGC_DIRECTORY "sgc-${PROJECT_VERSION}")
set(SGC_INCLUDE_DIRECTORY "${CMAKE_INSTALL_INCLUDEDIR}")

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION "${SGC_INCLUDE_DIRECTORY}"
    COMPONENT sgc_Development
)

install(
    TARGETS sgc
    EXPORT sgcTargets
    INCLUDES DESTINATION "${SGC_INCLUDE_DIRECTORY}"
)

write_basic_package_version_file(
    sgc-config-version.cmake
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

set(SGC_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${SGC_DIRECTORY}")

install(
    FILES "${PROJECT_BINARY_DIR}/sgc-config-version.cmake"
    DESTINATION "${SGC_INSTALL_CMAKEDIR}"
    COMPONENT sgc_Development
)

install(
    EXPORT sgcTargets
    FILE sgc-config.cmake
    NAMESPACE sgc::
    DESTINATION "${SGC_INSTALL_CMAKEDIR}"
    COMPONENT sgc_Development
)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    include(CPack)
endif()
