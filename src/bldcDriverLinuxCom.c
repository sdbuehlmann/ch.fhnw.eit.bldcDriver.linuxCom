/*
 * bldcDriverCom.c
 *
 *  Created on: Jul 25, 2018
 *      Author: simon
 */

// =============== Includes ==============================================
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <uartCom.h>

#include "loggerbldcmotordriver_serialcom_BLDCDriverCommunication.h"
#include "bldcDriverSerializer_logger.h"
#include "bldcDriverSerializer_observer.h"
#include "bldcDriverSerializer_operator.h"

// =============== Defines ===============================================

// =============== Typdefs ===============================================

// =============== Variables =============================================
JNIEnv *pEnv;
jobject this_obj;

// =============== Function pointers =====================================

// =============== Function declarations =================================

// =============== Functions =============================================

// --------------- JNI ---------------------------------------------------
JNIEXPORT jint JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_startSerial(JNIEnv *pEnv_param, jobject this_obj_param,
		jstring port_j, jint symbolrate_j, jboolean parity_j, jboolean twoStopBits_j, jint nrDatabits_j) {
	pEnv = pEnv_param;
	this_obj = this_obj_param;

	const char *pPort = (*pEnv)->GetStringUTFChars(pEnv, port_j, 0);

	boolean parity = false;
	if (parity_j == JNI_TRUE) {
		parity = true;
	}

	boolean twoStopBits = false;
	if (twoStopBits_j == JNI_TRUE) {
		twoStopBits = true;
	}

	int symbolrate = (int) symbolrate_j;
	int nrDatabits = (int) nrDatabits_j;

	// init jni callback methods
	loadMethods(pEnv, this_obj);
	printString("UART ProtoManager started...\n");

	// init serializer


	// init serial com
	printString("Init serial communication...\n");

	char temp_buffer[100];
	sprintf(temp_buffer, "Port: %s Symbolrate: %d Nr. databits: %d Parity: %d Two stop bits: %d\n", pPort, symbolrate, nrDatabits, parity,
			twoStopBits);
	printString(temp_buffer);

	int initCode = 0;
	initCode = initSerialCom(pPort, symbolrate, parity, twoStopBits, nrDatabits);

	if (initCode != SUCCESSFUL) {
		return initCode;
	}
	printString("Serial communication started.\n");

	char buffer[30];
	memset(&buffer, 0, sizeof(buffer)); // set all variables of port to 0

	char nextByte = 0;
	while (1) {
		if (readSerialCom(&nextByte, 1) > 0) {
			proceed(nextByte);
			printBytes(nextByte);
		}
	}

	(*pEnv)->ReleaseStringUTFChars(pEnv, port_j, pPort);
	return 0;
}

JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_enableSerialOperatingMode(JNIEnv *pEnv_param,
		jobject this_obj) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_enableLogging(JNIEnv *pEnv_param, jobject this_obj) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_enableDriver(JNIEnv *pEnv_param, jobject this_obj) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_disableDriver(JNIEnv *pEnv_param, jobject this_obj) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_selectPositiveTorque(JNIEnv *pEnv_param,
		jobject this_obj) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_selectNegativeTorque(JNIEnv *pEnv_param,
		jobject this_obj) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_rotadeClockwise(JNIEnv *pEnv_param, jobject this_obj) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_rotadeCounterclockwise(JNIEnv *pEnv_param,
		jobject this_obj) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_getObservingInfos(JNIEnv *pEnv_param, jobject this_obj) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_getLoggingConfiguration(JNIEnv *pEnv_param,
		jobject this_obj) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_setPositiveTorqueLevel(JNIEnv *pEnv_param,
		jobject this_obj, jint level_j) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_setNegativeTorqueLevel(JNIEnv *pEnv_param,
		jobject this_obj, jint level_j) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_setMaxAbsPhaseCurrent(JNIEnv *pEnv_param,
		jobject this_obj, jint surrent_j) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_setTiming(JNIEnv *pEnv_param, jobject this_obj,
		jint timing_j) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_setRotorPositionControllerPParam(JNIEnv *pEnv_param,
		jobject this_obj, jint pParam_j) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_setRotorPositionControllerIParam(JNIEnv *pEnv_param,
		jobject this_obj, jint pParam_j) {

}
JNIEXPORT void JNICALL Java_loggerbldcmotordriver_serialcom_BLDCDriverCommunication_setLoggingConfig(JNIEnv *pEnv_param, jobject this_obj,
		jint conf_j) {

}
