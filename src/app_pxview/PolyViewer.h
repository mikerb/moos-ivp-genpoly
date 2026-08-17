/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: PolyViewer.h                                         */
/*    DATE: Nov 22nd, 2025                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#ifndef POLY_VIEWER_HEADER
#define POLY_VIEWER_HEADER

#include <string>
#include "MarineViewer.h"
#include "XModel.h"
#include "XYSegList.h"
#include "XYGenPolygon.h"

class PolyViewer : public MarineViewer
{
 public:
  PolyViewer(int x,int y,int w,int h,const char *l=0);
  
  // Virtual defined
  void  draw();
  int   handle(int);
  void  handle_left_mouse(int, int, bool add=true);
  void  handle_left_ownship(int, int);
  void  handle_right_mouse(int, int);
  bool  setParam(std::string param, std::string value);
  bool  setParam(std::string param, double value);
  void  clear();
  
public:
  std::string getBorderSpec();
  std::string getGPolySpec();

  void   setXModel(XModel* xmo) {m_xmodel=xmo;}

  
  bool   getVerbose() const {return(m_verbose);}
  
  void   reApplySnapToCurrent();   

  void   shiftHorzPoints(double);
  void   shiftVertPoints(double);

  void   rotatePoints(int);
  void   growPoints(int);
  void   reversePoints();
  double getSnap() const  {return(m_snap_val);}

  unsigned int getPolyCount() const;
  double       getSolveTime() const   {return(m_solve_time);}
  std::string  getSolveMethod() const {return(m_solve_method);}
  bool         getSolveCollap() const {return(m_solve_collap);}

  double getSeglrDistToExit() const   {return(m_seglr_dist_to_exit);}
  double getOSHDistToExit() const     {return(m_osh_dist_to_exit);}
  double getSegDistToExit() const     {return(m_seg_dist_to_exit);}
  double getRayDistToExit() const     {return(m_ray_dist_to_exit);}
  
  XYPolygon getConvexHull();
  void      updateGenPoly();
  void      updateSeglr();
  
private: // Config vars
  bool   m_draw_pts;
  bool   m_draw_segl;
  bool   m_draw_hull;
  bool   m_draw_gpoly;
  double m_snap_val;

  bool        m_solve_collap;
  std::string m_solve_method;
  
private:
  XModel*  m_xmodel;
  XYSegList m_segl;

  double  m_seglr_dist_to_exit;
  double  m_osh_dist_to_exit;
  double  m_seg_dist_to_exit;
  double  m_ray_dist_to_exit;
  double  m_solve_time;
};

#endif 
