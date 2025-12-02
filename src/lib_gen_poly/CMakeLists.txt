#--------------------------------------------------------
# The CMakeLists.txt for:                     lib_genpoly
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

SET(SRC
  CoverEngine.cpp
  XYGenPolygon.cpp
)

SET(HEADERS
  XYCoverPolyUtils.h
  XYGenPolygon.h
)

# Build Library
ADD_LIBRARY(genpoly ${SRC})

TARGET_LINK_LIBRARIES(genpoly
   mbutil
)

