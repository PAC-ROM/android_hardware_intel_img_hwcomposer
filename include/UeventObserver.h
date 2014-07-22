/*
 * Copyright © 2012 Intel Corporation
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Jackie Li <yaodong.li@intel.com>
 */
#ifndef UEVENT_OBSERVER_H
#define UEVENT_OBSERVER_H

#include <utils/KeyedVector.h>
#include <utils/String8.h>
#include <SimpleThread.h>

namespace android {
namespace intel {

typedef void (*UeventListenerFunc)(void *data);

class UeventObserver
{
public:
    UeventObserver();
    virtual ~UeventObserver();

public:
    bool initialize();
    void deinitialize();
    void start();
    void registerListener(const char *event, UeventListenerFunc func, void *data);

private:
    DECLARE_THREAD(UeventObserverThread, UeventObserver);
    void onUevent();

private:
    enum {
        UEVENT_MSG_LEN = 4096,
    };

    char mUeventMessage[UEVENT_MSG_LEN];
    int mUeventFd;
    struct UeventListener {
        UeventListenerFunc func;
        void *data;
    };
    KeyedVector<String8, UeventListener*> mListeners;
};

} // namespace intel
} // namespace android

#endif
