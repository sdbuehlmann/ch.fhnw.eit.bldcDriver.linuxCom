/*
 * jniUtils.c
 *
 *  Created on: Jul 26, 2018
 *      Author: simon
 */

// =============== Includes ============================================================================================================
#include "jniMethods.h"

// =============== Defines =============================================================================================================

// =============== Typdefs =============================================================================================================

// =============== Variables ===========================================================================================================
static JNIEnv *pEnv;
static jobject this_obj;

// --------------- method id's ---------------------------------------------------------------------------------------------------------
static static jmethodID id_printString;

// observer
static jmethodID id_serialOperatingModeIsEnabled;
static jmethodID id_serialOperatingModeIsDisabled;
static jmethodID id_driverIsEnabled;
static jmethodID id_driverIsDisabled;
static jmethodID id_positiveTorqueIsSelected;
static jmethodID id_negativeTorqueIsSelected;
static jmethodID id_rotadeClockwiseIsSelected;
static jmethodID id_rotadeCounterclockwiseIsSelected;
static jmethodID id_driverReseted;
static jmethodID id_bufferOverflow;
static jmethodID id_encoderCalibrationValue;
static jmethodID id_entryState;
static jmethodID id_positiveTorqueLevel;
static jmethodID id_negativeTorqueLevel;
static jmethodID id_maxAbsPhaseCurrent;
static jmethodID id_timing;
static jmethodID id_rotorpositionControllerPParam;
static jmethodID id_rotorpositionControllerIParam;

// logger
static jmethodID id_loggingIsEnabled;
static jmethodID id_compA_IR;
static jmethodID id_compB_IR;
static jmethodID id_compC_IR;
static jmethodID id_currentA;
static jmethodID id_currentB;
static jmethodID id_currentRangeA;
static jmethodID id_currentRangeB;
static jmethodID id_absCurrentSetPoint;
static jmethodID id_dutyCycle;
static jmethodID id_currentControllerOutput;
static jmethodID id_absRotorPosEncoder;
static jmethodID id_rotorPosEncoder;
static jmethodID id_rotorPosSensorless;
static jmethodID id_rotorPosControllerOutput;
static jmethodID id_time60Deg;
static jmethodID id_cycleTime;
static jmethodID id_loggingConfiguration;
static jmethodID id_debugMsg;
static jmethodID id_infoMsg;
static jmethodID id_errorMsg;

// =============== Function pointers ===================================================================================================

// =============== Function declarations ===============================================================================================
/* --------------- load method utils ---------------------------------------------------------------------------------------------------
 * All loadMethodID functions are expensive (source: http://journals.ecs.soton.ac.uk/java/tutorial/native1.1/implementing/method.html)
 */
static jmethodID loadMethodID_handleEvent(JNIEnv *pEnv, jobject obj, char *pName);
static jmethodID loadMethodID_handleInt(JNIEnv *pEnv, jobject obj, char *pName);
//static jmethodID loadMethodID_handleLong(JNIEnv *pEnv, jobject obj, char *pName);
static jmethodID loadMethodID_handleString(JNIEnv *pEnv, jobject obj, char *pName);

static jmethodID loadMethodID_printString();

// --------------- call method utils ---------------------------------------------------------------------------------------------------
static void callMethod_handleEvent(JNIEnv *pEnv, jobject obj, jmethodID method_id, uint32_t timestamp);
static void callMethod_handleInt(JNIEnv *pEnv, jobject obj, jmethodID method_id, uint32_t timestamp, int32_t data);
//static void callMethod_handleLong(JNIEnv *pEnv, jobject obj, jmethodID method_id, uint32_t timestamp, int64_t data);
static void callMethod_handleString(JNIEnv *pEnv, jobject obj, jmethodID method_id, uint32_t timestamp, jbyte *pMsg, uint32_t size);


// =============== Functions ===========================================================================================================
// --------------- load method utils ---------------------------------------------------------------------------------------------------
static jmethodID loadMethodID_handleEvent(JNIEnv *pEnv, jobject obj, char *pName) {
	jclass obj_class = (*pEnv)->GetObjectClass(pEnv, obj);
	return (*pEnv)->GetMethodID(pEnv, obj_class, pName, "(J)V"); // public void event(long timestamp)
}
static jmethodID loadMethodID_handleInt(JNIEnv *pEnv, jobject obj, char *pName) {
	jclass obj_class = (*pEnv)->GetObjectClass(pEnv, obj);
	return (*pEnv)->GetMethodID(pEnv, obj_class, pName, "(IJ)V"); // public void handleInt((int data, long timestamp)
}
/*static jmethodID loadMethodID_handleLong(JNIEnv *pEnv, jobject obj, char *pName) {
	jclass obj_class = (*pEnv)->GetObjectClass(pEnv, obj);
	return (*pEnv)->GetMethodID(pEnv, obj_class, pName, "(JJ)V"); // public void handleLong((long data, long timestamp)
}*/
static jmethodID loadMethodID_handleString(JNIEnv *pEnv, jobject obj, char *pName) {
	jclass obj_class = (*pEnv)->GetObjectClass(pEnv, obj);
	return (*pEnv)->GetMethodID(pEnv, obj_class, pName, "([BJ)V"); // public void handleString(byte[] msg, long timestamp)
}
static jmethodID loadMethodID_printString() {
	// void printString(byte[] data)
	jclass obj_class = (*pEnv)->GetObjectClass(pEnv, this_obj);
	jmethodID id_method = (*pEnv)->GetMethodID(pEnv, obj_class, "printString", "([B)V");

	return id_method;
}

// --------------- call method utils ---------------------------------------------------------------------------------------------------
static void callMethod_handleEvent(JNIEnv *pEnv, jobject obj, jmethodID method_id, uint32_t timestamp) {
	// void handleEvent(long timestamp)
	(*pEnv)->CallVoidMethod(pEnv, obj, method_id, (jlong) timestamp);
}
static void callMethod_handleInt(JNIEnv *pEnv, jobject obj, jmethodID method_id, uint32_t timestamp, int32_t data) {
	// void handleInt((int data, long timestamp)
	(*pEnv)->CallVoidMethod(pEnv, obj, method_id, (jint) data, (jlong) timestamp);
}
/*static void callMethod_handleLong(JNIEnv *pEnv, jobject obj, jmethodID method_id, uint32_t timestamp, int64_t data) {
	// void handleLong((long data, long timestamp)
	(*pEnv)->CallVoidMethod(pEnv, obj, method_id, (jlong) data, (jlong) timestamp);
}*/
static void callMethod_handleString(JNIEnv *pEnv, jobject obj, jmethodID method_id, uint32_t timestamp, jbyte *pMsg, uint32_t size) {
	// void handleString(byte[] msg, long timestamp)
	jbyteArray array = (*pEnv)->NewByteArray(pEnv, (jsize) size);
	(*pEnv)->SetByteArrayRegion(pEnv, array, (jsize) 0, (jsize) size, pMsg);

	(*pEnv)->CallVoidMethod(pEnv, obj, method_id, array, timestamp);
}

// =============== jniUtils.h ==========================================================================================================
void loadMethods(JNIEnv *pEnv_param, jobject this_obj_param) {
	pEnv = pEnv_param;
	this_obj = this_obj_param;

	id_printString = loadMethodID_printString(pEnv, this_obj);

	// observer
	id_serialOperatingModeIsEnabled = loadMethodID_handleEvent(pEnv, this_obj, "serialOperatingModeIsEnabled");
	id_serialOperatingModeIsDisabled = loadMethodID_handleEvent(pEnv, this_obj, "serialOperatingModeIsDisabled");
	id_driverIsEnabled = loadMethodID_handleEvent(pEnv, this_obj, "driverIsEnabled");
	id_driverIsDisabled = loadMethodID_handleEvent(pEnv, this_obj, "driverIsDisabled");
	id_positiveTorqueIsSelected = loadMethodID_handleEvent(pEnv, this_obj, "positiveTorqueIsSelected");
	id_negativeTorqueIsSelected = loadMethodID_handleEvent(pEnv, this_obj, "negativeTorqueIsSelected");
	id_rotadeClockwiseIsSelected = loadMethodID_handleEvent(pEnv, this_obj, "rotadeClockwiseIsSelected");
	id_rotadeCounterclockwiseIsSelected = loadMethodID_handleEvent(pEnv, this_obj, "rotadeCounterclockwiseIsSelected");
	id_driverReseted = loadMethodID_handleEvent(pEnv, this_obj, "driverReseted");
	id_bufferOverflow = loadMethodID_handleEvent(pEnv, this_obj, "bufferOverflow");
	id_encoderCalibrationValue = loadMethodID_handleInt(pEnv, this_obj, "encoderCalibrationValue");
	id_entryState = loadMethodID_handleInt(pEnv, this_obj, "entryState");
	id_positiveTorqueLevel = loadMethodID_handleInt(pEnv, this_obj, "positiveTorqueLevel");
	id_negativeTorqueLevel = loadMethodID_handleInt(pEnv, this_obj, "negativeTorqueLevel");
	id_maxAbsPhaseCurrent = loadMethodID_handleInt(pEnv, this_obj, "maxAbsPhaseCurrent");
	id_timing = loadMethodID_handleInt(pEnv, this_obj, "timing");
	id_rotorpositionControllerPParam = loadMethodID_handleInt(pEnv, this_obj, "rotorpositionControllerPParam");
	id_rotorpositionControllerIParam = loadMethodID_handleInt(pEnv, this_obj, "rotorpositionControllerIParam");

	// logger
	id_loggingIsEnabled = loadMethodID_handleEvent(pEnv, this_obj, "loggingIsEnabled");
	id_compA_IR = loadMethodID_handleEvent(pEnv, this_obj, "compA_IR");
	id_compB_IR = loadMethodID_handleEvent(pEnv, this_obj, "compB_IR");
	id_compC_IR = loadMethodID_handleEvent(pEnv, this_obj, "compC_IR");
	id_currentA = loadMethodID_handleInt(pEnv, this_obj, "currentA");
	id_currentB = loadMethodID_handleInt(pEnv, this_obj, "currentB");
	id_currentRangeA = loadMethodID_handleInt(pEnv, this_obj, "currentRangeA");
	id_currentRangeB = loadMethodID_handleInt(pEnv, this_obj, "currentRangeB");
	id_absCurrentSetPoint = loadMethodID_handleInt(pEnv, this_obj, "absCurrentSetPoint");
	id_dutyCycle = loadMethodID_handleInt(pEnv, this_obj, "dutyCycle");
	id_currentControllerOutput = loadMethodID_handleInt(pEnv, this_obj, "currentControllerOutput");
	id_absRotorPosEncoder = loadMethodID_handleInt(pEnv, this_obj, "absRotorPosEncoder");
	id_rotorPosEncoder = loadMethodID_handleInt(pEnv, this_obj, "rotorPosEncoder");
	id_rotorPosSensorless = loadMethodID_handleInt(pEnv, this_obj, "rotorPosSensorless");
	id_rotorPosControllerOutput = loadMethodID_handleInt(pEnv, this_obj, "rotorPosControllerOutput");
	id_time60Deg = loadMethodID_handleInt(pEnv, this_obj, "time60Deg");
	id_cycleTime = loadMethodID_handleInt(pEnv, this_obj, "cycleTime");
	id_loggingConfiguration = loadMethodID_handleInt(pEnv, this_obj, "loggingConfiguration");
	id_debugMsg = loadMethodID_handleString(pEnv, this_obj, "debugMsg");
	id_infoMsg = loadMethodID_handleString(pEnv, this_obj, "infoMsg");
	id_errorMsg = loadMethodID_handleString(pEnv, this_obj, "errorMsg");
}

void printString(uint8_t *pMsg) {
	// count until (but without) zero-byte
		int cnt = 0;
		char *pTemp = pMsg;

		while (1) {
			if (*pTemp != 0) {
				cnt++;
				pTemp++;
			} else {
				break;
			}
		}

	jbyteArray array = (*pEnv)->NewByteArray(pEnv, (jsize) cnt);
	(*pEnv)->SetByteArrayRegion(pEnv, array, (jsize) 0, (jsize) cnt, (jbyte)pMsg);
	(*pEnv)->CallVoidMethod(pEnv, this_obj, id_printString, array);
}

// --------------- observer ------------------------------------------------------------------------------------------------------------
void serialOperatingModeIsEnabled(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_serialOperatingModeIsEnabled, timestamp);
}
void serialOperatingModeIsDisabled(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_serialOperatingModeIsDisabled, timestamp);
}
void driverIsEnabled(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_driverIsEnabled, timestamp);
}
void driverIsDisabled(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_driverIsDisabled, timestamp);
}
void positiveTorqueIsSelected(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_positiveTorqueIsSelected, timestamp);
}
void negativeTorqueIsSelected(uint32_t timestamp) {
	callMethod_callMethod_handleEvent(pEnv, this_obj, id_negativeTorqueIsSelected, timestamp);
}
void rotadeClockwiseIsSelected(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_rotadeClockwiseIsSelected, timestamp);
}
void rotadeCounterclockwiseIsSelected(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_rotadeCounterclockwiseIsSelected, timestamp);
}
void driverReseted(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_driverReseted, timestamp);
}
void bufferOverflow(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_bufferOverflow, timestamp);
}
void encoderCalibrationValue(uint32_t calibrationValue, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_encoderCalibrationValue, timestamp, calibrationValue);
}
void entryState(uint8_t state, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_entryState, timestamp, state);
}
void positiveTorqueLevel(uint8_t level, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_positiveTorqueLevel, timestamp, level);
}
void negativeTorqueLevel(uint8_t level, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_negativeTorqueLevel, timestamp, level);
}
void maxAbsPhaseCurrent(uint8_t current, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_maxAbsPhaseCurrent, timestamp, current);
}
void timing(uint8_t timing, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_timing, timestamp, timing);
}
void rotorpositionControllerPParam(uint32_t pParam, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_rotorpositionControllerPParam, timestamp, pParam);
}
void rotorpositionControllerIParam(uint32_t iParam, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_rotorpositionControllerIParam, timestamp, iParam);
}

// --------------- logger --------------------------------------------------------------------------------------------------------------
void loggingIsEnabled(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_loggingIsEnabled, timestamp);
}
void compA_IR(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_compA_IR, timestamp);
}
void compB_IR(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_compB_IR, timestamp);
}
void compC_IR(uint32_t timestamp) {
	callMethod_handleEvent(pEnv, this_obj, id_compC_IR, timestamp);
}
void currentA(uint8_t current, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_currentA, timestamp, current);
}
void currentB(uint8_t current, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, currentB, timestamp, current);
}
void currentRangeA(uint8_t range, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_currentRangeA, timestamp, range);
}
void currentRangeB(uint8_t range, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_currentRangeB, timestamp, range);
}
void absCurrentSetPoint(uint8_t setpoint, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_absCurrentSetPoint, timestamp, setpoint);
}
void dutyCycle(uint8_t dutyCycle, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_dutyCycle, timestamp, dutyCycle);
}
void currentControllerOutput(int8_t controllerOut, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_currentControllerOutput, timestamp, controllerOut);
}
void absRotorPosEncoder(uint32_t pos, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_absRotorPosEncoder, timestamp, pos);
}
void rotorPosEncoder(uint8_t pos, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_rotorPosEncoder, timestamp, pos);
}
void rotorPosSensorless(uint8_t pos, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_rotorPosSensorless, timestamp, pos);
}
void rotorPosControllerOutput(uint8_t controllerOut, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_rotorPosControllerOutput, timestamp, controllerOut);
}
void time60Deg(uint32_t t60deg, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_time60Deg, timestamp, t60deg);
}
void cycleTime(uint32_t cycletime, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_cycleTime, timestamp, cycletime);
}
void loggingConfiguration(uint32_t config, uint32_t timestamp) {
	callMethod_handleInt(pEnv, this_obj, id_loggingConfiguration, timestamp, config);
}
void debugMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp) {
	callMethod_handleString(pEnv, this_obj, id_debugMsg, timestamp, msg, lenght);
}
void infoMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp) {
	callMethod_handleString(pEnv, this_obj, id_infoMsg, timestamp, msg, lenght);
}
void errorMsg(uint8_t msg[], uint8_t lenght, uint32_t timestamp) {
	callMethod_handleString(pEnv, this_obj, id_errorMsg, timestamp, msg, lenght);
}
