/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: XModel.cpp                                           */
/*    DATE: Aug 16, 2026                                         */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include <cstdio>
#include "XModel.h"
#include "MBUtils.h"
#include "AngleUtils.h"

using namespace std;

//-------------------------------------------------------------------
// Constructor()

XModel::XModel()
{
  m_des_hdg = 90;
  m_osx = 0;
  m_osy = -50;
  m_osh = 45;
  m_osh = 2.5;

  m_pmgen.setParam("radius", "15");
  m_pmgen.setParam("spoke_degs", "12");
}

//-------------------------------------------------------------------
// Procedure: setDesHdg()

void XModel::setDesHdg(double dval)
{
  m_des_hdg = angle360(dval);
}

//-------------------------------------------------------------------
// Procedure: modDesHdg()

void XModel::modDesHdg(double dval)
{
  m_des_hdg = angle360(m_des_hdg + dval);
}

//-------------------------------------------------------------------
// Procedure: setTurnRad()

void XModel::setTurnRad(double dval)
{
  if(dval < 0)
    return;
  
  m_pmgen.setParam("radius", doubleToString(dval));
}

//-------------------------------------------------------------------
// Procedure: setSpokeDegs()

void XModel::setSpokeDegs(double dval)
{
  if(dval < 1)
    return;
  
  m_pmgen.setParam("spoke_degs", doubleToString(dval));
}

//-------------------------------------------------------------------
// Procedure: modTurnRad()

void XModel::modTurnRad(double dval)
{
  double curr_turn_rad = m_pmgen.getParamDbl("radius");
  double new_turn_rad = curr_turn_rad + dval;
  
  m_pmgen.setParam("radius", doubleToString(new_turn_rad));
}

//-------------------------------------------------------------------
// Procedure: modSpokeDegs()

void XModel::modSpokeDegs(double dval)
{
  double curr_degs = m_pmgen.getParamDbl("spoke_degs");
  double new_degs = curr_degs + dval;
  
  m_pmgen.setParam("spoke_degs", doubleToString(new_degs));
}

//-------------------------------------------------------------------
// Procedure: getPlatModel()

PlatModel XModel::getPlatModel()
{
  PlatModel plat_model = m_pmgen.generate(m_osx, m_osy, m_osh, m_osv);
  return(plat_model);
}

//-------------------------------------------------------------------
// Procedure: getTurnSeglr()

XYSeglr XModel::getTurnSeglr()
{
  PlatModel plat_model = getPlatModel();
  XYSeglr seglr = plat_model.getTurnSeglr(m_des_hdg);
  
  return(seglr);
}

