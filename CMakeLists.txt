cmake_minimum_required(VERSION 3.21)
project(webcpp VERSION 0.9.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)

# Generate paths header from the install prefix so theme.cpp knows where
# themes and backgrounds are installed at runtime.
set(WEBCPP_THEMES_DIR      "${CMAKE_INSTALL_FULL_DATADIR}/webcpp/themes/")
set(WEBCPP_BACKGROUNDS_DIR "${CMAKE_INSTALL_FULL_DATADIR}/webcpp/backgrounds/")

configure_file(
    webcpp/webcpp_paths.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/webcpp_paths.h
    @ONLY
)

file(GLOB WEBCPP_LIB_SOURCES "webcpp/*.cpp")
list(FILTER WEBCPP_LIB_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

add_library(webcpp_lib STATIC ${WEBCPP_LIB_SOURCES})
target_include_directories(webcpp_lib PUBLIC webcpp ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(webcpp_lib PRIVATE -O2 -fno-exceptions)

add_executable(webcpp webcpp/main.cpp)
target_link_libraries(webcpp PRIVATE webcpp_lib)
target_compile_options(webcpp PRIVATE -O2 -fno-exceptions)

# ── Install ──────────────────────────────────────────────────────────────────

install(TARGETS webcpp
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Themes → <prefix>/share/webcpp/themes  (both Linux and macOS)
file(GLOB THEME_FILES "webcpp/themes/*.Scs2")
install(FILES ${THEME_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/webcpp/themes
)

# Backgrounds → <prefix>/share/webcpp/backgrounds  (both Linux and macOS)
file(GLOB BACKGROUND_FILES "webcpp/backgrounds/*.bmp")
install(FILES ${BACKGROUND_FILES}
    DESTINATION ${CMAKE_INSTALL_DATADIR}/webcpp/backgrounds
)

# Docs → <prefix>/share/doc/webcpp
install(FILES docs.html
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
)

# ── Tests ─────────────────────────────────────────────────────────────────────

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)
# Prevent GTest from installing alongside this project
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES "tests/test_*.cpp")
add_executable(webcpp_tests ${TEST_SOURCES})
target_include_directories(webcpp_tests PRIVATE webcpp ${CMAKE_CURRENT_BINARY_DIR} tests)
target_link_libraries(webcpp_tests PRIVATE webcpp_lib GTest::gtest_main)
target_compile_options(webcpp_tests PRIVATE -fno-exceptions)

include(GoogleTest)
gtest_discover_tests(webcpp_tests)
