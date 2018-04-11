#include "ExceptionTemplate.h"

/*
 * Author: Jon Meilstrup
 *
 * Example of an exception class
 * 
 * Be sure to write '#include "ExampleException.cpp"' in the "ExceptionInclude.cpp" file, replacing "ExampleException" with the name
 * of the exception class you write.
 *
 * When initializing the exception, new up the ErrorCode, where the arguments are char type, int code, string summary, and
 * string example. These are used when logging errors to show the error code itself in the type and code, the summary describing
 * a basic one-phrase or one-sentence description of the error thrown, and the example text going more in-depth into the
 * error and why it might exist.
 */

class ExampleException : public ExceptionTemplate
{
public:
	std::string errorMessage;
	ErrorCode* errorCode;
	ExampleException()
	{
		errorCode = new ErrorCode('A', 101, "Example error", "This is an example error. You will never actually get an A101.");
	};
	~ExampleException()
	{
		delete errorCode;
	};
};