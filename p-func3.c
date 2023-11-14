#include "main.h"

/** PRINTS POINTER ****/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, put = ' ';
	int ind = BUFF_SIZE - 2, length = 2, put_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);


	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		put = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, put, extra_c, put_start));
}

/*** PRINT NON PRINTABLE ******/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lists the arguments
 * @buffer: Buffer array to handle print
 * @flags: can calculate active flags
 * @width: width
 * @precision: specifies precision
 * @size: specifies size
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int f = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[f] != '\0')
	{
		if (can_print(str[f]))
			buffer[f + offset] = str[f];
		else
			offset += append_hexa_code(str[f], buffer, f + offset);

		f++;
	}

	buffer[f + offset] = '\0';

	return (write(1, buffer, f + offset));
}

/*** PRINTS THE REVERSE *******/
/**
 * print_reverse - Will Print the reverse string.
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags: Will Calculate the  active flags
 * @width: width
 * @precision: Specifies the precision
 * @size: Specifies the size
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int f, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (f = 0; str[f]; f++)
		;

	for (f = f - 1; f >= 0; f--)
	{
		char z = str[f];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/**** PRINT A STRING IN ROT13 **/
/**
 * print_rot13string - Will print a string in rot13.
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags: Will Calculate active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int f, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (f = 0; str[f]; f++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[f])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[f];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
