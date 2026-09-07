/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: CoverUtils.cpp                                      */
/*    DATE: Sep 6th, 2026                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <string>
#include <cstdlib>
#include "CoverUtils.h"
#include "MBUtils.h"

constexpr double PI = 3.14159265358979323846;

using namespace std;

XYSegList genPolygonGP(double cx, double cy, int verts, double maxrad)
{
  XYSegList segl;
  if(verts < 3)
    return(segl);
  
  std::random_device rd;
  std::mt19937 gen(rd());
  
  // Step 1: Generate sorted random angles around the center [0, 2*PI)
  std::uniform_real_distribution<double> angle_dist(0.0, 2 * PI);
  std::vector<double> angles(verts);
  for (int i = 0; i < verts; ++i) {
    angles[i] = angle_dist(gen);
  }
  std::sort(angles.begin(), angles.end());
  
  // Step 2: Assign a random radius for each angle to introduce
  // non-convexity Using a minimum radius ensures the polygon doesn't
  // self-intersect through the origin
  double minrad = maxrad * 0.8; 
  std::uniform_real_distribution<double> radius_dist(minrad, maxrad);
  
  for (int i = 0; i < verts; ++i) {
    double r = radius_dist(gen);
    double x = cx + r * std::cos(angles[i]);
    double y = cy + r * std::sin(angles[i]);
    x = snapToStep(x, 0.001);
    y = snapToStep(y, 0.001);
    segl.add_vertex(x, y);
  }
  
  return(segl);
}
