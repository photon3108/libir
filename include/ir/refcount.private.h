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

#ifndef _IR_IR_REFCOUNT_PRIVATE_H_
#define _IR_IR_REFCOUNT_PRIVATE_H_

#include "ir/ir.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------- Public function declaration ---------------------- */
int ir_refcount__init(ir_refcount_t **refcount, ir_iobject_t *iobject);
int ir_refcount__destroy(ir_refcount_t *refcount);

int ir_refcount__inc_strong_ref(ir_refcount_t *refcount);
int ir_refcount__dec_strong_ref(ir_refcount_t *refcount);

int ir_refcount__inc_weak_ref(ir_refcount_t *refcount);
int ir_refcount__dec_weak_ref(ir_refcount_t *refcount);

/* ---------------------- Private function declaration ---------------------- */
//int ir_refcount__set_strong_ref(ir_refcount_t *refcount, const int value);
//int ir_refcount__set_weak_ref(ir_refcount_t *refcount, const int value);

#ifdef __cplusplus
}
#endif

#endif /* _IR_IR_REFCOUNT_PRIVATE_H_ */
