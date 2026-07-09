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
  m_sx = 0;
  m_sy = 0;
  m_sh = 0;

  m_dx = 0;
  m_dy = 0;
}

//---------------------------------------------------------------
// addPoly()

void PathField::addPoly(XYPolygon poly)
{
  if(poly.get_label() == "") {
    string label = "p" + uintToString(m_polys.size());
    poly.set_label(label);
  }
  m_polys.push_back(poly);
}


