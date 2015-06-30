#ifndef TEST_CONTROL_MODULE_H
#define	TEST_CONTROL_MODULE_H


class TestControlModule : public ControlModule {
	AxisData **test_axis;
	colorPrintfModuleVA_t *colorPrintf_p;

public:
	TestControlModule(){};

	//init
	const char *getUID();
	void prepare(colorPrintfModule_t *colorPrintf_p, colorPrintfModuleVA_t *colorPrintfVA_p);

	//compiler only
	AxisData** getAxis(unsigned int *count_axis);
	void *writePC(unsigned int *buffer_length);

	//intepreter - devices
	int init();
	void execute(sendAxisState_t sendAxisState);
	void final() {};

	//intepreter - program & lib
	void readPC(void *buffer, unsigned int buffer_length);

	//intepreter - program
	int startProgram(int uniq_index);
	int endProgram(int uniq_index);

	//destructor
	void destroy();
	~TestControlModule() {}

	void colorPrintf(ConsoleColor colors, const char *mask, ...);
};

#endif	/* TEST_CONTROL_MODULE_H */