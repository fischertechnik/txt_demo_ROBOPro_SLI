/*
 * XYTransformer.cpp
 * Joystick to Differential Drive - Throttle & Turn
 * Created on: 16 sep. 2018
 *      Author: ing. C.van Leeuwen Btw.
 *  Version 1.1.1.1 beta
 *  version 1.1.1.2 2019-02 improvement of the transformations.
 *  The fischertechnik x-y joystick are not lineair, so I replaced the calculation by a table.
 *  	transformer1..5 are using  tables.
 *  version 1.1.1.4 2019-05
 *      I adjust some small mistakes in the algorithm.
 * See also: https://www.impulseadventure.com/elec/robot-differential-steering.html
 *           Joystick to Differential Drive - Throttle & Turn
 */

#include "XYTransformer.h"
#include <stdio.h>          // for printf()
#include <unistd.h>         // for sleep()
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

namespace fischertechnik
{
  namespace joystick
  { //                        0    1    2     3      4     5     6     7     8     9   10
    const double tr1[] =
      { 0.0, 0.31, 0.44, 0.52, 0.61, 0.70, 0.78, 0.85, 0.91, 0.95, 1.0 };
    const double tr2[] =
      { 0.0, 0.35, 0.40, 0.45, 0.65, 0.69, 0.74, 0.80, 0.86, 0.92, 1.0 };
    //                        0    1    2     3      4     5     6     7     8     9   10,     11,   12,   13   ,14   15
    const double tr3[] =
      { 0.0, 0.36, 0.41, 0.45, 0.50, 0.54, 0.59, 0.64, 0.68, 0.73, 0.77, 0.82,
	  0.86, 0.91, 0.95, 1.0 };
    const double tr4[] =
      { 0.0, 0.38, 0.43, 0.48, 0.53, 0.59, 0.65, 0.71, 0.76, 0.81, 0.86, 0.90,
	  0.94, 0.96, 0.98, 1.0 };
    const double tr5[] =
      { 0.0, 0.39, 0.45, 0.50, 0.53, 0.59, 0.65, 0.71, 0.76, 0.81, 0.86, 0.91,
	  0.94, 0.97, 0.99, 1.0 };

 // Sign of x
 // @return 1 means >= 0.0, -1 means < 0.0
    int
    signnum_typical (double x)
    {
      if (x >= 0.0)
	return 1;
      if (x < 0.0)
	return -1;
      return 0;
    }
    // @return x, no changes
    double
    transform00 (double x)
    {
      return x;
    }
    //

    double
    transform1 (double x, int& index)
    {
      int sign = signnum_typical (x);
      x = fabs (x);
      index = (int) round (x * (10));
      return sign * tr1[index];
    }
    /*in: -1.0 <=x <=1.0  out: -1.0 <out <=1.0
     */
    double
    transform2 (double x, int& index)
    {
      int sign = signnum_typical (x);
      x = fabs (x);
       index = (int) round (x * (10));
      return sign * tr2[index];
    }
    /*in: -1.0 <=x <=1.0  out: -1.0 <=y <=1.0
     offset (log10(0.05) + variable part
     */
    double
    transform3    (double x, int& index)
    {
      int sign = signnum_typical (x);
      x = fabs (x);
      index = (int) round (x * (15));
      return sign * tr3[index];
    }
    /*in: -1.0 <=x <=1.0  out: -1.0 <=y <=1.0
     @return y based on a table
     */
    double
     transform4 (double x, int& index)
    {
      int sign = signnum_typical (x);
      x = fabs (x);
      index = (int) round (x * (15));
      return sign * tr4[index];
    }
    double
    transform5 (double x, int& index)
    {
      int sign = signnum_typical (x);
      x = fabs (x);
      index = (int) round (x * (15));
      return sign * tr5[index];
    }

    XYTransformer::XYTransformer ()
    {
      // TODO Auto-generated constructor stub
    }

    XYTransformer::~XYTransformer ()
    {
      // TODO Auto-generated destructor stub
    }

    /* @param X,Y in: X and Y both [-15..0..15]
     * @param selectTransformation in:
     *            0= no changes
     *            1..5= tranformation with table 1..5
     * out:  power for both motor ID left and right motor
     * @return  if true MotorRight and MotorLeft [-512..0.. 512]
     * @remark The joystick values are not a circle
     */
    bool
    XYTransformer::transformXYtoLeftRight (int X, int Y, int& MotorLeft,
					   int& MotorRight,
					   int selectTransformation)
    {

      //   ofstream myfile;   myfile.open ("XYTransformer.log",ios::out | ios::app)
    //  FILE *stream;
     // stream = fopen ("XYTransformer.log", "a");
      //==================================
      bool printCondition = (X>0 && X<4) || (Y>0 && Y<4) || (X==15) ||(Y==15);
      bool ret = true;
      int quadrant = 0;
      const int delta = 1, max = 15;      //joystick 0..15
      MotorLeft = 0;
      MotorRight = 0;
      //======= x and Y normalized to 1.0 ====================================
      double x = X / 15.0, y = Y / 15.0;

      if ((fabs (x) < 0.02) && (y >= 0.02))
	quadrant = 1;
      else if ((fabs (x) < 0.02) && (y <= -0.02))
	quadrant = 5;
      else if ((fabs (y) < 0.02) && (x >= 0.02))
	quadrant = 3;
      else if ((fabs (y) < 0.02) && (x <= -0.02))
	quadrant = 7;
      else if ((y >= 0.02) && (x >= 0.02))
	quadrant = 2;
      else if ((y >= 0.02) && (x <= -0.02))
	quadrant = 8;
      else if ((y <= -0.02) && (x >= 0.02))
	quadrant = 4;
      else if ((y <= -0.02) && (x <= -0.02))
	quadrant = 6;

      if ((fabs (x) > 1.0) || (fabs (y) > 1.0))
	{
	  //LogError("FtRoboticMathService#ToTwoWheelHandler:X or Y out of range (-1.0<=value<=1.0)");
	}
      double zz = sqrt (x * x + y * y), rad = 0.0, angle = 0.0;
      const double minZZ = 0.01;

/*      if ((printCondition))
	{
	  fprintf (
	      stream,
	      "X==========================: joystick Left [%d , %d][%6.2f,%6.2f ] quadrant=%d, tr=%d zz=%f\n",
	      X, Y, x, y, quadrant, selectTransformation, zz);
	}
	*/
      // First hypotenuse, 0.0 <= zz <= 1.0, however the fischertechnik joystick X-y values are not a real circle
     //   fprintf(stream,
     //  "========== %6.2f, %6.2f, %6.2f, %6.2f, %6.2f....%6.2f, %6.2f, %6.2f", tr5[0],tr5[1], tr5[2],tr5[3], tr5[4],tr5[14], tr5[15],tr5[16] );

     // fprintf (stream, "==========\n");
    	if (zz < minZZ)
	  {	  // move = 0; turn = 0;
	  }
	else
	  { // angle in radians
	    rad = acos (fabs (x) / zz);
	    // and in degrees
	    angle = rad * 180 / M_PI;
	  }

      double left = 0.0, right = 0.0;
      if (zz > 1.0)
	{
	 // fprintf (stream, "!!!!!!!!!!!!!: jzz=%f\n", zz);
	  zz = 1.0;
	}
      if (zz >= minZZ)
	{
	  switch (quadrant)
	    {
	    case 0:
	      break;     //do nothing
	    case 1:        //Ml +1; Mr = 1
	      left = zz;
	      right = zz;
	      break;
	    case 2:        //Ml +1 ; Mr +1=>0=>-1 ..
	      left = zz;
	      right = tan (rad - M_PI / 4) * zz;
	      break;
	    case 3:        //Ml +1 ; Mr = -1
	      left = zz;
	      right = -zz;
	      break;
	    case 4:        //Ml +1=>0=>-1 ;  Mr -1
	      left = -tan (rad - M_PI / 4) * zz;
	      right = -zz;
	      break;
	    case 5:        //Ml -1 ; Mr -1
	      left = -zz;
	      right = -zz;
	      break;
	    case 6:        //Ml -1 ;  Mr -1=>0=>+1
	      left = -zz;
	      right = -tan (rad - M_PI / 4) * zz;
	      break;
	    case 7:        //Ml -1 ; Mr +1
	      left = -zz;
	      right = zz;
	      break;
	    case 8:        //Ml -1=>0=>+1 ;  Mr +1
	      left = tan (rad - M_PI / 4) * zz;
	      right = zz;
	      break;
	    }
	}
      else
	{
	  left = 0.0;
	  right = 0.0;
	}
      //Get the power from the table
      double tLeft = 0.0, tRight = 0.0;
      int indexL = -1, indexR = -1;
      switch (selectTransformation)
	{
	case 0:
	  break;
	case 1:
	  tLeft = transform1 (left, indexL);
	  tRight = transform1 (right, indexR);
	  break;
	case 2:
	  tLeft = transform2 (left, indexL);
	  tRight = transform2 (right, indexR);
	  break;
	case 3:
	  tLeft = transform3 (left, indexL);
	  tRight = transform3 (right, indexR);
	  break;
	case 4:
	  tLeft = transform4 (left, indexL);
	  tRight = transform4 (right, indexR);
	  break;
	case 5:
	  tLeft = transform5 (left, indexL);
	  tRight = transform5 (right, indexR);
	  break;
	default:
	  break;
	}
   /*   if (printCondition)
	fprintf (
	    stream,
	    "==ZZ=======================: joystick Left [%d , %d][%6.2f,%6.2f ] tL,tR=[%6.2f,%6.2f ] index=[%d,%d], quadrant=%d zz=%6.2f angle=%6.2f \n",
	    X, Y, x, y, tLeft, tRight, indexL, indexR, quadrant, zz, angle);
	    */
      MotorLeft = (int) rint (tLeft * 512);
      MotorRight = (int) rint (tRight * 512);
   //   fclose (stream);
      // myfile.close();
      return ret;
    }

    // in: x and y both [-15..0..15]
    // out: if true MotorRight and MotorLeft [-512..0.. 512]
    bool
    XYTransformer::transformXYtoLeftRightSimple (int X, int Y, int& MotorLeft,
						 int& MotorRight)
    {
      MotorLeft = X * 512 / 15;
      MotorRight = Y * 512 / 15;
      return true;
    }

  }
} /* namespace fischertechnik */
