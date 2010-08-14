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

#ifndef __SXE_MOCK_H__
#define __SXE_MOCK_H__

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef WINDOWS_NT
#include <netdb.h>
#endif

/* CONVENTION EXCLUSION: system functions mocked using #define */

#ifdef MOCK

#define MOCK_SET_HOOK(func, test) mock_ ## func = (test)
#define MOCK_SKIP_START(numtests)
#define MOCK_SKIP_END

#ifdef WINDOWS_NT
#define MOCK_SIZE_T         unsigned
#define MOCK_STDCALL        __stdcall
#define MOCK_SOCKET         SOCKET
#define MOCK_SOCKET_VOID    char
#define MOCK_SOCKET_SSIZE_T int
#define MOCK_SSIZE_T        int
#define MOCK_SOCKLEN_T      int

#else  /* UNIX */
#define MOCK_SIZE_T         size_t
#define MOCK_STDCALL
#define MOCK_SOCKET         int
#define MOCK_SOCKET_VOID    void
#define MOCK_SOCKET_SSIZE_T size_t
#define MOCK_SSIZE_T        ssize_t
#define MOCK_SOCKLEN_T      socklen_t

#endif

/* External definitions of the mock function table
 *  - SXE_STDCALL signifies that Windows implements this function in an OS API, not the C runtime
 */
extern MOCK_SOCKET      (MOCK_STDCALL * mock_accept)       (MOCK_SOCKET, struct sockaddr *, MOCK_SOCKLEN_T *);
extern int              (MOCK_STDCALL * mock_bind)         (MOCK_SOCKET, const struct sockaddr *, MOCK_SOCKLEN_T);
extern void *           (             * mock_calloc)       (size_t, size_t);
extern int              (             * mock_close)        (int);
extern int              (MOCK_STDCALL * mock_connect)      (MOCK_SOCKET, const struct sockaddr *, MOCK_SOCKLEN_T);
extern FILE *           (             * mock_fopen)        (const char * file, const char * mode);
extern int              (             * mock_fputs)        (const char * string, FILE * file);
extern int              (MOCK_STDCALL * mock_getsockopt)   (MOCK_SOCKET, int, int, MOCK_SOCKET_VOID *, MOCK_SOCKLEN_T * __restrict);
extern int              (             * mock_gettimeofday) (struct timeval * __restrict, __timezone_ptr_t);
extern int              (MOCK_STDCALL * mock_listen)       (MOCK_SOCKET, int);
extern off_t            (             * mock_lseek)        (int fd, off_t offset, int whence);
extern MOCK_SSIZE_T     (MOCK_STDCALL * mock_recvfrom)     (MOCK_SOCKET, void *, MOCK_SOCKET_SSIZE_T, int, struct sockaddr *, MOCK_SOCKLEN_T *);
extern MOCK_SSIZE_T     (MOCK_STDCALL * mock_send)         (MOCK_SOCKET, const MOCK_SOCKET_VOID *, MOCK_SOCKET_SSIZE_T, int);
extern MOCK_SSIZE_T     (MOCK_STDCALL * mock_sendto)       (MOCK_SOCKET, const MOCK_SOCKET_VOID *, MOCK_SOCKET_SSIZE_T, int,
                                                            const struct sockaddr *, MOCK_SOCKLEN_T);
extern MOCK_SOCKET      (MOCK_STDCALL * mock_socket)       (int, int, int);
extern MOCK_SSIZE_T     (             * mock_write)        (int, const void *, MOCK_SIZE_T);

#ifndef MOCK_IMPL

#define accept(fd, addr, len)                    (*mock_accept)       ((fd), (addr), (len))
#define bind(fd, addr, len)                      (*mock_bind)         ((fd), (addr), (len))
#define calloc(num, size)                        (*mock_calloc)       ((num), (size))
#define close(fd)                                (*mock_close)        ((fd))
#define connect(fd, addr, len)                   (*mock_connect)      ((fd), (addr), (len))
#define fopen(file, mode)                        (*mock_fopen)        ((file), (mode))
#define fputs(string, file)                      (*mock_fputs)        ((string), (file))
#define getsockopt(fd, lev, oname, oval, olen)   (*mock_getsockopt)   ((fd), (lev), (oname), (oval), (olen))
#define gettimeofday(tm,tz)                      (*mock_gettimeofday) ((tm), (tz))
#define listen(fd, backlog)                      (*mock_listen)       ((fd), (backlog))
#define lseek(fd, offset, whence)                (*mock_lseek)        ((fd), (offset), (whence))
#define send(fd, buf, len, flags)                (*mock_send)         ((fd), (buf), (len), (flags))
#define sendto(fd, buf, len, flags, to, tolen)   (*mock_sendto)       ((fd), (buf), (len), (flags), (to), (tolen))
#define socket(dom, typ, pro)                    (*mock_socket)       ((dom), (typ), (pro))
#define recvfrom(fd, buf, len, flags, to, tolen) (*mock_recvfrom)     ((fd), (buf), (len), (flags), (to), (tolen))
#define write(fd, buf, len)                      (*mock_write)        ((fd), (buf), (len))

#endif /* !MOCK_IMPL     */

#else  /* !defined(MOCK) */

#define MOCK_SET_HOOK(func, test)       ((void)test)
#define MOCK_SKIP_START(num_tests)      skip_start(1, (num_tests), "- this test requires mock functions")
#define MOCK_SKIP_END                   skip_end

#endif /* !defined(MOCK) */

/* The following mock was removed because the function that it mocks cannot be linked statically with the debian version of glibc.
 */
#ifdef DYNAMIC_LINKING_REQUIRED
#define gethostbyname(name)                      (*mock_gethostbyname)((name))
extern struct hostent * (MOCK_STDCALL * mock_gethostbyname)(const char *);
#endif

#endif /* __SXE_MOCK_H__ */