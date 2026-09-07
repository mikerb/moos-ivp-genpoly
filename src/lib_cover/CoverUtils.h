/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Engineering, MIT, Cambridge MA    */
/*    FILE: CoverUtils.h                                        */
/*    DATE: Sep 6th, 2026                                       */
/*                                                               */
/* This is unreleased BETA code. No permission is granted or     */
/* implied to use, copy, modify, and distribute this software    */
/* except by the author(s), or those designated by the author.   */
/*****************************************************************/
 
#ifndef COVER_UTILS_HEADER
#define COVER_UTILS_HEADER

#include <vector>
#include "XYSegList.h"

XYSegList genPolygonGP(double cx=0, double cy=0,
		       int verts=15, double rad=100);

#endif
