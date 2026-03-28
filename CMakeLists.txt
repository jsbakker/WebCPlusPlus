cmake_minimum_required(VERSION 3.21)
project(webcpp VERSION 0.9.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)

file(GLOB WEBCPP_SOURCES "webcpp/*.cpp")

add_executable(webcpp ${WEBCPP_SOURCES})

target_include_directories(webcpp PRIVATE webcpp)

target_compile_options(webcpp PRIVATE
    -O2
    -fno-exceptions
)

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
