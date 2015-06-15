#ifndef TEST_CONTROL_MODULE_H
#define	TEST_CONTROL_MODULE_H


class TestControlModule : public ControlModule {
	AxisData **test_axis;
	//unsigned int COUNT_AXIS;
	colorPrintf_t *colorPrintf;

	//std::map<std::string, system_value> axis_names;

public:
	TestControlModule(){};

	//init
	const char *getUID();
	void prepare(colorPrintf_t *colorPrintf_p, colorPrintfVA_t *colorPrintfVA_p);

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
};

#endif	/* TEST_CONTROL_MODULE_H */