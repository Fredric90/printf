#include "main.h"
/****WILL PRINT CHAR ***/

/**
 * print_char - Prints a char
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags:  can calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char z = va_arg(types, int);

	return (handle_char(z, buffer, flags, width, precision, size));
}
/********WILL PRINT A STRING********/
/**
 * print_string - Prints a string
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags: Can calculate active flags
 * @width: width.
 * @precision:Specifies Precision
 * @size: Specifies Size
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, f;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (f = width - length; f > 0; f--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (f = width - length; f > 0; f--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/**WILL* PRINT PERCENT SIGN *******/
/**
 * print_percent - Prints a percent sign
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags: Can Calculate active flags
 * @width: width.
 * @precision: Specifies Precision
 * @size: Specifies Size
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/******WILL PRINT INT ************/
/**
 * print_int - Print int
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags: Can  Calculate active flags
 * @width: width.
 * @precision: Precision 
 * @size: Size 
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int f = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[f--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[f--] = (num % 10) + '0';
		num /= 10;
	}

	f++;

	return (write_number(is_negative, f, buffer, flags, width, precision, size));
}

/****** WILL PRINT BINARY *****/
/**
 * print_binary - Prints an unsigned number
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags: Can  Calculate active flags
 * @width: width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, f, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);

	m = 24;
	
	a[0] = n / m;
	for (f = 1; f < 32; f++)
	{
		m /= 2;
		a[f] = (n / m) % 2;
	}
	for (f = 0, sum = 0, count = 0; f < 32; f++)
	{
		sum += a[f];
		if (sum || f == 31)
		{
			char z = '0' + a[f];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
