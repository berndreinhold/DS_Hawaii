#-------------------------------------------------------------------------------------------
# Set up the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(test2)

#------------------------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
	find_package(Geant4 REQUIRED ui_all vis_all)
else()
	find_package(Geant4 REQUIRED)
endif()

#-------------------------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#-------------------------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
 
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                   # ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#------------------------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries

add_executable(test2App test2App.cc ${sources} ${headers})
target_link_libraries(test2App ${Geant4_LIBRARIES})

#-----------------------------------------------------------------------------------------
# Copy all scripts to the build directory. This is so that we can run the executable
# directly because it relies on these scripts being in the current working directory.

set(TESTAPP_SCRIPTS
  init.mac
  init_vis.mac
  run.mac
  vis.mac
  gui.mac
  icons.mac
  )

foreach(_script ${TESTAPP_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#-----------------------------------------------------------------------------------------
# Add program to the project targets
# (This avoids the need of typing the program name after make)

add_custom_target(test2 DEPENDS test2App)

#----------------------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX

install(TARGETS test2App DESTINATION bin)

