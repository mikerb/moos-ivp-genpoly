/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: PolyViewer.cpp                                       */
/*    DATE: Nov 22nd, 2025                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include <string>
#include "MBTimer.h"
#include "PolyViewer.h"
#include "MBUtils.h"
#include "GeomUtils.h"
#include "AngleUtils.h"
#include "XYFormatUtilsSegl.h"
#include "ConvexHullGenerator.h"
#include "XYGenPolygon.h"
#include "CoverEngine.h"

using namespace std;

//------------------------------------------------------------
// Constructor()

PolyViewer::PolyViewer(int x, int y, int w, int h, const char *l)
  : MarineViewer(x,y,w,h,l)
{
  // Superclass vars init
  m_vshift_x = 20;
  m_vshift_y = -280;

  // Config vars init
  m_draw_pts     = true;
  m_draw_segl    = true;
  m_draw_hull    = false;
  m_draw_gpoly   = true;
  m_snap_val     = 2.0;
  m_solve_collap = true;
  m_solve_method = "shallow"; 
  
  // State vars init
  m_solve_time = 0;
}

//-------------------------------------------------------------
// Procedure: handle()

int PolyViewer::handle(int event)
{
  int vx, vy;
  switch(event) {
  case FL_PUSH:
    vx = Fl::event_x();
    vy = h() - Fl::event_y();
    if(Fl_Window::handle(event) != 1) {

      if((Fl::event_button() == FL_LEFT_MOUSE) &&
	 (Fl::event_state(FL_ALT))) {
	cout << "Insert!!" << endl;
	handle_left_mouse(vx, vy, false);
      }

      else if((Fl::event_button() == FL_LEFT_MOUSE) &&
	 (!Fl::event_state(FL_CTRL)) &&
	 (!Fl::event_state(FL_SHIFT)))
	handle_left_mouse(vx, vy);
      
      else if(Fl::event_button() == FL_RIGHT_MOUSE) {
	handle_right_mouse(vx, vy);
      }
      
      else if((Fl::event_button() == FL_LEFT_MOUSE) &&
	 (Fl::event_state(FL_CTRL))) {
	handle_right_mouse(vx, vy);
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

void PolyViewer::draw()
{
  //cout << "pan_x:" << getPanX() << ", pan_y: " << getPanY() << endl;
  
  MarineViewer::draw();
  if(m_geo_settings.viewable("hash_viewable"))
    drawFastHash();

  // ------------------------------------------------------
  // Draw Points
  // ------------------------------------------------------
  if(m_draw_pts) {
    map<string, XYPoint> pts;
    for(unsigned int i=0; i<m_segl.size(); i++) {
      XYPoint pt = m_segl.get_point(i);
      string label = uintToString(i);
      pt.set_vertex_size(15);
      pt.set_vertex_color("white");
      pt.set_label(label);
      pts[label] = pt;
    }
    drawPoints(pts);
  }
  
  // ------------------------------------------------------
  // Draw SegList
  // ------------------------------------------------------
  if(m_draw_segl) {
    m_segl.set_vertex_size(10);

    if(m_segl.segs_cross())
      m_segl.set_edge_color("pink");
    else
      m_segl.set_edge_color("white");
      
    m_segl.set_vertex_color("dodger_blue");
    m_segl.set_label_color("off");
    m_segl.set_label("segl");
    drawSegList(m_segl);
  }

  // ------------------------------------------------------
  // Draw ConvexHull
  // ------------------------------------------------------
  if(m_draw_hull) {
    if(m_hull_poly.is_convex()) {
      m_hull_poly.set_vertex_size(4);
      m_hull_poly.set_vertex_color("yellow");
      m_hull_poly.set_label("hull");
      m_hull_poly.set_label_color("off");
      m_hull_poly.set_edge_color("dodger_blue");
      drawPolygon(m_hull_poly);
    }
  }

  if(m_draw_gpoly) {
    vector<XYPolygon> polys = m_gen_poly.getCoverPolys();
    //cout << "total polys:" << polys.size() << endl;
    for(unsigned int i=0; i<polys.size(); i++) {
      XYPolygon poly = polys[i];
      poly.set_color("edge", "gray80");
      poly.set_color("fill", "gray50");
      drawPolygon(poly);
    }
  }

}

//-------------------------------------------------------------
// Procedure: handle_left_mouse()

void PolyViewer::handle_left_mouse(int vx, int vy, bool add_point)
{
  double ix = view2img('x', vx);
  double iy = view2img('y', vy);
  double mx = img2meters('x', ix);
  double my = img2meters('y', iy);
  double sx = snapToStep(mx, m_snap_val);
  double sy = snapToStep(my, m_snap_val);

  if(add_point)
    m_segl.add_vertex(sx, sy);
  else
    m_segl.insert_vertex(sx, sy);

  updateConvexHull();
  updateGenPoly();
  redraw();
}

//-------------------------------------------------------------
// Procedure: handle_right_mouse()

void PolyViewer::handle_right_mouse(int vx, int vy)
{
  double ix = view2img('x', vx);
  double iy = view2img('y', vy);
  double mx = img2meters('x', ix);
  double my = img2meters('y', iy);
  m_segl.delete_vertex(mx, my);

  updateConvexHull();
  updateGenPoly();
  redraw();
}


//-------------------------------------------------------------
// Procedure: setParam()

bool PolyViewer::setParam(string param, string value)
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
  else if(param == "view_point") {
    cout << "Adding a point:" << endl; 
    //handled = m_geoshapes.addPoint(value);
    cout << "handled:" << handled << endl; 
  }

  else if(param == "draw_pts") 
    setBooleanOnString(m_draw_pts, value);
  else if(param == "draw_segl") 
    setBooleanOnString(m_draw_segl, value);
  else if(param == "draw_hull") 
    setBooleanOnString(m_draw_hull, value);
  else if(param == "draw_gpoly") 
    setBooleanOnString(m_draw_gpoly, value);
  else if(param == "collapse") 
    setBooleanOnString(m_solve_collap, value);
  else if(param == "verbose") 
    setBooleanOnString(m_verbose, value);
  else if(param == "method") {
    if(value == "shallow")
      m_solve_method = value;
    else if(value == "deep")
      m_solve_method = value;
    else if(value == "deepest")
      m_solve_method = value;
    else if(value == "toggle") {
      if(m_solve_method == "shallow")
	m_solve_method = "deep";
      else if(m_solve_method == "deep")
	m_solve_method = "deepest";
      else if(m_solve_method == "deepest")
	m_solve_method = "shallow";
    }
  }
  
  else
    handled = handled || m_vehi_settings.setParam(param, value);

  return(handled);
}

//-------------------------------------------------------------
// Procedure: setParam()

bool PolyViewer::setParam(string param, double pval)
{
  if(MarineViewer::setParam(param, pval))
    return(true);

  else if((param == "start") && (pval == 1)) {
    string s = "pts={-40,-50:-40,-100:-20,-100:-20,-60:0,-60:0,-100:20,-100:20,-50}";
    m_segl = string2SegList(s);
    updateConvexHull();
    updateGenPoly();
  }

  else if((param == "start") && (pval == 2)) {
    string s = "pts={-45,-100:-25,-85:0,-75:30,-75:50,-85:65,-100:40,-100:30,-85:";
    s += "0,-85:-15,-100}";
    m_segl = string2SegList(s);
    updateConvexHull();
    updateGenPoly();
  }
  else if((param == "start") && (pval == 3)) {
    string s = "pts={-45,-65:-25,-45:-15,-65:0,-45:10,-65:25,-45:35,-65:";
    s += "50,-45:60,-65:60,-100:-45,-100}";
    m_segl = string2SegList(s);
    updateConvexHull();
    updateGenPoly();
  }
  else if((param == "start") && (pval == 4)) {
    string s = "pts={2,-52:-16,-72:-8,-114:38,-126:82,-88:76,-54:64,-16:";
    s += "32,-2:-4,-8:-30,-22:-38,-32:-30,-42:-10,-42:14,-36:48,-46:52,-72:36,-94:16,-96}";
    m_segl = string2SegList(s);
    updateConvexHull();
    updateGenPoly();
  }
  else if((param == "start") && (pval == 5)) {
    string s = "pts={18,-44:-2,-66:-4,-102:36,-118:62,-84:92,-66:86,-36:66,-4:36,2:";
    s += "-2,-10:-20,-34:4,-36:40,-26:72,-44:50,-64:46,-86:32,-98:18,-68:40,-44}";
    m_segl = string2SegList(s);
    updateConvexHull();
    updateGenPoly();
  }
  else if((param == "start") && (pval == 6)) {
    string s = "pts={12,-18:24,-28:32,-18:44,-32:56,-32:58,-44:72,-42:70,-64:78,-78:";
    s += "56,-88:60,-100:34,-96:20,-108:26,-66:-2,-88:10,-58:-26,-60:30,-46:-34,-36}";
    m_segl = string2SegList(s);
    updateConvexHull();
    updateGenPoly();
  }
  else if((param == "start") && (pval == 7)) {
    string s = "pts={2,-48:-6,-68:-2,-98:8,-108:26,-114:48,-116:82,-108:106,-74:";
    s += "116,-38:112,-4:78,8:88,-24:86,-62:70,-86:48,-100:30,-94:42,-74:62,-60:";
    s += "68,-28:50,-4:-50,-40}";
    m_segl = string2SegList(s);
    updateConvexHull();
    updateGenPoly();
  }
  else if((param == "start") && (pval == 8)) {
    string s = "pts={74,0:82,-30:90,-68:90,-102:66,-130:38,-132:6,-118:-12,-102:";
    s += "-26,-58:-6,-24:0,-56:10,-88:32,-106:58,-112:76,-98:74,-66:66,-44:58,-28}";
    m_segl = string2SegList(s);
    updateConvexHull();
    updateGenPoly();
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
// Procedure: clear()

void PolyViewer::clear()
{  
  m_segl.clear();
  m_hull_poly.clear();
  m_gen_poly.clear();
  m_solve_time = 0;
}

// ----------------------------------------------------------
// Procedure: getBorderSpec()

string PolyViewer::getBorderSpec()
{  
  return(m_segl.get_spec());
}

// ----------------------------------------------------------
// Procedure: getGPolySpec()

string PolyViewer::getGPolySpec()
{  
  return(m_gen_poly.get_spec());
}

// ----------------------------------------------------------
// Procedure: shiftHorzPoly()

void PolyViewer::shiftHorzPoints(double shift_val)
{
  m_segl.shift_horz(shift_val);
  updateConvexHull();
  updateGenPoly();
}

// ----------------------------------------------------------
// Procedure: shiftVertPoints()

void PolyViewer::shiftVertPoints(double shift_val)
{
  m_segl.shift_vert(shift_val);
  updateConvexHull();
  updateGenPoly();
}

// ----------------------------------------------------------
// Procedure: rotatePoints()
//   Purpose: Rotate the points around its center by the given
//            number of degrees. Each point in the cluster is 
//            rotated around the calculated center of the clsteru

void PolyViewer::rotatePoints(int rval)
{
  m_segl.rotate(rval);
  updateConvexHull();
  updateGenPoly();
}

// ----------------------------------------------------------
// Procedure: growPoints()
//   Purpose: Expand the point cluster by the tive percent.
//            Each point in the cluster growsin distance from 
//            calculated center of the cluster.

void PolyViewer::growPoints(int gval)
{
  double dgval = (double)(gval) / 100.0;
  m_segl.grow_by_pct(dgval);
  updateConvexHull();
  updateGenPoly();
}

// ----------------------------------------------------------
// Procedure: reversePoints()
//   Purpose: Reverse the stored ordering of points

void PolyViewer::reversePoints()
{
  m_segl.reverse();
  updateConvexHull();
  updateGenPoly();
}

// ----------------------------------------------------------
// Procedure: reApplySnapToCurrent()

void PolyViewer::reApplySnapToCurrent()
{
  m_segl.apply_snap(m_snap_val);
  updateConvexHull();
  updateGenPoly();
}


// ----------------------------------------------------------
// Procedure: updateConvexHull()

void PolyViewer::updateConvexHull()
{
  if(!m_draw_hull)
    return;
  
  if(m_segl.size() < 3)
    return;
  
  ConvexHullGenerator generator;

  for(unsigned int i=0; i<m_segl.size(); i++) {
    double vx =  m_segl.get_vx(i);
    double vy =  m_segl.get_vy(i);
    generator.addPoint(vx, vy);
  }

  m_hull_poly = generator.generateConvexHull();
}

// ----------------------------------------------------------
// Procedure: updateGenPoly()

void PolyViewer::updateGenPoly()
{
  if(!m_draw_gpoly)
    return;
  
  CoverEngine engine;
  bool ok = engine.setPoints(m_segl);
  if(!ok)
    return;

  engine.setPostCollapse(m_solve_collap);
  engine.setSolveMethod(m_solve_method);
  engine.setVerbose(m_verbose);

  MBTimer timer;
  timer.start();
  m_gen_poly = engine.getGenPoly();
  timer.stop();
  m_solve_time = timer.get_float_wall_time();
}  

