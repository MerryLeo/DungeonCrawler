#ifndef EXCEPTION_H
#define EXCEPTION_H

#define ERROR -1
#define ERROR_NULL_PTR -2
#define SUCCESS 0

#define MSG_ERROR "ERROR: Unknown\n"
#define MSG_ERROR_NULL_PTR "ERROR: Null pointer\n"

void print_error(int error_code);

#endif