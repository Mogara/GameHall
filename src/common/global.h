#ifndef GLOBAL_H
#define GLOBAL_H

#include "config.h"

#include <QtGlobal>

#ifdef MGH_BUILD_LIBRARY
#define MGH_EXPORT Q_DECL_EXPORT
#else
#define MGH_EXPORT
#endif // MGH_BUILD_LIBRARY

/*
   MGH_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define MGH_VERSION      MGH_VERSION_CHECK(MGH_VERSION_MAJOR, MGH_VERSION_MINOR, MGH_VERSION_PATCH)
/*
   can be used like #if (MGH_VERSION >= MGH_VERSION_CHECK(4, 4, 0))
*/
#define MGH_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#define MGH_DECLARE_PRIVATE(Class) \
    inline Class##Private* p_func() { return reinterpret_cast<Class##Private *>(qGetPtrHelper(p_ptr)); } \
    inline const Class##Private* p_func() const { return reinterpret_cast<const Class##Private *>(qGetPtrHelper(p_ptr)); } \
    friend class Class##Private;

#define MGH_DECLARE_PUBLIC(Class)                                    \
    inline Class* b_func() { return static_cast<Class *>(b_ptr); } \
    inline const Class* b_func() const { return static_cast<const Class *>(b_ptr); } \
    friend class Class;

#define M_P(Class) Class##Private * const p = p_func()
#define M_B(Class) Class * const b = b_func()

/*
 * C++11 keywords and expressions
 */
#if __cplusplus >= 201103L
# define NULLPTR         nullptr
#else
# define NULLPTR         NULL
#endif // __cplusplus >= 201103L

#endif // GLOBAL_H
