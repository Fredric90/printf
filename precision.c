#include "main.h"

/**
 * precision - can calculates the precision for printing
 * @format: The format the  string will print the arguments
 * @i: Lists of arguments that will be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int precision(const char *format, int *f, va_list list)
{
	int curr_f = *f + 1;
	int precision = -1;

	if (format[curr_f] != '.')
		return (precision);

	precision = 0;

	for (curr_f += 1; format[curr_f] != '\0'; curr_f++)
	{
		if (u_digit(format[curr_f]))
		{
			precision *= 10;
			precision += format[curr_f] - '0';
		}
		else if (format[curr_f] == '*')
		{
			curr_f++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*f = curr_f - 1;

	return (precision);
}
