#--------------------------------------------------------
# The CMakeLists.txt for:                       lib_cover
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

SET(SRC
  CoverEngine.cpp
)

SET(HEADERS
  CoverEngine.h
)

# Build Library
ADD_LIBRARY(cover ${SRC})

TARGET_LINK_LIBRARIES(cover
   mbutil
)

