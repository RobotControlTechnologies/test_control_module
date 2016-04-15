#include <stdlib.h>
#include <stdio.h>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <stdarg.h>
#endif

#include "module.h"
#include "control_module.h"

#include "test_control_module.h"

#define IID "RCT.Test_control_module_v107"
unsigned int COUNT_AXIS = 3;

std::vector<variable_value> x_values = {100,  -30.1, -2.58, 48.9, 99.01,
                                        -100, 12.0,  -36.9, 0.25, 0};
std::vector<variable_value> y_values = {0,    0,   0,    1,    1,   0.5,
                                        0.25, 0.1, 0.75, 0.35, 0.95};
std::vector<variable_value> z_values = {4.56, 0,    78.9, 100, 50,
                                        48.8, 66.7, 32.4, 40,  20};

#define ADD_TEST_AXIS(AXIS_NAME, UPPER_VALUE, LOWER_VALUE) \
  test_axis[axis_id] = new AxisData;                       \
  test_axis[axis_id]->axis_index = axis_id + 1;            \
  test_axis[axis_id]->upper_value = UPPER_VALUE;           \
  test_axis[axis_id]->lower_value = LOWER_VALUE;           \
  test_axis[axis_id]->name = AXIS_NAME;                    \
  ++axis_id;

TestControlModule::TestControlModule() {
#if MODULE_API_VERSION > 000
  mi = new ModuleInfo;
  mi->uid = IID;
  mi->mode = ModuleInfo::Modes::PROD;
  mi->version = BUILD_NUMBER;
  mi->digest = NULL;
#endif

  int axis_id = 0;
  test_axis = new AxisData *[COUNT_AXIS];
  ADD_TEST_AXIS("X", 100, -100)
  ADD_TEST_AXIS("Y", 1, 0)
  ADD_TEST_AXIS("Z", 100, 0)
}

#if MODULE_API_VERSION > 000
const struct ModuleInfo &TestControlModule::getModuleInfo() { return *mi; }
#else
const char *TestControlModule::getUID() { return IID; }
#endif

void TestControlModule::execute(sendAxisState_t sendAxisState) {
  for (int i = 0; i < 10; ++i) {
    colorPrintf(ConsoleColor(ConsoleColor::dark_yellow), "x = %f\n",
                x_values[i]);
    (*sendAxisState)(this, 1, x_values[i]);

    colorPrintf(ConsoleColor(ConsoleColor::dark_yellow), "y = %f\n",
                y_values[i]);
    (*sendAxisState)(this, 2, y_values[i]);

    colorPrintf(ConsoleColor(ConsoleColor::dark_yellow), "z = %f\n",
                z_values[i]);
    (*sendAxisState)(this, 3, z_values[i]);

#ifdef _WIN32
    Sleep(1000);
#else
    usleep(1000000);
#endif
  }
}

void TestControlModule::prepare(colorPrintfModule_t *colorPrintf_p,
                                colorPrintfModuleVA_t *colorPrintfVA_p) {
  this->colorPrintf_p = colorPrintfVA_p;
}

void TestControlModule::colorPrintf(ConsoleColor colors, const char *mask,
                                    ...) {
  va_list args;
  va_start(args, mask);
  (*colorPrintf_p)(this, colors, mask, args);
  va_end(args);
}

int TestControlModule::init() { return 0; }

AxisData **TestControlModule::getAxis(unsigned int *count_axis) {
  (*count_axis) = COUNT_AXIS;
  return test_axis;
}

void TestControlModule::destroy() {
#ifndef CONTROL_MODULE_H_000
  delete mi;
#endif

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

#if MODULE_API_VERSION > 100
int TestControlModule::readPC(int pc_index, void *buffer, unsigned int buffer_length) { return 0; };
int TestControlModule::startProgram(int run_index, int pc_index) { return 0; }
#else
int TestControlModule::startProgram(int run_index) { return 0; }
#endif

int TestControlModule::endProgram(int run_index) { return 0; }

#if MODULE_API_VERSION > 000
PREFIX_FUNC_DLL unsigned short getControlModuleApiVersion() {
  return MODULE_API_VERSION;
};
#endif

PREFIX_FUNC_DLL ControlModule *getControlModuleObject() {
  return new TestControlModule();
}