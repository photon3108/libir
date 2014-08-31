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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ir/object.h"
#include "ir/refcount.private.h"

/* ----------------------- Public function definition ----------------------- */
int
ir_object_init(ir_object_t *object)
{
	int result = ir_result_f_unknown;
	int retcode = ir_result_f_unknown;

	if (!object) {
		retcode = ir_result_f_inval;
		goto failed;
	}

	object->iobject.self = object;

	ir_iobject_set_destroy_cb(
		object, (ir_iobject_destroy_cb)ir_object_destroy);
	ir_iobject_set_query_interface_cb(
		object, (ir_iobject_query_interface_cb)ir_object_query_interface);

	object->refcount = NULL;
	result = ir_refcount__init(&object->refcount, &object->iobject);
	if (result < 0 || !object->refcount) {
		retcode = result;
		goto failed;
	}

	return ir_result_s_ok;

failed:
	result = ir_object_destroy(object);
	assert(result >= 0);

	return retcode;
}

int
ir_object_destroy(ir_object_t *object)
{
	int result = ir_result_f_unknown;
	ir_unused(result);

	if (!object) return ir_result_f_inval;

	if (object->refcount) {
		result = ir_refcount__destroy(object->refcount);
		assert(result >= 0);
	}

#ifndef NDEBUG
	memset(object, 0, sizeof(*object));
#endif
	return ir_result_s_ok;
}

int
ir_object_query_interface(ir_object_t *object, const char *id, void **interface)
{
	if (!object || !id || !interface) return ir_result_f_inval;

	if (strcmp(id, IR_IOBJECT_ID) == 0) {
		*interface = &object->iobject;
		ir_iobject_inc_ref(*interface);
		return ir_result_s_ok;
	}

	return ir_result_f_no_interface;
}

int
ir_object__inc_ref(ir_object_t *object)
{
	int weak_count = ir_result_f_unknown;
	int strong_count = ir_result_f_unknown;

	if (!object) return ir_result_f_inval;

	weak_count = ir_refcount__inc_weak_ref(object->refcount);
	if (weak_count < 0) {
		char buffer[64];

		fprintf(
			stderr,
			"libir **FATAL**: weak_count(%s). %s:%d\n",
			ir_strresult(buffer, sizeof(buffer), weak_count),
			__FILE__,
			__LINE__);
		fflush(stderr);
		abort();
	}

	strong_count = ir_refcount__inc_strong_ref(object->refcount);
	if (strong_count < 0) {
		char buffer[64];

		fprintf(
			stderr,
			"libir **FATAL**: strong_count(%s). %s:%d\n",
			ir_strresult(buffer, sizeof(buffer), strong_count),
			__FILE__,
			__LINE__);
		fflush(stderr);
		abort();
	}

	return strong_count;
}

int
ir_object__dec_ref(ir_object_t *object)
{
	ir_refcount_t *refcount = NULL;
	int weak_count = ir_result_f_unknown;
	int strong_count = ir_result_f_unknown;

	if (!object) return ir_result_f_inval;
	refcount = object->refcount;

	strong_count = ir_refcount__dec_strong_ref(refcount);
	if (strong_count < 0) {
		char buffer[64];

		fprintf(
			stderr,
			"libir **FATAL**: strong_count(%s). %s:%d\n",
			ir_strresult(buffer, sizeof(buffer), strong_count),
			__FILE__,
			__LINE__);
		fflush(stderr);
		abort();
	}

	weak_count = ir_refcount__dec_weak_ref(refcount);
	if (weak_count < 0) {
		char buffer[64];

		fprintf(
			stderr,
			"libir **FATAL**: weak_count(%s). %s:%d\n",
			ir_strresult(buffer, sizeof(buffer), weak_count),
			__FILE__,
			__LINE__);
		fflush(stderr);
		abort();
	}

	return strong_count;
}
