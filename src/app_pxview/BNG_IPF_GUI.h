/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: BNG_IPF_GUI.h                                        */
/*    DATE: May 21 2013                                          */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#ifndef BNG_IPF_GUI_HEADER
#define BNG_IPF_GUI_HEADER

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include "IvPDomain.h"
#include "BNG_IPFViewer.h"
#include "Common_IPF_GUI.h"
#include "XModel.h"

class POLY_GUI;

class BNG_IPF_GUI : public Common_IPF_GUI {
public:
  BNG_IPF_GUI(int w, int h, const char *label=0);
  virtual ~BNG_IPF_GUI();
  
  // void setPairModels(PairModelOG*, PairModelPM*);
  void setParentGUI(POLY_GUI *pgui) {m_parent_gui=pgui;}
  
  int  handle(int);
  void clearBehaviorModes();
  void setDomain(IvPDomain);
  void setXModel(XModel*);
  void updatedXModel();
  
 protected:
  void augmentMenu();
  void initWidgets();
  void resizeWidgetsShape();
  void resizeWidgetsText();
  void updateXY();
  void resize(int, int, int, int);
  
 public:
  POLY_GUI      *m_parent_gui;
  BNG_IPFViewer *m_ipf_viewer1;
  BNG_IPFViewer *m_ipf_viewer2;

  bool           m_show_mode_browser;
  
  // Browser (Left)
  Fl_Browser *m_brw_modes;

  // Row 1 --------------------------
  Fl_Button       *m_but_toggle_brw1;

  Fl_Output       *m_fld_tol1;
  Fl_Check_Button *m_but_tol1;
  Fl_Button       *m_but_tol_add1;
  Fl_Button       *m_but_tol_sub1;

  // -------
  Fl_Button       *m_but_toggle_brw2;

  Fl_Output       *m_fld_tol2;
  Fl_Check_Button *m_but_tol2;
  Fl_Button       *m_but_tol_add2;
  Fl_Button       *m_but_tol_sub2;

  // Row 2 --------------------------
  Fl_Output       *m_fld_pieces1;
  Fl_Check_Button *m_but_show_pcs1;
  Fl_Output       *m_fld_smart1;
  Fl_Check_Button *m_but_smart1;
  Fl_Button       *m_but_smart_add1;
  Fl_Button       *m_but_smart_sub1;

  // -------
  Fl_Output       *m_fld_pieces2;
  Fl_Check_Button *m_but_show_pcs2;
  Fl_Output       *m_fld_smart2;
  Fl_Check_Button *m_but_smart2;
  Fl_Button       *m_but_smart_add2;
  Fl_Button       *m_but_smart_sub2;
  
  // Row 3 --------------------------
  Fl_Output  *m_fld_hdg_size1;
  Fl_Button  *m_but_hsz_add1;
  Fl_Button  *m_but_hsz_sub1;

  Fl_Input   *m_fld_minutil_cpa1;
  Fl_Button  *m_but_minutil_add1;
  Fl_Button  *m_but_minutil_sub1;

  // -------
  Fl_Output  *m_fld_hdg_size2;
  Fl_Button  *m_but_hsz_add2;
  Fl_Button  *m_but_hsz_sub2;

  Fl_Input   *m_fld_minutil_cpa2;
  Fl_Button  *m_but_minutil_add2;
  Fl_Button  *m_but_minutil_sub2;

  // Row 4 --------------------------
  Fl_Output  *m_fld_spd_size1;
  Fl_Button  *m_but_ssz_add1;
  Fl_Button  *m_but_ssz_sub1;
  
  Fl_Input   *m_fld_maxutil_cpa1;
  Fl_Button  *m_but_maxutil_add1;
  Fl_Button  *m_but_maxutil_sub1;

  // -------
  Fl_Output  *m_fld_spd_size2;
  Fl_Button  *m_but_ssz_add2;
  Fl_Button  *m_but_ssz_sub2;  

  Fl_Input   *m_fld_maxutil_cpa2;
  Fl_Button  *m_but_maxutil_add2;
  Fl_Button  *m_but_maxutil_sub2;
  
  // Row 5 --------------------------
  Fl_Output  *m_fld_plat_model1;

  // -------
  Fl_Output  *m_fld_plat_model2;

  // Row 6 --------------------------
  Fl_Check_Button *m_but_platmod1;
  Fl_Output       *m_fld_bhv_debug1;

  // -------
  Fl_Check_Button *m_but_platmod2;
  Fl_Output       *m_fld_bhv_debug2;

 private:
  // VIEWER  -------------------------------------
  inline void cb_StretchRad_i(int);
  static void cb_StretchRad(Fl_Widget*, int);

  inline void cb_SetScaleIPF_i(int vix, int val);
  static void cb_SetScaleIPF1(Fl_Widget*, int);
  static void cb_SetScaleIPF2(Fl_Widget*, int);
  static void cb_SetScaleIPF12(Fl_Widget*, int);

  inline void cb_PadIPF_i(int);
  static void cb_PadIPF(Fl_Widget*, int);

  // Row 1 -------------------------------------
  inline void cb_ButToggleModeBrowser_i();
  static void cb_ButToggleModeBrowser(Fl_Widget*);

  inline void cb_BehaviorType_i(int vix, int val);
  static void cb_BehaviorType1(Fl_Widget*, int);
  static void cb_BehaviorType2(Fl_Widget*, int);
  static void cb_BehaviorType12(Fl_Widget*, int);

  inline void cb_ToggleRefineryAct_i(int);
  static void cb_ToggleRefineryAct(Fl_Widget*, int);

  inline void cb_ToggleAutoTOL_i(int);
  static void cb_ToggleAutoTOL(Fl_Widget*, int);

  inline void cb_ButTOLMod_i(int, int);
  static void cb_ButTOLAdd1(Fl_Widget*);
  static void cb_ButTOLSub1(Fl_Widget*);
  static void cb_ButTOLAdd2(Fl_Widget*);
  static void cb_ButTOLSub2(Fl_Widget*);

  // Row 2 -------------------------------------
  inline void cb_ToggleDrawPcsAct_i(int);
  static void cb_ToggleDrawPcsAct(Fl_Widget*, int);

  inline void cb_ToggleUseSmartPcs_i(int);
  static void cb_ToggleUseSmartPcs(Fl_Widget*, int);

  inline void cb_ButSmartMod_i(int, int);
  static void cb_ButSmartAdd1(Fl_Widget*);
  static void cb_ButSmartSub1(Fl_Widget*);
  static void cb_ButSmartAdd2(Fl_Widget*);
  static void cb_ButSmartSub2(Fl_Widget*);

  // Row 3 -------------------------------------
  inline void cb_HeadingEdgeMod_i(int, int);
  static void cb_ButHdgEdgeAdd1(Fl_Widget*);
  static void cb_ButHdgEdgeSub1(Fl_Widget*);
  static void cb_ButHdgEdgeAdd2(Fl_Widget*);
  static void cb_ButHdgEdgeSub2(Fl_Widget*);
  
  inline void cb_ButMinUtilMod_i(int, int);
  static void cb_ButMinUtilAdd1(Fl_Widget*);
  static void cb_ButMinUtilSub1(Fl_Widget*);
  static void cb_ButMinUtilAdd2(Fl_Widget*);
  static void cb_ButMinUtilSub2(Fl_Widget*);

  // Row 4  -------------------------------------
  inline void cb_SpeedEdgeMod_i(int, int);
  static void cb_ButSpdEdgeAdd1(Fl_Widget*);
  static void cb_ButSpdEdgeSub1(Fl_Widget*);
  static void cb_ButSpdEdgeAdd2(Fl_Widget*);
  static void cb_ButSpdEdgeSub2(Fl_Widget*);

  inline void cb_ButMaxUtilMod_i(int, int);
  static void cb_ButMaxUtilAdd1(Fl_Widget*);
  static void cb_ButMaxUtilSub1(Fl_Widget*);
  static void cb_ButMaxUtilAdd2(Fl_Widget*);
  static void cb_ButMaxUtilSub2(Fl_Widget*);


  // Row 6  -------------------------------------
  inline void cb_TogglePlatModel_i(int);
  static void cb_TogglePlatModel(Fl_Widget*, int);


  
};
#endif



