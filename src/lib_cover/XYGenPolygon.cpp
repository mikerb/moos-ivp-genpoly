/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: XYGenPolygon.cpp                                     */
/*    DATE: Oct 16th, 2020                                       */
/*    DATE: Nov 27th, 2025                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include "XYFormatUtilsPoly.h"
#include "XYGenPolygon.h"
#include "MBUtils.h"

using namespace std;

//---------------------------------------------------------------
// Procedure: setGenPoly()

void XYGenPolygon::setGenPoly(XYSegList segl)
{
  m_segl = segl;
  m_cover_polys.clear();
}

//---------------------------------------------------------------
// Procedure: setGenPoly()

void XYGenPolygon::setGenPoly(XYSegList segl, vector<XYPolygon> polys)
{
  m_segl = segl;
  m_cover_polys = polys;
}

//---------------------------------------------------------------
// Procedure: contains()

bool XYGenPolygon::contains(double x, double y) const
{
  for(unsigned int i=0; i<m_cover_polys.size(); i++) {
    if(m_cover_polys[i].contains(x, y))
      return(true);
  }

  return(false);
}

//---------------------------------------------------------------
// Procedure: line_intersects()
//      Note: Individual polygons are checked. Disregard where line
//            may intersect. Unlike a convex polygon, a non-convex
//            poly may have an arbitrary number of intersection pts.
//      Note: We only care here about the Boolean return value.

bool XYGenPolygon::line_intersects(double x1, double y1,
				   double x2, double y2) const
{
  double rx1,ry1, rx2,ry2;
  
  for(unsigned int i=0; i<m_cover_polys.size(); i++) {
    if(m_cover_polys[i].line_intersects(x1,y1,x2,y2,rx1,ry1,rx2,ry2))
      return(true);
  }
  
  return(false);
}

//---------------------------------------------------------------
// Procedure: dist_to_poly()

double XYGenPolygon::dist_to_poly(double px, double py) const
{
  double min_dist = -1;

  for(unsigned int i=0; i<m_cover_polys.size(); i++) {
    double dist = m_cover_polys[i].dist_to_poly(px, py);
    if((i==0) || (dist < min_dist))
      min_dist = dist;
  }

  return(min_dist);
}

//---------------------------------------------------------------
// Procedure: dist_to_poly()
//      Note: Determine the distance between the line segment given
//            by x3,y3,x4,y4 to the polygon. An edge-by-edge check
//            is performed and the minimum returned.

double XYGenPolygon::dist_to_poly(double x3, double y3, 
				  double x4, double y4) const
{
  double min_dist = -1;
  
  for(unsigned int i=0; i<m_cover_polys.size(); i++) {
    double dist = m_cover_polys[i].dist_to_poly(x3,y3, x4,y4);
    if((i==0) || (dist < min_dist))
      min_dist = dist;
  }
  
  return(min_dist);
}

//---------------------------------------------------------------
// Procedure: shift_vert()

void XYGenPolygon::shift_vert(double amt)
{
  m_segl.shift_vert(amt);
  
  for(unsigned int i=0; i<m_cover_polys.size(); i++)
    m_cover_polys[i].shift_vert(amt);
}

//---------------------------------------------------------------
// Procedure: shift_horz()

void XYGenPolygon::shift_horz(double amt)
{
  m_segl.shift_horz(amt);

  for(unsigned int i=0; i<m_cover_polys.size(); i++)
    m_cover_polys[i].shift_horz(amt);
}


//---------------------------------------------------------------
// Procedure: area()

double XYGenPolygon::area() const
{
  double area = 0;
  for(unsigned int i=0; i<m_cover_polys.size(); i++)
    area += m_cover_polys[i].area();

  return(area);
}

//---------------------------------------------------------------
// Procedure: clear()

void XYGenPolygon::clear() 
{
  m_segl.clear();
  m_cover_polys.clear();
}


//---------------------------------------------------------------
// Procedure: clearCoverPolys()

void XYGenPolygon::clearCoverPolys() 
{
  m_cover_polys.clear();
}


//---------------------------------------------------------------
// Procedure: get_spec()
//   Example: border={},fill_color=red,duration=10 #
//            poly=(),fill_color=blue,vertex_size=2 #
//            poly=(),fill_color=blue,vertex_size=2 # ...


string XYGenPolygon::get_spec() const
{
  string spec = get_spec_bdr();

  for(unsigned int i=0; i<m_cover_polys.size(); i++) {
    string poly_spec = m_cover_polys[i].get_spec();
    poly_spec = findReplace(poly_spec, "pts=", "poly=");
    spec += " # " + poly_spec;
  }
  
  return(spec);
}

//---------------------------------------------------------------
// Procedure: get_spec_bdr()
//   Example: pts={},fill_color=red,duration=10,

string XYGenPolygon::get_spec_bdr() const
{
  string spec = m_segl.get_spec();
  spec = findReplace(spec, "pts=", "border=");
  return(spec);
}

//---------------------------------------------------------------
// Procedure: stringToGenPoly()
//   Example: border={},vertex_color=blue,vertex_size=2,edge_color=red #
//            poly={},fill_color=blue,vertex_size=2 #
//            poly={},fill_color=blue,vertex_size=2 #
//      Note: Vertices of the form: 3,4:8,9:0,0 


XYGenPolygon stringToGenPoly(string full_str)
{
  XYGenPolygon null_gpoly;
  XYGenPolygon gpoly;

  cout << "full_str: [" << full_str << "]" << endl;
  
  // Sanity check 1: Must begin with border={
  string part1 = biteStringX(full_str, '#');
  if(!strBegins(part1, "border={"))
    return(null_gpoly);


  biteString(part1, '{');
  string pts_str = biteString(part1, '}');

  // Part 1A: Get the SegList (border) points
  XYSegList segl;
  
  vector<string> svector = parseString(pts_str, ':');
  for(unsigned int i=0; i<svector.size(); i++) {
    string vertex = stripBlankEnds(svector[i]);
    string xstr = biteStringX(vertex, ',');
    string ystr = biteStringX(vertex, ',');
    if(!isNumber(xstr) || !isNumber(ystr))
      return(null_gpoly);
    double xval = atof(xstr.c_str());
    double yval = atof(ystr.c_str());
    segl.add_vertex(xval, yval);
  }

  if(segl.size() == 0)
    return(null_gpoly);
  
  // Part 1B: Get the other SegList properties
  svector = parseString(part1, ',');
  for(unsigned int i=0; i<svector.size(); i++) {
    string param = biteStringX(svector[i], '=');
    string value = svector[i];
    segl.set_param(param, value);
  }

  // Part 2: Read any cover polys
  vector<XYPolygon> cover_polys;

  svector = parseString(full_str, '#');
  for(unsigned int i=0; i<svector.size(); i++) {
    string poly_str = stripBlankEnds(svector[i]);
    poly_str = findReplace(poly_str, "poly=", "pts=");
    cout << "poly_str:[" << poly_str << "]" << endl;
    if(poly_str != "") {
      XYPolygon poly = string2Poly(poly_str);
      if(poly.size() == 0)
	return(null_gpoly);
      cover_polys.push_back(poly);
    }
  }



  if(cover_polys.size() == 0)
    return(null_gpoly);
      
  gpoly.setGenPoly(segl, cover_polys);
  
  return(gpoly);
}

