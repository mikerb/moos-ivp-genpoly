#--------------------------------------------------------
# The CMakeLists.txt for:                         polygen
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

SET(SYSTEM_LIBS m)

SET(SRC
  main.cpp
)

ADD_EXECUTABLE(polygen ${SRC})

TARGET_LINK_LIBRARIES(polygen
  cover
  mbutil
  geometry
  ${SYSTEM_LIBS}
  )


