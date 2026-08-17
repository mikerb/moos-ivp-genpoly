#--------------------------------------------------------
# The CMakeLists.txt for:                          pxview
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
#  BNG_IPF_GUI.cpp
#  BNG_IPF_GUI_Widgets.cpp
#  BNG_IPFViewer.cpp
 XModel.cpp
 main.cpp
)

ADD_EXECUTABLE(pxview ${SRC})

TARGET_LINK_LIBRARIES(pxview
  marineview
  ${MOOSGeodesy_LIBRARIES}
  helmivp
  cover
  gen_poly
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
  SET_TARGET_PROPERTIES(pxview PROPERTIES	  
    LINK_FLAGS "-framework OpenGL -framework Cocoa"
    )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-cast-function-type ")
ENDIF (${APPLE})



