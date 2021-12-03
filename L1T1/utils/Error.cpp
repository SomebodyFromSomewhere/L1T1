#include <iostream>
#include <vector>
#include <string>
#include "Error.h"

void Error::addCriticalError(std::string error, std::string functionName) {
	if (functionName == "NULL")
	{
		errors.push_back(error);
	}
	else {
		errors.push_back("[CRIT][" + functionName + "]\t" + error);
	}
	Error::~Error();
	throw std::runtime_error(error);
}

void Error::addWarning(std::string warning, std::string functionName) {
	if (functionName == "NULL")
	{
		errors.push_back(warning);
	}
	else {
		errors.push_back("[WARN][" + functionName + "]\t" + warning);
	}
}

void Error::printErrors() {
	for (std::string error : errors)
		std::cout << error << std::endl;
}

Error::~Error()
{
	printErrors();
}