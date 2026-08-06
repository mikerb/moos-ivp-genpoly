#--------------------------------------------------------
# The CMakeLists.txt for:                       lib_cover
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

SET(SRC
  CoverEngine.cpp
//  XYGenPolygon.cpp
)

SET(HEADERS
  CoverEngine.h
//  XYGenPolygon.h
)

# Build Library
ADD_LIBRARY(cover ${SRC})

TARGET_LINK_LIBRARIES(cover
   mbutil
)

