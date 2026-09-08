/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: main.cpp                                             */
/*    DATE: Sep 6th, 2026                                        */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <string>
#include <cstdlib>
#include "MBUtils.h"
#include "XYSegList.h"
#include "CoverUtils.h"

using namespace std;

void showHelpAndExit();

//--------------------------------------------------------
// Procedure: main

int main(int argc, char *argv[])
{
  unsigned int vertices = 20;
  double radius = 100;
  
  for(int i=1; i<argc; i++) {
    bool handled = true;
    string argi = argv[i];
    if((argi=="-h") || (argi == "--help") || (argi=="-help"))
      showHelpAndExit();
    else if(strBegins(argi, "--verts=")) {
      string str = argi.substr(8);
      vertices = atoi(str.c_str());
    }      
    else if(strBegins(argi, "--rad=")) {
      string str = argi.substr(6);
      radius = atoi(str.c_str());
    }      
  }  

  XYSegList segl = genPolygonGP(0, 0, vertices, radius);
  
  std::cout << "Generated " << segl.size() << "-gon Vertices (X, Y):\n";
  for(unsigned int i=0; i<segl.size(); i++) 
    std::cout << segl.get_vx(i) << ", " << segl.get_vy(i) << "\n";
  return 0;
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









