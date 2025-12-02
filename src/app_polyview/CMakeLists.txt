#--------------------------------------------------------
# The CMakeLists.txt for:                        polyview
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

SET(SYSTEM_LIBS m)


if(CMAKE_SYSTEM_NAME STREQUAL Linux)
  SET(SYSTEM_LIBS ${SYSTEM_LIBS} GL)
endif(CMAKE_SYSTEM_NAME STREQUAL Linux)

SET(SRC
  POLY_GUI.cpp
  POLY_GUI_Widgets.cpp
  PolyViewer.cpp
  main.cpp
)

ADD_EXECUTABLE(polyview ${SRC})

TARGET_LINK_LIBRARIES(polyview
  marineview
  ${MOOSGeodesy_LIBRARIES}
  genpoly
  contacts
  mbutil
  geometry
  ${SYSTEM_LIBS}
  
  # Standard libraries used by this project's FLTK apps...
  fltk 
  fltk_gl 
  dl
  tiff)

# http://developer.apple.com/qa/qa2007/qa1567.html
IF (${APPLE})
  SET_TARGET_PROPERTIES(polyview PROPERTIES	  
    LINK_FLAGS "-framework OpenGL -framework Cocoa"
    )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-function-type ")
ENDIF (${APPLE})



