/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: PathField.h                                          */
/*    DATE: July 9th, 2026                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/
 
#ifndef PATH_FIELD_HEADER
#define PATH_FIELD_HEADER

#include <vector>
#include "XYSegList.h"
#include "XYPolygon.h"

class PathField {
 public:
  PathField(); 
  ~PathField() {}

  void setSource(double x, double y) {m_sx=x; m_sy=y;}
  void setSrcHdg(double hdg)         {m_sh=hdg;}
  void setDest(double x, double y)   {m_dx=x; m_dy=y;}

  void addPoly(XYPolygon);

  double getSrcX() const  {return(m_sx);}
  double getSrcY() const  {return(m_sy);}
  double getSrcH() const  {return(m_sh);}
  double getDestX() const {return(m_dx);}
  double getDestY() const {return(m_dy);}

  std::vector<XYPolygon> getPolys() const {return(m_polys);}  

protected: // state vars
  double m_sx;
  double m_sy;
  double m_sh;

  double m_dx;
  double m_dy;

  std::vector<XYPolygon> m_polys;

  XYSegList m_segl_path;
};


#endif
