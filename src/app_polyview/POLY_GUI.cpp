/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: POLY_GUI.cpp                                          */
/*    DATE: Nov 22nd, 2025                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include <cstdio>
#include "POLY_GUI.h"
#include "MBUtils.h"

using namespace std;

//-------------------------------------------------------------------
// Constructor()

POLY_GUI::POLY_GUI(int wid, int hgt, const char *label)
  : MarineGUI(wid, hgt, label) {

  this->user_data((void*)(this));
  this->when(FL_WHEN_CHANGED);
  this->begin();

  m_start_hgt = hgt;
  m_start_wid = wid;
  
  pviewer   = new PolyViewer(0, 30, wid, hgt-160);
  m_mviewer = pviewer;

  augmentMenu();
  
  initWidgets();
  resizeWidgetsShape();
  resizeWidgetsText();

  this->end();
  this->resizable(this);
  this->show();
}

//-------------------------------------------------------------------
// Procedure: augmentMenu()

void POLY_GUI::augmentMenu() 
{
  m_menubar->add("Polygons/DumpSpec",   '>',
		 (Fl_Callback*)POLY_GUI::cb_DumpPolySpec, (void*)0, 0);
  m_menubar->add("Polygons/Move Right", FL_SHIFT + FL_Right,
		 (Fl_Callback*)POLY_GUI::cb_ShiftX, (void*)10, 0);
  m_menubar->add("Polygons/Move Left",  FL_SHIFT + FL_Left,
		 (Fl_Callback*)POLY_GUI::cb_ShiftX, (void*)-10, 0);
  m_menubar->add("Polygons/Move Up",    FL_SHIFT + FL_Up,
		 (Fl_Callback*)POLY_GUI::cb_ShiftY, (void*)10, 0);
  m_menubar->add("Polygons/Move Down",  FL_SHIFT + FL_Down,
		 (Fl_Callback*)POLY_GUI::cb_ShiftY, (void*)-10, FL_MENU_DIVIDER);
  m_menubar->add("Polygons/Move Right (slow)", FL_SHIFT + FL_ALT + FL_Right,
		 (Fl_Callback*)POLY_GUI::cb_ShiftX, (void*)1, 0);
  m_menubar->add("Polygons/Move Left (slow)",  FL_SHIFT + FL_ALT + FL_Left,
		 (Fl_Callback*)POLY_GUI::cb_ShiftX, (void*)-1, 0);
  m_menubar->add("Polygons/Move Up (slow)",    FL_SHIFT + FL_ALT + FL_Up,
		 (Fl_Callback*)POLY_GUI::cb_ShiftY, (void*)1, 0);
  m_menubar->add("Polygons/Move Down (slow)",  FL_SHIFT + FL_ALT + FL_Down,
		 (Fl_Callback*)POLY_GUI::cb_ShiftY, (void*)-1, FL_MENU_DIVIDER);

  m_menubar->add("Polygons/Rotate Right", '}',
		 (Fl_Callback*)POLY_GUI::cb_Rotate, (void*)1, 0);
  m_menubar->add("Polygons/Rotate Left",  '{',
		 (Fl_Callback*)POLY_GUI::cb_Rotate, (void*)-1, 0);

  m_menubar->add("Polygons/Enlarge", ']',
		 (Fl_Callback*)POLY_GUI::cb_Grow, (void*)1, 0);
  m_menubar->add("Polygons/Shrink",  '[',
		 (Fl_Callback*)POLY_GUI::cb_Grow, (void*)-1, 0);

  m_menubar->add("Polygons/Reverse", 'R',
		 (Fl_Callback*)POLY_GUI::cb_Reverse, (void*)0, 0);
  
  m_menubar->add("SnapValue/200.0 meters", 0,
		 (Fl_Callback*)POLY_GUI::cb_SnapVal, (void*)20000, FL_MENU_RADIO);
  m_menubar->add("SnapValue/100.0 meters", 0,
		 (Fl_Callback*)POLY_GUI::cb_SnapVal, (void*)10000, FL_MENU_RADIO);
  m_menubar->add("SnapValue/50.0 meters", 0,
		 (Fl_Callback*)POLY_GUI::cb_SnapVal, (void*)5000, FL_MENU_RADIO);
  m_menubar->add("SnapValue/10.0 meters", 0,
		 (Fl_Callback*)POLY_GUI::cb_SnapVal, (void*)1000, FL_MENU_RADIO|FL_MENU_VALUE);
  m_menubar->add("SnapValue/ 5.0 meters", 0,
		 (Fl_Callback*)POLY_GUI::cb_SnapVal, (void*)500, FL_MENU_RADIO);
  m_menubar->add("SnapValue/ 2.0 meters", 0,
		 (Fl_Callback*)POLY_GUI::cb_SnapVal, (void*)200, FL_MENU_RADIO);
  m_menubar->add("SnapValue/ 1.0 meters", 0,
		 (Fl_Callback*)POLY_GUI::cb_SnapVal, (void*)100, FL_MENU_RADIO);
  m_menubar->add("SnapValue/ 0.1 meters", 0,
		 (Fl_Callback*)POLY_GUI::cb_SnapVal, (void*)10, FL_MENU_RADIO);
  m_menubar->add("SnapValue/ 0.01 meters", 0,
		 (Fl_Callback*)POLY_GUI::cb_SnapVal, (void*)1, FL_MENU_RADIO);
  m_menubar->add("SnapValue/ 0.00 meters", 0,
		 (Fl_Callback*)POLY_GUI::cb_SnapVal, (void*)0, FL_MENU_RADIO);
  m_menubar->add("SnapValue/Re-Apply To Current", 0,
		 (Fl_Callback*)POLY_GUI::cb_ReApplySnapVal, (void*)0, 0);


  m_menubar->add("Starts/Start1", '1',
		 (Fl_Callback*)POLY_GUI::cb_StartPoints, (void*)1);
  m_menubar->add("Starts/Start2", '2',
		 (Fl_Callback*)POLY_GUI::cb_StartPoints, (void*)2);
  m_menubar->add("Starts/Start3", '3',
		 (Fl_Callback*)POLY_GUI::cb_StartPoints, (void*)3);
  m_menubar->add("Starts/Start4", '4',
		 (Fl_Callback*)POLY_GUI::cb_StartPoints, (void*)4);
  m_menubar->add("Starts/Start5", '5',
		 (Fl_Callback*)POLY_GUI::cb_StartPoints, (void*)5);
  m_menubar->add("Starts/Start6", '6',
		 (Fl_Callback*)POLY_GUI::cb_StartPoints, (void*)6);
  m_menubar->add("Starts/Start7", '7',
		 (Fl_Callback*)POLY_GUI::cb_StartPoints, (void*)7);
  m_menubar->add("Starts/Start8", '8',
		 (Fl_Callback*)POLY_GUI::cb_StartPoints, (void*)8);

}

//----------------------------------------------------------
// Procedure: handle()
//     Notes: We want the various "Output" widgets to ignore keyboard
//            events (as they should, right?!), so we wrote a MY_Output
//            subclass to do just that. However the keyboard arrow keys
//            still seem to be grabbed by Fl_Window to change focuse
//            between sub-widgets. We over-ride that here to do the 
//            panning on the image by invoking the pan callbacks. By
//            then returning (1), we've indicated that the event has
//            been handled.

int POLY_GUI::handle(int event) 
{
  switch(event) {
  case FL_PUSH:
    Fl_Window::handle(event);
    updateXY();
    return(1);
    break;
  default:
    return(Fl_Window::handle(event));
  }
}

//----------------------------------------- Rotate
inline void POLY_GUI::cb_Rotate_i(int v) {
  pviewer->rotatePoints(v);
  updateXY();
  pviewer->redraw();
}
void POLY_GUI::cb_Rotate(Fl_Widget* o, int v) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_Rotate_i(v);
}

//----------------------------------------- ShiftX
inline void POLY_GUI::cb_ShiftX_i(int amt) {
  pviewer->shiftHorzPoints((float)(amt));
  updateXY();
  pviewer->redraw();
}
void POLY_GUI::cb_ShiftX(Fl_Widget* o, int v) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_ShiftX_i(v);
}

//----------------------------------------- ShiftY
inline void POLY_GUI::cb_ShiftY_i(int amt) {
  pviewer->shiftVertPoints((float)(amt));
  updateXY();
  pviewer->redraw();
}
void POLY_GUI::cb_ShiftY(Fl_Widget* o, int v) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_ShiftY_i(v);
}

//----------------------------------------- Grow
inline void POLY_GUI::cb_Grow_i(int v) {
  pviewer->growPoints(v);
  updateXY();
  pviewer->redraw();
}
void POLY_GUI::cb_Grow(Fl_Widget* o, int v) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_Grow_i(v);
}

//----------------------------------------- Reverse
inline void POLY_GUI::cb_Reverse_i() {
  pviewer->reversePoints();
  updateXY();
  pviewer->redraw();
}
void POLY_GUI::cb_Reverse(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_Reverse_i();
}

//----------------------------------------- SnapVal
inline void POLY_GUI::cb_SnapVal_i(int v) {
  pviewer->setParam("snap", v/100.0);
  updateXY();
  pviewer->redraw();
}
void POLY_GUI::cb_SnapVal(Fl_Widget* o, int v) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_SnapVal_i(v);
}

//----------------------------------------- ReApplySnapVal
inline void POLY_GUI::cb_ReApplySnapVal_i() {
  pviewer->reApplySnapToCurrent();
  updateXY();
  pviewer->redraw();
}
void POLY_GUI::cb_ReApplySnapVal(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_ReApplySnapVal_i();
}

//----------------------------------------- DumpPolySpec
void POLY_GUI::cb_DumpPolySpec_i() {
  cout << "BORDER: " << pviewer->getBorderSpec() << endl;
  cout << "GEN_POLY: " << pviewer->getGPolySpec() << endl;
}
void POLY_GUI::cb_DumpPolySpec(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_DumpPolySpec_i();
}
  
//----------------------------------------- DrawPts
void POLY_GUI::cb_DrawPts_i() {
  pviewer->setParam("draw_pts", "toggle");
  pviewer->redraw();
}
void POLY_GUI::cb_DrawPts(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_DrawPts_i();
}
  
//----------------------------------------- DrawSegl
void POLY_GUI::cb_DrawSegl_i() {
  pviewer->setParam("draw_segl", "toggle");
  pviewer->redraw();
}
void POLY_GUI::cb_DrawSegl(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_DrawSegl_i();
}
  
//----------------------------------------- DrawHull
void POLY_GUI::cb_DrawHull_i() {
  pviewer->setParam("draw_hull", "toggle");
  pviewer->redraw();
}
void POLY_GUI::cb_DrawHull(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_DrawHull_i();
}
  
//----------------------------------------- DrawGPoly
void POLY_GUI::cb_DrawGPoly_i() {
  pviewer->setParam("draw_gpoly", "toggle");
  pviewer->redraw();
}
void POLY_GUI::cb_DrawGPoly(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_DrawGPoly_i();
}

//----------------------------------------- Resolve
void POLY_GUI::cb_Resolve_i() {
  pviewer->updateGenPoly();
  pviewer->redraw();
  updateXY();
}
void POLY_GUI::cb_Resolve(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_Resolve_i();
}

//----------------------------------------- MethodToggle
void POLY_GUI::cb_MethodToggle_i() {
  pviewer->setParam("method", "toggle");
  pviewer->updateGenPoly();  
  pviewer->redraw();
  updateXY();
}
void POLY_GUI::cb_MethodToggle(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_MethodToggle_i();
}

//----------------------------------------- CollapseToggle
void POLY_GUI::cb_CollapseToggle_i() {
  pviewer->setParam("collapse", "toggle");
  pviewer->updateGenPoly();  
  pviewer->redraw();
  updateXY();
}
void POLY_GUI::cb_CollapseToggle(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_CollapseToggle_i();
}

//----------------------------------------- VerboseToggle
void POLY_GUI::cb_VerboseToggle_i() {
  pviewer->setParam("verbose", "toggle");
  pviewer->updateGenPoly();  
  pviewer->redraw();
  updateXY();
}
void POLY_GUI::cb_VerboseToggle(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_VerboseToggle_i();
}

//----------------------------------------- Clear
void POLY_GUI::cb_Clear_i() {
  pviewer->clear();
  pviewer->redraw();
  updateXY();
}
void POLY_GUI::cb_Clear(Fl_Widget* o) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_Clear_i();
}

//----------------------------------------- StartPoints
void POLY_GUI::cb_StartPoints_i(int val) {
  pviewer->setParam("start", (double)(val));
  pviewer->redraw();
  updateXY();
}
void POLY_GUI::cb_StartPoints(Fl_Widget* o, int i) {
  ((POLY_GUI*)(o->parent()->user_data()))->cb_StartPoints_i(i);
}
  
//----------------------------------------- UpdateXY
void POLY_GUI::updateXY()
{ 
  // Snap Value
  double dval = pviewer->getSnap();
  string sval = doubleToStringX(dval);
  m_fld_snap->value(sval.c_str());

  // Poly Count
  unsigned int ival = pviewer->getPolyCount();
  sval = uintToString(ival);
  m_fld_polys->value(sval.c_str());

  // Solve Time
  dval = pviewer->getSolveTime();
  sval = doubleToString(dval,2);
  m_fld_solve->value(sval.c_str());

  // Solve Method
  sval = pviewer->getSolveMethod();
  m_fld_method->value(sval.c_str());

  // Solve Collap
  bool bval = pviewer->getSolveCollap();
  sval = boolToString(bval);
  m_fld_collap->value(sval.c_str());

  // Verbosity
  bval = pviewer->getVerbose();
  sval = boolToString(bval);
  m_fld_verbose->value(sval.c_str());

  // SegList string
  string str = pviewer->getBorderSpec();
  m_fld_segl->value(str.c_str());

  // GenPoly string
  str = pviewer->getGPolySpec();
  m_fld_gpoly->value(str.c_str());
}
