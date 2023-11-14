#include "main.h"

/*************** HANDLE ***************/
/**
 * handle_char can print a string
 * @z: char types.
 * @buffer: The buffer array will handle print
 * @flags:  Will calculate active flags.
 * @width: will get width.
 * @precision: specifies the precision
 * @size: specifies the size
 *
 * Return: number chars.
 */
int handle_char(char z, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and put at buffer's right */
	int f = 0;
	char put = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		put = '0';

	buffer[f++] = z;
	buffer[f] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (f = 0; f < width - 1; f++)
			buffer[BUFF_SIZE - f - 2] = put;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - f - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - f - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/********** WRITE NUMBER **************/
/**
 * write_number - will print a string
 * @is_negative: Lists of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: specifies the precision
 * @size: specifies the size
 *
 * Return: Number of chars.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char put = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		put = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, put, extra_ch));
}

/**
 * write_num - Writes a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @pre: Specifies precision
 * @length: Number length
 * @put: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int pre,
	int length, char put, char extra_c)
{
	int f, put_start = 1;

	if (pre == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (pre == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = put = ' '; /* width is displayed with padding ' ' */
	if (pre > 0 && pre < length)
		put = ' ';
	while (pre > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (f = 1; f < width - length + 1; f++)
			buffer[i] = put;
		buffer[i] = '\0';
		if (flags & F_MINUS && put == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], f - 1));
		}
		else if (!(flags & F_MINUS) && put == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], f - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && put == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--put_start] = extra_c;
			return (write(1, &buffer[put_start], f - put_start) +
				write(1, &buffer[ind], length - (1 - put_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - will Write an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: specifies flags
 * @width: specifies width
 * @precision: specifies precision
 * @size: specifies the size
 *
 * Return: Number of written chars will return.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position f */
	int length = BUFF_SIZE - ind - 1, f = 0;
	char put = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		put = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		put = '0';

	if (width > length)
	{
		for (f = 0; f < width - length; f++)
			buffer[f] = put;

		buffer[f] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>put]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], f));
		}
		else /* Asign extra char to left of padding [put>buffer]*/
		{
			return (write(1, &buffer[0], f) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Writes a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: width specifier
 * @flags: Flags specifier
 * @put: Char representing the padding
 * @extra_c: Char representing extra char
 * @put_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char put, char extra_c, int put_start)
{
	int f;

	if (width > length)
	{
		for (f = 3; f < width - length + 3; f++)
			buffer[i] = put;
		buffer[i] = '\0';
		if (flags & F_MINUS && put == ' ')/* Asigns extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], f - 3));
		}
		else if (!(flags & F_MINUS) && put == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], f - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && put == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--put_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[put_start], f - put_start) +
				write(1, &buffer[ind], length - (1 - put_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
