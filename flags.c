#include "main.h"

/**
 * flags - can be used to calculate active flags
 * @format: String formatted  in which to print the arguments
 * @f: take a parameter.
 * 
 * Return: Flags:
 */
int flags(const char *format, int *f)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, curr_f;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_f = *f + 1; format[curr_f] != '\0'; curr_f++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curr_f] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*f = curr_f - 1;

	return (flags);
}
