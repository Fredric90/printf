#include "main.h"

/**
 * width - Will Calculate the width for printing
 * @format: Will Format the string in which to print the arguments.
 * @f: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int width(const char *format, int *f, va_list list)
{
	int curr_f;
	int width = 0;

	for (curr_f = *f + 1; format[curr_f] != '\0'; curr_f++)
	{
		if (is_digit(format[curr_f]))
		{
			width *= 10;
			width += format[curr_f] - '0';
		}
		else if (format[curr_f] == '*')
		{
			curr_f++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*f = curr_f - 1;

	return (width);
}
