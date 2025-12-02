##############################################################################
# FILE:        moos-ivp-genpoly/src/CMakeLists.txt
# DATE:        2025/11/27
# DESCRIPTION: CMakeLists.txt file for the moos-ivp-genpoly source directory
##############################################################################


#============================================================================
# Add the libraries in the current directory to the include path
#============================================================================
FILE(GLOB LOCAL_LIBRARY_DIRS ./lib_*)
INCLUDE_DIRECTORIES(${LOCAL_LIBRARY_DIRS})

#============================================================================
# List the subdirectories to build...
#============================================================================
ADD_SUBDIRECTORY(lib_gen_poly)
ADD_SUBDIRECTORY(app_polyview)

##############################################################################
#                           END of CMakeLists.txt
##############################################################################

