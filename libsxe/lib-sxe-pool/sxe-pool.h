/* Copyright (c) 2010 Sophos Group.
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __SXE_POOL_H__
#define __SXE_POOL_H__

#define SXE_POOL_NO_INDEX             -1U
#define SXE_POOL_LOCK_TAKEN           -2U /* Only used in sxe_pool_set_indexed_element_state_locked() */
#define SXE_POOL_LOCK_NEVER_TAKEN     -3U /* Used in sxe_pool_*_locked() to indicate we gave up trying to acquire lock */
#define SXE_POOL_NAME_MAXIMUM_LENGTH   31
#define SXE_POOL_LOCKS_ENABLED         1
#define SXE_POOL_LOCKS_DISABLED        0

typedef void (*SXE_POOL_EVENT_TIMEOUT)(    void * array, unsigned array_index, void * caller_info);

#include "sxe-pool-proto.h"
#endif
