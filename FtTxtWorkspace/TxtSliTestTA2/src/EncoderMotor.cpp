/*
 * EncoderMotor.cpp
 *
 *  Created on: 12 mei 2020
 *      Author: Carel
 */

#include <stdio.h>          // for printf()
#include "KeLibTxtDl.h"     // TXT Lib
#include "FtShmem.h"        // TXT Transfer Area see KeLib header
#include <iostream>       // std::cout
#include "EncoderMotor.h"
/*!
 \brief Includes for the spdlog
 */
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"
using namespace std;

namespace fischertechnik {
namespace TXT {
namespace TrSli2020 {

EncoderMotor::EncoderMotor() {
	// TODO Auto-generated constructor stub

}

EncoderMotor::~EncoderMotor() {
	// TODO Auto-generated destructor stub
}

void EncoderMotor::setMPower(int power) {
	this->MPower = power;
}

int EncoderMotor::getMPower() {
	return this->MPower;
}
void EncoderMotor::setMDistance(int distance) {
	this->MDistance = distance;
}

int EncoderMotor::getMDistance() {
	return this->MDistance;
}

void EncoderMotor::setMDirection(int direction) {
	this->MDirection = direction;
}

int EncoderMotor::getMDirection() {
	return this->MDirection;
}

void EncoderMotor::setMPowerDirection(int powdir) {
	if (powdir > 0) {
		this->MPower = powdir;
		this->MDirection = 1;
	} else if (powdir < 0) {
		this->MPower = powdir * (-1);
		this->MDirection = -1;
	} else {
		this->MPower = 0;
		this->MDirection = 0;
	};
}

int EncoderMotor::getMPowerDirection() {
	return this->MPower * MDirection;
}

/**********************************************************/
int EncoderMotor::setMStartWait(INT16 mId) {
	FISH_X1_TRANSFER *pTArea;
	if (!MotorIOLib_ThreadIsRunning()) {
		fprintf(stderr,
				"setMotorStopShort:MotorIOLib_Thread Is Not Running!\n");
		return -2;
	}
	if (!((mId > 0) && (mId < 5))) {
		SPDLOG_LOGGER_ERROR(spdlog::get("file_logger"),
				" Motor Id out of range!\n");
		return -5;
	}

	pTArea = GetKeLibTransferAreaMainAddress();
	if (pTArea) {   // It's a real pointer
		int motorId = mId - 1;
		// Step 1: Switch Motor on (with a distance from MDistance)
		pTArea->ftX1out.distance[motorId] = this->MDistance; // Distance to drive motorId
		pTArea->ftX1out.motor_ex_cmd_id[motorId]++; // Activate new Distance Value for motorId [0]
		if (this->MDirection > 0) {
			pTArea->ftX1out.duty[motorId * 2] = MPower; // Switch Motor 1 ( O1 [0] ) on with PWM Value MSpeed (= max speed)
			pTArea->ftX1out.duty[motorId * 2 + 1] = 0; // Switch Motor 1 ( O2 [1] ) with minus
		} else {
			pTArea->ftX1out.duty[motorId * 2] = 0; // Switch Motor 1 ( O1 [0] ) on with PWM Value MSpeed (= max speed)
			pTArea->ftX1out.duty[motorId * 2 + 1] = MPower; // Switch Motor 1 ( O2 [1] ) with minus
		}
		SPDLOG_LOGGER_TRACE(spdlog::get("file_logger"),
				" before wait!\n");		// Wait until the extended motor is ready
		while (pTArea->ftX1in.motor_ex_cmd_id[motorId]
				< pTArea->ftX1out.motor_ex_cmd_id[motorId]) {
			SPDLOG_LOGGER_TRACE(spdlog::get("file_logger"),
					" OutExCmd: {}  InExCmd: {}  Counter: {}",
					pTArea->ftX1out.motor_ex_cmd_id[motorId],
					pTArea->ftX1in.motor_ex_cmd_id[motorId],
					pTArea->ftX1in.counter[motorId]);
		};
		SPDLOG_LOGGER_INFO(spdlog::get("file_logger"),
				" after wait!\n");		// Wait until the extended motor is ready

		SPDLOG_LOGGER_TRACE(spdlog::get("file_logger"),
				" OutExCmd: {}  InExCmd: {}  Counter: {} ",
				pTArea->ftX1out.motor_ex_cmd_id[motorId],
				pTArea->ftX1in.motor_ex_cmd_id[motorId],
				pTArea->ftX1in.counter[motorId]);
	} else {
		SPDLOG_LOGGER_ERROR(spdlog::get("file_logger"),
				" TA is not available!\n");
		return -1;
	}
	return 0;
}

/*!
*/
int EncoderMotor::setMStart(INT16 mId) {
	FISH_X1_TRANSFER *pTArea;
	if (!MotorIOLib_ThreadIsRunning()) {
		fprintf(stderr,
				"setMotorStopShort:MotorIOLib_Thread Is Not Running!\n");
		return -2;
	}
	if (!((mId > 0) && (mId < 5))) {
		SPDLOG_LOGGER_ERROR(spdlog::get("file_logger"),
				" Motor Id out of range!\n");
		return -5;
	};
	pTArea = GetKeLibTransferAreaMainAddress();
	if (pTArea) {   // It's a real pointer
		int motorId = mId - 1;
		// Step 1: Switch Motor on (with a distance from MDistance)
		pTArea->ftX1out.distance[motorId] = MDistance; // Distance to drive motorId
		pTArea->ftX1out.motor_ex_cmd_id[motorId]++; // Activate new Distance Value for motorId [0]
		if (this->MDirection > 0) {
			pTArea->ftX1out.duty[motorId * 2] = MPower; // Switch Motor 1 ( O1 [0] ) on with PWM Value MSpeed (= max speed)
			pTArea->ftX1out.duty[motorId * 2 + 1] = 0; // Switch Motor 1 ( O2 [1] ) with minus
		} else {
			pTArea->ftX1out.duty[motorId * 2] = 0; // Switch Motor 1 ( O1 [0] ) on with PWM Value MSpeed (= max speed)
			pTArea->ftX1out.duty[motorId * 2 + 1] = MPower; // Switch Motor 1 ( O2 [1] ) with minus
		}
	} else {
		SPDLOG_LOGGER_TRACE(spdlog::get("file_logger"),
				" No TA Main address!\n");
		return -1;
	};
	// printf( "ExampleSLI:setMotorsStartShort: %d\n", v);
	return 0;
}
/*!
 */
int EncoderMotor::setMStop(INT16 mId) {
//	fprintf(stderr, "setMotorStopShort: Not implemented yet!\n");
//	return -1;

	FISH_X1_TRANSFER *pTArea;
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
		SPDLOG_LOGGER_TRACE(spdlog::get("file_logger"),
				" OutExCmd: {}  InExCmd: {}  Counter: {} ",
				pTArea->ftX1out.motor_ex_cmd_id[motorId],
				pTArea->ftX1in.motor_ex_cmd_id[motorId],
				pTArea->ftX1in.counter[motorId]);
	} else {
		fprintf(stderr, "setMStopShort:No TA Main address!\n");
		return -1;
	};
		SPDLOG_LOGGER_INFO(spdlog::get("file_logger"),
				" end!\n");		// Wait until the extended motor is ready	//   printf( "ExampleSLI.setMStopShort: %d\n", mId);
	return 0;

}
} /* namespace TrSli */
} /* namespace TXT */
} /* namespace fischertechnik */

