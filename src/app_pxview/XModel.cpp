/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: XModelPV.cpp                                           */
/*    DATE: Aug 16, 2026                                         */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include <cstdio>
#include "XModelPV.h"
#include "MBUtils.h"
#include "AngleUtils.h"

using namespace std;

//-------------------------------------------------------------------
// Constructor()

XModelPV::XModel()
{
  m_des_hdg = 30;
  m_des_spd = 1;
  m_cpa_win = 21;
  
  m_osx = 39;
  m_osy = -75;
  m_osh = 7;
  m_osv = 0.8;

  m_pmgen_dubins.setParam("radius", "15");
  m_pmgen_dubins.setParam("spoke_degs", "12");
}

//-------------------------------------------------------------------
// Procedure: setDesHdg()

void XModelPV::setDesHdg(double dval)
{
  m_des_hdg = angle360(dval);
}

//-------------------------------------------------------------------
// Procedure: modDesHdg()

void XModelPV::modDesHdg(double dval)
{
  m_des_hdg = angle360(m_des_hdg + dval);
}

//-------------------------------------------------------------------
// Procedure: setDesSpd()

void XModelPV::setDesSpd(double dval)
{
  m_des_spd = dval;
  if(m_des_spd < 0)
    m_des_spd = 0;
}

//-------------------------------------------------------------------
// Procedure: modDesSpd()

void XModelPV::modDesSpd(double dval)
{
  m_des_spd = m_des_spd + dval;
}

//-------------------------------------------------------------------
// Procedure: setCPAWin()

void XModelPV::setCPAWin(double dval)
{
  m_cpa_win = dval;
  if(m_cpa_win < 0)
    m_cpa_win = 0;
}

//-------------------------------------------------------------------
// Procedure: modCPAWin()

void XModelPV::modCPAWin(double dval)
{
  m_cpa_win = m_cpa_win + dval;
}

//-------------------------------------------------------------------
// Procedure: setTurnRad()

void XModelPV::setTurnRad(double dval)
{
  if(dval < 0)
    return;
  
  m_pmgen_dubins.setParam("radius", doubleToString(dval));
}

//-------------------------------------------------------------------
// Procedure: setSpokeDegs()

void XModelPV::setSpokeDegs(double dval)
{
  if(dval < 1)
    return;
  
  m_pmgen_dubins.setParam("spoke_degs", doubleToString(dval));
}

//-------------------------------------------------------------------
// Procedure: modTurnRad()

void XModelPV::modTurnRad(double dval)
{
  double curr_turn_rad = m_pmgen_dubins.getParamDbl("radius");
  double new_turn_rad = curr_turn_rad + dval;
  
  m_pmgen_dubins.setParam("radius", doubleToString(new_turn_rad));
}

//-------------------------------------------------------------------
// Procedure: modSpokeDegs()

void XModelPV::modSpokeDegs(double dval)
{
  double curr_degs = m_pmgen_dubins.getParamDbl("spoke_degs");
  double new_degs = curr_degs + dval;
  
  m_pmgen_dubins.setParam("spoke_degs", doubleToString(new_degs));
}

//-------------------------------------------------------------------
// Procedure: getTurnRad()

double XModelPV::getTurnRad() const
{
  return(m_pmgen_dubins.getParamDbl("radius"));
}

//-------------------------------------------------------------------
// Procedure: getSpokeDegs()

double XModelPV::getSpokeDegs() const
{
  return(m_pmgen_dubins.getParamDbl("degs"));
}

//-------------------------------------------------------------------
// Procedure: getPlatModel()

PlatModel XModelPV::getPlatModel()
{
  PlatModel plat_model = m_pmgen_dubins.generate(m_osx, m_osy, m_osh, m_osv);
  return(plat_model);
}

//-------------------------------------------------------------------
// Procedure: getTurnSeglr()

XYSeglr XModelPV::getTurnSeglr()
{
  PlatModel plat_model = getPlatModel();
  XYSeglr seglr = plat_model.getTurnSeglr(m_des_hdg);
  
  return(seglr);
}

