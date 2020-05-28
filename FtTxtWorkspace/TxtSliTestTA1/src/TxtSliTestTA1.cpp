/*!
 *   \copyright (c) 2019-2020 C. van Leeuwen
 *    \version   1.1.1.1
 *  \file TxtSliTestTA1.cpp
 *  \brief Example about how to use the TA
 *   1 Encoder motor also connected to the fast counter
 */
/*!
 \def SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
 Sets the compilation level of SPDLOG.
 */
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <stdio.h>          // for printf()
#include "KeLibTxtDl.h"     // TXT Lib
#include "FtShmem.h"        // TXT Transfer Area see KeLib header
#include <iostream>       // std::cout
/*!
 \brief Is needed for the TXT libraries.
 */
unsigned int DebugFlags;
FILE *DebugFile;

/*!
 \brief Includes for the spdlog
 */
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"

using namespace std;

/*!
 \brief spdlog globals, two loggers.
 */
static std::shared_ptr<spdlog::logger> console = nullptr; /*!< spdlogger */
//spdlog::rotating_logger_mt<spdlog::async_factory>("console", "Data/SliCon.log", 248576 * 1, 8,true);
static std::shared_ptr<spdlog::logger> file_logger = nullptr; /*!< spdlogger */
//spdlog::rotating_logger_mt<spdlog::async_factory>("file_logger", "Data/SliLogr.log", 248576 * 1, 8,true);

//static is optional, the variable will be created by the runtime when
//it loads the SLI.
//Remark: The SLi is not unloaded when a RoboPro program has been terminated/stop.
static bool IsInit = false; /*!< Set after initialization*/
static bool IsStop = false; /*!< Set after stop */
static INT16 MPower = 0; /*!< TA M1 power*/
static INT16 MDistance = 0; /*!< TA M1 distance*/



extern "C" {

/**********************************************************************
 * init, stop and StayAwake
 ***********************************************************************/

/*!
 * @param *t input, not in use
 * @return  0: success, otherwise error ()
 */
int init(short *t) {
	if (IsStop) {
		//Expected;
		printf("*****init: IsStop\n");
		IsStop = false;
	} else {
		printf("*****init: Not expected, was not IsStop\n");
		//Execute the stop
	}
	if (!IsInit) {
		//Todo: Init what is necessary
		IsInit = true;
		printf("*****init: Set has been done\n");
	} else {
		printf("*****init: Not expected, was already done ");
		//What is the meaning of this?
	}
	return 0;
}
/*!
 * Empty function as work around for the 5sec bug in the online mode
 * @param[in] t not in use
 * @return  0: success, otherwise error ()
 */
int setKeepAwakeShort(short t) {
	return 0;
}

/*!
 * @param[out] *t  not in use
 * @return  0: success, otherwise error ()
 */
int stop(short *t) {
	if (IsInit) {
		//
		IsInit = false;
		printf("*****stop: IsInit\n");
	} else {
		printf("*****stop: Not IsInit\n");
	}
	if (!IsStop) {
		//Todo: clean up
		IsStop = true;
		printf("*****stop: Not IsStop\n");
	} else {
		printf("*****stop: IsStop\n");
	}
	return 0;
}

/**********************************************************************
 * SpdLog related
 ***********************************************************************/

/*!
 *Init both spd loggers<br/>
 * console and file_logger
 * @param[out] *t not in use
 * @see  <a href="https://github.com/gabime/spdlog/blob/v1.x/README.md">SPDLog info</a>
 * @return 0
 */
int getInitSpdLogShort(short *t) {
	std::cout << "############Start init  " << std::endl;
	try {
		if (spdlog::get("file_logger") == nullptr) {
			file_logger = spdlog::rotating_logger_mt("file_logger",
					"/opt/knobloch/Data/SliFx.log", 248576 * 1, 8, true);
			std::cout << "############file_logger init " << std::endl;
		} else {
			SPDLOG_LOGGER_INFO(file_logger, "flush ");
			std::cout << "############file_logger flush" << std::endl;
			file_logger->flush();
		}

		if (spdlog::get("console") == nullptr) {
			std::cout << "############Not init " << std::endl;
			console = spdlog::stdout_color_mt("console");
			std::cout << "############console init " << std::endl;
		} else {
			SPDLOG_LOGGER_INFO(console, "flush ");
			std::cout << "############console flush " << std::endl;
			console->flush();
		}
		spdlog::set_pattern("[%t][%Y-%m-%d %T.%e][%L](%^%@%$ %!) %v");
		//spdlog::get("console")->set_pattern("####[%t %T.%e][%L][%^%@:%!%$] %v");
		spdlog::set_level(spdlog::level::trace);

	} catch (const spdlog::spdlog_ex &ex) {
		std::cout << "############init:Log initialization failed: " << ex.what()
				<< std::endl;
		return -2;
	}
	SPDLOG_LOGGER_INFO(file_logger, "Initialization has been finished.");
	SPDLOG_LOGGER_INFO(console, "Initialization has been finished.");

	*t = (short) 25;
	return 0;
}

/*!
 * Drop only Flush the loggers<br/>
 * console and file_logger
 * @see  <a href="https://github.com/gabime/spdlog/blob/v1.x/README.md">SPDLog info</a>
 * @return  0: success, otherwise error ()
 */

int getDropdLogShort(short *t) {
	if (file_logger != nullptr || console != nullptr) {
		spdlog::drop_all();
		std::cout << "############ drop all " << std::endl;
	}
	*t = (short) 25;
	return 0;
}
/*!
 * Flush only the loggers<br/>
 * console and file_logger
 * @see  <a href="https://github.com/gabime/spdlog/blob/v1.x/README.md">SPDLog info</a>
 * @param *t not in use
 * @return  0 = success, otherwise error ()
 */
int getFlushSpdLogShort(short *t) {
	if (file_logger != nullptr) {
		SPDLOG_LOGGER_INFO(file_logger, "Flush.");
		file_logger->flush();
		std::cout << "############ flush file_logger " << std::endl;
	} else
		std::cout << "############ no file_logger " << std::endl;

	if (console != nullptr) {
		SPDLOG_LOGGER_INFO(console, "Flush.");
		console->flush();
		std::cout << "############ flush  console " << std::endl;
	} else
		std::cout << "############ no console " << std::endl;

	*t = (short) 25;
	return 0;
}
/*!
 * Flush and Drop the loggers<br/>
 * console and file_logger
 * @see  <a href="https://github.com/gabime/spdlog/blob/v1.x/README.md">SPDLog info</a>
 * @param *t not in use
 * @return  0 success, otherwise error ()
 */
int getFlushDropSpdLogShort(short *t) {
	if (file_logger != nullptr) {
		SPDLOG_LOGGER_INFO(file_logger, "Flush.");
		file_logger->flush();
		std::cout << "############ flush file_logger " << std::endl;
	} else
		std::cout << "############ no file_logger " << std::endl;
	if (console != nullptr) {
		SPDLOG_LOGGER_INFO(console, "Flush.");
		console->flush();
		std::cout << "############ flush  console " << std::endl;
	} else
		std::cout << "############ no console " << std::endl;
	if (file_logger != nullptr || console != nullptr) {
		spdlog::drop_all();
		std::cout << "############ drop all " << std::endl;
	}
	*t = (short) 25;
	return 0;
}

/*****************************************************************************
 * About TA
 ***************************************************************************** */

/*! set the power for the motor
 * @param power
 * @return Error 0  success,
 * -1 if not initialized
 *  -4 if power is out of range, constrain [0..512]
 */
int setMPowerShort(INT16 power) {
	if (!IsInit) {
		fprintf(stderr, "setMPowerShort: Error, not initialized!\n");
		return -1;
	}
	if (!((power >= 0) && (power <= 512))) {
		fprintf(stderr, "setMPowerShort: Error, speed out of range!\n");
		return -4; //speed out of range.
	}
	MPower = power;
	return 0;
}

/*!
 * set the distance for the motor
 * @param distance
 * * @return  0  success,
 *  -1 if not initialized
 *  -3 if distance is out of range, constrain [smaller than 1]
 */
int setMDistanceShort(INT16 distance) {

	if (!IsInit) {
		fprintf(stderr, "setMotorDistanceShort: Error not initialized!\n");
		return -1;
	}
	if (!(distance > 0)) {
		fprintf(stderr,
				"setMotorDistanceShort:Error, distance smaller than 0!\n");
		return -3; //distance out of range.
	}
	MDistance = distance;
	return 0;
}

//start motor v ([1,2,3,4] and let it run for a distance of 240 units.
//Wait until the motor is ready (his is a blocking function)
//
/*!
 * Start Motor Starts Motor mId  with  MDistance and MPower.
 * Blocking. Wait until the end is reached.
 * @param mId    Motor  [1,2,3,4]
 * @return Error 0  success,
 *               -1 if not initialized
 *               -2 if MotoIor thread in not running
 *               -5 if mId  out of range
 */
int setMStartWaitShort(INT16 mId) {
	FISH_X1_TRANSFER *pTArea;
	if (!IsInit) {
		SPDLOG_LOGGER_TRACE(file_logger, " Not initialized!\n");
		return -1;
	}
	// value_d = mId;
	if (!MotorIOLib_ThreadIsRunning()) {
		SPDLOG_LOGGER_ERROR(file_logger,
				" MotorIOLib_Thread Is Not Running!\n");
		return -2;
	}

	if (!((mId > 0) && (mId < 5))){
		SPDLOG_LOGGER_ERROR(file_logger, " Motor Id out of range!\n");
	return -5;
	}

	pTArea = GetKeLibTransferAreaMainAddress();
	if (pTArea) {   // It's a real pointer
		int motorId = mId - 1;
		// Switch M1 - Encoder Motor on with MSpped and for MDistance
		// Note: the range of the motor duty cycle values is 0..512

		// Step 1: Switch Motor on (with a distance from MDistance)
		pTArea->ftX1out.distance[motorId] = MDistance; // Distance to drive motorId
		pTArea->ftX1out.motor_ex_cmd_id[motorId]++; // Activate new Distance Value for motorId [0]

		pTArea->ftX1out.duty[motorId * 2] = MPower; // Switch Motor 1 ( O1 [0] ) on with PWM Value MSpeed (= max speed)
		pTArea->ftX1out.duty[motorId * 2 + 1] = 0; // Switch Motor 1 ( O2 [1] ) with minus
		// Wait until the extended motor is ready
		while (pTArea->ftX1in.motor_ex_cmd_id[motorId]
				< pTArea->ftX1out.motor_ex_cmd_id[motorId]) {
			SPDLOG_LOGGER_INFO(console,	" OutExCmd: {}  InExCmd: {}  Counter: {}",
					pTArea->ftX1out.motor_ex_cmd_id[motorId],
					pTArea->ftX1in.motor_ex_cmd_id[motorId],
					pTArea->ftX1in.counter[motorId]);
		};

		SPDLOG_LOGGER_INFO(console,	" OutExCmd: {}  InExCmd: {}  Counter: {} ",
							pTArea->ftX1out.motor_ex_cmd_id[motorId],
							pTArea->ftX1in.motor_ex_cmd_id[motorId],
							pTArea->ftX1in.counter[motorId]);
	} else {
		SPDLOG_LOGGER_ERROR(file_logger, " TA is not available!\n");
		return -1;
	}

	printf("setMotorStartWaitShort: %d\n", mId);
	return 0;
}

/*!
 * Starts Motor mId  with  MDistance and MPower
 * Not blocking. In the RoboPro program needs Ready to be detect in a normal way.
 * @param mId Motor [1,2,3,4]
 * @return Error 0  success,
 *               -1 if not initialized
 *               -2 if MotoIor thread in not running
 *               -5 if mId  out of range */
int setMStartShort(INT16 mId) {
	FISH_X1_TRANSFER *pTArea;
	if (!IsInit) {
		SPDLOG_LOGGER_ERROR(file_logger, " Not initialized!\n");
		return -1;
	}
	if (!MotorIOLib_ThreadIsRunning()) {
		SPDLOG_LOGGER_ERROR(file_logger,
				" MotorIOLib_Thread Is Not Running!\n");
		return -2;
	} else {
	}

	if (!((mId > 0) && (mId < 5))) {
		SPDLOG_LOGGER_ERROR(file_logger, " Motor Id out of range!\n");
		return -5;
	};
	pTArea = GetKeLibTransferAreaMainAddress();
	if (pTArea) {   // It's a real pointer
		int motorId = mId - 1;
		// Switch M1 - Encoder Motor on with MSpped and for MDistance
		// Note: the range of the motor duty cycle values is 0..512

		// Step 1: Switch Motor on (with a distance from MDistance)
		pTArea->ftX1out.distance[motorId] = MDistance; // Distance to drive motorId
		pTArea->ftX1out.motor_ex_cmd_id[motorId]++; // Activate new Distance Value for motorId [0]
		pTArea->ftX1out.duty[motorId * 2] = MPower; // Switch Motor 1 ( O1 [0] ) on with PWM Value MSpeed (= max speed)
		pTArea->ftX1out.duty[motorId * 2 + 1] = 0; // Switch Motor 1 ( O2 [1] ) with minus    if( !IsInit )
	} else {
		SPDLOG_LOGGER_TRACE(file_logger, " No TA Main address!\n");
		return -1;
	};

	// printf( "ExampleSLI:setMotorsStartShort: %d\n", v);
	return 0;
}

/*!
 *

 * @param mId    Motor  [1,2,3,4]
 * @return Error 0  success,
 *               -1 if not initialized
 *               -2 if MotoIor thread in not running
 *               -5 if mId  out of range
 */
int setMStopShort(INT16 mId) {
//	fprintf(stderr, "setMotorStopShort: Not implemented yet!\n");
//	return -1;

	FISH_X1_TRANSFER *pTArea;

	if (!IsInit) {
		fprintf(stderr, "setMotorStopShort: Not initialized!\n");
		return -1;
	}
	if (!MotorIOLib_ThreadIsRunning()) {
		fprintf(stderr,
				"setMotorStopShort:MotorIOLib_Thread Is Not Running!\n");
		return -2;
	}

	if (!((mId > 0) && (mId < 5))) {
		fprintf(stderr, "setMotorStopShort:Motor Id out of range!\n");
		return -5;
	};
	pTArea = GetKeLibTransferAreaMainAddress();
	if (pTArea) {
		int motorId = mId - 1;

		pTArea->ftX1out.distance[motorId] = 0; // set distance on 0, end exetended use.
		pTArea->ftX1out.motor_ex_cmd_id[motorId]++;           // set new command
		pTArea->ftX1out.duty[motorId * 2] = 0;                   // set no power
		pTArea->ftX1out.duty[motorId * 2 + 1] = 0;               // set no power
		printf(
				"setMotorsStopShort:4:OutExCmd: %d  InExCmd: %d  Counter: %d  \n",
				pTArea->ftX1out.motor_ex_cmd_id[motorId],
				pTArea->ftX1in.motor_ex_cmd_id[motorId],
				pTArea->ftX1in.counter[motorId]);    //actual fast counter state
	} else {
		fprintf(stderr, "setMStopShort:No TA Main address!\n");
		return -1;
	};
	//   printf( "ExampleSLI.setMStopShort: %d\n", mId);
	return 0;

}

}	//End extern "C"

