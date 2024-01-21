cmake_minimum_required (VERSION 3.11)
 
# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG        cdf28903a7781f97ba94d30b79c3a4b0c97ccce7
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
 
# ------------------------------------------------------------------------------
# source https://github.com/Soundux/Soundux/blob/master/FindPipeWire.cmake 
# Use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
find_package(PkgConfig QUIET)
pkg_search_module(PKG_Spa QUIET libspa-0.2 libspa-0.1)

set(PipeWire_DEFINITIONS "${PKG_PipeWire_CFLAGS}" "${PKG_Spa_CFLAGS}")
set(PipeWire_VERSION "${PKG_PipeWire_VERSION}")

find_path(PipeWire_INCLUDE_DIRS
    NAMES
        pipewire/pipewire.h
    HINTS
        ${PKG_PipeWire_INCLUDE_DIRS}
        ${PKG_PipeWire_INCLUDE_DIRS}/pipewire-0.3
)

find_path(Spa_INCLUDE_DIRS
    NAMES
        spa/param/props.h
    HINTS
        ${PKG_Spa_INCLUDE_DIRS}
        ${PKG_Spa_INCLUDE_DIRS}/spa-0.2
)

find_library(PipeWire_LIBRARIES
    NAMES
        pipewire-0.3
        pipewire-0.2
    HINTS
        ${PKG_PipeWire_LIBRARY_DIRS}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PipeWire
    FOUND_VAR
        PipeWire_FOUND
    REQUIRED_VARS
        PipeWire_LIBRARIES
        PipeWire_INCLUDE_DIRS
        Spa_INCLUDE_DIRS
    VERSION_VAR
        PipeWire_VERSION
)

if(PipeWire_FOUND AND NOT TARGET PipeWire::PipeWire)
    add_library(PipeWire::PipeWire UNKNOWN IMPORTED)
    set_target_properties(PipeWire::PipeWire PROPERTIES
        IMPORTED_LOCATION "${PipeWire_LIBRARIES}"
        INTERFACE_COMPILE_OPTIONS "${PipeWire_DEFINITIONS}"
        INTERFACE_INCLUDE_DIRECTORIES "${PipeWire_INCLUDE_DIRS};${Spa_INCLUDE_DIRS}"
    )
endif()

mark_as_advanced(PipeWire_LIBRARIES PipeWire_INCLUDE_DIRS)

include(FeatureSummary)
set_package_properties(PipeWire PROPERTIES
    URL "https://www.pipewire.org"
    DESCRIPTION "PipeWire - multimedia processing"
)
# ------------------------------------------------------------------------------
project(music-maker
    LANGUAGES C CXX
    VERSION 1.0.0
)

add_executable(music-maker src/main.cpp)
target_include_directories(music-maker PRIVATE src)
 
target_link_libraries(music-maker
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)

 

