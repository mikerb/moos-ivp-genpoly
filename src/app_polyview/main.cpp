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
  int i;
  unsigned int j;

  // Look for a request for version information
  if(scanArgs(argc, argv, "-v", "--version", "-version")) {
    showReleaseInfo("polyview", "gpl");
    return(0);
  }
  
  // Look for a request for usage information
  if(scanArgs(argc, argv, "-h", "--help", "-help")) {
    cout << "Usage: polyview [filename] [filename]..." << endl;
    return(0);
  }

  Fl::add_idle(idleProc);
  POLY_GUI* gui = new POLY_GUI(900, 800, "polyview");

  string tif_file = "MIT_SP.tif";  // default

  for(i=1; i<argc; i++) {
    string argi  = tolower(argv[i]);
    if((argi == "mit") || (argi=="charles"))
      tif_file = "MIT_SP.tif";
    else if((argi == "forrest-lake") || (argi=="fl"))
      tif_file = "forrest19.tif";
  }

  vector<string>    all_poly_strings;
  vector<string>    all_segl_strings;
  vector<string>    all_point_strings;

  for(i=1; i<argc; i++) {
    string argi  = argv[i];
    
    if(strContains(argi, ".tif"))
      tif_file = argi;
    else if(argi == "-noimg")
      tif_file = "";
    else {
      vector<string> svector;
      svector = readEntriesFromFile(argi, "poly:polygon");
      for(j=0; j<svector.size(); j++)
	all_poly_strings.push_back(svector[j]);

      svector = readEntriesFromFile(argi, "segl:seglist:points");
      for(j=0; j<svector.size(); j++)
	all_segl_strings.push_back(svector[j]);

      svector = readEntriesFromFile(argi, "point");
      for(j=0; j<svector.size(); j++)
	all_point_strings.push_back(svector[j]);
    }
  }
 
  gui->pviewer->setParam("tiff_file", tif_file);

  cout << "# of file polys: " << all_poly_strings.size() << endl;
  for(j=0; j<all_poly_strings.size(); j++)
    gui->pviewer->setParam("view_polygon", all_poly_strings[j]);

  cout << "# of file points: " << all_point_strings.size() << endl;
  for(j=0; j<all_point_strings.size(); j++)
    gui->pviewer->setParam("view_point", all_point_strings[j]);

  cout << "# of file seglists: " << all_segl_strings.size() << endl;
  for(j=0; j<all_segl_strings.size(); j++)
    gui->pviewer->setParam("view_seglist", all_segl_strings[j]);
  
  gui->updateXY();

  return Fl::run();
}











