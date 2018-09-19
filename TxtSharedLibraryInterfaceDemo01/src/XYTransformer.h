/*
 * XYTransformer.h
 *
 *  Created on: 16 sep. 2018
 *      Author: ing. C.van Leeuwen Btw.
 *  Version 1.1.1.1 beta
 */

#ifndef SRC_XYTRANSFORMER_H_
#define SRC_XYTRANSFORMER_H_

namespace fischertechnik
 {
    namespace joystick
    {
  class XYTransformer
  {
  public:
    XYTransformer ();
    virtual
    ~XYTransformer ();

  static bool transformXYtoLeftRight(int X, int Y, int& MotorLeft, int& MotorRight,int selectTransformation);

  static bool transformXYtoLeftRightSimple(int X, int Y, int& MotorLeft, int& MotorRight);


  };/* class XYTransformer*/
  } /* namespace joystick */
} /* namespace fischertechnik */

#endif /* SRC_XYTRANSFORMER_H_ */
