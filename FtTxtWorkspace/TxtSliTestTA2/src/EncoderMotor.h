/*!
 *  \brief     Encoder Motor helper for the fischertechnik TXT controller.
 *  \details   File EncoderMotor.h   for TXT firmware >= 4.6.6.
 *   project started on 2020-04-08
 *  \author    ing C van Leeeuwen Btw.
 *  \version   1.1.1.1
 *  \date      2020-04-30
 *  \pre       First initialize the system.
 *  \bug       No bugs
 *  \warning   No warnings
 *  \copyright (c) 2020 TescaWeb C. van Leeuwen
 */

#ifndef ENCODERMOTOR_H_
#define ENCODERMOTOR_H_

#include "common.h"
namespace fischertechnik {
namespace TXT {
namespace TrSli2020 {
class EncoderMotor {
private:
	INT16 MPower = 0; /*!< TA M1 power [0..512]*/
	INT16 MDistance = 0; /*!< TA M1 distance [0..]*/
	INT16 MDirection = 0; /*!< TA M1 direction -1=ccw, 0=stop, 1=cw*/
public:
	EncoderMotor();
	virtual ~EncoderMotor();
	/*!
	 * Set the power MPower for the motor .
	 * @param[in] power  [0..512]
	 * @return 	  0  success,
	 */
	void setMPower(int power);
	/*!
	 * Get the power MPower for the motor .
	 * @return  power [0..512]
	 */
	int getMPower();
	/*!
	 * Set the distance MDistance for the motor .
	 * @param[in] distance  [0..    ]
	 * @return Error 0  success,
	 */
	void setMDistance(int distance);
	/*!
	 * Get the distance MDistance for the motor .
	 * @return MDistance  [0..    ],
	 */
	int getMDistance();
	/*!
	 * Set the direction MDirection for the motor .
	 * @param[in] direction  [-1=ccw, 0=stop, 1=cw]
	 * @return Error 0  success,
	 */
	void setMDirection(int direction);
	/*!
	 * Get the direction MDirection for the motor
	 * @return the direction [direction -1=ccw, 0=stop, 1=cw]
	 */
	int getMDirection();

	/*!
	 * Get the combined power MPower and MDirection for the motor .
	 * @return power  [-512..0..512]
	 */
	int getMPowerDirection();
	/*!
	 * Set the power MPower and MDirection for the motor .
	 * @param[in] dirpow  [-512..0..512]
	 * @return Error 0  success,
	 */
	void setMPowerDirection(int dirpow);

	/*!
	 * Start Motor mId  with  MDistance and MPower.
	 * Blocking. Wait until the end is reached.
	 * @param mId    Motor  [1,2,3,4]
	 * @return Error 0  success,
	 *               -2 if MotoIor thread in not running
	 *               -5 if mId out of range
	 */
	int setMStartWait(INT16 mId);

	/*!
	 * Starts Motor mId  with  MDistance and MPower
	 * Not blocking. In the RoboPro program needs Ready to be detect in a normal way.
	 * @param mId Motor [1,2,3,4]
	 * @return Error 0  success,
	 *               -2 if MotoIor thread in not running
	 *               -5 if mId  out of range */
	int setMStart(INT16 mId);
	/*!
	 * @param mId    Motor  [1,2,3,4]
	 * @return Error 0  success,
	 *               -2 if MotoIor thread in not running
	 *               -5 if mId  out of range
	 */
	int setMStop(INT16 mId);
};
} /* namespace TrSli */
} /* namespace TXT */
} /* namespace fischertechnik */
#endif /* ENCODERMOTOR_H_ */
