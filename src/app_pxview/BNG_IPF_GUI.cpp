/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: BNG_IPF_GUI.cpp                                      */
/*    DATE: May 21, 2013                                         */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "BNG_IPF_GUI.h"
#include "POLY_GUI.h"
#include "MBUtils.h"
#include "FL/fl_ask.H"

using namespace std;

//----------------------------------------------------------------
// Constructor()

BNG_IPF_GUI::BNG_IPF_GUI(int wid, int hgt, const char *label)
  : Common_IPF_GUI(wid, hgt, label) 
{
  this->user_data((void*)(this));
  this->when(FL_WHEN_CHANGED);  
  this->begin();

  // Set minimum size 800x800, maximum size 1800x1800  
  this->size_range(800,800, 3000,1800, 0,0, 1);
  
  m_parent_gui  = 0;
  m_ipf_viewer1 = 0;
  m_ipf_viewer2 = 0;
  augmentMenu();
    
  initWidgets();
  resizeWidgetsShape();
  resizeWidgetsText();
  updateXY();

  this->end();
  this->resizable(this);
  this->show();
}


//-------------------------------------------------------------------
// Destructor()
//
// Note: Must carefully implement since master GUI may create
//       and destroy instances of this GUI all in same session

BNG_IPF_GUI::~BNG_IPF_GUI()
{
  // Row 1 --------------------------
  // Viewer 1
  if(m_fld_tol1)
    delete(m_fld_tol1);
  if(m_but_tol1)
    delete(m_but_tol1);
  if(m_but_tol_add1)
    delete(m_but_tol_add1);
  if(m_but_tol_sub1)
    delete(m_but_tol_sub1);
  
  // Viewer 2 ----
  if(m_fld_tol2)
    delete(m_fld_tol2);
  if(m_but_tol2)
    delete(m_but_tol2);
  if(m_but_tol_add2)
    delete(m_but_tol_add2);
  if(m_but_tol_sub2)
    delete(m_but_tol_sub2);


  // Row 2 --------------------------
  // Viewer 1  
  if(m_fld_pieces1)
    delete(m_fld_pieces1);
  if(m_but_show_pcs1)
    delete(m_but_show_pcs1);

  if(m_fld_smart1)
    delete(m_fld_smart1);
  if(m_but_smart1)
    delete(m_but_smart1);
  if(m_but_smart_add1)
    delete(m_but_smart_add1);
  if(m_but_smart_sub1)
    delete(m_but_smart_sub1);

  
  // Viewer 2 ----
  if(m_fld_pieces2) 
    delete(m_fld_pieces2);
  if(m_but_show_pcs2)
    delete(m_but_show_pcs2);

  if(m_fld_smart2)
    delete(m_fld_smart2);
  if(m_but_smart2)
    delete(m_but_smart2);
  if(m_but_smart_add2)
    delete(m_but_smart_add2);
  if(m_but_smart_sub2)
    delete(m_but_smart_sub2);

  // Row 3 --------------------------
  // Viewer 1
  if(m_fld_hdg_size1)
    delete(m_fld_hdg_size1);
  if(m_but_hsz_add1)
    delete(m_but_hsz_add1);
  if(m_but_hsz_sub1)
    delete(m_but_hsz_sub1);
  
  if(m_fld_minutil_cpa1)
    delete(m_fld_minutil_cpa1);
  if(m_but_minutil_add1)
    delete(m_but_minutil_add1);
  if(m_but_minutil_sub1)
    delete(m_but_minutil_sub1);

  // Viewer 2 ----
  if(m_fld_hdg_size2)
    delete(m_fld_hdg_size2);
  if(m_but_hsz_add2)
    delete(m_but_hsz_add2);
  if(m_but_hsz_sub1)
    delete(m_but_hsz_sub2);

  if(m_fld_minutil_cpa2)
    delete(m_fld_minutil_cpa2);
  if(m_but_minutil_add2)
    delete(m_but_minutil_add2);
  if(m_but_minutil_sub2)
    delete(m_but_minutil_sub2);  

  // Row 4 --------------------------
  if(m_fld_spd_size1)
    delete(m_fld_spd_size1);
  if(m_but_ssz_add1)
    delete(m_but_ssz_add1);
  if(m_but_ssz_sub1)
    delete(m_but_ssz_sub1);
  
  if(m_fld_maxutil_cpa1)
    delete(m_fld_maxutil_cpa1);
  if(m_but_maxutil_add1)
    delete(m_but_maxutil_add1);
  if(m_but_maxutil_sub1)
    delete(m_but_maxutil_sub1);

  // Viewer 2 ----
  if(m_fld_spd_size2)
    delete(m_fld_spd_size2);
  if(m_but_ssz_add2)
    delete(m_but_ssz_add2);
  if(m_but_ssz_sub2)
    delete(m_but_ssz_sub2);

  if(m_fld_maxutil_cpa2)
    delete(m_fld_maxutil_cpa2);
  if(m_but_maxutil_add2)
    delete(m_but_maxutil_add2);
  if(m_but_maxutil_sub2)
    delete(m_but_maxutil_sub2);


  // Row 5 --------------------------  
  if(m_fld_plat_model1)
    delete(m_fld_plat_model1);

  // Viewer 2 ----
  if(m_fld_plat_model2)
    delete(m_fld_plat_model2);

  // Row 6 --------------------------  
  if(m_but_platmod1)
    delete(m_but_platmod1);
  if(m_fld_bhv_debug1)
    delete(m_fld_bhv_debug1);

  // Viewer 2 ----
  if(m_but_platmod2)
    delete(m_but_platmod2);
  if(m_fld_bhv_debug2)
    delete(m_fld_bhv_debug2);
}


//--------------------------------------------------------------------------- 
// Procedure: setDomain()

void BNG_IPF_GUI::setDomain(IvPDomain domain)
{ 
  if(m_ipf_viewer1) 
    m_ipf_viewer1->setDomain(domain);
  if(m_ipf_viewer2)
    m_ipf_viewer2->setDomain(domain);
  updateXY();
}

//--------------------------------------------------------------------------- 
// Procedure: setXModel()

void BNG_IPF_GUI::setXModel(XModel *xmo)
{
  if(m_ipf_viewer1) 
    m_ipf_viewer1->setXModel(xmo);
  if(m_ipf_viewer2)
    m_ipf_viewer2->setXModel(xmo);
  updateXY();
}

//--------------------------------------------------------------------------- 
// Procedure: updatedXModel()

void BNG_IPF_GUI::updatedXModel()
{
  if(m_ipf_viewer1) 
    m_ipf_viewer1->resetIPF();
  if(m_ipf_viewer2)
    m_ipf_viewer2->resetIPF();
  updateXY();
}

//-------------------------------------------------------------
// Procedure: resize()

void BNG_IPF_GUI::resize(int lx, int ly, int lw, int lh)
{
  Fl_Window::resize(lx, ly, lw, lh);
  resizeWidgetsShape();
  resizeWidgetsText();
}

 
//-------------------------------------------------------------
// Procedure: augmentMenu()

void BNG_IPF_GUI::augmentMenu() 
{
  //==============================================================
  // Behaviors 
  //==============================================================
  m_menubar->add("IPF/Pad++", '\\',
		 (Fl_Callback*)BNG_IPF_GUI::cb_PadIPF, (void*)8, 0);
  m_menubar->add("IPF/Pad--", '/',
		 (Fl_Callback*)BNG_IPF_GUI::cb_PadIPF, (void*)7, 0);

  m_menubar->add("Left/BHV_Type/CPA AvoidCollision", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType1, (void*)15, 0);
  m_menubar->add("Left/BHV_Type/COLREGS_V22", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType1, (void*)16, 0);
  m_menubar->add("Left/BHV_Type/COLREGS_V26", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType1, (void*)17, 0);
  m_menubar->add("Left/BHV_Type/Waypoint", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType1, (void*)19, 0);

  m_menubar->add("Right/BHV_Type/CPA AvoidCollision", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType2, (void*)15, 0);
  m_menubar->add("Right/BHV_Type/COLREGS_V22", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType2, (void*)16, 0);
  m_menubar->add("Right/BHV_Type/COLREGS_V26", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType2, (void*)17, 0);
  m_menubar->add("Right/BHV_Type/Waypoint", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType2, (void*)19, 0);

  m_menubar->add("Both/BHV_Type/CPA AvoidCollision", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType12, (void*)15, 0);
  m_menubar->add("Both/BHV_Type/COLREGS_V22", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType12, (void*)16, 0);
  m_menubar->add("Both/BHV_Type/COLREGS_V26", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType12, (void*)17, 0);
  m_menubar->add("Both/BHV_Type/Waypoint", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_BehaviorType12, (void*)19, 0);
  

  m_menubar->add("Left/Scale/Scale 0", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF1, (void*)0, 0);
  m_menubar->add("Left/Scale/Scale 1", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF1, (void*)1, 0);
  m_menubar->add("Left/Scale/Scale 2", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF1, (void*)2, 0);
  m_menubar->add("Left/Scale/Scale 3", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF1, (void*)3, 0);
  m_menubar->add("Left/Scale/Scale 4", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF1, (void*)4, 0);
  m_menubar->add("Left/Scale/Scale 5", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF1, (void*)5, 0);
  m_menubar->add("Left/Scale/Scale 5", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF1, (void*)6, 0);

  m_menubar->add("Right/Scale/Scale 0", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF2, (void*)0, 0);
  m_menubar->add("Right/Scale/Scale 1", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF2, (void*)1, 0);
  m_menubar->add("Right/Scale/Scale 2", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF2, (void*)2, 0);
  m_menubar->add("Right/Scale/Scale 3", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF2, (void*)3, 0);
  m_menubar->add("Right/Scale/Scale 4", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF2, (void*)4, 0);
  m_menubar->add("Right/Scale/Scale 5", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF2, (void*)5, 0);
  m_menubar->add("Right/Scale/Scale 6", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF2, (void*)6, 0);

  m_menubar->add("Both/Scale/Scale 0", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF12, (void*)0, 0);
  m_menubar->add("Both/Scale/Scale 1", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF12, (void*)1, 0);
  m_menubar->add("Both/Scale/Scale 2", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF12, (void*)2, 0);
  m_menubar->add("Both/Scale/Scale 3", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF12, (void*)3, 0);
  m_menubar->add("Both/Scale/Scale 4", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF12, (void*)4, 0);
  m_menubar->add("Both/Scale/Scale 5", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF12, (void*)5, 0);
  m_menubar->add("Both/Scale/Scale 6", 0,
		 (Fl_Callback*)BNG_IPF_GUI::cb_SetScaleIPF12, (void*)6, 0);


}

//----------------------------------------------------------------
// Procedure: clearBehaviorModes()

void BNG_IPF_GUI::clearBehaviorModes()
{
  if(m_ipf_viewer1)
    m_ipf_viewer1->clearBehaviorModes();
  if(m_ipf_viewer2)
    m_ipf_viewer2->clearBehaviorModes();
}
 
//----------------------------------------------------------------
// Procedure: handle()

int BNG_IPF_GUI::handle(int event) 
{
  switch(event) {
  case FL_KEYDOWN:
 
    // Contact 1 Sec forward/backward
    if((Fl::event_key() == ']') &&
       (Fl::event_state() == FL_ALT) &&
       (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(31);
    else if((Fl::event_key() == '[') &&
	    (Fl::event_state() == FL_ALT) &&
	    (Fl::event_state() == FL_CTRL)) 
      m_parent_gui->handleActionSubGUI(32);

    // Ownship AND Contact 0.1 Sec forward/Backward
    else if((Fl::event_key() == ']') &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(11);
    else if((Fl::event_key() == '[') &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(12);

    // Ownship 0.1 Sec forward/Backward
    else if((Fl::event_key() == ']') &&
	    (Fl::event_state() == FL_ALT))
      m_parent_gui->handleActionSubGUI(21);
    else if((Fl::event_key() == '[') &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(22);

    // Ownship AND Contact   1 Sec forward/Backward
    else if(Fl::event_key() == ']') 
      m_parent_gui->handleActionSubGUI(11);
    else if(Fl::event_key() == '[')
      m_parent_gui->handleActionSubGUI(12);

    else if((Fl::event_key() == 'a') &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(120);
    else if((Fl::event_key() == 'z') &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(121);

    else if(Fl::event_key() == 'a')
      m_parent_gui->handleActionSubGUI(130);
    else if(Fl::event_key() == 'z')
      m_parent_gui->handleActionSubGUI(131);

    else if(Fl::event_key() == 'm')
      m_parent_gui->handleActionSubGUI(140);
    else if(Fl::event_key() == 'n')
      m_parent_gui->handleActionSubGUI(141);
    else if((Fl::event_key() == 'a') &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(150);
    else if((Fl::event_key() == 'z') &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(151);

    else if(Fl::event_key() == 's')
      m_parent_gui->handleActionSubGUI(101);
    else if(Fl::event_key() == 'y')
      m_parent_gui->handleActionSubGUI(102);

    else if((Fl::event_key() == 'e') &&
	    (Fl::event_state() == FL_SHIFT))
      m_parent_gui->handleActionSubGUI(160); 
    else if(Fl::event_key() == 'e')
      m_parent_gui->handleActionSubGUI(161);

    else if((Fl::event_key() == 'w') && 
	    (Fl::event_state() == FL_SHIFT))
      m_parent_gui->handleActionSubGUI(170); 
    else if(Fl::event_key() == 'w')
      m_parent_gui->handleActionSubGUI(171);
    
    else if((Fl::event_key() == FL_Up) &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(130);
    else if((Fl::event_key() == FL_Down) &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(131);
    
    else if((Fl::event_key() == FL_Left) &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(180);
    else if((Fl::event_key() == FL_Right) &&
	    (Fl::event_state() == FL_CTRL))
      m_parent_gui->handleActionSubGUI(181);

    else if((Fl::event_key() == FL_Left) &&
	    (Fl::event_state() == FL_CTRL) &&
	    (Fl::event_state() == FL_ALT))
      m_parent_gui->handleActionSubGUI(182);
    else if((Fl::event_key() == FL_Right) &&
	    (Fl::event_state() == FL_CTRL) &&
	    (Fl::event_state() == FL_ALT))
      m_parent_gui->handleActionSubGUI(183);
    
    else 
      return(Common_IPF_GUI::handle(event));

    
    return(1);
    break;
  default:
    return(Fl_Window::handle(event));
  }
}

//----------------------------------------- Stretch Radius
inline void BNG_IPF_GUI::cb_StretchRad_i(int amt) {
  if(m_ipf_viewer1) {
    if(amt > 0) m_ipf_viewer1->setParam("mod_radius", 1.05263);  // 20/19
    if(amt < 0) m_ipf_viewer1->setParam("mod_radius", 0.95);     // 19/20
  }
  if(m_ipf_viewer2) {
    if(amt > 0) m_ipf_viewer2->setParam("mod_radius", 1.05263);  // 20/19
    if(amt < 0) m_ipf_viewer2->setParam("mod_radius", 0.95);     // 19/20
  }
}
void BNG_IPF_GUI::cb_StretchRad(Fl_Widget* o, int v) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_StretchRad_i(v);
}

//------------------------------------------ CB_ToggleAutoTOL

inline void BNG_IPF_GUI::cb_ToggleAutoTOL_i(int vix)
{
  if(vix == 1) {
    m_ipf_viewer1->setUseAutoTOL("toggle");
    m_ipf_viewer1->resetIPFX();
  }
  else if(vix == 2) {
    m_ipf_viewer2->setUseAutoTOL("toggle");
    m_ipf_viewer2->resetIPFX();
  }
  else
    return;
  redraw();
  updateXY();
}
void BNG_IPF_GUI::cb_ToggleAutoTOL(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ToggleAutoTOL_i(val);
}


//----------------------------------------- CB_ButTOLMod
inline void BNG_IPF_GUI::cb_ButTOLMod_i(int vix, int delta) {
  if(vix == 1) {
    if(!m_ipf_viewer1)
      return;
    m_ipf_viewer1->modTOL(delta);
    m_ipf_viewer1->resetIPF();
    m_ipf_viewer1->redraw();
  }
  else if(vix == 2) {
    if(!m_ipf_viewer2)
      return;
    m_ipf_viewer2->modTOL(delta);
    m_ipf_viewer2->resetIPF();
    m_ipf_viewer2->redraw();
  }
  else
    return;
  updateXY();
}
void BNG_IPF_GUI::cb_ButTOLAdd1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButTOLMod_i(1,1);
}
void BNG_IPF_GUI::cb_ButTOLSub1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButTOLMod_i(1,-1);
}
void BNG_IPF_GUI::cb_ButTOLAdd2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButTOLMod_i(2,1);
}
void BNG_IPF_GUI::cb_ButTOLSub2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButTOLMod_i(2,-1);
}


//----------------------------------------- CB_ButSartMod
inline void BNG_IPF_GUI::cb_ButSmartMod_i(int vix, int delta) {
  if(vix == 1) {
    if(!m_ipf_viewer1)
      return;
    m_ipf_viewer1->modSmartPcs(delta);
    m_ipf_viewer1->resetIPF();
    m_ipf_viewer1->redraw();
  }
  else if(vix == 2) {
    if(!m_ipf_viewer2)
      return;
    m_ipf_viewer2->modSmartPcs(delta);
    m_ipf_viewer2->resetIPF();
    m_ipf_viewer2->redraw();
  }
  else
    return;
  updateXY();
}
void BNG_IPF_GUI::cb_ButSmartAdd1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButSmartMod_i(1,1);
}
void BNG_IPF_GUI::cb_ButSmartSub1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButSmartMod_i(1,-1);
}
void BNG_IPF_GUI::cb_ButSmartAdd2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButSmartMod_i(2,1);
}
void BNG_IPF_GUI::cb_ButSmartSub2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButSmartMod_i(2,-1);
}

//----------------------------------------- CB_HeadingEdgeMod
inline void BNG_IPF_GUI::cb_HeadingEdgeMod_i(int vix, int delta) {
  if(vix == 1) {
    if(!m_ipf_viewer1)
      return;
    m_ipf_viewer1->modHdgEdgeSize(delta);
    m_ipf_viewer1->resetIPF();
    m_ipf_viewer1->redraw();
  }
  else if(vix == 2) {
    if(!m_ipf_viewer2)
      return;
    m_ipf_viewer2->modHdgEdgeSize(delta);
    m_ipf_viewer2->resetIPF();
    m_ipf_viewer2->redraw();
  }
  else
    return;
  updateXY();
}
void BNG_IPF_GUI::cb_ButHdgEdgeAdd1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_HeadingEdgeMod_i(1,1);
}
void BNG_IPF_GUI::cb_ButHdgEdgeSub1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_HeadingEdgeMod_i(1,-1);
}
void BNG_IPF_GUI::cb_ButHdgEdgeAdd2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_HeadingEdgeMod_i(2,1);
}
void BNG_IPF_GUI::cb_ButHdgEdgeSub2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_HeadingEdgeMod_i(2,-1);
}

//----------------------------------------- CB_SpeedEdgeSize()
inline void BNG_IPF_GUI::cb_SpeedEdgeMod_i(int vix, int delta) {
  cout << "cb_speedEdgeMod() " << vix << "," << delta << endl;
  if(vix == 1) {
    if(!m_ipf_viewer1)
      return;
    m_ipf_viewer1->modSpdEdgeSize(delta);
    m_ipf_viewer1->resetIPF();
    m_ipf_viewer1->redraw();
  }
  else if(vix == 2) {
    if(!m_ipf_viewer2)
      return;
    m_ipf_viewer2->modSpdEdgeSize(delta);
    m_ipf_viewer2->resetIPF();
    m_ipf_viewer2->redraw();
  }
  else
    return;
  updateXY();
}
void BNG_IPF_GUI::cb_ButSpdEdgeAdd1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_SpeedEdgeMod_i(1,1);
}
void BNG_IPF_GUI::cb_ButSpdEdgeSub1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_SpeedEdgeMod_i(1,-1);
}
void BNG_IPF_GUI::cb_ButSpdEdgeAdd2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_SpeedEdgeMod_i(2,1);
}
void BNG_IPF_GUI::cb_ButSpdEdgeSub2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_SpeedEdgeMod_i(2,-1);
}

//----------------------------------------- BehaviorType
inline void BNG_IPF_GUI::cb_BehaviorType_i(int vix, int val)
{
  BNG_IPFViewer *viewer = 0;
  if(vix == 1)
    viewer = m_ipf_viewer1;
  else if(vix == 2)
    viewer = m_ipf_viewer2;
  if(!viewer)
    return;
  
  if(val == 15)
    viewer->setBehaviorType("cpa");
  else if(val == 16)
    viewer->setBehaviorType("colregs_v22");
  else if(val == 17)
    viewer->setBehaviorType("colregs_v26");
  else if(val == 19)
    viewer->setBehaviorType("waypoint");
  else 
    return;

  viewer->clearBehaviorModes();
  viewer->resetIPF();
  viewer->redraw();

  m_parent_gui->handleActionSubGUI(99);
  updateXY();
}
void BNG_IPF_GUI::cb_BehaviorType1(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_BehaviorType_i(1,val);
}
void BNG_IPF_GUI::cb_BehaviorType2(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_BehaviorType_i(2,val);
}
void BNG_IPF_GUI::cb_BehaviorType12(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_BehaviorType_i(1,val);
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_BehaviorType_i(2,val);
}

//----------------------------------------- BehaviorType
inline void BNG_IPF_GUI::cb_SetScaleIPF_i(int vix, int val)
{
  if((vix == 1) && m_ipf_viewer1) {
    m_ipf_viewer1->setParam("set_scale", (double)(val));
    m_ipf_viewer1->resetIPF();
    m_ipf_viewer1->redraw();
  }
  if((vix == 2) && m_ipf_viewer2) {
    m_ipf_viewer2->setParam("set_scale", (double)(val));
    m_ipf_viewer2->resetIPF();
    m_ipf_viewer2->redraw();
  }
  else
    return;
  m_parent_gui->handleActionSubGUI(99);
  updateXY();
}
void BNG_IPF_GUI::cb_SetScaleIPF1(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_SetScaleIPF_i(1, val);
}
void BNG_IPF_GUI::cb_SetScaleIPF2(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_SetScaleIPF_i(2, val);
}
void BNG_IPF_GUI::cb_SetScaleIPF12(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_SetScaleIPF_i(1, val);
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_SetScaleIPF_i(2, val);
}

//----------------------------------------- PadIPF
inline void BNG_IPF_GUI::cb_PadIPF_i(int v)
{
  if(m_ipf_viewer1) {
    if(v == 8) 
      m_ipf_viewer1->modPolarPad(0.025);
    else if(v == 7)
      m_ipf_viewer1->modPolarPad(-0.025);
    else
      return;
    m_ipf_viewer1->resetIPF();
    m_ipf_viewer1->redraw();
  }
  if(m_ipf_viewer2) {
    if(v == 8) 
      m_ipf_viewer2->modPolarPad(0.025);
    else if(v == 7)
      m_ipf_viewer2->modPolarPad(-0.025);
    else
      return;
    m_ipf_viewer2->resetIPF();
    m_ipf_viewer2->redraw();
  }
  updateXY();
}
void BNG_IPF_GUI::cb_PadIPF(Fl_Widget* o, int v) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_PadIPF_i(v);
}

//----------------------------------------- CB_ButMinUtilMod
inline void BNG_IPF_GUI::cb_ButMinUtilMod_i(int vix, int delta)
{
  if(vix == 1) {
    if(!m_ipf_viewer1)
      return;
    m_ipf_viewer1->modMinUtilCPA((double)(delta));
    m_ipf_viewer1->draw();
  }
  else if(vix == 2) {
    if(!m_ipf_viewer2)
      return;
    m_ipf_viewer2->modMinUtilCPA((double)(delta));
    m_ipf_viewer2->draw();
  }
  else
    return;
  updateXY();
}
void BNG_IPF_GUI::cb_ButMinUtilAdd1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMinUtilMod_i(1,1);
}
void BNG_IPF_GUI::cb_ButMinUtilSub1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMinUtilMod_i(1,-1);
}
void BNG_IPF_GUI::cb_ButMinUtilAdd2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMinUtilMod_i(2,1);
}
void BNG_IPF_GUI::cb_ButMinUtilSub2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMinUtilMod_i(2,-1);
}


//----------------------------------------- CB_ButMaxUtilMod
inline void BNG_IPF_GUI::cb_ButMaxUtilMod_i(int vix, int delta)
{
  if(vix == 1) {
    if(!m_ipf_viewer1)
      return;
    m_ipf_viewer1->modMaxUtilCPA((double)(delta));
    m_ipf_viewer1->draw();
  }
  else if(vix == 2) {
    if(!m_ipf_viewer2)
      return;
    m_ipf_viewer2->modMaxUtilCPA((double)(delta));
    m_ipf_viewer2->draw();
  }
  else
    return;
  updateXY();
}
void BNG_IPF_GUI::cb_ButMaxUtilAdd1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMaxUtilMod_i(1,1);
}
void BNG_IPF_GUI::cb_ButMaxUtilSub1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMaxUtilMod_i(1,-1);
}
void BNG_IPF_GUI::cb_ButMaxUtilAdd2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMaxUtilMod_i(2,1);
}
void BNG_IPF_GUI::cb_ButMaxUtilSub2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMaxUtilMod_i(2,-1);
}


//----------------------------------------- CB_ButMinUtilETAMod
inline void BNG_IPF_GUI::cb_ButMinUtilETAMod_i(int vix, int delta)
{
  if(vix == 1) {
    if(!m_ipf_viewer1)
      return;
    m_ipf_viewer1->modMinUtilETA((double)(delta));
    m_ipf_viewer1->draw();
  }
  else if(vix == 2) {
    if(!m_ipf_viewer2)
      return;
    m_ipf_viewer2->modMinUtilETA((double)(delta));
    m_ipf_viewer2->draw();
  }
  else 
    return;
  updateXY();
}
void BNG_IPF_GUI::cb_ButMinUtilETAAdd1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMinUtilETAMod_i(1,1);
}
void BNG_IPF_GUI::cb_ButMinUtilETASub1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMinUtilETAMod_i(1,-1);
}
void BNG_IPF_GUI::cb_ButMinUtilETAAdd2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMinUtilETAMod_i(2,1);
}
void BNG_IPF_GUI::cb_ButMinUtilETASub2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMinUtilETAMod_i(2,-1);
}


//----------------------------------------- CB_ButMaxUtilETAMod
inline void BNG_IPF_GUI::cb_ButMaxUtilETAMod_i(int vix, int delta)
{
  if(vix == 1) {
    if(!m_ipf_viewer1)
      return;
    m_ipf_viewer1->modMaxUtilETA((double)(delta));
    m_ipf_viewer1->draw();
  }
  else if(vix == 2) {
    if(!m_ipf_viewer2)
      return;
    m_ipf_viewer2->modMaxUtilETA((double)(delta));
    m_ipf_viewer2->draw();
  }
  else
    return;
  updateXY();
}
void BNG_IPF_GUI::cb_ButMaxUtilETAAdd1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMaxUtilETAMod_i(1,1);
}
void BNG_IPF_GUI::cb_ButMaxUtilETASub1(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMaxUtilETAMod_i(1,-1);
}
void BNG_IPF_GUI::cb_ButMaxUtilETAAdd2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMaxUtilETAMod_i(2,1);
}
void BNG_IPF_GUI::cb_ButMaxUtilETASub2(Fl_Widget* o) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ButMaxUtilETAMod_i(2,-1);
}


//------------------------------------------ CB_TogglePlatModel

inline void BNG_IPF_GUI::cb_TogglePlatModel_i(int vix)
{
  if(vix == 1) {
    m_ipf_viewer1->setUsePlatModel("toggle");

    // Disallow the refinery if using the platmodel (for now)
    if(m_ipf_viewer1->getUsePlatModel())
      m_ipf_viewer1->setParam("use_refinery", "false");

    m_ipf_viewer1->resetIPFX();
  }
  else if(vix == 2) {
    m_ipf_viewer2->setUsePlatModel("toggle");

    // Disallow the refinery if using the platmodel (for now)
    if(m_ipf_viewer2->getUsePlatModel())
      m_ipf_viewer2->setParam("use_refinery", "false");

    m_ipf_viewer2->resetIPFX();
  }
  else
    return;
  redraw();
  updateXY();
}
void BNG_IPF_GUI::cb_TogglePlatModel(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_TogglePlatModel_i(val);
}


//------------------------------------------ CB_ToggleDrawPcsAct

inline void BNG_IPF_GUI::cb_ToggleDrawPcsAct_i(int vix)
{
  if(vix == 1) {
    m_ipf_viewer1->setParam("draw_pieces", "toggle");
    m_ipf_viewer1->resetIPFX();
  }
  else if(vix == 2) {
    m_ipf_viewer2->setParam("draw_pieces", "toggle");
    m_ipf_viewer2->resetIPFX();
  }
  else
    return;
  redraw();
  updateXY();
}
void BNG_IPF_GUI::cb_ToggleDrawPcsAct(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ToggleDrawPcsAct_i(val);
}


//------------------------------------------ CB_ToggleUseETA

inline void BNG_IPF_GUI::cb_ToggleUseETA_i(int vix)
{
  if(vix == 1) {
    m_ipf_viewer1->setParam("eta_factored", "toggle");
    m_ipf_viewer1->resetIPFX();
  }
  else if(vix == 2) {
    m_ipf_viewer2->setParam("eta_factored", "toggle");
    m_ipf_viewer2->resetIPFX();
  }
  else
    return;
  redraw();
  updateXY();
}
void BNG_IPF_GUI::cb_ToggleUseETA(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ToggleUseETA_i(val);
}

//------------------------------------------ CB_ToggleUseCPA

inline void BNG_IPF_GUI::cb_ToggleUseCPA_i(int vix)
{
  if(vix == 1) {
    m_ipf_viewer1->setParam("cpa_factored", "toggle");
    m_ipf_viewer1->resetIPFX();
  }
  else if(vix == 2) {
    m_ipf_viewer2->setParam("cpa_factored", "toggle");
    m_ipf_viewer2->resetIPFX();
  }
  else
    return;
  redraw();
  updateXY();
}
void BNG_IPF_GUI::cb_ToggleUseCPA(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ToggleUseCPA_i(val);
}


//------------------------------------------ CB_ToggleUseSmartPcs

inline void BNG_IPF_GUI::cb_ToggleUseSmartPcs_i(int vix)
{
  if(vix == 1) {
    m_ipf_viewer1->setUseSmartPcs("toggle");
    m_ipf_viewer1->resetIPFX();
  }
  else if(vix == 2) {
    m_ipf_viewer2->setUseSmartPcs("toggle");
    m_ipf_viewer2->resetIPFX();
  }
  else
    return;
  redraw();
  updateXY();
}
void BNG_IPF_GUI::cb_ToggleUseSmartPcs(Fl_Widget* o, int val) {
  ((BNG_IPF_GUI*)(o->parent()->user_data()))->cb_ToggleUseSmartPcs_i(val);
}


//------------------------------------------------------
// Procedure  UpdateXY()

void BNG_IPF_GUI::updateXY() 
{
  if(m_ipf_viewer1) {

    // Row 1  -------------
    bool pc1 = m_ipf_viewer1->getShowPieces();
    m_but_show_pcs1->value((int)(pc1));

    string pcs = m_ipf_viewer1->getInfo("pieces");
    m_fld_pieces1->value(pcs.c_str());

    string min_eta = m_ipf_viewer1->getInfo("minutil_eta");
    m_fld_minutil_eta1->value(min_eta.c_str());

    bool eta1 = m_ipf_viewer1->getETAFactored();
    m_but_use_eta1->value((int)(eta1));

    // Row 2 --------------
    bool sm1 = m_ipf_viewer1->getUseSmartPcs();
    m_but_smart1->value((int)(sm1));

    string smart = m_ipf_viewer1->getInfo("smart");
    m_fld_smart1->value(smart.c_str());

    string max_eta = m_ipf_viewer1->getInfo("maxutil_eta");
    m_fld_maxutil_eta1->value(max_eta.c_str());

    // Row 3  -------------
    string hdg_size = m_ipf_viewer1->getInfo("hdg_size");
    m_fld_hdg_size1->value(hdg_size.c_str());  
  
    string minutil_cpa1 = m_ipf_viewer1->getInfo("minutil_cpa");
    m_fld_minutil_cpa1->value(minutil_cpa1.c_str());  
    
    bool cpa1 = m_ipf_viewer1->getCPAFactored();
    m_but_tol1->value((int)(cpa1));

    // Row 4
    string spd_size = m_ipf_viewer1->getInfo("spd_size");
    m_fld_spd_size1->value(spd_size.c_str());  

    string maxutil_cpa1 = m_ipf_viewer1->getInfo("maxutil_cpa");
    m_fld_maxutil_cpa1->value(maxutil_cpa1.c_str());  

    // Row 5
    string pmod1 = m_ipf_viewer1->getInfo("pmodel_config");
    m_fld_plat_model1->value(pmod1.c_str());  

    string tol = m_ipf_viewer1->getInfo("time_on_leg");
    m_fld_tol1->value(tol.c_str());

    // Row 6
    bool pmo = m_ipf_viewer1->getUsePlatModel();
    m_but_platmod1->value((int)(pmo));

    string debug1 = m_ipf_viewer1->getInfo("debug1");
    m_fld_bhv_debug1->value(debug1.c_str());  
  }

  //============================================================
  if(m_ipf_viewer2) {
    // Row 1  -------------
    bool pc2 = m_ipf_viewer2->getShowPieces();
    m_but_show_pcs2->value((int)(pc2));

    string pcs = m_ipf_viewer2->getInfo("pieces");
    m_fld_pieces2->value(pcs.c_str());

    string min_eta = m_ipf_viewer2->getInfo("minutil_eta");
    m_fld_minutil_eta2->value(min_eta.c_str());

    bool eta1 = m_ipf_viewer2->getETAFactored();
    m_but_use_eta2->value((int)(eta1));

    // Row 2  -------------
    bool sm2 = m_ipf_viewer2->getUseSmartPcs();
    m_but_smart2->value((int)(sm2));

    string smart = m_ipf_viewer2->getInfo("smart");
    m_fld_smart2->value(smart.c_str());
    
    string max_eta = m_ipf_viewer2->getInfo("maxutil_eta");
    m_fld_maxutil_eta2->value(max_eta.c_str());

    // Row 3  -------------
    string hdg_size = m_ipf_viewer2->getInfo("hdg_size");
    m_fld_hdg_size2->value(hdg_size.c_str());  
  
    string minutil_cpa2 = m_ipf_viewer2->getInfo("minutil_cpa");
    m_fld_minutil_cpa2->value(minutil_cpa2.c_str());  
    
    bool cpa2 = m_ipf_viewer2->getCPAFactored();
    m_but_tol2->value((int)(cpa2));

    // Row 4  -------------
    string spd_size = m_ipf_viewer2->getInfo("spd_size");
    m_fld_spd_size2->value(spd_size.c_str());  

    string maxutil_cpa2 = m_ipf_viewer2->getInfo("maxutil_cpa");
    m_fld_maxutil_cpa2->value(maxutil_cpa2.c_str());  

    // Row 5  -------------
    string pmod2 = m_ipf_viewer2->getInfo("pmodel_config");
    m_fld_plat_model2->value(pmod2.c_str());  

    string tol = m_ipf_viewer2->getInfo("time_on_leg");
    m_fld_tol2->value(tol.c_str());

    // Row 6  -------------
    bool pmo = m_ipf_viewer2->getUsePlatModel();
    m_but_platmod2->value((int)(pmo));

    string debug2 = m_ipf_viewer2->getInfo("debug1");
    m_fld_bhv_debug2->value(debug2.c_str());  
  }
}


