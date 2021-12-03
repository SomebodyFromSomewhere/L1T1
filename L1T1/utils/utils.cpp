#include <iostream>
#include <string>
#include <time.h>
#include "utils.h"

void calculateTime(clock_t  startTime, std::string functionName	) {
	clock_t endTime = clock();
	double seconds = (double)(endTime - double(startTime)) / CLOCKS_PER_SEC;
	if (functionName == "NULL")
	{
		std::cout << "EXECUTION TIME : " << seconds << std::endl;
	}
	else
	{
		std::cout << "[" << functionName << "]EXECUTION TIME : " << seconds << std::endl;
	}
}