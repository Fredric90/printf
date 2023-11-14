#include "main.h"

/**
 * size: Will Calculate the size thaa gives the argument
 * @format: Will format the  string in which to print the arguments
 * @f: List of arguments to be printed.
 *
 * Return: Precision.
 */
int size(const char *format, int *f)
{
	int curr_f = *f + 1;
	int size = 0;

	if (format[curr_f] == 'l')
		size = S_LONG;
	else if (format[curr_f] == 'h')
		size = S_SHORT;

	if (size == 0)
		*f = curr_f - 1;
	else
		*f = curr_f;

	return (size);
}
