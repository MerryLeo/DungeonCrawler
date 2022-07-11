#include "stdio.h"
#include "exception.h"

void print_error(int error)
{
    switch (error)
    {
        case ERROR:
            printf(MSG_ERROR);
            return;
        case ERROR_NULL_PTR:
            printf(MSG_ERROR_NULL_PTR);
            return;
        default:
            return;
    }
}