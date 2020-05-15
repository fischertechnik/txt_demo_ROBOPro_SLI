/*
 * XYTransformer.h
 *
 *  Created on: 16 sep. 2018
 *      Author: ing. C.van Leeuwen Btw.
 *  Version 1.1.1.1
 *    version 1.1.1.4 2019-05
 *      I adjust some small mistakes in the algorithm.
 *
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
    /* @param X,Y in: X and Y both [-15..0..15]
        * @param selectTransformation in:
        *            0= no changes
        *            1= tranformation algoritme
        *            2= tranformation algoritme
        *            3= tranformation with table 11
        *            4= tranformation with table 12
        *            5= tranformation with table 13, tested with the FT-bot
        * out:  power for both motor ID left and right motor
       * @return  if true MotorRight and MotorLeft [-512..0.. 512]
       */
  static bool transformXYtoLeftRight(int X, int Y, int& MotorLeft, int& MotorRight,int selectTransformation);

  static bool transformXYtoLeftRightSimple(int X, int Y, int& MotorLeft, int& MotorRight);//only for testing


  };/* class XYTransformer*/
  } /* namespace joystick */
} /* namespace fischertechnik */

#endif /* SRC_XYTRANSFORMER_H_ */
