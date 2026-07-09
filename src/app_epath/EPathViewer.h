/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: EPathViewer.h                                        */
/*    DATE: July 9th, 2026                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#ifndef POLY_VIEWER_HEADER
#define POLY_VIEWER_HEADER

#include <string>
#include "MarineViewer.h"
#include "XYSegList.h"
#include "XYGenPolygon.h"
#include "PathField.h"

class EPathViewer : public MarineViewer
{
 public:
  EPathViewer(int x,int y,int w,int h,const char *l=0);
  
  // Virtual defined
  void  draw();
  int   handle(int);
  void  handle_left_mouse(int, int, bool add=true);
  void  handle_right_mouse(int, int);
  bool  setParam(std::string param, std::string value);
  bool  setParam(std::string param, double value);
  void  clear();

  void  handle_mouse_src(int, int);
  void  handle_mouse_dest(int, int);

  
public:
  std::string getBorderSpec();
  std::string getGPolySpec();

  bool getVerbose() const {return(m_verbose);}
  
  void   reApplySnapToCurrent();   

  void   shiftHorzPoints(double);
  void   shiftVertPoints(double);

  void   rotatePoints(int);
  void   growPoints(int);
  void   reversePoints();
  double getSnap() const  {return(m_snap_val);}

  unsigned int getPolyCount() const {return(m_gen_poly.getPolyCount());}
  double       getSolveTime() const {return(m_solve_time);}
  std::string  getSolveMethod() const {return(m_solve_method);}
  bool         getSolveCollap() const {return(m_solve_collap);}
  
  void   updateConvexHull();
  void   updateGenPoly();

private: // Config vars
  bool   m_draw_pts;
  bool   m_draw_segl;
  bool   m_draw_hull;
  bool   m_draw_gpoly;
  double m_snap_val;

  bool        m_solve_collap;
  std::string m_solve_method;
  
private:
  XYSegList m_segl;
  XYPolygon m_hull_poly;

  XYGenPolygon m_gen_poly;

  double m_solve_time;

  PathField m_pfield;
};

#endif 
