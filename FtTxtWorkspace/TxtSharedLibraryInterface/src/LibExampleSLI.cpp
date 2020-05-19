#include <stdio.h>

#include "KeLibTxtDl.h"          // TXT Lib
#include "FtShmem.h"             // TXT Transfer Area


static bool IsInit = false;/*!< Is set by init and reset by stop */
static bool IsStop = true;/*!< Is reset by init and set by stop */

static double value_d=0.0; /*!< Example of a global double variable */
static short value_s=0; /*!< Example of a global short variable */

extern "C" {
/*******************************************************************************
 * 3 basic functions for the SLI
 *******************************************************************************/
/*!
 * @brief Can be used to initialize this SLI. <br/>
 *          It is also necessary to check if the SLI has been stopped.
 * @remark The TXT load a SLI lib on the first time that it used.
 * After ending a RoboPro program, the SLI stays in memory. The global values keep their last values.
 * @param[out] t
 * @return  0: success,continuation by the workflow
 *          Other values error, continuation by the error workflow
 */
int init(short *t) {
	if (!IsStop) {
		fprintf(stderr, "****init: was not stopped!\n");
		IsInit = false; 	IsStop = true;
		//set variable and object to their initial value.
	} else {
		printf( "****init: was stopped!\n");
	}

	if (!IsInit) {
		fprintf(stderr, "****init: Not initialized!\n");
		//set variable and object to their start value
		 /*! <value_d = 0.0; */
		value_s = 0;
		IsInit = true;		IsStop = false;
	} else {
		fprintf(stderr, "****init: already initialized!\n");
		return -1;
	}
	return 0;
}

/*****************************************************************************************
* the SLI functions.
*****************************************************************************************/
/*!

 * @brief set a global double value in the SLI
 * @param[in] v the value for value_d
 * @return  0: success,continuation by the workflow
 *          Other values error, continuation by the error workflow
 */
int setValueDouble(double v) {
	if (!IsInit) {
		fprintf(stderr, "ExampleSLI:setValueDouble: Not initialized!\n");
		return -1;
	}
	value_d = v;
	printf("****ExampleSLI:setValueDouble: %f\n", v);
	return 0;
}
/*!
 * @brief set a global short value in the SLI
 * @param[in] v the value for value_s
 * @return  0: success,continuation by the workflow
 *          Other values error, continuation by the error workflow
 */
int setValueShort(short v) {
	if (!IsInit) {
		fprintf(stderr, "ExampleSLI:setValueShort: Not initialized!\n");
		return -1;
	}
	value_s = v;
	printf("****ExampleSLI:setValueShort: %i\n", v);
	return 0;
}

/*!
 * @brief get a global double value from the SLI
 * @param[out] v the value of value_d
 * @return  0: success,continuation by the workflow
 *          Other values error, continuation by the error workflow
 */
int getValueDouble(double *v) {
	 if (!IsInit) {
		fprintf(stderr, "ExampleSLI:getValueDouble: Not initialized!\n");
		return -1;
	}
	*v = value_d;
	printf("****ExampleSLI:getValueDouble: %f\n", *v);
	return 0;
}
/*!
 * @brief get a global short value from the SLI
 * @param[out] v the value of value_s
 * @return  0: success,continuation by the workflow
 *          Other values error, continuation by the error workflow
 */
int getValueShort(short *v) {
	if (!IsInit) {
		fprintf(stderr, "ExampleSLI:getValueShort: Not initialized!\n");
		return -1;
	}
	*v = value_s;
	printf("****ExampleSLI:getValueShort: %d\n", *v);
	return 0;
}

} // extern "C"
