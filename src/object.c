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

#include <assert.h>
#include <string.h>

#include "ir/object.h"

/* ----------------------- Public function definition ----------------------- */
int ir_object_init(ir_object_t *object)
{
	if (!object) return ir_result_f_inval;

	object->iobject.self = object;

	ir_iobject_set_destroy_cb(
		object, (ir_iobject_destroy_cb)ir_object_destroy);
	ir_iobject_set_query_interface_cb(
		object, (ir_iobject_query_interface_cb)ir_object_query_interface);

	object->ref_count = 0;
	return ir_result_s_ok;
}

int ir_object_destroy(ir_object_t *object)
{
	if (!object) return ir_result_f_inval;
	assert(object->ref_count == 0);

#ifndef NDEBUG
	memset(object, 0, sizeof(*object));
#endif
	return ir_result_s_ok;
}

int ir_object_query_interface(
	ir_object_t *object, const char *id, void **interface)
{
	if (!object || !id || !interface) return ir_result_f_inval;

	if (strcmp(id, IR_IOBJECT_ID) == 0) {
		*interface = &object->iobject;
		ir_iobject_inc_ref(*interface);
		return ir_result_s_ok;
	}

	return ir_result_f_no_interface;
}

int ir_object__inc_ref(ir_object_t *object)
{
	return ++object->ref_count;
}

int ir_object__dec_ref(ir_object_t *object)
{
	int result = -1;

	result = --object->ref_count;
	if (result > 0) return result;
	assert(result == 0);

	result = object->destroy(object);
	assert(result >= 0);
	return 0;
}
