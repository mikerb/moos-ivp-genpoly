/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: EPATH_GUI.cpp                                        */
/*    DATE: July 9th, 2026                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include <cstdio>
#include "EPATH_GUI.h"
#include "MBUtils.h"

using namespace std;

//-------------------------------------------------------------------
// Constructor()

EPATH_GUI::EPATH_GUI(int wid, int hgt, const char *label)
  : MarineGUI(wid, hgt, label) {

  this->user_data((void*)(this));
  this->when(FL_WHEN_CHANGED);
  this->begin();

  m_start_hgt = hgt;
  m_start_wid = wid;
  
  pviewer   = new EPathViewer(0, 30, wid, hgt-160);
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

void EPATH_GUI::augmentMenu() 
{
  m_menubar->add("Polygons/DumpSpec",   '>',
		 (Fl_Callback*)EPATH_GUI::cb_DumpPolySpec, (void*)0, 0);
  m_menubar->add("Polygons/Move Right", FL_SHIFT + FL_Right,
		 (Fl_Callback*)EPATH_GUI::cb_ShiftX, (void*)10, 0);
  m_menubar->add("Polygons/Move Left",  FL_SHIFT + FL_Left,
		 (Fl_Callback*)EPATH_GUI::cb_ShiftX, (void*)-10, 0);
  m_menubar->add("Polygons/Move Up",    FL_SHIFT + FL_Up,
		 (Fl_Callback*)EPATH_GUI::cb_ShiftY, (void*)10, 0);
  m_menubar->add("Polygons/Move Down",  FL_SHIFT + FL_Down,
		 (Fl_Callback*)EPATH_GUI::cb_ShiftY, (void*)-10, FL_MENU_DIVIDER);
  m_menubar->add("Polygons/Move Right (slow)", FL_SHIFT + FL_ALT + FL_Right,
		 (Fl_Callback*)EPATH_GUI::cb_ShiftX, (void*)1, 0);
  m_menubar->add("Polygons/Move Left (slow)",  FL_SHIFT + FL_ALT + FL_Left,
		 (Fl_Callback*)EPATH_GUI::cb_ShiftX, (void*)-1, 0);
  m_menubar->add("Polygons/Move Up (slow)",    FL_SHIFT + FL_ALT + FL_Up,
		 (Fl_Callback*)EPATH_GUI::cb_ShiftY, (void*)1, 0);
  m_menubar->add("Polygons/Move Down (slow)",  FL_SHIFT + FL_ALT + FL_Down,
		 (Fl_Callback*)EPATH_GUI::cb_ShiftY, (void*)-1, FL_MENU_DIVIDER);

  m_menubar->add("Polygons/Enlarge", ']',
		 (Fl_Callback*)EPATH_GUI::cb_Grow, (void*)1, 0);
  m_menubar->add("Polygons/Shrink",  '[',
		 (Fl_Callback*)EPATH_GUI::cb_Grow, (void*)-1, 0);

  m_menubar->add("Starts/Start1", '1',
		 (Fl_Callback*)EPATH_GUI::cb_StartPoints, (void*)1);
  m_menubar->add("Starts/Start2", '2',
		 (Fl_Callback*)EPATH_GUI::cb_StartPoints, (void*)2);
  m_menubar->add("Starts/Start3", '3',
		 (Fl_Callback*)EPATH_GUI::cb_StartPoints, (void*)3);
  m_menubar->add("Starts/Start4", '4',
		 (Fl_Callback*)EPATH_GUI::cb_StartPoints, (void*)4);
  m_menubar->add("Starts/Start5", '5',
		 (Fl_Callback*)EPATH_GUI::cb_StartPoints, (void*)5);
  m_menubar->add("Starts/Start6", '6',
		 (Fl_Callback*)EPATH_GUI::cb_StartPoints, (void*)6);
  m_menubar->add("Starts/Start7", '7',
		 (Fl_Callback*)EPATH_GUI::cb_StartPoints, (void*)7);
  m_menubar->add("Starts/Start8", '8',
		 (Fl_Callback*)EPATH_GUI::cb_StartPoints, (void*)8);

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

int EPATH_GUI::handle(int event) 
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

//----------------------------------------- ShiftX
inline void EPATH_GUI::cb_ShiftX_i(int amt) {
  pviewer->shiftHorzPoints((float)(amt));
  updateXY();
  pviewer->redraw();
}
void EPATH_GUI::cb_ShiftX(Fl_Widget* o, int v) {
  ((EPATH_GUI*)(o->parent()->user_data()))->cb_ShiftX_i(v);
}

//----------------------------------------- ShiftY
inline void EPATH_GUI::cb_ShiftY_i(int amt) {
  pviewer->shiftVertPoints((float)(amt));
  updateXY();
  pviewer->redraw();
}
void EPATH_GUI::cb_ShiftY(Fl_Widget* o, int v) {
  ((EPATH_GUI*)(o->parent()->user_data()))->cb_ShiftY_i(v);
}

//----------------------------------------- Grow
inline void EPATH_GUI::cb_Grow_i(int v) {
  pviewer->growPoints(v);
  updateXY();
  pviewer->redraw();
}
void EPATH_GUI::cb_Grow(Fl_Widget* o, int v) {
  ((EPATH_GUI*)(o->parent()->user_data()))->cb_Grow_i(v);
}

//----------------------------------------- DumpPolySpec
void EPATH_GUI::cb_DumpPolySpec_i() {

}
void EPATH_GUI::cb_DumpPolySpec(Fl_Widget* o) {
  ((EPATH_GUI*)(o->parent()->user_data()))->cb_DumpPolySpec_i();
}
  
//----------------------------------------- DrawDeads
void EPATH_GUI::cb_DrawDeads_i() {
  pviewer->setParam("draw_deads", "toggle");
  pviewer->redraw();
}
void EPATH_GUI::cb_DrawDeads(Fl_Widget* o) {
  ((EPATH_GUI*)(o->parent()->user_data()))->cb_DrawDeads_i();
}
  
//----------------------------------------- Solve
void EPATH_GUI::cb_Solve_i(int amt) {
  //pviewer->updateGenPoly();
  pviewer->solve(amt);
  pviewer->redraw();
  updateXY();
}
void EPATH_GUI::cb_Solve(Fl_Widget* o, int amt) {
  ((EPATH_GUI*)(o->parent()->user_data()))->cb_Solve_i(10);
}

//----------------------------------------- ClearPolys
void EPATH_GUI::cb_ClearPolys_i() {
  pviewer->clearPolys();
  pviewer->redraw();
  updateXY();
}
void EPATH_GUI::cb_ClearPolys(Fl_Widget* o) {
  ((EPATH_GUI*)(o->parent()->user_data()))->cb_ClearPolys_i();
}

//----------------------------------------- ClearSolve
void EPATH_GUI::cb_ClearSolve_i() {
  pviewer->clearSolve();
  pviewer->redraw();
  updateXY();
}
void EPATH_GUI::cb_ClearSolve(Fl_Widget* o) {
  ((EPATH_GUI*)(o->parent()->user_data()))->cb_ClearSolve_i();
}

//----------------------------------------- StartPoints
void EPATH_GUI::cb_StartPoints_i(int val) {
  pviewer->setParam("start", (double)(val));
  pviewer->redraw();
  updateXY();
}
void EPATH_GUI::cb_StartPoints(Fl_Widget* o, int i) {
  ((EPATH_GUI*)(o->parent()->user_data()))->cb_StartPoints_i(i);
}
  
//----------------------------------------- UpdateXY
void EPATH_GUI::updateXY()
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

  sval = pviewer->getSeglShortest();
  m_fld_segl_shortest->value(sval.c_str());

  sval = pviewer->getSeglShortestStar();
  m_fld_segl_star->value(sval.c_str());
}
