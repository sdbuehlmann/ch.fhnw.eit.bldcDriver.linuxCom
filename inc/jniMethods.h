/*
 * jniUtils.h
 *
 *  Created on: Jul 26, 2018
 *      Author: simon
 */

#ifndef INC_JNIMETHODS_H_
#define INC_JNIMETHODS_H_

// =============== Includes ============================================================================================================
#include <stdint.h>
#include <jni.h>

// =============== Functions ===========================================================================================================
void loadMethods(JNIEnv *pEnv, jobject obj);

void printString(uint8_t msg[]);

// observer
void serialOperatingModeIsEnabled(uint32_t timestamp);
void serialOperatingModeIsDisabled(uint32_t timestamp);
void driverIsEnabled(uint32_t timestamp);
void driverIsDisabled(uint32_t timestamp);
void positiveTorqueIsSelected(uint32_t timestamp);
void negativeTorqueIsSelected(uint32_t timestamp);
void rotadeClockwiseIsSelected(uint32_t timestamp);
void rotadeCounterclockwiseIsSelected(uint32_t timestamp);
void driverReseted(uint32_t timestamp);
void bufferOverflow(uint32_t timestamp);
void encoderCalibrationValue(uint32_t calibrationValue, uint32_t timestamp);
void entryState(uint8_t state, uint32_t timestamp);
void positiveTorqueLevel(uint8_t level, uint32_t timestamp);
void negativeTorqueLevel(uint8_t level, uint32_t timestamp);
void maxAbsPhaseCurrent(uint8_t current, uint32_t timestamp);
void timing(uint8_t timing, uint32_t timestamp);
void rotorpositionControllerPParam(uint32_t pParam, uint32_t timestamp);
void rotorpositionControllerIParam(uint32_t iParam, uint32_t timestamp);

// logger
void loggingIsEnabled(uint32_t timestamp);
void compA_IR(uint32_t timestamp);
void compB_IR(uint32_t timestamp);
void compC_IR(uint32_t timestamp);
void currentA(uint8_t current, uint32_t timestamp);
void currentB(uint8_t current, uint32_t timestamp);
void currentRangeA(uint8_t range, uint32_t timestamp);
void currentRangeB(uint8_t range, uint32_t timestamp);
void absCurrentSetPoint(uint8_t setpoint, uint32_t timestamp);
void dutyCycle(uint8_t dutyCycle, uint32_t timestamp);
void currentControllerOutput(int8_t controllerOut, uint32_t timestamp);
void absRotorPosEncoder(uint32_t pos, uint32_t timestamp);
void rotorPosEncoder(uint8_t pos, uint32_t timestamp);
void rotorPosSensorless(uint8_t pos, uint32_t timestamp);
void rotorPosControllerOutput(uint8_t controllerOut, uint32_t timestamp);
void time60Deg(uint32_t t60deg, uint32_t timestamp);
void cycleTime(uint32_t cycletime, uint32_t timestamp);
void loggingConfiguration(uint32_t config, uint32_t timestamp);
void debugMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp);
void infoMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp);
void errorMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp);

#endif /* INC_JNIMETHODS_H_ */
