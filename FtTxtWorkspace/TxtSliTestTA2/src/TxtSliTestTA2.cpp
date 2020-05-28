/*!
 *  \copyright (c) 2019-2020 C. van Leeuwen
 *   \version   1.1.1.1
 *  \file TxtSliTestTA2.cpp
 *  \brief Follow up for the TxtSliTestTA1 project
 *   The functionality has been moved to the class EncoderMotor
 *   In this file only the RoboPRo element interfaces.
 */
/*!
   Sets the compilation level of SPDLOG.
*/
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <stdio.h>          // for printf()
#include <iostream>       // std::cout
#include "EncoderMotor.h"
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
using namespace fischertechnik::TXT::TrSli2020;

/*!
 \brief spdlog globals, two loggers.
 */
static std::shared_ptr<spdlog::logger> console = nullptr; /*!< spdlogger */
//spdlog::rotating_logger_mt<spdlog::async_factory>("console", "Data/SliCon.log", 248576 * 1, 8,true);
static std::shared_ptr<spdlog::logger> file_logger = nullptr; /*!< spdlogger */
//spdlog::rotating_logger_mt<spdlog::async_factory>("file_logger", "Data/SliLogr.log", 248576 * 1, 8,true);

static bool IsInit = false; /*!< Set after initialization*/
static bool IsStop = false; /*!< Set after stop */
static EncoderMotor *em= nullptr;

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
		em=new EncoderMotor();
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
 * @param[out] t  not in use
 * @return  0: success, otherwise error ()
 */
int stop(short *t) {
	if (IsInit) {
		em->~EncoderMotor();
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
 * @see  <a href="https://github.com/gabime/spdlog/blob/v1.x/README.md">SPDLog info</a>
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
	*t = (short) 0;
	return 0;
}
/*!
 * Flush the loggers<br/>
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
 *Flush and Drop the loggers<br/>
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

/*! set the power for themotor
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
	em->setMPower(power);
	return 0;
}
/*!
 * set the distance for  motor M
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
	em->setMDistance( distance);
	return 0;
}

/*!
 * Start Motor mID  with the last distance, power and (direction).
 * Blocking. Wait until the distance has been reached.
 * @param mID    Motor  [1,2,3,4]
 * @return Error 0  success,
 *               -1 if not initialized
 *               -2 if MotoIo-thread in not running
 *               -5 if mID  out of range
 */
int setMStartWaitShort(INT16 mID) {
	if (!IsInit) {
		SPDLOG_LOGGER_TRACE(file_logger, " Not initialized!\n");
		return -1;
	}
    int res=em->setMStartWait(mID);
	printf("setMotorStartWaitShort: %d\n", mID);
	return res;
}

/*!
 * Starts Motor mID  with the last distance, power and (direction)
 * Not blocking. In the RoboPro program needs Ready to be detect in a normal way.
 * @param mID Motor [1,2,3,4]
 * @return Error 0  success,
 *               -1 if not initialized
 *               -2 if MotoIor thread in not running
 *               -5 if mId  out of range */
int setMStart(INT16 mID) {
	if (!IsInit) {
		SPDLOG_LOGGER_ERROR(file_logger, " Not initialized!\n");
		return -1;
	}
    int res=em->setMStart(mID);
	printf( "setMotorsStartShort: %d\n", mID);
	return res;
}
/*!
 * @param mID    Motor  [1,2,3,4]
 * @return Error 0  success,
 *               -2 if MotoIor thread in not running
 *               -5 if mId  out of range
 */
int setMStop(INT16 mID) {
	if (!IsInit) {
		fprintf(stderr, "setMotorStopShort: Not initialized!\n");
		return -1;
	}
    int res=em->setMStop(mID);
	printf( "setMotorsStop: %d\n", mID);
	return res;
}
}	//End extern "C"

