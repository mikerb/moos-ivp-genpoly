/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: XYGenPolygon.h                                       */
/*    DATE: Oct 16th, 2020                                       */
/*    DATE: Nov 27th, 2025                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/
 
#ifndef XY_GEN_POLYGON_HEADER
#define XY_GEN_POLYGON_HEADER

#include <vector>
#include "XYSegList.h"
#include "XYPolygon.h"

class XYGenPolygon {
 public:
  XYGenPolygon() {}
  ~XYGenPolygon() {}

  void   setGenPoly(XYSegList);
  void   setGenPoly(XYSegList, std::vector<XYPolygon> polys);
  
  bool   contains(double px, double py) const;
  double dist_to_poly(double px, double py) const;
  double dist_to_poly(double x1, double y1, double x2, double y2) const;
  bool   line_intersects(double x1, double y1, double x2, double y2) const;

  void   shift_vert(double amt);
  void   shift_horz(double amt);
  double area() const;
  void   clear();
  void   clearCoverPolys();

  unsigned int sizeSegl() const  {return(m_segl.size());}
  unsigned int sizeCover() const {return(m_cover_polys.size());}
  
  std::vector<XYPolygon> getCoverPolys() const {return(m_cover_polys);}
  XYSegList getSegList() const {return(m_segl);}
  
  std::string get_spec() const;
  std::string get_spec_bdr() const;

  unsigned int getBorderPtsSize() const  {return(m_segl.size());}
  unsigned int getCoverPolyCount() const {return(m_cover_polys.size());}

  unsigned int getSeglSize() const  {return(m_segl.size());}
  unsigned int getPolyCount() const {return(m_cover_polys.size());}
  
protected:
  XYSegList m_segl;  // border

  std::vector<XYPolygon> m_cover_polys;
};

XYGenPolygon stringToGenPoly(std::string);

#endif
