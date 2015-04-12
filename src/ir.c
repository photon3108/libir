/* The MIT License (MIT)
 *
 * Copyright (c) 2014 Steven Huang <photon3108(at)gmail.com>. All rights
 * reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include "ir/ir.h"

/* ---------------------- Private function declaration ---------------------- */
static const char *
ir_result_print(
	const ir_result_e result,
	const char *output,
	char *buffer,
	const int buffer_size);

/* ----------------------- Public function definition ----------------------- */
const char *
ir_result_get_name(
	const ir_result_e result, char *buffer, const int buffer_size)
{
	const char *output = NULL;

#define IR_REPLACE(idx, name, description, ...) \
	if (result == ir_result_##name) { \
		output = "ir_result_" #name; \
		goto finally; \
	}
	IR_RESULT_LIST(IR_REPLACE)
#undef IR_REPLACE

	goto finally;

finally:
	return ir_result_print(result, output, buffer, buffer_size);
}

const char *
ir_result_get_description(
	const ir_result_e result, char *buffer, const int buffer_size)
{
	const char *output = NULL;

#define IR_REPLACE(idx, name, description, ...) \
	if (result == ir_result_##name) { \
		output = description; \
		goto finally; \
	}
	IR_RESULT_LIST(IR_REPLACE)
#undef IR_REPLACE

	goto finally;

finally:
	return ir_result_print(result, output, buffer, buffer_size);
}

static const char *
ir_result_print(
	const ir_result_e result,
	const char *output,
	char *buffer,
	const int buffer_size)
{
	int num_write = 0;

	if (!buffer || buffer_size < 1) goto failed;

	if (!output) {
		num_write = snprintf(
			buffer, buffer_size, "Unknown result code %d", result);
		if (num_write < 0 || num_write >= buffer_size) goto failed;
		output = buffer;
		goto finally;
	}

	goto print_output;

print_output:
	num_write = snprintf(buffer, buffer_size, "%s", output);
	if (num_write < 0) goto failed;
	goto finally;

failed:
	output = "Unknown result code";
	goto finally;

finally:
	return output;
}

