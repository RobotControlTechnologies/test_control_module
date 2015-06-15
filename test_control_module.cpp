
#ifdef _WIN32
	#define _CRT_SECURE_NO_WARNINGS
#endif	

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <map>
#include <time.h>
#include <iostream>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
	
#endif	

#include "module.h"
#include "control_module.h"

#include "test_control_module.h"

unsigned int COUNT_AXIS = 3;

#define ADD_TEST_AXIS(AXIS_NAME, UPPER_VALUE, LOWER_VALUE) \
	test_axis[axis_id] = new AxisData; \
	test_axis[axis_id]->axis_index = axis_id + 1; \
	test_axis[axis_id]->upper_value = UPPER_VALUE; \
	test_axis[axis_id]->lower_value = LOWER_VALUE; \
	test_axis[axis_id]->name = AXIS_NAME; \
	++axis_id;

#define DEFINE_ALL_AXIS \
	ADD_TEST_AXIS("X", 100, -100)\
	ADD_TEST_AXIS("Y", 1, 0)\
	ADD_TEST_AXIS("Z", 100, 0)

void TestControlModule::execute(sendAxisState_t sendAxisState) {
	srand(time(NULL));
	for (int i = 0; i < 10; i++){
		int x = rand() % 201 - 100;
		int y = rand() % 2;
		int z = rand() % 101;
		std::cout << x << " " << y << " " << z << std::endl;
		(*sendAxisState)(1, x);
		(*sendAxisState)(2, y);
		(*sendAxisState)(3, z);

#ifdef _WIN32
		Sleep(1000);
#else
		usleep(1000000);
#endif	
		
	}
}


void TestControlModule::prepare(colorPrintf_t *colorPrintf_p, colorPrintfVA_t *colorPrintfVA_p) {
	srand(time(NULL));
	this->colorPrintf = colorPrintf_p;

	int axis_id = 0;
	test_axis = new AxisData*[COUNT_AXIS];
	DEFINE_ALL_AXIS
}

int TestControlModule::init() {
	return  0;
}

const char *TestControlModule::getUID() {
	return "Test control module 1";
}

AxisData** TestControlModule::getAxis(unsigned int *count_axis) {
	(*count_axis) = COUNT_AXIS;
	return test_axis;
}

void TestControlModule::destroy() {
	for (unsigned int j = 0; j < COUNT_AXIS; ++j) {
		delete test_axis[j];
	}
	delete[] test_axis;
	delete this;
}

void *TestControlModule::writePC(unsigned int *buffer_length) {
	*buffer_length = 0;
	return NULL;
}

int TestControlModule::startProgram(int uniq_index) {
	return 0;
}

void TestControlModule::readPC(void *buffer, unsigned int buffer_length) {
}

int TestControlModule::endProgram(int uniq_index) {
	return 0;
}

PREFIX_FUNC_DLL  ControlModule* getControlModuleObject() {
	return new TestControlModule();
}