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

#ifndef _IR_IR_OBJECT_H_
#define _IR_IR_OBJECT_H_

#include "ir/ir.h"
#include "ir/object.private.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------- Public type definition ------------------------- */
typedef int (*
ir_iobject_destroy_cb)(void *self);
typedef int (*
ir_iobject_query_interface_cb)(void *self, const char *id, void **interface);

struct ir_iobject_s {
/* Private: */
	ir_object_t *self;
};

struct ir_object_s {
/* Private: */
	ir_iobject_t iobject;
	ir_iobject_destroy_cb destroy;
	ir_iobject_query_interface_cb query_interface;

	ir_refcount_t *refcount;
};

/* ---------------------- Public function declaration ---------------------- */
int ir_object_init(ir_object_t *object);
int ir_object_destroy(ir_object_t *object);

int ir_object_query_interface(
	ir_object_t *object, const char *id, void **interface);

/* ----------------------- Public function definition ----------------------- */
static IR_INLINE int
ir_iobject_inc_ref(void *iobject)
{
	return ir_object__inc_ref(((ir_iobject_t*)iobject)->self);
}

static IR_INLINE int
ir_iobject_dec_ref(void *iobject)
{
	return ir_object__dec_ref(((ir_iobject_t*)iobject)->self);
}

static IR_INLINE int
ir_iobject_query_interface(void *iobject, const char *id, void **interface)
{
	return ((ir_iobject_t*)iobject)->self->query_interface(
		((ir_iobject_t*)iobject)->self, id, interface);
}

static IR_INLINE void
ir_iobject_set_destroy_cb(void *iobject, ir_iobject_destroy_cb destroy)
{
	((ir_iobject_t*)iobject)->self->destroy = destroy;
}

static IR_INLINE void
ir_iobject_set_query_interface_cb(
	void *iobject, ir_iobject_query_interface_cb query_interface)
{
	((ir_iobject_t*)iobject)->self->query_interface = query_interface;
}

/* ---------------------- Private function definition ---------------------- */
static IR_INLINE int
ir_iobject__destroy(ir_iobject_t *iobject)
{
	return iobject->self->destroy(iobject->self);
}

#ifdef __cplusplus
}
#endif

#endif /* _IR_IR_OBJECT_H_ */
