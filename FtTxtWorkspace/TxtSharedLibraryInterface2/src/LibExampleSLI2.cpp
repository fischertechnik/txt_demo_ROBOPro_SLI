#include <stdio.h>

#include "KeLibTxtDl.h"          // TXT Lib
#include "FtShmem.h"             // TXT Transfer Area
#include <unistd.h> //sleep
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

static bool IsInit = false;/*!< Is set by init and reset by stop */
static bool IsStop = true;/*!< Is reset by init and set by stop */

static double value_d; /*!< Example of a global double variable */
static short value_s; /*!< Example of a global short variable */

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
		 /*! <value_d = 0.0; Will be  reset in @see {stop} */
		value_s = 0;
		IsInit = true;		IsStop = false;
	} else {
		fprintf(stderr, "****init: already initialized!\n");
		return -1;
	}
	return 0;
}
/*!
 * @brief Can be used to close this SLI decently
 * @param t not in use
 * @return 0 successful, -1 error no init
 */
int stop(short *t) {
	if (!IsInit) {
		fprintf(stderr, "stop: Not initialized!\n");
		return -1; //this is an error

	} else {
		printf( "stop: already initialized!\n");
	}
	if (!IsStop) {
		printf( "stop: was not stopped!\n");
		value_d = 0.0;
		printf( "stop: set value_d = 0.0!\n");
		IsInit = false;		IsStop = true;
		//set variable and object to their initial value.
	} else {
		fprintf(stderr, "stop: was already stopped!\n");
	}

	return 0;
}
/*! \brief need to be used in the online mode.
 * \bug In the online mode, RoboPro is terminating
 * ("ERROR calling read") the contact with the SLI modules after 5 sec of inactivity.
 * As workaround for this bug, RoboPro can call this empty function every  msec <5000.
 * \param t not in use
 * \return 0
 */
int setStayAwakeShort(short msSleep) {

	if (!IsInit) {
		fprintf(stderr, "setStayAwakeShort: Not initialized!\n");
		return -1;
	} else {
		// fprintf( "ExampleSLI:setValueDouble: already initialized!\n");
	}
	//Add sleep to the StayAwake
	if(msSleep>0) std::this_thread::sleep_for(std::chrono::milliseconds(msSleep));
	else printf( "setStayAwakeShort: t not Ok!\n");
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
	/*!
	 * @brief For this example the check on IsInit has been disabled.
	 */
	/*if (!IsInit) {
		fprintf(stderr, "ExampleSLI:getValueDouble: Not initialized!\n");
		return -1;
	}*/
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
	/*!
	 * @brief For this example the check on IsInit has been disabled.
	 */
	/*if (!IsInit) {
		fprintf(stderr, "ExampleSLI:getValueShort: Not initialized!\n");
		return -1;
	}*/
	*v = value_s;
	printf("****ExampleSLI:getValueShort: %d\n", *v);
	return 0;
}

} // extern "C"
