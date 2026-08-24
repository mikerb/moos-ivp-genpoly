/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: POLY_GUI.h                                           */
/*    DATE: Aug 16th, 2026                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#ifndef XMODEL_HEADER
#define XMODEL_HEADER

#include "PMGen_Dubins.h"
#include "PlatModel.h"
#include "XYGenPolygon.h"

class XModel {
public:
  XModel();
  ~XModel() {}

  // Set Desired Heading
  void setDesHdg(double);
  void modDesHdg(double);

  // Set Desired Speed
  void setDesSpd(double);
  void modDesSpd(double);

  // Set CPA Window
  void setCPAWin(double);
  void modCPAWin(double);

  // Setters for PMGen_Dubins
  void setTurnRad(double);
  void setSpokeDegs(double);
  void modTurnRad(double);
  void modSpokeDegs(double);

  // Setters for Seeding PMGen
  void setOSX(double v) {m_osx = v;}
  void setOSY(double v) {m_osy = v;}
  void setOSH(double v) {m_osh = v;}
  void setOSV(double v) {m_osv = v;}

  void modOSX(double v) {m_osx += v;}
  void modOSY(double v) {m_osy += v;}
  void modOSH(double v) {m_osh += v;}
  void modOSV(double v) {m_osv += v;}
  
  // Setters for XYGenPoly
  void setGenPoly(XYGenPolygon gp) {m_gen_poly=gp;}

  XYGenPolygon getGenPoly() const {return(m_gen_poly);}

  double getDesHdg() const {return(m_des_hdg);}
  double getDesSpd() const {return(m_des_spd);}
  double getCPAWin() const {return(m_cpa_win);}
  double getOSX() const    {return(m_osx);}
  double getOSY() const    {return(m_osy);}
  double getOSH() const    {return(m_osh);}
  double getOSV() const    {return(m_osv);}

  double getTurnRad() const;
  double getSpokeDegs() const;
  
  PlatModel  getPlatModel();
  XYSeglr    getTurnSeglr();

protected:
  double       m_des_hdg;
  double       m_des_spd;

  double       m_cpa_win;
  
  double       m_osx;
  double       m_osy;
  double       m_osh;
  double       m_osv;

  PMGen_Dubins m_pmgen;

  XYGenPolygon m_gen_poly;
};
#endif
