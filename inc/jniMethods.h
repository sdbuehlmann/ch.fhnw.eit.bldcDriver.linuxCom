/*
 * jniUtils.h
 *
 *  Created on: Jul 26, 2018
 *      Author: simon
 */

#ifndef INC_JNIMETHODS_H_
#define INC_JNIMETHODS_H_

#include <stdint.h>

#include "bldcDriverSerializer_logger.h"
#include "bldcDriverSerializer_observer.h"
#include "bldcDriverSerializer_operator.h"

void loadMethods(JNIEnv *pEnv, jobject obj);
void printString(uint8_t msg[]);

#endif /* INC_JNIMETHODS_H_ */
