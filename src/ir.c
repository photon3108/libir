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

/* ----------------------- Public function definition ----------------------- */
const char *
ir_strresult(char *buffer, const int buffer_size, const ir_result_e result)
{
	int num_write = 0;
	const char *strresult = "";

	if (!buffer || buffer_size < 0) goto failed;

#define IR_REPLACE(idx, name, description, ...) \
	if (result == ir_result_##name) { \
		strresult = description; \
		goto print; \
	}
	IR_RESULT_LIST(IR_REPLACE)
#undef IR_REPLACE

	num_write = snprintf(
		buffer, buffer_size, "Unknown result code %d", result);
	if (num_write < 0 || num_write >= buffer_size) goto failed;
	return buffer;

print:
	num_write = snprintf(buffer, buffer_size, "%s", strresult);
	if (num_write < 0 || num_write >= buffer_size) goto failed;
	return buffer;

failed:
	return "";
}
