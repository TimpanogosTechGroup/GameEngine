#ifndef CLASS_CAST_MISMATCH_H
#define CLASS_CAST_MISMATCH_H

#include "ExceptionTemplate.h"

class ClassCastMismatchException : public ExceptionTemplate {
public:
	ClassCastMismatchException() {
		ErrorCode error('R', 404, "Class mismatch", "Class mismatch");
		errorCode = error;
	};
	~ClassCastMismatchException() {};
private:

};

#endif