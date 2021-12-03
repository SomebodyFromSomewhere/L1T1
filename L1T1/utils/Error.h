#ifndef ERROR_H
#define ERROR_H

#include <vector>

class Error
{
public:
	~Error();
	void addCriticalError(std::string error, std::string functionName = "NULL");
	void addWarning(std::string warning, std::string functionName = "NULL");
	void printErrors();

private:
	std::vector<std::string> errors;
};
#endif // ERROR_H