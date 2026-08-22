/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: BNG_IPF_GUI_Widgets.cpp                              */
/*    DATE: Mar 03, 2026 (broken out into Widgets file)          */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include "BNG_IPF_GUI.h"

//----------------------------------------------------------------
// Procedure: initWidgets()     

void BNG_IPF_GUI::initWidgets()
{

  Fl_Color fcolor_aqua  = fl_rgb_color(197, 255, 232);
  Fl_Color fcolor_blue  = fl_rgb_color(140, 140, 220);
  Fl_Color fcolor_beige = fl_rgb_color(223, 219, 191);
  Fl_Color fcolor_green = fl_rgb_color(200, 230, 190);                        
  Fl_Color fcolor_dark_goldenrod  = fl_rgb_color(184, 136, 11);
  Fl_Color fcolor_olive = fl_rgb_color(136, 136, 11);
  
  m_ipf_viewer1 = new BNG_IPFViewer(0, 0, 1, 1);
  m_ipf_viewer2 = new BNG_IPFViewer(0, 0, 1, 1);
  m_viewer  = (Common_IPFViewer*)(m_ipf_viewer1);
  m_viewer2 = (Common_IPFViewer*)(m_ipf_viewer2);
  
  Fl_Color fcolor2 = fl_rgb_color(190, 255, 190); // green

  //============================================================
  // Row 1
  //============================================================
  // Viewer 1
  m_fld_pieces1 = new Fl_Output(0, 0, 1, 1, "pcs:");
  m_fld_pieces1->clear_visible_focus();

  m_but_show_pcs1 = new Fl_Check_Button(0, 0, 1, 1, "show pcs");
  m_but_show_pcs1->clear_visible_focus();
  m_but_show_pcs1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ToggleDrawPcsAct,
			   (void*)1);  

  // Viewer 2
  m_fld_pieces2 = new Fl_Output(0, 0, 1, 1, "pcs:");
  m_fld_pieces2->clear_visible_focus();

  m_but_show_pcs2 = new Fl_Check_Button(0, 0, 1, 1, "show pcs");
  m_but_show_pcs2->clear_visible_focus();
  m_but_show_pcs2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ToggleDrawPcsAct,
			   (void*)2);  




  //============================================================
  // Row 2
  //============================================================
  // Viewer 1

  m_fld_smart1 = new Fl_Output(0, 0, 1, 1, "smart:");
  m_fld_smart1->clear_visible_focus();

  m_but_smart1 = new Fl_Check_Button(0, 0, 1, 1, "");
  m_but_smart1->clear_visible_focus();
  m_but_smart1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ToggleUseSmartPcs,
			   (void*)1);  

  m_but_smart_add1 = new Fl_Button(0, 0, 1, 1, "+"); 
  m_but_smart_add1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButSmartAdd1);
  m_but_smart_add1->clear_visible_focus();
  
  m_but_smart_sub1 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_smart_sub1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButSmartSub1);
  m_but_smart_sub1->clear_visible_focus();
  
  m_fld_tol1 = new Fl_Output(0, 0, 1, 1, "ostol:");
  m_fld_tol1->clear_visible_focus();
  m_fld_tol1->color(fcolor_blue);

  m_but_tol1 = new Fl_Check_Button(0, 0, 1, 1, "");
  m_but_tol1->clear_visible_focus();
  m_but_tol1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ToggleAutoTOL,
			   (void*)1);  

  m_but_tol_add1 = new Fl_Button(0, 0, 1, 1, "+"); 
  m_but_tol_add1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButTOLAdd1);
  m_but_tol_add1->clear_visible_focus();
  
  m_but_tol_sub1 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_tol_sub1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButTOLSub1);
  m_but_tol_sub1->clear_visible_focus();
  

  // Viewer 2 --------------------------------
  m_fld_smart2 = new Fl_Output(0, 0, 1, 1, "smart:");
  m_fld_smart2->clear_visible_focus();

  m_but_smart2 = new Fl_Check_Button(0, 0, 1, 1, "");
  m_but_smart2->clear_visible_focus();
  m_but_smart2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ToggleUseSmartPcs,
			   (void*)2);  

  m_but_smart_add2 = new Fl_Button(0, 0, 1, 1, "+"); 
  m_but_smart_add2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButSmartAdd2);
  m_but_smart_add2->clear_visible_focus();
  
  m_but_smart_sub2 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_smart_sub2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButSmartSub2);
  m_but_smart_sub2->clear_visible_focus();
  
  m_fld_tol2 = new Fl_Output(0, 0, 1, 1, "ostol:");
  m_fld_tol2->clear_visible_focus();
  m_fld_tol2->color(fcolor_blue);
  
  
  m_but_tol2 = new Fl_Check_Button(0, 0, 1, 1, "");
  m_but_tol2->clear_visible_focus();
  m_but_tol2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ToggleAutoTOL,
			   (void*)2);  

  m_but_tol_add2 = new Fl_Button(0, 0, 1, 1, "+"); 
  m_but_tol_add2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButTOLAdd2);
  m_but_tol_add2->clear_visible_focus();
  
  m_but_tol_sub2 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_tol_sub2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButTOLSub2);
  m_but_tol_sub2->clear_visible_focus();
  

  //============================================================
  // Row 3
  //============================================================
  // Viewer 1
  m_fld_hdg_size1 = new Fl_Output(0, 0, 1, 1, "hdg_psize:");
  m_fld_hdg_size1->clear_visible_focus();

  m_but_hsz_add1 = new Fl_Button(0, 0, 1, 1, "+"); 
  m_but_hsz_add1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButHdgEdgeAdd1);
  m_but_hsz_add1->clear_visible_focus();
  
  m_but_hsz_sub1 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_hsz_sub1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButHdgEdgeSub1);
  m_but_hsz_sub1->clear_visible_focus();
  
  m_fld_minutil_cpa1 = new Fl_Output(0, 0, 1, 1, "min_util_cpa:");
  m_fld_minutil_cpa1->clear_visible_focus();
  m_fld_minutil_cpa1->color(fcolor_blue);
  
  m_but_minutil_add1 = new Fl_Button(0, 0, 1, 1, "+");
  m_but_minutil_add1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButMinUtilAdd1);
  m_but_minutil_add1->clear_visible_focus();
  
  m_but_minutil_sub1 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_minutil_sub1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButMinUtilSub1);
  m_but_minutil_sub1->clear_visible_focus();
  
  // Viewer 2 
  m_fld_hdg_size2 = new Fl_Output(0, 0, 1, 1, "hdg_psize:");
  m_fld_hdg_size2->clear_visible_focus();

  m_but_hsz_add2 = new Fl_Button(0, 0, 1, 1, "+");
  m_but_hsz_add2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButHdgEdgeAdd2);
  m_but_hsz_add2->clear_visible_focus();
  
  m_but_hsz_sub2 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_hsz_sub2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButHdgEdgeSub2);
  m_but_hsz_sub2->clear_visible_focus();
  
  m_fld_minutil_cpa2 = new Fl_Output(0, 0, 1, 1, "min_util_cpa:");
  m_fld_minutil_cpa2->clear_visible_focus();
  m_fld_minutil_cpa2->color(fcolor_blue);
  
  m_but_minutil_add2 = new Fl_Button(0, 0, 1, 1, "+");
  m_but_minutil_add2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButMinUtilAdd2);
  m_but_minutil_add2->clear_visible_focus();
  
  m_but_minutil_sub2 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_minutil_sub2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButMinUtilSub2);
  m_but_minutil_sub2->clear_visible_focus();
  

  //============================================================
  // Row 4
  //============================================================
  // Viewer 1
  m_fld_spd_size1 = new Fl_Output(0, 0, 1, 1, "spd_psize:");
  m_fld_spd_size1->clear_visible_focus();

  m_but_ssz_add1 = new Fl_Button(0, 0, 1, 1, "+");
  m_but_ssz_add1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButSpdEdgeAdd1);
  m_but_ssz_add1->clear_visible_focus();
  
  m_but_ssz_sub1 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_ssz_sub1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButSpdEdgeSub1);
  m_but_ssz_sub1->clear_visible_focus();
  
  m_fld_maxutil_cpa1 = new Fl_Output(0, 0, 1, 1, "max_util_cpa:");
  m_fld_maxutil_cpa1->clear_visible_focus();
  m_fld_maxutil_cpa1->color(fcolor_blue);
  
  m_but_maxutil_add1 = new Fl_Button(0, 0, 1, 1, "+");
  m_but_maxutil_add1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButMaxUtilAdd1);
  m_but_maxutil_add1->clear_visible_focus();
  
  m_but_maxutil_sub1 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_maxutil_sub1->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButMaxUtilSub1);
  m_but_maxutil_sub1->clear_visible_focus();
  

  // Viewer 2
  m_fld_spd_size2 = new Fl_Output(0, 0, 1, 1, "spd_psize:");
  m_fld_spd_size2->clear_visible_focus();

  m_but_ssz_add2 = new Fl_Button(0, 0, 1, 1, "+");
  m_but_ssz_add2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButSpdEdgeAdd2);
  m_but_ssz_add2->clear_visible_focus();
  
  m_but_ssz_sub2 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_ssz_sub2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButSpdEdgeSub2);
  m_but_ssz_sub2->clear_visible_focus();
  
  m_fld_maxutil_cpa2 = new Fl_Output(0, 0, 1, 1, "max_util_cpa:");
  m_fld_maxutil_cpa2->clear_visible_focus();
  m_fld_maxutil_cpa2->color(fcolor_blue);
  
  m_but_maxutil_add2 = new Fl_Button(0, 0, 1, 1, "+");
  m_but_maxutil_add2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButMaxUtilAdd2);
  m_but_maxutil_add2->clear_visible_focus();
  
  m_but_maxutil_sub2 = new Fl_Button(0, 0, 1, 1, "-");
  m_but_maxutil_sub2->callback((Fl_Callback*)BNG_IPF_GUI::cb_ButMaxUtilSub2);
  m_but_maxutil_sub2->clear_visible_focus();
  
  //============================================================
  // Row 5
  //============================================================
  m_fld_plat_model1 = new Fl_Output(0, 0, 1, 1, "plat_model:");
  m_fld_plat_model1->clear_visible_focus();

  m_fld_plat_model2 = new Fl_Output(0, 0, 1, 1, "plat_model:");
  m_fld_plat_model2->clear_visible_focus();
  

  //============================================================
  // Row 6
  //============================================================
  m_but_platmod1 = new Fl_Check_Button(0, 0, 1, 1, "platmod");
  m_but_platmod1->clear_visible_focus();
  m_but_platmod1->align(FL_ALIGN_LEFT);
  m_but_platmod1->callback((Fl_Callback*)BNG_IPF_GUI::cb_TogglePlatModel,
			    (void*)1);  
  
  m_fld_bhv_debug1 = new Fl_Output(0, 0, 1, 1, "debug1:");
  m_fld_bhv_debug1->clear_visible_focus();


  m_but_platmod2 = new Fl_Check_Button(0, 0, 1, 1, "platmod");
  m_but_platmod2->clear_visible_focus();
  m_but_platmod2->align(FL_ALIGN_LEFT);
  m_but_platmod2->callback((Fl_Callback*)BNG_IPF_GUI::cb_TogglePlatModel,
			    (void*)2);  
  
  m_fld_bhv_debug2 = new Fl_Output(0, 0, 1, 1, "debug2:");
  m_fld_bhv_debug2->clear_visible_focus();
}

//-------------------------------------------------------------- 
// Procedure: resizeWidgetsShape()     

void BNG_IPF_GUI::resizeWidgetsShape()
{
  int extra_wid = w() - m_start_wid;

  int fld_hgt = 20;
  int row1 = h()-180;
  int row2 = h()-150;
  int row3 = h()-120;
  int row4 = h()-90;
  int row5 = h()-60;
  int row6 = h()-30;
 
  int browser_wid = 200;

  double margin = 5;
  double panel = w() - (4 * margin);
  
  double sx1  = margin;
  double wid1 = panel / 2;
  double wid2 = panel / 2;
  double sx2  = sx1 + wid1 + margin*2; 
  double lmarg = 10;
  
  if(m_ipf_viewer1)
    m_ipf_viewer1->resize(sx1, 30, wid1, h()-220);
  if(m_ipf_viewer2)
    m_ipf_viewer2->resize(sx2, 30, wid2, h()-220);
  
  //============================================================
  // The Viewer Window
  //============================================================
  //m_ipf_viewer1->resize(margin, 30, wid1, h()-100);
  
  //============================================================
  // Row 1
  //============================================================
  // Viewer 1
  int pcs_x = sx1 + 65;
  int pcs_y = row1;
  int pcs_w = 35 + (extra_wid/4);
  m_fld_pieces1->resize(pcs_x, pcs_y, pcs_w, fld_hgt);

  int bpc_x = pcs_x + pcs_w + 10;
  int bpc_y = row1;
  int bpc_w = 20;
  m_but_show_pcs1->resize(bpc_x, bpc_y, bpc_w, fld_hgt);


  // Viewer 2  -------------------------------
  int pcs2_x = sx2 + 65;
  int pcs2_y = row1;
  int pcs2_w = 35 + (extra_wid/4);
  m_fld_pieces2->resize(pcs2_x, pcs2_y, pcs2_w, fld_hgt);

  int bpc2_x = pcs2_x + pcs2_w + 10;
  int bpc2_y = row1;
  int bpc2_w = 20;
  m_but_show_pcs2->resize(bpc2_x, bpc2_y, bpc2_w, fld_hgt);

  //============================================================
  // Row 2
  //============================================================
  // Viewer 1
  int sm1_x = sx1 + 65;
  int sm1_y = row2;
  int sm1_w = 35 + (extra_wid/4);
  m_fld_smart1->resize(sm1_x, sm1_y, sm1_w, fld_hgt);

  int bs1_x = sm1_x + sm1_w + 5;
  int bs1_y = row2;
  int bs1_w = 15;
  m_but_smart1->resize(bs1_x, bs1_y, bs1_w, fld_hgt);
  
  int bsa1_x = bs1_x + bs1_w + 6;
  int bsa1_y = row2;
  int bsa1_w = 15;
  m_but_smart_add1->resize(bsa1_x, bsa1_y, bsa1_w, fld_hgt);

  int bss1_x = bsa1_x + bsa1_w + 4;
  int bss1_y = row2;
  int bss1_w = 15;
  m_but_smart_sub1->resize(bss1_x, bss1_y, bss1_w, fld_hgt);

  int ftol1_x = bpc_x + bpc_w + 100;
  int ftol1_y = row2;
  int ftol1_w = 35 + (extra_wid/4);
  m_fld_tol1->resize(ftol1_x, ftol1_y, ftol1_w, fld_hgt);
  
  int btol1_x = ftol1_x + ftol1_w + 5;
  int btol1_y = row2;
  int btol1_w = 15;
  m_but_tol1->resize(btol1_x, btol1_y, btol1_w, fld_hgt);
  
  int btola1_x = btol1_x + btol1_w + 6;
  int btola1_y = row2;
  int btola1_w = 15;
  m_but_tol_add1->resize(btola1_x, btola1_y, btola1_w, fld_hgt);

  int btols1_x = btola1_x + btola1_w + 4;
  int btols1_y = row2;
  int btols1_w = 15;
  m_but_tol_sub1->resize(btols1_x, btols1_y, btols1_w, fld_hgt);

  // Viewer 2 -----------------------------
  int sm2_x = sx2 + 65;
  int sm2_y = row2;
  int sm2_w = 35 + (extra_wid/4);
  m_fld_smart2->resize(sm2_x, sm2_y, sm2_w, fld_hgt);

  int bs2_x = sm2_x + sm2_w + 5;
  int bs2_y = row2;
  int bs2_w = 14;
  m_but_smart2->resize(bs2_x, bs2_y, bs2_w, fld_hgt);
  
  int bsa2_x = bs2_x + bs2_w + 6;
  int bsa2_y = row2;
  int bsa2_w = 15;
  m_but_smart_add2->resize(bsa2_x, bsa2_y, bsa2_w, fld_hgt);

  int bss2_x = bsa2_x + bsa2_w + 4;
  int bss2_y = row2;
  int bss2_w = 15;
  m_but_smart_sub2->resize(bss2_x, bss2_y, bss2_w, fld_hgt);

  int ftol2_x = bpc2_x + bpc2_w + 100;
  int ftol2_y = row2;
  int ftol2_w = 35 + (extra_wid/4);
  m_fld_tol2->resize(ftol2_x, ftol2_y, ftol2_w, fld_hgt);
  
  int btol2_x = ftol2_x + ftol2_w + 5;
  int btol2_y = row2;
  int btol2_w = 15;
  m_but_tol2->resize(btol2_x, btol2_y, btol2_w, fld_hgt);
  
  int btola2_x = btol2_x + btol2_w + 6;
  int btola2_y = row2;
  int btola2_w = 15;
  m_but_tol_add2->resize(btola2_x, btola2_y, btola2_w, fld_hgt);

  int btols2_x = btola2_x + btola2_w + 4;
  int btols2_y = row2;
  int btols2_w = 15;
  m_but_tol_sub2->resize(btols2_x, btols2_y, btols2_w, fld_hgt);

  //============================================================
  // Row 3
  //============================================================
  // Viewer 1
  int hsz_x = sx1 + 65;
  int hsz_y = row3;
  int hsz_w = 35 + (extra_wid/4);
  m_fld_hdg_size1->resize(hsz_x, hsz_y, hsz_w, fld_hgt);

  int hsza1_x = hsz_x + hsz_w + 4;
  int hsza1_y = row3;
  int hsza1_w = 15;
  m_but_hsz_add1->resize(hsza1_x, hsza1_y, hsza1_w, fld_hgt);

  int hszs1_x = hsza1_x + hsza1_w + 5;
  int hszs1_y = row3;
  int hszs1_w = 15;
  m_but_hsz_sub1->resize(hszs1_x, hszs1_y, hszs1_w, fld_hgt);

  int minc_x = hszs1_x + hszs1_w + 90;
  int minc_y = row3;
  int minc_w = 35 + (extra_wid/4); 
  m_fld_minutil_cpa1->resize(minc_x, minc_y, minc_w, fld_hgt);

  int mia1_x = minc_x + minc_w + 5;
  int mia1_y = row3;
  int mia1_w = 15;
  m_but_minutil_add1->resize(mia1_x, mia1_y, mia1_w, fld_hgt);

  int mis1_x = mia1_x + mia1_w + 5;
  int mis1_y = row3;
  int mis1_w = 15;
  m_but_minutil_sub1->resize(mis1_x, mis1_y, mis1_w, fld_hgt);

  
  // Viewer 2  --------------------------------
  int hsz2_x = sx2 + 65;
  int hsz2_y = row3;
  int hsz2_w = 35  + (extra_wid/4);
  m_fld_hdg_size2->resize(hsz2_x, hsz2_y, hsz2_w, fld_hgt);

  int hsza2_x = hsz2_x + hsz2_w + 4;
  int hsza2_y = row3;
  int hsza2_w = 15;
  m_but_hsz_add2->resize(hsza2_x, hsza2_y, hsza2_w, fld_hgt);

  int hszs2_x = hsza2_x + hsza2_w + 5;
  int hszs2_y = row3;
  int hszs2_w = 15;
  m_but_hsz_sub2->resize(hszs2_x, hszs2_y, hszs2_w, fld_hgt);

  int minc2_x = hszs2_x + hszs2_w + 90;
  int minc2_y = row3;
  int minc2_w = 35 + (extra_wid/4); 
  m_fld_minutil_cpa2->resize(minc2_x, minc2_y, minc2_w, fld_hgt);

  int mia2_x = minc2_x + minc2_w + 5;
  int mia2_y = row3;
  int mia2_w = 15;
  m_but_minutil_add2->resize(mia2_x, mia2_y, mia2_w, fld_hgt);

  int mis2_x = mia2_x + mia2_w + 5;
  int mis2_y = row3;
  int mis2_w = 15;
  m_but_minutil_sub2->resize(mis2_x, mis2_y, mis2_w, fld_hgt);

  //============================================================
  // Row 4
  //============================================================
  // Viewer 1
  int ssz_x = sx1 + 65;
  int ssz_y = row4;
  int ssz_w = 35 + (extra_wid/4);
  m_fld_spd_size1->resize(ssz_x, ssz_y, ssz_w, fld_hgt);

  int ssza1_x = ssz_x + ssz_w + 5;
  int ssza1_y = row4;
  int ssza1_w = 15;
  m_but_ssz_add1->resize(ssza1_x, ssza1_y, ssza1_w, fld_hgt);

  int sszs1_x = ssza1_x + ssza1_w + 5;
  int sszs1_y = row4;
  int sszs1_w = 15;
  m_but_ssz_sub1->resize(sszs1_x, sszs1_y, sszs1_w, fld_hgt);
  
  int maxc_x = sszs1_x + sszs1_w + 90;
  int maxc_y = row4;
  int maxc_w = 35 + (extra_wid/4);
  m_fld_maxutil_cpa1->resize(maxc_x, maxc_y, maxc_w, fld_hgt);

  int maa1_x = maxc_x + maxc_w + 5;
  int maa1_y = row4;
  int maa1_w = 15; 
  m_but_maxutil_add1->resize(maa1_x, maa1_y, maa1_w, fld_hgt);

  int mas1_x = maa1_x + maa1_w + 5;
  int mas1_y = row4;
  int mas1_w = 15; 
  m_but_maxutil_sub1->resize(mas1_x, mas1_y, mas1_w, fld_hgt);

  // Viewer 2  -------------------------------
  int ssz2_x = sx2 + 65;
  int ssz2_y = row4;
  int ssz2_w = 35 + (extra_wid/4);
  m_fld_spd_size2->resize(ssz2_x, ssz2_y, ssz2_w, fld_hgt);

  int ssza2_x = ssz2_x + ssz2_w + 5;
  int ssza2_y = row4;
  int ssza2_w = 15;
  m_but_ssz_add2->resize(ssza2_x, ssza2_y, ssza2_w, fld_hgt);

  int sszs2_x = ssza2_x + ssza2_w + 5;
  int sszs2_y = row4;
  int sszs2_w = 15;
  m_but_ssz_sub2->resize(sszs2_x, sszs2_y, sszs2_w, fld_hgt);

  int maxc2_x = sszs2_x + sszs2_w + 90;
  int maxc2_y = row4;
  int maxc2_w = 35 + (extra_wid/4);
  m_fld_maxutil_cpa2->resize(maxc2_x, maxc2_y, maxc2_w, fld_hgt);

  int maa2_x = maxc2_x + maxc2_w + 5;
  int maa2_y = row4;
  int maa2_w = 15; 
  m_but_maxutil_add2->resize(maa2_x, maa2_y, maa2_w, fld_hgt);

  int mas2_x = maa2_x + maa2_w + 5;
  int mas2_y = row4;
  int mas2_w = 15; 
  m_but_maxutil_sub2->resize(mas2_x, mas2_y, mas2_w, fld_hgt);

  //============================================================
  // Row 5
  //============================================================
  int mod1_x = sx1 + 65;
  int mod1_y = row5;
  int mod1_w = (w()/2) - mod1_x - 2*lmarg;
  m_fld_plat_model1->resize(mod1_x, mod1_y, mod1_w, fld_hgt);

  // Viewer 2  -------------------------------
  int mod2_x = sx2 + 65;
  int mod2_y = row5;
  int mod2_w = w() - mod2_x - 2*lmarg;
  m_fld_plat_model2->resize(mod2_x, mod2_y, mod2_w, fld_hgt);

  //============================================================
  // Row 6
  //============================================================
  int bpm1_x = sx1 + 65;
  int bpm1_y = row6;
  int bpm1_w = 20;
  m_but_platmod1->resize(bpm1_x, bpm1_y, bpm1_w, fld_hgt);

  int db1_x = bpm1_x + bpm1_w + 50;
  int db1_y = row6;
  int db1_w = (w()/2) - db1_x - bpm1_w;
  m_fld_bhv_debug1->resize(db1_x, db1_y, db1_w, fld_hgt);

  // Viewer 2  -------------------------------
  int bpm2_x = sx2 + 65;
  int bpm2_y = row6;
  int bpm2_w = 20;
  m_but_platmod2->resize(bpm2_x, bpm2_y, bpm2_w, fld_hgt);

  int db2_x = bpm2_x + bpm2_w + 50;
  int db2_y = row6;
  int db2_w = db1_w;
  m_fld_bhv_debug2->resize(db2_x, db2_y, db2_w, fld_hgt);

  
}

//------------------------------------------------------------- 
// Procedure: resizeWidgetsText()

void BNG_IPF_GUI::resizeWidgetsText()
{
  int text_size = 12;
  
  //===========================================================
  // Browser (Left)
  //===========================================================

  //===========================================================
  // Row 1
  //===========================================================
  // Viewer1
  m_fld_pieces1->textsize(text_size);
  m_fld_pieces1->labelsize(text_size);
  m_but_show_pcs1->labelsize(text_size);

  // Viewer 2
  m_fld_pieces2->textsize(text_size);
  m_fld_pieces2->labelsize(text_size);
  m_but_show_pcs2->labelsize(text_size);

  //===========================================================
  // Row 2
  //===========================================================
  // Viewer 1
  m_fld_smart1->textsize(text_size);
  m_fld_smart1->labelsize(text_size);
  m_but_smart1->labelsize(text_size);

  m_fld_tol1->textsize(text_size);
  m_fld_tol1->labelsize(text_size);
  m_but_tol1->labelsize(text_size);
  
  // Viewer 2
  m_fld_smart2->textsize(text_size);
  m_fld_smart2->labelsize(text_size);
  m_but_smart2->labelsize(text_size);
  
  m_fld_tol2->textsize(text_size);
  m_fld_tol2->labelsize(text_size);
  m_but_tol2->labelsize(text_size);

  //===========================================================
  // Row 3
  //===========================================================
  // Viewer 1
  m_fld_hdg_size1->textsize(text_size);
  m_fld_hdg_size1->labelsize(text_size);
  m_but_hsz_add1->labelsize(text_size);
  m_but_hsz_sub1->labelsize(text_size);
  
  m_fld_spd_size1->textsize(text_size);
  m_fld_spd_size1->labelsize(text_size);
  m_but_ssz_add1->labelsize(text_size);
  m_but_ssz_sub1->labelsize(text_size);

  // Viewer 2
  m_fld_hdg_size2->textsize(text_size);
  m_fld_hdg_size2->labelsize(text_size);
  m_but_hsz_add2->labelsize(text_size);
  m_but_hsz_sub2->labelsize(text_size);

  m_fld_spd_size2->textsize(text_size);
  m_fld_spd_size2->labelsize(text_size);
  m_but_ssz_add2->labelsize(text_size);
  m_but_ssz_sub2->labelsize(text_size);

  //===========================================================
  // Row 4
  //===========================================================
  // Viewer 1
  m_fld_minutil_cpa1->textsize(text_size);
  m_fld_minutil_cpa1->labelsize(text_size);
  m_but_minutil_add1->labelsize(text_size);
  m_but_minutil_sub1->labelsize(text_size);

  m_fld_maxutil_cpa1->textsize(text_size);
  m_fld_maxutil_cpa1->labelsize(text_size);
  m_but_maxutil_add1->labelsize(text_size);
  m_but_maxutil_sub1->labelsize(text_size);

  // Viewer 2
  m_fld_minutil_cpa2->textsize(text_size);
  m_fld_minutil_cpa2->labelsize(text_size);
  m_but_minutil_add2->labelsize(text_size);
  m_but_minutil_sub2->labelsize(text_size);

  m_fld_maxutil_cpa2->textsize(text_size);
  m_fld_maxutil_cpa2->labelsize(text_size);
  m_but_maxutil_add2->labelsize(text_size);
  m_but_maxutil_sub2->labelsize(text_size);

  //===========================================================
  // Row 5
  //===========================================================
  // Viewer 1
  m_fld_plat_model1->textsize(text_size);
  m_fld_plat_model1->labelsize(text_size);

  // Viewer 2
  m_fld_plat_model2->textsize(text_size);
  m_fld_plat_model2->labelsize(text_size);

  //===========================================================
  // Row 6
  //===========================================================
  // Viewer 1
  m_but_platmod1->labelsize(text_size);
  m_fld_bhv_debug1->textsize(text_size);
  m_fld_bhv_debug1->labelsize(text_size);

  // Viewer 2
  m_but_platmod2->labelsize(text_size);
  m_fld_bhv_debug2->textsize(text_size);
  m_fld_bhv_debug2->labelsize(text_size);
}

