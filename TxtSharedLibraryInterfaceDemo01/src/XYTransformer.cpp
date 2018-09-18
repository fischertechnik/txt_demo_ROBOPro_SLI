/*
 * XYTransformer.cpp
 *
 *  Created on: 16 sep. 2018
 *      Author: Carel
 *  Version 1.1.1.1 beta
 */

#include "XYTransformer.h"
#include <stdio.h>          // for printf()
#include <unistd.h>         // for sleep()
#include <math.h>

namespace fischertechnik
{
  namespace joystick
  {

    int
    signnum_typical (double x)
    {
      if (x > 0.0)
	return 1;
      if (x < 0.0)
	return -1;
      return 0;
    }
    double
    transform00 (double x)
    {
      return x;
    }

    double
    transform01 (double x)
    {
      int sign = signnum_typical (x);
      x = fabs (x);
      double y;
      if (x < 0.1)
	y = 0;
      else
	{
	  y = (log10 (x) + 1.0);
	}
      return sign * y;
    }
    //in: -1.0 <=x <=1.0  out: -1.0 <=y <=1.0
    // offset (log10(0.05) + variable part
    double
    transform02 (double x)
    {
      int sign = signnum_typical (x);
      x = fabs (x);
      double y;
      const double a = 0.05;
      if (x < a)
	y = 0;
      else
	{
	  y = (log10 (x) - log10 (a) / -log10 (a));
	}
      return sign * y;
    }
    //in: -1.0 <=x <=1.0  out: -1.0 <=y <=1.0
    // offset (=0.45) + variable part
    double
    transform03 (double x)
    {
      int sign = signnum_typical (x);
      x = fabs (x);
      double y;
      const double offset = 0.45;
      if (x < offset)
	y = 0;
      else
	{
	  y = ((1.0 - offset) * x + offset);
	}
      //      if (y > 1.0)
      //          LogWarning("FtRoboticMathService#X= " + x + " Y= " + y);

      return sign * y;
    }
    XYTransformer::XYTransformer ()
    {
      // TODO Auto-generated constructor stub

    }

    XYTransformer::~XYTransformer ()
    {
      // TODO Auto-generated destructor stub
    }

    // in: x and y both [-15..0..15]
    // out: if true MotorRight and MotorLeft [-512..0.. 512]
    bool    XYTransformer::transformXYtoLeftRight (int X, int Y, int& MotorLeft,
					   int& MotorRight,
					   int selectTransformation)
    {
      bool ret = true;
      MotorLeft = 0;
      MotorRight = 0;
      double left = 0.0, right = 0.0;
      int quadrant = 0;
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

      //  double move, turn, tcoeff;
      if ((fabs (x) > 1.0) || (fabs (y) > 1.0))
	{
	  //LogError("FtRoboticMathService#ToTwoWheelHandler:X or Y out of range (-1.0<=value<=1.0)");

	}

      // First hypotenuse
      double zz = sqrt (x * x + y * y);
      if (zz > 1.0)
	zz = 1;
      //TX-C Power has a range of 0..512 steps, in this service there are 32+1 powerlevel defined.
      //level01=16 level 32=512 and level00 is 0
      //
      double rad = 0.0, angle = 0.0;
      if (fabs (zz) < 0.0002)
	{
	  // move = 0; turn = 0;
	}
      else
	{
	  // angle in radians
	  rad = acos (fabs (x) / zz);
	  // and in degrees
	  angle = rad * 180 / M_PI;

	  // Now angle indicates the measure of turn
	  // Along a straight line, with an angle o, the turn co-efficient is same
	  // this applies for angles between 0-90, with angle 0 the co-eff is -1
	  // with angle 45, the co-efficient is 0 and with angle 90, it is 1
	  //  tcoeff = -1 + (angle / 90) * 2;
	  //  turn = tcoeff * math.Abs(math.Abs(y) - math.Abs(x));
	  //  turn = math.Round(turn * 100.0) / 100.0;

	  // And max of y or x is the movement
	  //  move = math.Max(math.Abs(y), math.Abs(x));
	}

      if (zz >= 0.01)
	{
	  switch (quadrant)
	    {
	    case 0:        //niets
	      break;
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
	  //LogWarning("FtRoboticMathService#\nX= " + x + " Y= " + y
	  //    + "\n zz=" + zz
	  //    + "\nleft= " + left + " right= " + right);
	}
      //double speed = 0;
      switch (selectTransformation)
	{
	case 1:
	  break;
	case 2:
	  left = transform01 (left);
	  right = transform01 (right);
	  break;
	case 3:
	  left = transform02 (left);
	  right = transform02 (right);
	  break;
	case 4:
	  left = transform03 (left);
	  right = transform03 (right);
	  break;
	default:
	  break;
	}

      MotorLeft = (int) rint (left * 512);
      MotorRight = (int) round (right * 512);

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
