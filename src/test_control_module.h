#ifndef TEST_CONTROL_MODULE_H
#define TEST_CONTROL_MODULE_H

class TestControlModule : public ControlModule {
  AxisData **test_axis;
  colorPrintfModuleVA_t *colorPrintf_p;

#if MODULE_API_VERSION > 000
  ModuleInfo *mi;
#endif

 public:
  TestControlModule();

// init
#if MODULE_API_VERSION > 000
  const struct ModuleInfo &getModuleInfo();
#else
  const char *getUID();
#endif
  void prepare(colorPrintfModule_t *colorPrintf_p,
               colorPrintfModuleVA_t *colorPrintfVA_p);

  // compiler only
  AxisData **getAxis(unsigned int *count_axis);
  void *writePC(unsigned int *buffer_length);

  // intepreter - devices
  #if MODULE_API_VERSION == 102
    virtual int init(initCallback_t& initCallback);
  #else
    int init();
  #endif
#if MODULE_API_VERSION > 100  
  void execute(int run_index, sendAxisState_t sendAxisState);
#else
  void execute(sendAxisState_t sendAxisState);
#endif
  void final(){};

#if MODULE_API_VERSION > 100
  // intepreter - program & lib
  int readPC(int pc_index, void *buffer, unsigned int buffer_length);
  // intepreter - program
  int startProgram(int run_index, int pc_index);
#else
  void readPC(void *buffer, unsigned int buffer_length) {};
  int startProgram(int run_index);
#endif

  int endProgram(int run_index);

  // destructor
  void destroy();
  ~TestControlModule() {}

  void colorPrintf(ConsoleColor colors, const char *mask, ...);
};

#endif /* TEST_CONTROL_MODULE_H */