/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: CoverEngine.cpp                                      */
/*    DATE: Nov 28th, 2025                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <cmath>
#include "CoverEngine.h"
#include "MBUtils.h"
#include "GeomUtils.h"
#include "AngleUtils.h"
#include "ConvexHullGenerator.h"

using namespace std;

//---------------------------------------------------------------
// Constructor()

CoverEngine::CoverEngine()
{
  m_method   = "shallow";
  m_collapse = true;
  m_verbose  = false;
}

//---------------------------------------------------------------
// Procedure: setPoints()

bool CoverEngine::setPoints(vector<double> vx, vector<double> vy)
{
  // Sanity check 
  if(vx.size() != vy.size())
    return(false);

  // Create an XYSegList from the points
  XYSegList segl;
  for(unsigned int i=0; i<vx.size(); i++) 
    segl.add_vertex(vx[i], vy[i]);

  return(setPoints(segl));
}

//---------------------------------------------------------------
// Procedure: setPoints(XYSegList)

bool CoverEngine::setPoints(XYSegList segl)
{
  if(segl.segs_cross())
    return(false);

  if(segl.is_clockwise())
    segl.reverse();

  clear();
  for(unsigned int i=0; i<segl.size(); i++) {
    m_vx.push_back(segl.get_vx(i));
    m_vy.push_back(segl.get_vy(i));
  }
  return(true);
}


//---------------------------------------------------------------
// Procedure: clear()

void CoverEngine::clear()
{
  m_vx.clear();
  m_vy.clear();
}

//---------------------------------------------------------------
// Procedure: setSolveMethod()

void CoverEngine::setSolveMethod(string method)
{
  if((method == "shallow") || (method == "deep") || (method == "deepest"))
    m_method = method;
}

//---------------------------------------------------------------
// Procedure: getGenPoly()

XYGenPolygon CoverEngine::getGenPoly()
{
  //-------------------------------------------------
  // Part 1: Determine the cover polygons
  //-------------------------------------------------
  vector<XYPolygon> cover_polys;
  unsigned int poly_count = 0;
  unsigned int min_so_far = 0;
  string gap;
  cover_polys = coverRecursive(m_vx, m_vy, gap, poly_count, min_so_far);

  if(m_collapse)
    collapseNeighbors(cover_polys);
  
  
  //-------------------------------------------------
  // Part 2: Create the XYGenPolygon (segl + polys)
  //-------------------------------------------------
  // Part 2A: Create an XYSegList from the points
  XYSegList segl;
  for(unsigned int i=0; i<m_vx.size(); i++) 
    segl.add_vertex(m_vx[i], m_vy[i]);

  // Part 2B: Create the GenPoly with the two core components
  XYGenPolygon gpoly;
  gpoly.setGenPoly(segl, cover_polys);

  return(gpoly);
}


//---------------------------------------------------------------
// Procedure: coverRecursive()

vector<XYPolygon> CoverEngine::coverRecursive(vector<double> vx,
					      vector<double> vy,
					      string gap, 
					      unsigned int poly_count, 
					      unsigned int& min_so_far)
{
  gap = gap + "  ";
  if(m_verbose) {
    cout << gap << "S-Count:" << poly_count << ", min_so_far: "; 
    cout << min_so_far << "----------- verts:" << vx.size() << endl;
  }
  
  // cout << "In coverRecursive(" << vx.size() << ")" << endl;
  vector<XYPolygon> cover_polys;
  if((vx.size() != vy.size()) || (vx.size() < 3)) {
    if(m_verbose)
      cout << gap << "END ++++++" << endl;
    return(cover_polys);
  }

  bool all_thru = false;
  for(unsigned int i=0; (i<vx.size() && !all_thru); i++) {
    vector<XYPolygon> cover_polys_i;
    if(!okTermIXB(vx, vy, 2)) {
      shiftVertices(vx, vy);
      continue;
    }

    vector<double> nvx = vx;
    vector<double> nvy = vy;
    
    all_thru = true;
    for(unsigned int j=3; j<vx.size(); j++) {
      if(!okTermIX(vx, vy, j)) {
	all_thru = false;
	XYPolygon new_poly = carvePoly(nvx, nvy, j-1);
	cover_polys_i.push_back(new_poly);
	break;
      }
    }
    
    bool found_solution = true;
    if(all_thru) {
      XYPolygon new_poly = carvePoly(nvx, nvy, nvx.size()-1); 
      if(new_poly.size() != 0) {
	cover_polys_i.push_back(new_poly);
      }
    }
    else {
      unsigned int zag_uint_count = zagCount(nvx, nvy);
      int zag_int_count = (int)((zag_uint_count + 1)/2);

      int thresh = 2;
      if(m_method == "deep")
	thresh = 1;
      if(m_method == "deepest")
	thresh = 0;

      unsigned int new_count = poly_count + thresh + zag_int_count;
      if((min_so_far == 0) || (new_count < min_so_far)) {
	// Make recursive call
	vector<XYPolygon> polys;
	polys = coverRecursive(nvx, nvy, gap, new_count, min_so_far); 
	if(polys.size() == 0)
	  found_solution = false;
	if(m_verbose) 
	  cout << gap << "PR poly_count:" << poly_count << ", polys.size(): " <<
	    polys.size();

	cover_polys_i.insert(cover_polys_i.end(), polys.begin(), polys.end());

	if(m_verbose)
	  cout << ", polys_i.size():" << cover_polys_i.size() << endl;
      }
      else
	found_solution = false;
    }

    if((cover_polys_i.size() > 0) && found_solution) {
      if((cover_polys.size() == 0) || (cover_polys_i.size() < cover_polys.size())) {
	cover_polys = cover_polys_i;

	if((min_so_far == 0) ||
	   ((cover_polys.size() + poly_count) < min_so_far)) {

	  min_so_far = cover_polys.size() + poly_count;
	  if(m_verbose) {
	    cout << gap << "J-Count:" << poly_count;
	    cout << ", glm:" << min_so_far << endl;
	  }
	}

      }
    }

    shiftVertices(vx, vy);
  }

  if(m_verbose)
    cout << gap << "E-Count:" << poly_count << ", cover_polys.size():" <<
      cover_polys.size() << ", glm:" << min_so_far << endl;
  
  return(cover_polys);
}
  

//---------------------------------------------------------------
// Procedure: mergePolys()

XYPolygon CoverEngine::mergePolys(const XYPolygon& poly1,
				  const XYPolygon& poly2)
{
  XYPolygon null_poly;

  if(!poly1.is_convex() || !poly2.is_convex())
    return(null_poly);
  
  ConvexHullGenerator generator;
  for(unsigned int i=0; i<poly1.size(); i++)
    generator.addPoint(poly1.get_point(i));
  for(unsigned int i=0; i<poly2.size(); i++)
    generator.addPoint(poly2.get_point(i));

  XYPolygon hull_poly = generator.generateConvexHull();

  double hull_area  = hull_poly.area();
  double comb_area  = poly1.area() + poly2.area();

  hull_area = snapToStep(hull_area, 0.001);
  comb_area = snapToStep(comb_area, 0.001);

  if(m_verbose) {
    cout << "hull=" << doubleToStringX(hull_area,7);
    cout << ", comb=" << doubleToStringX(comb_area,7) << endl;
  }
  
  if(hull_area == comb_area) {
    if(m_verbose)
      cout << "merge to hull!!!" << endl;
    return(hull_poly);
  }
 
  return(null_poly);
}


//---------------------------------------------------------------
// Procedure: collapseNeighors()

void CoverEngine::collapseNeighbors(vector<XYPolygon>& polys)
{
  if(polys.size() <= 1)
    return;

  for(unsigned int i=0; i<polys.size(); i++)
    polys[i].determine_convexity();
  
  bool done = false;
  while(!done) {
    bool merge_found = false;

    for(unsigned int i=0; i<polys.size()-1; i++) {
      for(unsigned int j=i+1; j<polys.size(); j++) {
	XYPolygon merged_poly = mergePolys(polys[i], polys[j]);

	if(merged_poly.size() != 0) {
	  polys[i] = merged_poly;
	  polys[j] = XYPolygon();
	  merge_found = true;
	}
      }
    }

    if(!merge_found)
      done = true;
    else {
      vector<XYPolygon> new_polys;
      for(unsigned int i=0; i<polys.size(); i++) {
	if(polys[i].size() != 0)
	  new_polys.push_back(polys[i]);
      }
      polys = new_polys;
    }
  }
}
    
  

//---------------------------------------------------------------
// Procedure: okTermIX()
//   Purpose: See if we can make a convex poly from the first few
//            points, given a vector of x-y points and an index ix.
//            The candidate poly will be at least 3 vertices, so ix
//            will be >= 2. If we can make a convext polygon from
//            vertices 0, 1, ..., ix, then simply return true. 
//            Also check to see if none of the later vertices are
//            contained within the convex poly created.
//
//                                                                  
//       v4                                                           
//        o-------------o v2
//        |           /                                              
//        |          /                                                  
//        |        /                                                  
//        o------o
//        v0     v1


bool CoverEngine::okTermIX(vector<double> vx, vector<double> vy, unsigned int ix)
{
  // Sanity check
  if(ix >= vx.size())
    return(false);
  
  // For initial 3 vertex poly, make sure it is a left turn
  if(ix == 2)
    if(!threePointTurnLeft(vx[0],vy[0], vx[1],vy[1], vx[2],vy[2])) 
      return(false);
  
  
  // Part 1: Build a poly from verts [0...ix], check for convexity
  XYPolygon poly;
  for(unsigned int i=0; i<=ix; i++)
    poly.add_vertex(vx[i], vy[i]);
   
  poly.determine_convexity();
  if(!poly.is_convex()) 
    return(false);

  // Part 2: Check that no remaining verts are within the poly
  for(unsigned int i=ix+1; i<vx.size(); i++)
    if(poly.contains(vx[i], vy[i]))
      return(false);
  
  return(true);
}

bool CoverEngine::okTermIXB(vector<double> vx, vector<double> vy, unsigned int ix)
{
  // Sanity check
  if(ix >= vx.size())
    return(false);
  
  // For initial 3 vertex poly, make sure it is a left turn
  if(ix == 2) 
    if(!threePointTurnLeft(vx[0],vy[0], vx[1],vy[1], vx[2],vy[2]))
      return(false);
  

  // Part 1: Build a poly from verts [0...ix], check for convexity
  XYPolygon poly;
  for(unsigned int i=0; i<=ix; i++)
    poly.add_vertex(vx[i], vy[i]);
   
  poly.determine_convexity();
  if(!poly.is_convex())
    return(false);
  
  // Part 2: Check that no remaining verts are within the poly
  for(unsigned int i=ix+1; i<vx.size(); i++)
    if(poly.contains(vx[i], vy[i]))
      return(false);
  
  return(true);
}

//---------------------------------------------------------------
// Procedure: carvePoly()
//
//                                                                  
//  v6       v5                                                 |
//  o-------o                                                   |    
//  |         \                                                 |
//  |           \                                               |
//  |             \ v4                                          |
//  |               o-------------o v2                          |
//  |               |           /                               |
//  |               |          /                                |
//  |               |        /                                  |
//  o---------------o------o                                    |
//  v7              v0     v1                                   |
//                                                              |
//         |                                                    |
//         V                                                    |
//                                                              |
//                                                              |
//  v3       v2                                                 |
//  o-------o                                                   |
//  |         \                                                 |
//  |           \                                               |
//  |             \  v1           v4                            |
//  |               o             o-------------o v2            |
//  |               |             |           /                 |
//  |               |             |          /                  |
//  |               |             |        /                    |
//  o---------------o             o------o                      |
//  v4              v0            v0     v1




XYPolygon CoverEngine::carvePoly(vector<double>& vx, vector<double>& vy, unsigned ix)
{
  XYPolygon null_poly;
  // Sanity check 1: Index needs to be in range
  if(ix >= vx.size())
    return(null_poly);
  
  // Create the carved off poly
  XYPolygon new_poly;
  for(unsigned int i=0; i<=ix; i++)
    new_poly.add_vertex(vx[i], vy[i]);

  // The remainder, still possibly non-convex poly
  vector<double> new_vx;
  vector<double> new_vy;
  new_vx.push_back(vx[0]);
  new_vy.push_back(vy[0]);
  new_vx.push_back(vx[ix]);
  new_vy.push_back(vy[ix]);
  
  for(unsigned int i=ix+1; i<vx.size(); i++) {
    new_vx.push_back(vx[i]);
    new_vy.push_back(vy[i]);
  }

  vx = new_vx;
  vy = new_vy;

  return(new_poly);
}

//---------------------------------------------------------------
// Procedure: zagCount()
//      Note: A zag is a righthand turn that followed a non-righthand turn
//            An approximation of polys needed to cover

unsigned int CoverEngine::zagCount(vector<double> vx, vector<double> vy)
{
  // Sanity checks
  if((vx.size() != vy.size()) || (vx.size() < 4))
    return(0);
  
  unsigned int zags = 0;
  
  bool prev_turn_left = false;
  for(unsigned int i=0; i<=vx.size(); i++) {
    unsigned int ix1 = i;
    unsigned int ix2 = i + 1;
    unsigned int ix3 = i + 2;
    
    if(i == (vx.size()-2))
      ix3 = 0;
    else if(i == (vx.size()-1)) {
      ix2 = 0;
      ix3 = 1;
    }
    else if(i == vx.size()) {
      ix1 = 0;
      ix2 = 1;
      ix3 = 2;
    }
    
    bool is_left = threePointTurnLeft(vx[ix1],vy[ix1], vx[ix2],vy[ix2], vx[ix3],vy[ix3]);
    if(is_left)
      prev_turn_left = true;
    else {
      if(prev_turn_left == true)
	zags++;
      prev_turn_left = false;
    }
  }
  
  return(zags);
}

