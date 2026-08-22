/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: BNG_IPFViewer.cpp                                    */
/*    DATE: Feb 13, 2007                                         */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include "MBUtils.h"
#include "ACTable.h"
#include "PlatModelGenerator.h"
#include "FunctionEncoder.h"
#include "BFactoryStatic.h"
#include "BFactoryDynamic.h"
#include "BNG_IPFViewer.h"
#include "IPF_Utils.h"

using namespace std;
 
// ----------------------------------------------------------
// Constructor()
 
BNG_IPFViewer::BNG_IPFViewer(int x, int y, int w, int h, const char *label)
 : Common_IPFViewer(x, y, w, h, label)
{
  // Superclass config settings
  m_polar = 1;
  m_scale = 3;
  setParam("reset_view", "2");
  m_clear_color.setColor("0.285,0.242,0.469");
  m_clear_color.setColor("white");


  // Helm/Behavior mechanics
  m_bhv           = 0;
  m_xmodel        = 0;
  m_info_buffer   = new InfoBuffer(); 
  m_ledger_snap   = new LedgerSnap();

  m_domain.addDomain("course", 0, 359, 360);
  m_domain.addDomain("speed",  0, 5, 51);

  // Analysis of behavior and build IPF
  m_ipf_pieces = 0;

  // Behavior config params
  m_bhv_type       = "opreg26";
  m_rad_ratio      = 1.70;
  m_use_plat_model = false;
  m_minutil_cpa    = 8;
  m_maxutil_cpa    = 15;
  m_plat_model_config = "holonomic";

  // IPF config params
  m_hdg_edge_size = 5;
  m_spd_edge_size = 4;
  m_smart_pcs     = 20;
  m_use_smart_pcs = true;
  m_time_on_leg   = 20;
  
  // Rendering config params
  m_polar_pad  = 0.42;
  m_radius_pad = 1.75;

}

//-------------------------------------------------------------
// Procedure: setXModel()

void BNG_IPFViewer::setXModel(XModel *xmo)
{
  if(m_xmodel)
    delete(m_xmodel);

  m_xmodel = xmo;
}

//-------------------------------------------------------------
// Procedure: setBehaviorType()

bool BNG_IPFViewer::setBehaviorType(string bhv_type)
{
  m_refresh_quadset_aof_pending = true;
  m_refresh_quadset_ipf_pending = true;
  if(bhv_type == "opreg") {
    m_bhv_type = bhv_type;
    return(true);
  }
  
  if(bhv_type == "toggle") {
    if(m_bhv_type == "opreg")
      m_bhv_type = "opreg";
    return(true);
  }

  m_refresh_quadset_aof_pending = false;
  m_refresh_quadset_ipf_pending = false;
  return(false);
}

//-------------------------------------------------------------
// Procedure: draw()

void BNG_IPFViewer::draw()
{
  if(m_refresh_quadset_ipf_pending) {
    m_refresh_quadset_ipf_pending = false;
    resetIPF();
  }
  
  Common_IPFViewer::draw();
  glPushMatrix();
  glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(m_zRot, 0.0f, 0.0f, 1.0f);

  if(m_draw_ipf)
    Common_IPFViewer::drawQuadSet(m_quadset_ipf);
   
  if(m_draw_frame && (m_polar==0))
    drawFrame(); 
  if(m_draw_frame && (m_polar==1)) {
    drawFloor(2500, 0.2, 0.4);
    drawPolarFrame(m_radius_pad);
  }

  glPopMatrix();

  ColorPack cpack4("light_blue");
  drawText2(10, 10, m_bhv_type, cpack4, 12);
  
  glFlush(); 
} 

// ----------------------------------------------------------
// Procedure: getInfo()

string BNG_IPFViewer::getInfo(string param)
{
  if(param == "pieces") 
    return(uintToString(m_ipf_pieces));
  else if(param == "hdg_size") 
    return(uintToString(m_hdg_edge_size));
  else if(param == "spd_size") 
    return(uintToString(m_spd_edge_size));
  if(param == "bhv_type") 
    return(m_bhv_type);
  if(param == "minutil_cpa") 
    return(doubleToStringX(m_minutil_cpa,2));
  if(param == "maxutil_cpa") 
    return(doubleToStringX(m_maxutil_cpa,2));
  if(param == "smart") 
    return(uintToString(m_smart_pcs));
  if(param == "pmodel_config") 
    return(m_plat_model_config);
  if(param == "time_on_leg") 
    return(doubleToStringX(m_time_on_leg));
  
  if(m_bhv)
    return(m_bhv->getInfo(param));
  else
    return("");
}

// ----------------------------------------------------------
// Procedure: resetIPFX()

void BNG_IPFViewer::resetIPFX()
{
  m_draw_ipf = true;
  m_refresh_quadset_ipf_pending = true;
  resetIPF();
}

// ----------------------------------------------------------
// Procedure: resetIPF()

void BNG_IPFViewer::resetIPF()
{
  //-----------------------------------------------------------
  // Part 1: Santity checks
  //-----------------------------------------------------------
  if(!m_draw_ipf || !m_info_buffer)
    return;

  //-----------------------------------------------------------
  // Part 2: Update info buffer and build an IPF from the behavior
  //-----------------------------------------------------------
  if(m_bhv) {
    delete(m_bhv);
    m_bhv = 0;
  }  

  updateInfoBuffer();  
  IvPFunction *ipf = 0;
  cout << "Dbb 4: BNG_IPFViewer -- bhv_type = [" << m_bhv_type << "]" << endl;
  if(m_bhv_type == "opreg26")
    ipf = buildIPF_OpRegion();

  if(!ipf) {
    QuadSet null_quadset;
    m_quadset_ipf = null_quadset;
    m_ipf_pieces = 0;
    redraw();
    return;
  }

  bool ipf_valid = ipf->valid();
  if(!ipf_valid)
    ipf->getPDMap()->valid(true);
  
  bool dense = !m_show_pieces;

  m_quadset_ipf = buildQuadSetFromIPF(ipf, dense);

  m_ipf_pieces = ipf->size();
  delete(ipf); 

  resetRadVisuals();
  m_quadset_ipf.normalize(0, 100);
  m_quadset_ipf.applyColorMap(m_color_map);
  m_quadset_ipf.applyColorIntensity(m_intensity);
  m_quadset_ipf.interpolate(1);
  m_quadset_ipf.applyScale(m_scale);

  if(m_polar == 0)
    m_quadset_ipf.applyTranslation(-250, -250);
  else if(m_polar == 1)
    m_quadset_ipf.applyPolar(m_rad_ratio*m_radius_pad, 1, m_polar_pad);
  else if(m_polar == 2) 
    m_quadset_ipf.applyPolar(m_rad_ratio*m_radius_pad, 2, m_polar_pad);

  redraw();
}

// ----------------------------------------------------------
// Procedure: setMinUtilCPA()

void BNG_IPFViewer::setMinUtilCPA(double val)
{
  if(val < 0)
    val = 0;
  if(val > m_maxutil_cpa)
    val = m_maxutil_cpa;
  m_minutil_cpa = val;
  m_refresh_quadset_ipf_pending = true;
}


// ----------------------------------------------------------
// Procedure: setMaxUtilCPA()

void BNG_IPFViewer::setMaxUtilCPA(double val)
{
  if(val < 0)
    val = 0;
  if(val < m_minutil_cpa)
    val = m_minutil_cpa;
  m_maxutil_cpa = val;
  m_refresh_quadset_ipf_pending = true;
}

// ----------------------------------------------------------
// Procedure: modMinUtilCPA()

void BNG_IPFViewer::modMinUtilCPA(double val)
{
  setMinUtilCPA(m_minutil_cpa + val);
}

// ----------------------------------------------------------
// Procedure: modMaxUtilCPA()

void BNG_IPFViewer::modMaxUtilCPA(double val)
{
  setMaxUtilCPA(m_maxutil_cpa + val);
}

// ----------------------------------------------------------
// Procedure: modPolarPad()

void BNG_IPFViewer::modPolarPad(double val)
{
  m_polar_pad += val;
  m_refresh_quadset_ipf_pending = true;
}

// ----------------------------------------------------------
// Procedure: setUsePlatModel()

bool BNG_IPFViewer::setUsePlatModel(string str)
{
  return(setBooleanOnString(m_use_plat_model, str));
}

// ----------------------------------------------------------
// Procedure: setUseSmartPcs()

bool BNG_IPFViewer::setUseSmartPcs(string str)
{
  return(setBooleanOnString(m_use_smart_pcs, str));
}

// ----------------------------------------------------------
// Procedure: modTOL()

void BNG_IPFViewer::modTOL(double delta)
{
  m_time_on_leg += delta;
  if(m_time_on_leg < 0)
    m_time_on_leg = 0;
}

// ----------------------------------------------------------
// Procedure: modSmartPcs()

void BNG_IPFViewer::modSmartPcs(int delta)
{
  if(((int)(m_smart_pcs) + delta) >= 0)
    m_smart_pcs += (unsigned int)(delta);
}

// ----------------------------------------------------------
// Procedure: spawnBehavior()

IvPBehavior* BNG_IPFViewer::spawnBehavior(string bhv)
{
  if(m_bhv) {
    delete(m_bhv);
    m_bhv = 0;
  }
  
  // Part 1: Try to make the behavior from static set
  BFactoryStatic bhv_factory_static;
  bhv_factory_static.setDomain(m_domain);

  IvPBehavior *behavior_stat = bhv_factory_static.newBehavior(bhv);
  if(behavior_stat)
    return(behavior_stat);

  // Part 2: Try to make the behavior dynamically
  BFactoryDynamic bhv_factory_dynamic;
  bhv_factory_dynamic.setDomain(m_domain);
  bhv_factory_dynamic.loadEnvVarDirectories("IVP_BEHAVIOR_DIRS");
  
  IvPBehavior *behavior_dyn = bhv_factory_dynamic.newBehavior(bhv);
  if(behavior_dyn)
    return(behavior_dyn);
  
  cout << "Failed to make a behavior: " << bhv << endl;
  return(0); 
}   

// ----------------------------------------------------------
// Procedure: buildIPF_OpRegion()

IvPFunction *BNG_IPFViewer::buildIPF_OpRegion()
{
  // Part 1: Create the behavior or die trying
  m_bhv = spawnBehavior("BHV_OpRegionV26");
  if(!m_bhv)
    return(0); 

  if(!m_xmodel)
    return(0);
 
  // Part 2: Create the PlatModel and pass to the behavior
  PlatModel plat_model = m_xmodel->getPlatModel();
  m_bhv->setPlatModel(plat_model);

  // Part 3: Update the InfoBuffer
  m_bhv->setInfoBuffer(m_info_buffer);

  XYGenPolygon core_poly = m_xmodel->getGenPoly();
  string core_poly_str = core_poly.get_spec();

  
  // Part 4: Set the Behavior parameters
  string piece = "discrete@course:";
  piece += uintToString(m_hdg_edge_size);
  piece += ",speed:";
  piece += uintToString(m_spd_edge_size);

  bool ok = true;
  ok = ok && m_bhv->setParam("core_poly", core_poly_str);
  ok = ok && m_bhv->setParam("build_info", "clear");
  ok = ok && m_bhv->setParam("build_info", "uniform_piece=" + piece);
  ok = ok && m_bhv->setParam("build_info", "uniform_grid=" + piece);

  ok = ok && m_bhv->setParam("min_util_eta", "10");
  ok = ok && m_bhv->setParam("max_util_eta", "30");
  
  if(m_use_smart_pcs) {
    string str = uintToString(m_smart_pcs);
    ok = ok && m_bhv->setParam("build_info", "smart_amount=" + str);
  }
  
  if(!ok) {
    cout << "BHV_OpRegionV26 Init Failure" << endl;
    return(0);
  }

  m_bhv->onSetParamComplete();

  // Part 3: Generate and return the IvPFunction
  IvPFunction *ipf = m_bhv->onRunState();
  if(!ipf)
    cout << "BHV_OpRegionV26: Null IvP Function!!!" << endl;
  return(ipf);
}

// ----------------------------------------------------------
// Procedure: updateInfoBuffer()
//   Purpose: Update the InfoBuffer to be used by the behavior

void BNG_IPFViewer::updateInfoBuffer()
{
  // Sanity Check
  if(!m_xmodel)
    return;
  
  m_info_buffer->setValue("NAV_X",       m_xmodel->getOSX());
  m_info_buffer->setValue("NAV_Y",       m_xmodel->getOSY());
  m_info_buffer->setValue("NAV_HEADING", m_xmodel->getOSH());
  m_info_buffer->setValue("NAV_SPEED",   m_xmodel->getOSV());
}



// ----------------------------------------------------------
// Procedure: setHdgEdgeSize()

void BNG_IPFViewer::setHdgEdgeSize(unsigned int val)
{
  m_hdg_edge_size = val;
  if(m_hdg_edge_size < 1)
    m_hdg_edge_size = 1;
  if(m_hdg_edge_size > 90)
    m_hdg_edge_size = 90;
}
// ----------------------------------------------------------
// Procedure: modHdgEdgeSize()

void BNG_IPFViewer::modHdgEdgeSize(int val)
{
  setHdgEdgeSize(m_hdg_edge_size + val);
}

// ----------------------------------------------------------
// Procedure: setSpdEdgeSize()

void BNG_IPFViewer::setSpdEdgeSize(unsigned int val)
{
  //cout << "SetSpdEdgeSize() " << val << endl;
  m_spd_edge_size = val;
  if(m_spd_edge_size < 1)
    m_spd_edge_size = 1;
  if(m_spd_edge_size > 25)
    m_spd_edge_size = 25;
}

// ----------------------------------------------------------
// Procedure: modSpdEdgeSize()

void BNG_IPFViewer::modSpdEdgeSize(int val)
{
  //cout << "modSpdEdgeSize() " << val << endl;
  setSpdEdgeSize(m_spd_edge_size + val);
}


// ----------------------------------------------------------
// Procedure: clearBehaviorModes()

void BNG_IPFViewer::clearBehaviorModes()
{
  m_curr_bhv_mode = "";
  m_curr_bhv_submode = "";

  if(m_bhv) {
    delete(m_bhv);
    m_bhv = 0;
  }
}

