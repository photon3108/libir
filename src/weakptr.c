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
#include <stdlib.h>
#include <string.h>

#include "ir/object.h"
#include "ir/refcount.private.h"
#include "ir/weakptr.h"

/* ------------------------ Private type definition ------------------------ */
struct ir_weakptr_s {
	void *strong_ptr;
	ir_refcount_t *refcount;
};

/* ---------------------- Private function declaration ---------------------- */
static int
ir_weakptr_init_impl(
	ir_weakptr_t **weakptr, void *strong_ptr, ir_refcount_t *refcount);

/* ----------------------- Public function definition ----------------------- */
int
ir_weakptr_init(ir_weakptr_t **weakptr, void *iobject)
{
	return ir_weakptr_init_impl(
		weakptr, iobject, ((ir_iobject_t*)iobject)->self->refcount);
}

int
ir_weakptr_init_by_weakptr(ir_weakptr_t **weakptr, ir_weakptr_t *ptr)
{
	return ir_weakptr_init_impl(weakptr, ptr->strong_ptr, ptr->refcount);
}

int
ir_weakptr_destroy(ir_weakptr_t *weakptr)
{
	int result = ir_result_f_unknown;
	ir_unused(result);

	if (!weakptr) return ir_result_f_inval;

	if (weakptr->refcount) {
		result = ir_refcount__dec_weak_ref(weakptr->refcount);
		assert(result >= 0);
	}

#ifndef NDEBUG
	memset(weakptr, 0, sizeof(*weakptr));
#endif
	free(weakptr);
	return ir_result_s_ok;
}

int
ir_weakptr_summon(ir_weakptr_t *weakptr, void **strong_ptr)
{
	int result = ir_result_f_unknown;

	if (!weakptr || !strong_ptr) return ir_result_f_inval;

	result = ir_refcount__inc_strong_ref(weakptr->refcount);
	if (result < 1) return result;

	result = ir_refcount__inc_weak_ref(weakptr->refcount);
	assert(result >= 1);

	*strong_ptr = weakptr->strong_ptr;
	return ir_result_s_ok;
}

/* ---------------------- Private function definition ---------------------- */
static int
ir_weakptr_init_impl(
	ir_weakptr_t **weakptr, void *strong_ptr, ir_refcount_t *refcount)
{
	int result = ir_result_f_unknown;
	int retcode = ir_result_f_unknown;
	ir_weakptr_t *new_weakptr = NULL;

	ir_unused(result);

	if (!weakptr || !strong_ptr || !refcount) {
		retcode = ir_result_f_inval;
		goto failed;
	}

	new_weakptr = calloc(1, sizeof(*new_weakptr));
	if (!new_weakptr) {
		retcode = ir_result_f_nomem;
		goto failed;
	}

	new_weakptr->strong_ptr = strong_ptr;
	new_weakptr->refcount = refcount;

	retcode = ir_refcount__inc_weak_ref(new_weakptr->refcount);
	if (retcode < 0) goto failed;

	*weakptr = new_weakptr;
	return ir_result_s_ok;

failed:
	if (new_weakptr) {
		result = ir_weakptr_destroy(new_weakptr);
		assert(result >= 0);
	}
	return retcode;
}
