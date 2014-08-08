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
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "ir/object.h"
#include "ir/refcount.private.h"

/* ------------------------- Local macro definition ------------------------- */
#define DEFAULT_STRONG_COUNT INT_MIN

/* ------------------------- Local type definition ------------------------- */
struct ir_refcount_s {
	ir_iobject_t *iobject;
	volatile int strong_count;
	volatile int weak_count;
};

/* ----------------------- Public function definition ----------------------- */
int ir_refcount__init(ir_refcount_t **refcount, ir_iobject_t *iobject)
{
	int result = ir_result_f_unknown;
	ir_refcount_t *new_refcount = NULL;

	if (!refcount || !iobject) {
		result = ir_result_f_inval;
		goto failed;
	}

	new_refcount = calloc(1, sizeof(*new_refcount));
	if (!new_refcount) {
		result = ir_result_f_nomem;
		goto failed;
	}

	new_refcount->iobject = iobject;

	new_refcount->strong_count = DEFAULT_STRONG_COUNT;
	assert(new_refcount->strong_count < 0);

	*refcount = new_refcount;
	return ir_result_s_ok;

failed:
	if (new_refcount) {
		result = ir_refcount__destroy(new_refcount);
		assert(result == ir_result_s_ok);
	}
	return result;
}

int ir_refcount__destroy(ir_refcount_t *refcount)
{
	if (!refcount) return ir_result_f_inval;
	if (refcount->weak_count) return ir_result_s_false;

	assert(refcount->weak_count == 0);
	assert(refcount->strong_count == 0 ||
		   refcount->strong_count == DEFAULT_STRONG_COUNT);

#ifndef NDEBUG
	memset(refcount, 0, sizeof(*refcount));
#endif
	free(refcount);
	return ir_result_s_ok;
}

int ir_refcount__inc_strong_ref(ir_refcount_t *refcount)
{
	const int one = 1;
	int count = 0;

	if (!refcount) return ir_result_f_inval;

	count = ++refcount->strong_count;
	if (count >= 2) return count;

	if (count == DEFAULT_STRONG_COUNT + 1) {
		refcount->strong_count = one;
		return one;
	}

	--refcount->strong_count;
	return ir_result_f_perm;
}

int ir_refcount__dec_strong_ref(ir_refcount_t *refcount)
{
	int result = ir_result_f_unknown;
	int count = 0;

	ir_unused(result);
	if (!refcount) return ir_result_f_inval;

	count = refcount->strong_count--;
	if (count > 1) return count - 1;

	if (count == 1) {
		result = ir_iobject__destroy(refcount->iobject);
		assert(result >= 0);
		return 0;
	}

	refcount->strong_count = count;
	return ir_result_f_perm;
}

int ir_refcount__inc_weak_ref(ir_refcount_t *refcount)
{
	int count = 0;

	if (!refcount) return ir_result_f_inval;

	count = ++refcount->weak_count;
	if (count >= 1) return count;

	--refcount->weak_count;
	return ir_result_f_perm;
}

int ir_refcount__dec_weak_ref(ir_refcount_t *refcount)
{
	int result = ir_result_f_unknown;
	int count = 0;

	ir_unused(result);
	if (!refcount) return ir_result_f_inval;

	count = refcount->weak_count--;
	if (count > 1) return count - 1;

	if (count == 1) {
		if (refcount->strong_count == DEFAULT_STRONG_COUNT) {
			result = ir_iobject__destroy(refcount->iobject);
			assert(result >= 0);
			return 0;
		}

		result = ir_refcount__destroy(refcount);
		assert(result == ir_result_s_ok);
		return 0;
	}

	refcount->weak_count = count;
	return ir_result_f_perm;
}

/* ---------------------- Private function definition ---------------------- */
//int ir_refcount__set_strong_ref(ir_refcount_t *refcount, const int value)
//{
//	if (!refcount) return ir_result_f_inval;
//	refcount->strong_count = value;
//	return ir_result_s_ok;
//}
//
//int ir_refcount__set_weak_ref(ir_refcount_t *refcount, const int value)
//{
//	if (!refcount) return ir_result_f_inval;
//	refcount->weak_count = value;
//	return ir_result_s_ok;
//}
//
//int ir_refcount__inc_ref(ir_refcount_t *refcount)
//{
//	int weak_count = -1;
//	int strong_count = -1;
//
//	weak_count = ir_refcount__inc_weak_ref(refcount);
//	if (weak_count < 1) {
//		char buffer[64];
//
//		fprintf(stderr,
//				"[%s:%d]:\n"
//				"weak_count must be >= 1, weak_count(%ld), result(%s)\n",
//				__FILE__,
//				__LINE__,
//				weak_count,
//				ir_strresult(weak_count, buffer, sizeof(buffer)));
//		fflush(stderr);
//		goto failed;
//	}
//
//	strong_count = ir_refcount__inc_strong_ref(refcount);
//	if (strong_count < 1) {
//		char buffer[64];
//
//		fprintf(stderr,
//				"[%s:%d]:\n"
//				"strong_count must be >= 1, strong_count(%ld), result(%s)\n",
//				__FILE__,
//				__LINE__,
//				strong_count,
//				ir_strresult(strong_count, buffer, sizeof(buffer)));
//		fflush(stderr);
//		goto failed;
//	}
//
//	return strong_count;
//
//failed:
//	abort();
//}
//
//int ir_refcount__dec_ref(ir_refcount_t *refcount)
//{
//	int weak_count = -1;
//	int strong_count = -1;
//
//	strong_count = ir_refcount__dec_strong_ref(refcount);
//	if (strong_count < 0) {
//		char buffer[64];
//
//		fprintf(stderr,
//				"[%s:%d]:\n"
//				"strong_count must be >= 0, strong_count(%ld), result(%s)\n",
//				__FILE__,
//				__LINE__,
//				strong_count,
//				ir_strresult(strong_count, buffer, sizeof(buffer)));
//		fflush(stderr);
//		goto failed;
//	}
//
//	weak_count = ir_refcount__dec_weak_ref(refcount);
//	if (weak_count < 0) {
//		char buffer[64];
//
//		fprintf(stderr,
//				"[%s:%d]:\n"
//				"weak_count must be >= 0, weak_count(%ld), result(%s)\n",
//				__FILE__,
//				__LINE__,
//				weak_count,
//				ir_strresult(weak_count, buffer, sizeof(buffer)));
//		fflush(stderr);
//		goto failed;
//	}
//
//	return strong_count;
//
//failed:
//	abort();
//}
