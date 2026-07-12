/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: EPATH_GUI.h                                          */
/*    DATE: July 9th, 2026                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#ifndef EPATH_GUI_HEADER
#define EPATH_GUI_HEADER

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include "EPathViewer.h"
#include "MarineGUI.h"

class EPATH_GUI : public MarineGUI {
public:
  EPATH_GUI(int w, int h, const char *l=0);
  ~EPATH_GUI() {}
  
  void updateXY();
  int  handle(int);

protected:
  void initWidgets();
  void resizeWidgetsShape();
  void resizeWidgetsText();

public: 
  EPathViewer *pviewer;

protected:
  Fl_Button  *m_but_draw_deads;
  Fl_Button  *m_but_solve10;
  Fl_Button  *m_but_clear_polys;
  Fl_Button  *m_but_clear_solve;

  Fl_Output  *m_fld_snap;
  Fl_Output  *m_fld_polys;
  Fl_Output  *m_fld_solve;

  Fl_Output  *m_fld_segl_shortest;
  Fl_Output  *m_fld_segl_star;

  int m_start_hgt;
  int m_start_wid;
  
 protected:
  void augmentMenu();
 
private:
  inline void cb_DrawDeads_i();
  static void cb_DrawDeads(Fl_Widget*);

  inline void cb_Solve_i(int);
  static void cb_Solve(Fl_Widget*, int);

  inline void cb_ClearPolys_i();
  static void cb_ClearPolys(Fl_Widget*);

  inline void cb_ClearSolve_i();
  static void cb_ClearSolve(Fl_Widget*);

  inline void cb_ShiftX_i(int);
  static void cb_ShiftX(Fl_Widget*, int);

  inline void cb_ShiftY_i(int);
  static void cb_ShiftY(Fl_Widget*, int);

  inline void cb_Grow_i(int);
  static void cb_Grow(Fl_Widget*, int);

  inline void cb_DumpPolySpec_i();
  static void cb_DumpPolySpec(Fl_Widget*);

  inline void cb_StartPoints_i(int);
  static void cb_StartPoints(Fl_Widget*, int);

};
#endif
