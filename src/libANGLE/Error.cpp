//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Error.cpp: Implements the egl::Error and gl::Error classes which encapsulate API errors
// and optional error messages.

#include "libANGLE/Error.h"

#include "common/angleutils.h"

#include <cstdarg>

namespace gl
{

Error::Error(GLenum errorCode, const char *msg, ...)
    : mCode(errorCode), mID(errorCode), mMessage(nullptr)
{
    va_list vararg;
    va_start(vararg, msg);
    createMessageString();
    *mMessage = FormatString(msg, vararg);
    va_end(vararg);
}

Error::Error(GLenum errorCode, GLuint id, const char *msg, ...)
    : mCode(errorCode), mID(id), mMessage(nullptr)
{
    va_list vararg;
    va_start(vararg, msg);
    createMessageString();
    *mMessage = FormatString(msg, vararg);
    va_end(vararg);
}

void Error::createMessageString() const
{
    if (mMessage == nullptr)
    {
        mMessage = new std::string();
    }
}

const std::string &Error::getMessage() const
{
    createMessageString();
    return *mMessage;
}

bool Error::operator==(const Error &other) const
{
    if (mCode != other.mCode)
        return false;

    // TODO(jmadill): Compare extended error codes instead of strings.
    if ((mMessage == nullptr || other.mMessage == nullptr) &&
        ((mMessage == nullptr) != (other.mMessage == nullptr)))
        return false;

    return (*mMessage == *other.mMessage);
}

bool Error::operator!=(const Error &other) const
{
    return !(*this == other);
}
}

namespace egl
{

Error::Error(EGLint errorCode, const char *msg, ...)
    : mCode(errorCode),
      mID(0),
      mMessage(nullptr)
{
    va_list vararg;
    va_start(vararg, msg);
    createMessageString();
    *mMessage = FormatString(msg, vararg);
    va_end(vararg);
}

Error::Error(EGLint errorCode, EGLint id, const char *msg, ...)
    : mCode(errorCode),
      mID(id),
      mMessage(nullptr)
{
    va_list vararg;
    va_start(vararg, msg);
    createMessageString();
    *mMessage = FormatString(msg, vararg);
    va_end(vararg);
}
void Error::createMessageString() const
{
    if (mMessage == nullptr)
    {
        mMessage = new std::string();
    }
}

const std::string &Error::getMessage() const
{
    createMessageString();
    return *mMessage;
}

}
