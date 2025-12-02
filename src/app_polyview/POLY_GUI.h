/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: POLY_GUI.h                                           */
/*    DATE: Nov 22nd, 2025                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#ifndef POLY_GUI_HEADER
#define POLY_GUI_HEADER

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>
#include "PolyViewer.h"
#include "MarineGUI.h"

class POLY_GUI : public MarineGUI {
public:
  POLY_GUI(int w, int h, const char *l=0);
  ~POLY_GUI() {}
  
  void updateXY();
  int  handle(int);

protected:
  void initWidgets();
  void resizeWidgetsShape();
  void resizeWidgetsText();

public: 
  PolyViewer *pviewer;

protected:
  Fl_Button  *m_but_draw_pts;
  Fl_Button  *m_but_draw_segl;
  Fl_Button  *m_but_draw_hull;
  Fl_Button  *m_but_draw_gpoly;

  Fl_Button  *m_but_resolve;
  Fl_Button  *m_but_method;
  Fl_Button  *m_but_collapse;
  Fl_Button  *m_but_clear;
  Fl_Button  *m_but_verbose;

  Fl_Output  *m_fld_snap;
  Fl_Output  *m_fld_polys;
  Fl_Output  *m_fld_solve;

  Fl_Output  *m_fld_method;
  Fl_Output  *m_fld_collap;
  Fl_Output  *m_fld_verbose;

  Fl_Output  *m_fld_segl;
  Fl_Output  *m_fld_gpoly;

  int m_start_hgt;
  int m_start_wid;
  
 protected:
  void augmentMenu();
 
private:
  inline void cb_DrawPts_i();
  static void cb_DrawPts(Fl_Widget*);

  inline void cb_DrawSegl_i();
  static void cb_DrawSegl(Fl_Widget*);

  inline void cb_DrawHull_i();
  static void cb_DrawHull(Fl_Widget*);

  inline void cb_DrawGPoly_i();
  static void cb_DrawGPoly(Fl_Widget*);

  inline void cb_Resolve_i();
  static void cb_Resolve(Fl_Widget*);

  inline void cb_MethodToggle_i();
  static void cb_MethodToggle(Fl_Widget*);

  inline void cb_CollapseToggle_i();
  static void cb_CollapseToggle(Fl_Widget*);

  inline void cb_Clear_i();
  static void cb_Clear(Fl_Widget*);

  inline void cb_VerboseToggle_i();
  static void cb_VerboseToggle(Fl_Widget*);


  inline void cb_Rotate_i(int);
  static void cb_Rotate(Fl_Widget*, int);

  inline void cb_ShiftX_i(int);
  static void cb_ShiftX(Fl_Widget*, int);

  inline void cb_ShiftY_i(int);
  static void cb_ShiftY(Fl_Widget*, int);

  inline void cb_Grow_i(int);
  static void cb_Grow(Fl_Widget*, int);

  inline void cb_Reverse_i();
  static void cb_Reverse(Fl_Widget*);

  inline void cb_SnapVal_i(int);
  static void cb_SnapVal(Fl_Widget*, int);

  inline void cb_SetColor_i(int);
  static void cb_SetColor(Fl_Widget*, int);

  inline void cb_ReApplySnapVal_i();
  static void cb_ReApplySnapVal(Fl_Widget*);

  inline void cb_DumpPolySpec_i();
  static void cb_DumpPolySpec(Fl_Widget*);


  inline void cb_StartPoints_i(int);
  static void cb_StartPoints(Fl_Widget*, int);

};
#endif
