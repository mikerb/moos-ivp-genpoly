/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: POLY_GUI.cpp                                          */
/*    DATE: Nov 22nd, 2025                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include <cstdio>
#include "EPATH_GUI.h"
#include "MBUtils.h"

using namespace std;

//--------------------------------------------------------------------------- 
// Procedure: initWidgets()     

void EPATH_GUI::initWidgets()
{
  m_but_draw_pts = new Fl_Button(0, 0, 1, 1, "Draw Pts");
  m_but_draw_pts->clear_visible_focus();
  m_but_draw_pts->callback((Fl_Callback*)EPATH_GUI::cb_DrawPts);
  m_but_draw_pts->shortcut('p');
			   m_but_draw_pts->tooltip("Shortcut key is 'p'");

  m_but_draw_segl = new Fl_Button(0, 0, 1, 1, "Draw Segl");
  m_but_draw_segl->clear_visible_focus();
  m_but_draw_segl->callback((Fl_Callback*)EPATH_GUI::cb_DrawSegl);
  m_but_draw_segl->shortcut('p');
  m_but_draw_segl->tooltip("Shortcut key is 's'");

  m_but_draw_hull = new Fl_Button(0, 0, 1, 1, "Draw Hull");
  m_but_draw_hull->clear_visible_focus();
  m_but_draw_hull->callback((Fl_Callback*)EPATH_GUI::cb_DrawHull);
  m_but_draw_hull->shortcut('u');
  m_but_draw_hull->tooltip("Shortcut key is 'u'");

  m_but_draw_gpoly = new Fl_Button(0, 0, 1, 1, "Draw GPoly");
  m_but_draw_gpoly->clear_visible_focus();
  m_but_draw_gpoly->callback((Fl_Callback*)EPATH_GUI::cb_DrawGPoly);
  m_but_draw_gpoly->shortcut('g');
  m_but_draw_gpoly->tooltip("Shortcut key is 'g'");
  
  m_but_solve10 = new Fl_Button(0, 0, 1, 1, "Solve10");
  m_but_solve10->clear_visible_focus();
  m_but_solve10->callback((Fl_Callback*)EPATH_GUI::cb_Solve);
  m_but_solve10->shortcut('s');
  m_but_solve10->tooltip("Shortcut key is 's'");
  
  m_but_clear_polys = new Fl_Button(0, 0, 1, 1, "Clear Polys");
  m_but_clear_polys->clear_visible_focus();
  m_but_clear_polys->callback((Fl_Callback*)EPATH_GUI::cb_ClearPolys);

  m_but_clear_solve = new Fl_Button(0, 0, 1, 1, "Clear Solve");
  m_but_clear_solve->clear_visible_focus();
  m_but_clear_solve->callback((Fl_Callback*)EPATH_GUI::cb_ClearSolve);

  m_but_keep_fulls = new Fl_Button(0, 0, 1, 1, "Keep Fulls");
  m_but_keep_fulls->clear_visible_focus();
  m_but_keep_fulls->callback((Fl_Callback*)EPATH_GUI::cb_KeepFulls);

  m_but_drop_fulls = new Fl_Button(0, 0, 1, 1, "Drop Fulls");
  m_but_drop_fulls->clear_visible_focus();
  m_but_drop_fulls->callback((Fl_Callback*)EPATH_GUI::cb_DropFulls);

  m_but_drop_fulls = new Fl_Button(0, 0, 1, 1, "Drop Fulls");
  m_but_drop_fulls->clear_visible_focus();
  m_but_drop_fulls->callback((Fl_Callback*)EPATH_GUI::cb_DropFulls);

  m_fld_snap = new Fl_Output(0, 0, 1, 1, "snap:"); 
  m_fld_snap->set_output();

  m_fld_polys = new Fl_Output(0, 0, 1, 1, "polys:"); 
  m_fld_polys->set_output();

  m_fld_solve = new Fl_Output(0, 0, 1, 1, "solve:"); 
  m_fld_solve->set_output();

  //----------------------------------------------------------
  m_fld_segl = new Fl_Output(0, 0, 1, 1, "seglist:"); 
  m_fld_segl->set_output();

  m_fld_gpoly = new Fl_Output(0, 0, 1, 1, "gpoly:"); 
  m_fld_gpoly->set_output();
}

//--------------------------------------------------------------------------- 
// Procedure: resizeWidgetsShape()     

void EPATH_GUI::resizeWidgetsShape()
{
  int extra_wid = w() - m_start_wid;
  if(extra_wid < 0)
    extra_wid = 0;
  int field_hgt = 20;

  int row1 = h() - 120;
  int row2 = row1 + 30;
  int row3 = row2 + 30;
  int row4 = row3 + 30;

  int wid1 = 80;
  int wid2 = 90;
  int wid3 = 40;
  int wid4 = 60;
  int wid5 = 60;
  int wid6 = 60;
  int wid7 = 60;
  int wid8 = 100;
  //int wid9 = 50;
  int sep = 10;

  int col1 = 10;
  int col2 = col1 + wid1 + sep;
  int col3 = col2 + wid2 + sep + 50; 
  int col4 = col3 + wid3 + sep + 40;
  int col5 = col4 + wid4 + sep + 50;
  int col6 = col5 + wid5 + sep + 50;
  int col7 = col6 + wid6 + sep + 60;
  int col8 = col7 + wid7 + sep + 30;

  //-------------------- Column 1
  int pts_x = col1;
  int pts_y = row1;
  int pts_wid = wid1;
  m_but_draw_pts->resize(pts_x, pts_y, pts_wid, field_hgt);
  
  int hul_x = col1;
  int hul_y = row2;
  int hul_wid = wid1;
  m_but_draw_hull->resize(hul_x, hul_y, hul_wid, field_hgt);
  
  //-------------------- Column 2
  int seg_x = col2;
  int seg_y = row1;
  int seg_wid = wid2;
  m_but_draw_segl->resize(seg_x, seg_y, seg_wid, field_hgt);
  
  int gpo_x = col2;
  int gpo_y = row2;
  int gpo_wid = wid2;
  m_but_draw_gpoly->resize(gpo_x, gpo_y, gpo_wid, field_hgt);

  //-------------------- Column 3
  int snp_x = col3;
  int snp_y = row1;
  int snp_wid = wid3;
  m_fld_snap->resize(snp_x, snp_y, snp_wid, field_hgt);

  int fpo_x = col3;
  int fpo_y = row2;
  int fpo_wid = wid3;
  m_fld_polys->resize(fpo_x, fpo_y, fpo_wid, field_hgt);

  //-------------------- Column 4
  int bso_x = col4;
  int bso_y = row1;
  int bso_wid = wid4;
  m_but_solve10->resize(bso_x, bso_y, bso_wid, field_hgt);

  int sot_x = col4;
  int sot_y = row2;
  int sot_wid = wid4;
  m_fld_solve->resize(sot_x, sot_y, sot_wid, field_hgt);

  //-------------------- Column 6
  int kfull_x = col6;
  int kfull_y = row1;
  int kfull_wid = wid6;
  m_but_keep_fulls->resize(kfull_x, kfull_y, kfull_wid, field_hgt);

  int dfull_x = col6;
  int dfull_y = row2;
  int dfull_wid = wid6;
  m_but_drop_fulls->resize(dfull_x, dfull_y, dfull_wid, field_hgt);
  
  //-------------------- Column 7
  int clep_x = col7;
  int clep_y = row1;
  int clep_wid = wid8;
  m_but_clear_polys->resize(clep_x, clep_y, clep_wid, field_hgt);

  int cles_x = col7;
  int cles_y = row2;
  int cles_wid = wid8;
  m_but_clear_solve->resize(cles_x, cles_y, cles_wid, field_hgt);
  
  //---------------------------------------------------------
  // Bottom Two ROWS
  //---------------------------------------------------------
  int lst_x = 80;
  int lst_y = row3;
  int lst_wid = w()-90;
  m_fld_segl->resize(lst_x, lst_y, lst_wid, field_hgt);

  //---------------------------------------------------------
  int gps_x = 80;
  int gps_y = row4;
  int gps_wid = w()-90;
  m_fld_gpoly->resize(gps_x, gps_y, gps_wid, field_hgt);
  
 }
 
//--------------------------------------------------------------------------- 
// Procedure: resizeWidgetsText()

void EPATH_GUI::resizeWidgetsText()
{
  int text_size  = 12;
  int label_size = 12;

  m_but_draw_pts->labelsize(label_size);
  m_but_draw_segl->labelsize(label_size);
  m_but_draw_hull->labelsize(label_size);
  m_but_draw_gpoly->labelsize(label_size);

  m_but_solve10->labelsize(label_size);
  m_but_clear_polys->labelsize(label_size);
  m_but_clear_solve->labelsize(label_size);
  
  m_fld_snap->textsize(text_size);
  m_fld_snap->labelsize(label_size);

  m_fld_polys->textsize(text_size);
  m_fld_polys->labelsize(label_size);

  m_fld_solve->textsize(text_size);
  m_fld_solve->labelsize(label_size);

  m_fld_segl->textsize(text_size);
  m_fld_segl->labelsize(label_size);

  m_fld_gpoly->textsize(text_size);
  m_fld_gpoly->labelsize(label_size);
}

