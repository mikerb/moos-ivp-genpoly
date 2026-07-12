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
  m_keep_fulls = true;
  m_base_branches = 40;
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
// Procedure: clearSolve()

void PathField::clearSolve()
{
  m_segls_drop.clear();
  m_segls_full.clear();
  m_segls_part.clear();
}

//---------------------------------------------------------------
// Procedure: solve()

void PathField::solve(unsigned int amt)
{
  m_segls_drop.clear();

  cout << "PathField::solve()" << amt << endl;

  // Part 1: maintain at least N working Segls  
  XYSegList segl;
  segl.add_vertex(m_sx,m_sy);
  for(unsigned int i=0; i<amt; i++) {
    double rx,ry;
    genleg(m_sx,m_sy, m_dx,m_dy, 40, 40, rx,ry);    
    XYSegList isegl = segl;
    isegl.add_vertex(rx,ry);

    if(!freeSegl(isegl))
      m_segls_drop.push_back(isegl);
    else if(fullSegl(isegl)) {
      isegl.add_vertex(m_dx,m_dy);
      m_segls_full.push_back(isegl);
    }
    else
      m_segls_part.push_back(isegl);    
  }

  clearFulls();
  clearPartials();
}

//---------------------------------------------------------------
// Procedure: solve2()

void PathField::solve2()
{
  m_segls_dead.clear();

  XYSegList segl;
  segl.add_vertex(m_sx, m_sy);
  solve2Aux(segl, 0);
}

//---------------------------------------------------------------
// Procedure: solve2Aux()

void PathField::solve2Aux(XYSegList segl, int depth)
{
  if(depth > 5)
    return;

  
  
  unsigned int branch_amt = 12;

  XYPoint pt = segl.get_last_point();
  double  sx = pt.x();
  double  sy = pt.y();

  for(unsigned int i=0; i<branch_amt; i++) {
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
      solve2Aux(new_segl, depth+1);
    }
  }
}


//---------------------------------------------------------------
// Procedure: clearFulls()
//   Purpose: Drop all the full paths, except the shortest path

void PathField::clearFulls()
{
  if(m_segls_full.size() == 0)
    return;

  XYSegList shortest_segl = m_segls_full[0];
  double shortest_dist = shortest_segl.length();
  for(unsigned int i=1; i<m_segls_full.size(); i++) {
    double ilen = m_segls_full[i].length();
    if(ilen < shortest_dist) {
      shortest_segl = m_segls_full[i];
      shortest_dist = ilen;
    }
  }
  m_segl_shortest = shortest_segl;
  m_dist_shortest = shortest_dist;
  
  if(!m_keep_fulls) {
    m_segls_full.clear();
    m_segls_full.push_back(shortest_segl);
  }
}

//---------------------------------------------------------------
// Procedure: clearPartials()
//   Purpose: Drop all the partial paths that would be longer,
//            even if there were a direct path to the destination
//            from the current last point in the seglist.

void PathField::clearPartials()
{
  // If no actual path has been found, cannot yet clear partials
  if(m_dist_shortest < 0)
    return;

  vector<XYSegList> viable_segls;
  for(unsigned int i=0; i<m_segls_part.size(); i++) {
    XYSegList psegl = m_segls_part[i];
    if(psegl.size() == 0)
      continue;
    XYPoint pt = psegl.get_last_point();
    double dist = hypot(pt.x()-m_dx, pt.y()-m_dy);
    // If best case, direct path, shorter than best full segl, then
    // keep around for further testing
    if((psegl.length() + dist) < m_dist_shortest) 
      viable_segls.push_back(psegl);
  }
  m_segls_part = viable_segls;
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

  cout << "ang_to_dest:" << doubleToString(ang_to_dest,2) << endl;
  
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

bool PathField::freeSegl(XYSegList seglr)
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

bool PathField::fullSegl(XYSegList seglr)
{
  if(m_polys.size() == 0)
    return(true);

  if(seglr.size() == 0)
    return(false);

  seglr.add_vertex(m_dx,m_dy);

  return(freeSegl(seglr));
}

