/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: EPathViewer.cpp                                      */
/*    DATE: July 9th, 2026                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include <string>
#include "MBTimer.h"
#include "EPathViewer.h"
#include "MBUtils.h"
#include "GeomUtils.h"
#include "AngleUtils.h"
#include "XYFormatUtilsSegl.h"
#include "XYFormatUtilsPoly.h"
#include "ConvexHullGenerator.h"
#include "XYGenPolygon.h"
#include "CoverEngine.h"

using namespace std;

//------------------------------------------------------------
// Constructor()

EPathViewer::EPathViewer(int x, int y, int w, int h, const char *l)
  : MarineViewer(x,y,w,h,l)
{
  // Superclass vars init
  m_vshift_x = 20;
  m_vshift_y = -280;

  // Config vars init
  m_draw_deads   = true;
  m_draw_segl    = true;
  m_draw_hull    = false;
  m_draw_gpoly   = true;
  m_snap_val     = 2.0;
  m_solve_collap = true;
  m_solve_method = "shallow"; 

  // State vars init
  m_solve_time = 0;

  m_pfield.setSource(-50,-100);
  m_pfield.setDest(110,-70);
}

//-------------------------------------------------------------
// Procedure: handle()

int EPathViewer::handle(int event)
{
  int vx, vy;
  switch(event) {
  case FL_PUSH:
    vx = Fl::event_x();
    vy = h() - Fl::event_y();
    if(Fl_Window::handle(event) != 1) {

      if((Fl::event_button() == FL_LEFT_MOUSE) &&
	 (Fl::event_state(FL_CTRL))) {
	cout << "Focus Poly!!" << endl;
	handle_mouse_focus_poly(vx, vy);
      }

      else if((Fl::event_button() == FL_LEFT_MOUSE) &&
	 (Fl::event_state(FL_SHIFT))) {
	cout << "Poly!!" << endl;
	handle_mouse_poly(vx, vy);
      }

      else if((Fl::event_button() == FL_LEFT_MOUSE) &&
	 (!Fl::event_state(FL_CTRL)) &&
	 (!Fl::event_state(FL_SHIFT)))
	handle_mouse_src(vx, vy);
      
      else if(Fl::event_button() == FL_RIGHT_MOUSE) {
	handle_mouse_dest(vx, vy);
      }
      
      else if((Fl::event_button() == FL_LEFT_MOUSE) &&
	 (Fl::event_state(FL_CTRL))) {
	handle_mouse_dest(vx, vy);
      }

    }
    return(1);
    break;
  default:
    return(Fl_Gl_Window::handle(event));
  }
}

//-------------------------------------------------------------
// Procedure: draw()

void EPathViewer::draw()
{
  //cout << "pan_x:" << getPanX() << ", pan_y: " << getPanY() << endl;
  
  MarineViewer::draw();
  if(m_geo_settings.viewable("hash_viewable"))
    drawFastHash();

  // ------------------------------------------------------
  // Draw Source
  // ------------------------------------------------------
  double sx = m_pfield.getSrcX();
  double sy = m_pfield.getSrcY();
  XYPoint spt(sx,sy);
  spt.set_vertex_size(15);
  spt.set_vertex_color("white");
  spt.set_label("s");
  drawPoint(spt);
  
  // ------------------------------------------------------
  // Draw Destination
  // ------------------------------------------------------
  double dx = m_pfield.getDestX();
  double dy = m_pfield.getDestY();
  XYPoint dpt(dx,dy);
  dpt.set_vertex_size(15);
  dpt.set_vertex_color("green");
  dpt.set_label("d");
  drawPoint(dpt);
  
  // ------------------------------------------------------
  // Draw Polys
  // ------------------------------------------------------
  int focus_poly = m_pfield.getFocusPoly();
  
  vector<XYPolygon> polys = m_pfield.getPolys();
  for(unsigned int i=0; i<polys.size(); i++) {
    XYPolygon poly = polys[i];
    poly.set_color("fill", "gray50");
    poly.set_edge_color("white");
    poly.set_vertex_color("dodger_blue");

    if(focus_poly >= 0) {
      if(focus_poly == i)
	poly.set_color("fill", "orange");
    }
    else {    
      string pass_side = m_pfield.getPolyPassSide(i);
      if(pass_side == "star")
	poly.set_color("fill", "red");
      else if(pass_side == "port")
	poly.set_color("fill", "green");
    }
    
    drawPolygon(poly);
  }
  
  // ------------------------------------------------------
  // Draw Segls
  // ------------------------------------------------------
  if(m_draw_deads) {
    vector<XYSegList> segls;
    segls = m_pfield.getSeglsDead();
    for(unsigned int i=0; i<segls.size(); i++) {
      XYSegList segl = segls[i];
      segl.set_edge_color("white");
      segl.set_vertex_color("white");
      drawSegList(segl);
    }
  }

  if(m_pfield.getFocusPoly() < 0) {
    XYSegList segl_shortest = m_pfield.getSeglShortest();
    if(segl_shortest.size() > 0) {
      segl_shortest.set_edge_color("green");
      segl_shortest.set_vertex_color("white");  
      drawSegList(segl_shortest);
    }
  }
  else {
    XYSegList seglp = m_pfield.getSeglShortestPort();
    if(seglp.size() > 0) {
      seglp.set_edge_color("pink");
      seglp.set_vertex_color("white");  
      drawSegList(seglp);
    }
    XYSegList segls = m_pfield.getSeglShortestStar();
    if(segls.size() > 0) {
      segls.set_edge_color("green");
      segls.set_vertex_color("white");  
      drawSegList(segls);
    }
  }
}

//-------------------------------------------------------------
// Procedure: handle_mouse_src()

void EPathViewer::handle_mouse_src(int vx, int vy)
{
  double ix = view2img('x', vx);
  double iy = view2img('y', vy);
  double mx = img2meters('x', ix);
  double my = img2meters('y', iy);
  m_pfield.setSource(mx, my);
  m_pfield.clearSolve();

  redraw();
}

//-------------------------------------------------------------
// Procedure: handle_mouse_dest()

void EPathViewer::handle_mouse_dest(int vx, int vy)
{
  double ix = view2img('x', vx);
  double iy = view2img('y', vy);
  double mx = img2meters('x', ix);
  double my = img2meters('y', iy);
  m_pfield.setDest(mx, my);
  m_pfield.clearSolve();

  redraw();
}

//-------------------------------------------------------------
// Procedure: handle_mouse_poly()

void EPathViewer::handle_mouse_poly(int vx, int vy)
{
  double ix = view2img('x', vx);
  double iy = view2img('y', vy);
  double mx = img2meters('x', ix);
  double my = img2meters('y', iy);

  string polystr = "format=radial";
  polystr += ",x=" + doubleToStringX(mx,2);
  polystr += ",y=" + doubleToStringX(my,2);
  polystr += ",radius=12, pts=6, snap=0.1";
  XYPolygon poly = string2Poly(polystr);
  
  m_pfield.addPoly(poly);

  redraw();
}

//-------------------------------------------------------------
// Procedure: handle_mouse_focus_poly()

void EPathViewer::handle_mouse_focus_poly(int vx, int vy)
{
  double ix = view2img('x', vx);
  double iy = view2img('y', vy);
  double mx = img2meters('x', ix);
  double my = img2meters('y', iy);

  m_pfield.focusPoly(mx,my);

  redraw();
}


//-------------------------------------------------------------
// Procedure: setParam()

bool EPathViewer::setParam(string param, string value)
{
  param = tolower(stripBlankEnds(param));
  value = stripBlankEnds(value);
  
  if(MarineViewer::setParam(param, value))
    return(true);

  bool handled = true;
  if(param == "view_polygon") 
    m_segl = string2SegList(value);
  else if(param == "view_seglist")
    m_segl = string2SegList(value);
  else if(param == "draw_deads") 
    setBooleanOnString(m_draw_deads, value);
  else if(param == "verbose") 
    setBooleanOnString(m_verbose, value);
  
  else
    handled = handled || m_vehi_settings.setParam(param, value);

  return(handled);
}

//-------------------------------------------------------------
// Procedure: setParam()

bool EPathViewer::setParam(string param, double pval)
{
  if(MarineViewer::setParam(param, pval))
    return(true);

  else if((param == "start") && (pval == 1)) {
    string s = "pts={-40,-50:-40,-100:-20,-100:-20,-60:0,-60:0,-100:20,-100:20,-50}";
    m_segl = string2SegList(s);
  }

  else if((param == "start") && (pval == 2)) {
    string s = "pts={-45,-100:-25,-85:0,-75:30,-75:50,-85:65,-100:40,-100:30,-85:";
    s += "0,-85:-15,-100}";
    m_segl = string2SegList(s);
  }
  else if((param == "start") && (pval == 3)) {
    string s = "pts={-45,-65:-25,-45:-15,-65:0,-45:10,-65:25,-45:35,-65:";
    s += "50,-45:60,-65:60,-100:-45,-100}";
    m_segl = string2SegList(s);
  }
  
  else if(param == "snap") {
    m_snap_val = pval;
    return(true);
  }
  else
    return(false);

  return(true);
}

// ----------------------------------------------------------
// Procedure: clearPolys()

void EPathViewer::clearPolys()
{  
  m_pfield.clearPolys();
  m_segl.clear();
  //m_hull_poly.clear();
  //m_gen_poly.clear();
  m_solve_time = 0;
}

// ----------------------------------------------------------
// Procedure: clearSolve()

void EPathViewer::clearSolve()
{  
  m_pfield.clearSolve();
  m_segl.clear();
  //m_hull_poly.clear();
  //m_gen_poly.clear();
  m_solve_time = 0;
}

// ----------------------------------------------------------
// Procedure: solve()

void EPathViewer::solve(unsigned int amt)
{
  m_pfield.solve();
  redraw();
}

// ----------------------------------------------------------
// Procedure: shiftHorzPoly()

void EPathViewer::shiftHorzPoints(double shift_val)
{
  m_segl.shift_horz(shift_val);
}

// ----------------------------------------------------------
// Procedure: shiftVertPoints()

void EPathViewer::shiftVertPoints(double shift_val)
{
  m_segl.shift_vert(shift_val);
}

// ----------------------------------------------------------
// Procedure: rotatePoints()
//   Purpose: Rotate the points around its center by the given
//            number of degrees. Each point in the cluster is 
//            rotated around the calculated center of the clsteru

void EPathViewer::rotatePoints(int rval)
{
  m_segl.rotate(rval);
}

// ----------------------------------------------------------
// Procedure: growPoints()
//   Purpose: Expand the point cluster by the tive percent.
//            Each point in the cluster growsin distance from 
//            calculated center of the cluster.

void EPathViewer::growPoints(int gval)
{
  double dgval = (double)(gval) / 100.0;
  m_segl.grow_by_pct(dgval);
}

// ----------------------------------------------------------
// Procedure: getSeglShortest()

string EPathViewer::getSeglShortest()
{
  XYSegList segl = m_pfield.getSeglShortest();
  string spec = segl.get_spec();
  return(spec);
}

// ----------------------------------------------------------
// Procedure: getSeglShortestStar()

string EPathViewer::getSeglShortestStar()
{
  XYSegList segl = m_pfield.getSeglShortestStar();
  string spec = segl.get_spec();
  return(spec);
}


