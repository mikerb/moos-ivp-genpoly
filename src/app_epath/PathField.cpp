/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: PathField.cpp                                        */
/*    DATE: July 9th, 2026                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <cmath>
#include "PathField.h"
#include "MBUtils.h"
#include "GeomUtils.h"
#include "AngleUtils.h"

using namespace std;

//---------------------------------------------------------------
// Constructor()

PathField::PathField()
{
  // Init state vars
  m_sx = 0;
  m_sy = 0;
  m_sh = 0;

  m_dx = 0;
  m_dy = 0;

  m_dist_shortest = -1; // -1 means no path found yet.

  // Init config vars
  m_branches   = 40;
  m_focus_poly = -1;
}

//---------------------------------------------------------------
// Procedure: addPoly()

void PathField::addPoly(XYPolygon poly)
{
  if(poly.get_label() == "") {
    string label = "p" + uintToString(m_polys.size());
    poly.set_label(label);
  }
  m_polys.push_back(poly);
}

//---------------------------------------------------------------
// Procedure: focusPoly()

void PathField::focusPoly(double vx, double vy)
{
  int focus_poly = -1;

  double closest_dist = -1;

  for(unsigned int i=0; i<m_polys.size(); i++) {
    if(m_polys[i].contains(vx,vy)) {
      double dist = m_polys[i].dist_to_poly(vx,vy);
      if((closest_dist < 0) || (dist < closest_dist)) {
	focus_poly = i;
	closest_dist = dist;
      }
    }
  }

  // If prior focus poly is selected, treat this as disabel request
  if(focus_poly == m_focus_poly)
    m_focus_poly = -1;
  else if(focus_poly >= 0)
    m_focus_poly = focus_poly;
  
  cout << "Focus_poly:" << focus_poly << endl;
}

//---------------------------------------------------------------
// Procedure: clearSolve()

void PathField::clearSolve()
{
  m_segls_dead.clear();
  m_segl_shortest.clear();
  m_dist_shortest = -1;
}

//---------------------------------------------------------------
// Procedure: solve()

void PathField::solve()
{
  m_segls_dead.clear();

  XYSegList segl;
  segl.add_vertex(m_sx, m_sy);
  solveAux(segl, 0);
}

//---------------------------------------------------------------
// Procedure: solveAux()

void PathField::solveAux(XYSegList segl, int depth)
{
  if(depth > 5)
    return;
  
  XYPoint pt = segl.get_last_point();
  double  sx = pt.x();
  double  sy = pt.y();

  for(unsigned int i=0; i<m_branches; i++) {
    double rx,ry;
    genleg(m_sx,m_sy, m_dx,m_dy, 40, 40, rx,ry);    
    
    XYSegList new_segl = segl;
    new_segl.add_vertex(rx,ry);

    if(!freeSegl(new_segl)) {
      m_segls_dead.push_back(new_segl);
      continue;
    }

    double full_dist = new_segl.length() + hypot(rx-m_dx, ry-m_dy);
    if((m_dist_shortest >= 0) && (full_dist >= m_dist_shortest))
      continue;

    if(fullSegl(new_segl)) {
      new_segl.add_vertex(m_dx,m_dy);      
      m_segl_shortest = new_segl;
      m_dist_shortest = full_dist;
    }
    else {
      solveAux(new_segl, depth+1);
    }
  }
}

//---------------------------------------------------------------
// Procedure: genleg()
//   Purpose: Generate a random leg from the given start position
//            (sx,sy) toward the given destination position (dx,dy).
//            The random leg direction will be +/ angrng degrees
//            from the angle from start to dest.
//            The distance range will +/- pct from default 50% dist.
//            A value of distrng=30 will be anywhere between 20% and 80%
//            of the distance.
//            Legal range for distrng = (0,50], meaning legs will be
//            somewhere between 0 and 100% of the straightline dist
//            between source and dest.

void PathField::genleg(double sx, double sy,
		       double dx, double dy,
		       double angrng, double distrng,
		       double& rx, double& ry)
{
  double ang_to_dest = relAng(sx, sy, dx, dy);
  double dist_to_dest = hypot(sx-dx, sy-dy);

  int int_rand_hdg = rand() % ((int)(angrng * 2 * 100));
  double rand_hdg  = ((double)(int_rand_hdg)) / 100.0;
  
  int int_rand_dist = rand() % ((int)(distrng * 2 * 100));
  double rand_dist  = ((double)(int_rand_dist)) / 100.0;

  // rand_hdg is in the range [0, 2*hdg]. Convert to [-hdg,+hdg].
  rand_hdg -= angrng;
  
  double hdg = ang_to_dest + rand_hdg;

  // rand_dist is in range [0,distrng], e.g., [0,60]
  // Convert to [50-distrng,50+distrng], e.g., [20,80]
  rand_dist = (50-distrng) + rand_dist;

  double dist = (rand_dist / 100) * dist_to_dest;
  
  projectPoint(hdg, dist, sx,sy, rx,ry);
}


//---------------------------------------------------------------
// Procedure: freeSeg()
//   Purpose: Determine if the given line segment intersects with
//            any of the polygon obstacles

bool PathField::freeSeg(double sx, double sy, double dx, double dy)
{
  if(m_polys.size() == 0)
    return(true);

  for(unsigned int i=0; i<m_polys.size(); i++) {
    if(m_polys[i].seg_intercepts(sx,sy, dx,dy))
      return(false);
  }

  return(true);
}

//---------------------------------------------------------------
// Procedure: freeSegl()
//   Purpose: Determine if the given seglist intersects with any
//            of the polygon obstacles

bool PathField::freeSegl(const XYSegList& seglr)
{
  if(m_polys.size() == 0)
    return(true);

  if(seglr.size() == 0)
    return(false);

  if(seglr.size() == 1) {
    double vx = seglr.get_vx(0);
    double vy = seglr.get_vy(0);
    for(unsigned int i=0; i<m_polys.size(); i++) {
      if(m_polys[i].contains(vx,vy))
	return(true);
    }
  }

  for(unsigned int i=0; i<seglr.size()-1; i++) {
    double vx1 = seglr.get_vx(i);
    double vy1 = seglr.get_vy(i);
    double vx2 = seglr.get_vx(i+1);
    double vy2 = seglr.get_vy(i+1);
    if(!freeSeg(vx1,vy1, vx2,vy2))
      return(false);
  }

  return(true);
}

//---------------------------------------------------------------
// Procedure: fullSegl()
//   Purpose: Determine if the given seglist, augmented with an
//            additional leg from the last point to the dest, 
//            represents a collision-free path from start to dest.


bool PathField::fullSegl(XYSegList seglr)
{
  if(m_polys.size() == 0)
    return(true);

  if(seglr.size() == 0)
    return(false);

  seglr.add_vertex(m_dx,m_dy);

  return(freeSegl(seglr));
}

//---------------------------------------------------------------
// Procedure: getPolyPassSide()

string PathField::getPolyPassSide(unsigned int ix)
{
  // Sanity checks
  if(ix >= m_polys.size())
    return("");
  if(m_segl_shortest.length() < 2)
    return("");
  if(m_dist_shortest < 0)
    return("");

  return(seglPassPoly(m_polys[ix], m_segl_shortest));
}

//---------------------------------------------------------------
// Procedure: seglPassPoly()

string PathField::seglPassPoly(XYPolygon poly, XYSegList segl)
{
  if(!poly.is_convex() || (segl.size() < 2))
    return("");

  double sx = segl.get_vx(0);
  double sy = segl.get_vy(0);
  
  double pcx = poly.get_center_x();
  double pcy = poly.get_center_y();
  double ang_to_pcent = relAng(sx,sy, pcx,pcy);

  double star_ang = angle360(ang_to_pcent + 90);
  double port_ang = angle360(ang_to_pcent - 90);
  
  unsigned int xport = crossRaySegl(pcx,pcy,port_ang, segl);
  unsigned int xstar = crossRaySegl(pcx,pcy,star_ang, segl);

  if(xport > 0)
    return("port");
  else if(xstar > 0)
    return("star");
  else
    return("");
}

  
//---------------------------------------------------------------
// Procedure: crossRaySegl()
//   Purpose: Determine if the given ray crosses anywhere in the given
//            SegList and count the number of crosses.

unsigned int PathField::crossRaySegl(double px, double py, double ph,
				     const XYSegList& segl)
{
  unsigned int vsize = segl.size();
  if(vsize < 2)
    return(0);
  
  unsigned int crosses = 0;
  
  // For each line segment
  for(unsigned int i=0; i<vsize-1; i++) {

    double x1 = segl.get_vx(i);
    double y1 = segl.get_vy(i);
    double x2 = segl.get_vx(i+1);
    double y2 = segl.get_vy(i+1);

    double ix, iy;
    bool may_intersect = lineRayCross(px, py, ph, x1, y1, x2, y2, ix, iy);

    if(may_intersect) {
      bool x_intersect = false;
      if((x1==x2) && (x1==ix))
	x_intersect = true;
      else if((x1>x2) && (ix>=x2) && (ix<=x1))
	x_intersect = true;
      else {
	if((ix>=x1) && (ix<=x2))
	  x_intersect = true;
      }

      bool y_intersect = false;
      if((y1==y2) && (y1==iy))
	y_intersect = true;
      else if((y1>y2) && (iy>=y2) && (iy<=y1))
	y_intersect = true;
      else {
	if((iy>=y1) && (iy<=y2))
	  y_intersect = true;
      }

      if(x_intersect && y_intersect)
	crosses++;
    }
  }
  return(crosses);
}  
