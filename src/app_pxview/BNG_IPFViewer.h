/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: BNG_IPFViewer.h                                      */
/*    DATE: May 21 2013                                          */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#ifndef BNG_IPF_VIEWER_HEADER
#define BNG_IPF_VIEWER_HEADER

#include <list>
#include <string>
#include "IvPFunction.h"
#include "IvPBehavior.h"
#include "PlatModel.h"
#include "LedgerSnap.h"
#include "Common_IPFViewer.h"
#include "XModel.h"

class BNG_IPFViewer : public Common_IPFViewer
{
 public:
  BNG_IPFViewer(int x, int y, int w, int h, const char *label=0);
  ~BNG_IPFViewer() {};

  void   draw();
  void   resetIPF();
  void   resetIPFX();
  void   updateXY();
  void   setXModel(XModel*);
  
 public: // Helm/behavior mechanics
  bool   setBehaviorType(std::string);
  void   setDomain(IvPDomain dom) {m_domain=dom;}

  void   clearBehaviorModes();

 public: // Analysis of behavior and built IPF
  std::string getInfo(std::string);

  std::vector<std::string> getModeHistory();

  unsigned int getIPFPieces()   const {return(m_ipf_pieces);}
  unsigned int getHdgEdgeSize() const {return(m_hdg_edge_size);}
  unsigned int getSpdEdgeSize() const {return(m_spd_edge_size);}

  std::string getBHVType() const {return(m_bhv_type);}

  double getMinUtilCPA() const {return(m_minutil_cpa);}
  double getMaxUtilCPA() const {return(m_maxutil_cpa);}

 public: // Behavior config 
  void   setMinUtilCPA(double);
  void   setMaxUtilCPA(double);  
  void   setCPAWindow(double);
  void   modMinUtilCPA(double);
  void   modMaxUtilCPA(double);
  void   modCPAWindow(double);

  void   setMinUtilETA(double);
  void   setMaxUtilETA(double);  
  void   modMinUtilETA(double);
  void   modMaxUtilETA(double);

  bool   setUsePlatModel(std::string);
  bool   getUsePlatModel() const {return(m_use_plat_model);}

 public: // IPF config 
  void   setHdgEdgeSize(unsigned int);
  void   setSpdEdgeSize(unsigned int);
  void   modHdgEdgeSize(int);
  void   modSpdEdgeSize(int);

  void   modTOL(double);
  bool   setUseAutoTOL(std::string) {return(true);}
  bool   getUseAutoTOL() {return(true);}

  void   modSmartPcs(int);
  bool   setUseSmartPcs(std::string);
  bool   getUseSmartPcs() const {return(m_use_smart_pcs);}
  
 public: // Rendering config
  void   modPolarPad(double);

 
 protected: // Local utility functions
  IvPBehavior*  spawnBehavior(std::string);

  IvPFunction*  buildIPF_OpRegion();
  
  void      updateInfoBuffer();
  
 private:

private: // Helm/Behavior mechanics
  IvPBehavior  *m_bhv;
  IvPDomain     m_domain;
  InfoBuffer   *m_info_buffer;
  LedgerSnap   *m_ledger_snap;
  XModel       *m_xmodel;
  
private: // Analysis of behavior and built IPF
  unsigned int  m_ipf_pieces;
  std::string   m_curr_bhv_mode;
  std::string   m_curr_bhv_submode;

private: // Behavior Config
  std::string   m_bhv_type;
  std::string   m_plat_model_config;
  bool          m_use_plat_model;

  double        m_minutil_eta;
  double        m_maxutil_eta;
  double        m_minutil_cpa;
  double        m_maxutil_cpa;
  double        m_cpa_window;
  
private: // IPF config params
  unsigned int  m_hdg_edge_size;
  unsigned int  m_spd_edge_size;
  unsigned int  m_smart_pcs;
  bool          m_use_smart_pcs;
  double        m_time_on_leg;
  
private: // Rendering config params
  double        m_polar_pad;
  double        m_radius_pad;
};

#endif 




