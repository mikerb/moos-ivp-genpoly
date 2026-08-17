/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: main.cpp                                             */
/*    DATE: Nov 22nd, 2025                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include <vector>
#include "POLY_GUI.h"
#include "MBUtils.h"
#include "ReleaseInfo.h"
#include "IO_GeomUtils.h"
#include "XYPolygon.h"
#include "XYSegList.h"
#include "XYPoint.h"
#include "LMV_Utils.h"
#include "XYFormatUtilsPoly.h"
#include "XYFormatUtilsPoint.h"

using namespace std;

void idleProc(void *);
void showHelpAndExit();

//--------------------------------------------------------
// Procedure: idleProc

void idleProc(void *)
{
  Fl::flush();
  millipause(10);
}

//--------------------------------------------------------
// Procedure: main

int main(int argc, char *argv[])
{
  string tif_file = "MIT_SP.tif";  // default
  string border_file;
  

  for(int i=1; i<argc; i++) {
    string argi  = argv[i];

    bool handled = true;
    if((argi == "-h") || (argi == "--help"))
      showHelpAndExit();
    
    else if((argi == "-v") || (argi == "--version")) {
      showReleaseInfo("polyview", "gpl");
      return(0);
    }
    
    else if(strEnds(argi, ".tif"))
      tif_file = argi;
    
    else if(strEnds(argi, ".txt"))
      border_file = argi;    
  }

  Fl::add_idle(idleProc);
  POLY_GUI* gui = new POLY_GUI(900, 800, "polyview");

  gui->pviewer->setParam("tiff_file", tif_file);  
  gui->pviewer->setParam("border_file", border_file);  
  gui->updateXY();

  return Fl::run();
}


//------------------------------------------------------------
// Procedure: showHelpAndExit()                                  

void showHelpAndExit()
{
  cout << "Usage: " << endl;
  cout << "  polyview [file.tif] [border.txt]                  " << endl;
  cout << "                                                    " << endl;
  cout << "Synopsis:                                           " << endl;
  cout << "  " << endl;
  cout << "  " << endl;
  cout << "                                                    " << endl;
  cout << "Options:                                            " << endl;
  cout << "  -h,--help            Displays this help message   " << endl;
  exit(0);
}









