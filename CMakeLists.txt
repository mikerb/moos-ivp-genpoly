#===========================================================================
# FILE:  moos-ivp-swarm/CMakeLists.txt
# DATE:  2019/11/24
# INFO:  Top-level CMakeLists.txt file for the moos-ivp-swarm project
# NAME:  Maintained by Mike Benjamin - Original setup by Christian Convey
#        Chris Gagner, and tips borrowed from Dave Billin
#===========================================================================

CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT( IVP_EXTEND )

#=============================================================================
# Set the output directories for the binary and library files
#=============================================================================

GET_FILENAME_COMPONENT(IVP_SWARM_BIN_DIR "${CMAKE_SOURCE_DIR}/bin"  ABSOLUTE )
GET_FILENAME_COMPONENT(IVP_SWARM_LIB_DIR "${CMAKE_SOURCE_DIR}/lib"  ABSOLUTE )

SET( LIBRARY_OUTPUT_PATH      "${IVP_SWARM_LIB_DIR}" CACHE PATH "" )
SET( ARCHIVE_OUTPUT_DIRECTORY "${IVP_SWARM_LIB_DIR}" CACHE PATH "" )
SET( LIBRARY_OUTPUT_DIRECTORY "${IVP_SWARM_LIB_DIR}" CACHE PATH "" )

SET( EXECUTABLE_OUTPUT_PATH    "${IVP_SWARM_BIN_DIR}" CACHE PATH "" )
SET( RUNTIME_OUTPUT_DIRECTORY "${IVP_SWARM_BIN_DIR}"  CACHE PATH "" )

#=============================================================================
# Find MOOS
#=============================================================================
find_package(MOOS 10.0)
INCLUDE_DIRECTORIES(${MOOS_INCLUDE_DIRS})

message("+++++++++++++++++++++++++++++++++++++++++")
message("MOOS_INCLUDE_DIRS:" ${MOOS_INCLUDE_DIRS})
message("+++++++++++++++++++++++++++++++++++++++++")

#=============================================================================
# FINDING MOOSGeodesy' HEADERS AND LIBRARIES...  
#=============================================================================
find_package(MOOSGeodesy) 
include_directories(${MOOSGeodesy_INCLUDE_DIRS}) 
link_directories(${MOOSGeodesy_LIBRARY_PATH})       

message("+++++++++++++++++++++++++++++++++++++++++")
message("MOOSGeodesy_INCLUDE_DIRS:" ${MOOSGeodesy_INCLUDE_DIRS})
message("MOOSGeodesy_LIBRARY_PATH:" ${MOOSGeodesy_LIBRARY_PATH}) 
message("+++++++++++++++++++++++++++++++++++++++++")                

#=============================================================================
# Find the "moos-ivp" base directory
#=============================================================================
# Search for the moos-ivp folder
find_path( MOOSIVP_SOURCE_TREE_BASE
           NAMES build-ivp.sh build-moos.sh configure-ivp.sh
           PATHS "../moos-ivp" "../../moos-ivp"
           DOC "Base directory of the MOOS-IvP source tree"
           NO_DEFAULT_PATH
)

if (NOT MOOSIVP_SOURCE_TREE_BASE)
    message("Please set MOOSIVP_SOURCE_TREE_BASE to  ")
    message("the location of the \"moos-ivp\" folder ")
    return()
endif()

#=============================================================================
# Specify where to find IvP's headers and libraries...
#=============================================================================

FILE(GLOB IVP_INCLUDE_DIRS ${MOOSIVP_SOURCE_TREE_BASE}/ivp/src/lib_* )
INCLUDE_DIRECTORIES(${IVP_INCLUDE_DIRS})

FILE(GLOB IVP_LIBRARY_DIRS ${MOOSIVP_SOURCE_TREE_BASE}/lib )
LINK_DIRECTORIES(${IVP_LIBRARY_DIRS})



#=============================================================================
# Find the "moos-ivp-pavlab" base directory
#=============================================================================
# Search for the moos-ivp-pavlab folder
find_path( MOOSIVP_PAVLAB_SOURCE_TREE_BASE
           NAMES build.sh
           PATHS "../moos-ivp-pavlab" "../../moos-ivp-pavlab" 
           DOC "Base directory of the moos-ivp-pavlab source tree"
           NO_DEFAULT_PATH
)

if (NOT MOOSIVP_SOURCE_TREE_BASE)
    message("Please set MOOSIVP_PAVLAB_SOURCE_TREE_BASE to  ")
    message("the location of the \"moos-ivp-pavlab\" folder ")
    return()
endif()

# Specify where to find moos-ivp-pavlab headers and libraries...

FILE(GLOB PAVLAB_INCLUDE_DIRS ${MOOSIVP_PAVLAB_SOURCE_TREE_BASE}/src*/lib_* )
INCLUDE_DIRECTORIES(${PAVLAB_INCLUDE_DIRS})

FILE(GLOB PAVLAB_LIBRARY_DIRS ${MOOSIVP_PAVLAB_SOURCE_TREE_BASE}/lib )
LINK_DIRECTORIES(${PAVLAB_LIBRARY_DIRS})



#=============================================================================
# Find the "moos-ivp-swarm" base directory
#=============================================================================
# Search for the moos-ivp-swarm folder
find_path( MOOSIVP_SWARM_SOURCE_TREE_BASE
           NAMES build.sh
           PATHS "../moos-ivp-swarm" "../../moos-ivp-swarm" 
           DOC "Base directory of the moos-ivp-swarm source tree"
           NO_DEFAULT_PATH
)

if (NOT MOOSIVP_SWARM_SOURCE_TREE_BASE)
    message("Please set MOOSIVP_SWARM_SOURCE_TREE_BASE to  ")
    message("the location of the \"moos-ivp-swarm\" folder ")
    return()
endif()

# Specify where to find moos-ivp-swarm headers and libraries...

FILE(GLOB SWARM_INCLUDE_DIRS ${MOOSIVP_SWARM_SOURCE_TREE_BASE}/src*/lib_* )
INCLUDE_DIRECTORIES(${SWARM_INCLUDE_DIRS})

FILE(GLOB SWARM_LIBRARY_DIRS ${MOOSIVP_SWARM_SOURCE_TREE_BASE}/lib )
LINK_DIRECTORIES(${SWARM_LIBRARY_DIRS})




#=============================================================================
# Specify Compiler Flags
#=============================================================================
IF (${WIN32})
  # Define Windows Compiler flags here
  SET(CMAKE_CXX_FLAGS " ")
ELSE (${WIN32})
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g -Wno-psabi ")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g -Wno-cast-function-type ")
ENDIF ()


#=============================================================================
# Tell CMake (and thus C++) where to find IvP's header files...
#=============================================================================

IF( EXISTS /usr/local/include AND EXISTS /usr/local/lib )
  INCLUDE_DIRECTORIES(/usr/local/include)
  LINK_DIRECTORIES(/usr/local/lib)
ENDIF()

IF( EXISTS /opt/local/include AND EXISTS /opt/local/lib )
  INCLUDE_DIRECTORIES(/opt/local/include)
  LINK_DIRECTORIES(/opt/local/lib)
ENDIF()

IF( EXISTS /opt/homebrew/include AND EXISTS /opt/homebrew/lib )
  INCLUDE_DIRECTORIES(/opt/homebrew/include)
  LINK_DIRECTORIES(/opt/homebrew/lib)
ENDIF()

#=============================================================================
# Add Subdirectories
#=============================================================================
ADD_SUBDIRECTORY( src )

IF( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src_towbody)
  ADD_SUBDIRECTORY( src_towbody )
ENDIF()

