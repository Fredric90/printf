#include "main.h"

/**
 * can_print - can evaluate if a char is printable
 * @z: Char to be evaluated.
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int can_print(char z)
{
	if (z >= 32 && z < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @f: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 *
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int f)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[f++] = '\\';
	buffer[f++] = 'x';

	buffer[f++] = map_to[ascii_code / 16];
	buffer[f] = map_to[ascii_code % 16];

	return (3);
}

/**
 * u_digit - Verifies if a char is a digit
 * @z: Char to be evaluated
 *
 * Return: 1 if z is a digit, 0 otherwise
 */
int u_digit(char z)
{
	if (z >= '0' && z <= '9')
		return (1);

	return (0);
}

/**
 * Convert_size_number - Casts a number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Will Cast a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
