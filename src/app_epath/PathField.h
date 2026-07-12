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
  void setKeepFulls(bool v=true)     {m_keep_fulls=v;} 

  double getSrcX() const  {return(m_sx);}
  double getSrcY() const  {return(m_sy);}
  double getSrcH() const  {return(m_sh);}
  double getDestX() const {return(m_dx);}
  double getDestY() const {return(m_dy);}
  
  void addPoly(XYPolygon);
  void clearPolys() {m_polys.clear();}
  void clearSolve();

  void solve(unsigned int);

  void solve2();
  void solve2Aux(XYSegList, int depth=0);


  void clearPartials();
  void clearFulls();
  
  std::vector<XYPolygon> getPolys() const {return(m_polys);}  

  void genleg(double sx, double sy,
	      double dx, double dy,
	      double angrng, double distrng,
	      double& rx, double& ry);

  bool freeSeg(double sx, double sy, double dx, double dy);
  bool freeSegl(XYSegList);

  bool fullSegl(XYSegList);
  
  std::vector<XYSegList> getSeglsDrop() {return(m_segls_drop);}
  std::vector<XYSegList> getSeglsFull() {return(m_segls_full);}
  std::vector<XYSegList> getSeglsPart() {return(m_segls_part);}

  XYSegList getSeglShortest() {return(m_segl_shortest);}
  std::vector<XYSegList> getSeglsDead() {return(m_segls_dead);}

  
protected: // state vars
  double m_sx;
  double m_sy;
  double m_sh;

  double m_dx;
  double m_dy;

  std::vector<XYPolygon> m_polys;

  std::vector<XYSegList> m_segls_drop;
  std::vector<XYSegList> m_segls_full;
  std::vector<XYSegList> m_segls_part;
  
  XYSegList m_segl_shortest;
  double    m_dist_shortest;

  std::vector<XYSegList> m_segls_dead;

protected: // config vars

  unsigned int m_base_branches;
  
  bool m_keep_fulls;
  
};


#endif
