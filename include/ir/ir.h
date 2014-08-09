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

#ifndef _IR_IR_IR_H_
#define _IR_IR_IR_H_

#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------ Public macro definition ------------------------ */
/* X Macro */
#define IR_RESULT_LIST(XX) \
	/* Succeeded */ \
	XX(1, s_false, "Succeeded(False)") \
	XX(0, s_ok, "Succeeded(Ok/True)") \
	\
	/* Failed */ \
	XX(-9000, f_unknown, "Failed(Unknown error)") \
	XX(-9001, f_no_interface, "Failed(No interface)") \
	\
	/* Failed: errno*/ \
	XX(-E2BIG, f_2big, "Failed(Argument list too long)") \
	XX(-EACCES, f_acces, "Failed(Permission denied)") \
	XX(-EADDRINUSE, f_addrinuse, "Failed(Address already in use)") \
	XX(-EADDRNOTAVAIL,  \
	   f_addrnotavail,  \
	   "Failed(Cannot assign requested address)") \
	XX(-EADV, f_adv, "Failed(Advertise error)") \
	XX(-EAFNOSUPPORT,  \
	   f_afnosupport,  \
	   "Failed(Address family not supported by protocol)") \
	XX(-EAGAIN, f_again, "Failed(Resource temporarily unavailable)") \
	XX(-EALREADY, f_already, "Failed(Operation already in progress)") \
	XX(-EBADE, f_bade, "Failed(Invalid exchange)") \
	XX(-EBADF, f_badf, "Failed(Bad file descriptor)") \
	XX(-EBADFD, f_badfd, "Failed(File descriptor in bad state)") \
	XX(-EBADMSG, f_badmsg, "Failed(Bad message)") \
	XX(-EBADR, f_badr, "Failed(Invalid request descriptor)") \
	XX(-EBADRQC, f_badrqc, "Failed(Invalid request code)") \
	XX(-EBADSLT, f_badslt, "Failed(Invalid slot)") \
	XX(-EBFONT, f_bfont, "Failed(Bad font file format)") \
	XX(-EBUSY, f_busy, "Failed(Device or resource busy)") \
	XX(-ECANCELED, f_canceled, "Failed(Operation canceled)") \
	XX(-ECHILD, f_child, "Failed(No child processes)") \
	XX(-ECHRNG, f_chrng, "Failed(Channel number out of range)") \
	XX(-ECOMM, f_comm, "Failed(Communication error on send)") \
	XX(-ECONNABORTED,  \
	   f_connaborted,  \
	   "Failed(Software caused connection abort)") \
	XX(-ECONNREFUSED, f_connrefused, "Failed(Connection refused)") \
	XX(-ECONNRESET, f_connreset, "Failed(Connection reset by peer)") \
	XX(-EDEADLK, f_deadlk, "Failed(Resource deadlock avoided)") \
	XX(-EDEADLOCK, f_deadlock, "Failed(Resource deadlock avoided)") \
	XX(-EDESTADDRREQ, f_destaddrreq, "Failed(Destination address required)") \
	XX(-EDOM, f_dom, "Failed(Numerical argument out of domain)") \
	XX(-EDOTDOT, f_dotdot, "Failed(RFS specific error)") \
	XX(-EDQUOT, f_dquot, "Failed(Disk quota exceeded)") \
	XX(-EEXIST, f_exist, "Failed(File exists)") \
	XX(-EFAULT, f_fault, "Failed(Bad address)") \
	XX(-EFBIG, f_fbig, "Failed(File too large)") \
	XX(-EHOSTDOWN, f_hostdown, "Failed(Host is down)") \
	XX(-EHOSTUNREACH, f_hostunreach, "Failed(No route to host)") \
	XX(-EIDRM, f_idrm, "Failed(Identifier removed)") \
	XX(-EILSEQ,  \
	   f_ilseq,  \
	   "Failed(Invalid or incomplete multibyte or wide character)") \
	XX(-EINPROGRESS, f_inprogress, "Failed(Operation now in progress)") \
	XX(-EINTR, f_intr, "Failed(Interrupted system call)") \
	XX(-EINVAL, f_inval, "Failed(Invalid argument)") \
	XX(-EIO, f_io, "Failed(Input/output error)") \
	XX(-EISCONN, f_isconn, "Failed(Transport endpoint is already connected)") \
	XX(-EISDIR, f_isdir, "Failed(Is a directory)") \
	XX(-EISNAM, f_isnam, "Failed(Is a named type file)") \
	XX(-EKEYEXPIRED, f_keyexpired, "Failed(Key has expired)") \
	XX(-EKEYREJECTED, f_keyrejected, "Failed(Key was rejected by service)") \
	XX(-EKEYREVOKED, f_keyrevoked, "Failed(Key has been revoked)") \
	XX(-EL2HLT, f_l2hlt, "Failed(Level 2 halted)") \
	XX(-EL2NSYNC, f_l2nsync, "Failed(Level 2 not synchronized)") \
	XX(-EL3HLT, f_l3hlt, "Failed(Level 3 halted)") \
	XX(-EL3RST, f_l3rst, "Failed(Level 3 reset)") \
	XX(-ELIBACC, f_libacc, "Failed(Can not access a needed shared library)") \
	XX(-ELIBBAD, f_libbad, "Failed(Accessing a corrupted shared library)") \
	XX(-ELIBEXEC, f_libexec, "Failed(Cannot exec a shared library directly)") \
	XX(-ELIBMAX,  \
	   f_libmax,  \
	   "Failed(Attempting to link in too many shared libraries)") \
	XX(-ELIBSCN, f_libscn, "Failed(.lib section in a.out corrupted)") \
	XX(-ELNRNG, f_lnrng, "Failed(Link number out of range)") \
	XX(-ELOOP, f_loop, "Failed(Too many levels of symbolic links)") \
	XX(-EMEDIUMTYPE, f_mediumtype, "Failed(Wrong medium type)") \
	XX(-EMFILE, f_mfile, "Failed(Too many open files)") \
	XX(-EMLINK, f_mlink, "Failed(Too many links)") \
	XX(-EMSGSIZE, f_msgsize, "Failed(Message too long)") \
	XX(-EMULTIHOP, f_multihop, "Failed(Multihop attempted)") \
	XX(-ENAMETOOLONG, f_nametoolong, "Failed(File name too long)") \
	XX(-ENAVAIL, f_navail, "Failed(No XENIX semaphores available)") \
	XX(-ENETDOWN, f_netdown, "Failed(Network is down)") \
	XX(-ENETRESET, f_netreset, "Failed(Network dropped connection on reset)") \
	XX(-ENETUNREACH, f_netunreach, "Failed(Network is unreachable)") \
	XX(-ENFILE, f_nfile, "Failed(Too many open files in system)") \
	XX(-ENOANO, f_noano, "Failed(No anode)") \
	XX(-ENOBUFS, f_nobufs, "Failed(No buffer space available)") \
	XX(-ENOCSI, f_nocsi, "Failed(No CSI structure available)") \
	XX(-ENODATA, f_nodata, "Failed(No data available)") \
	XX(-ENODEV, f_nodev, "Failed(No such device)") \
	XX(-ENOENT, f_noent, "Failed(No such file or directory)") \
	XX(-ENOEXEC, f_noexec, "Failed(Exec format error)") \
	XX(-ENOKEY, f_nokey, "Failed(Required key not available)") \
	XX(-ENOLCK, f_nolck, "Failed(No locks available)") \
	XX(-ENOLINK, f_nolink, "Failed(Link has been severed)") \
	XX(-ENOMEDIUM, f_nomedium, "Failed(No medium found)") \
	XX(-ENOMEM, f_nomem, "Failed(Cannot allocate memory)") \
	XX(-ENOMSG, f_nomsg, "Failed(No message of desired type)") \
	XX(-ENONET, f_nonet, "Failed(Machine is not on the network)") \
	XX(-ENOPKG, f_nopkg, "Failed(Package not installed)") \
	XX(-ENOPROTOOPT, f_noprotoopt, "Failed(Protocol not available)") \
	XX(-ENOSPC, f_nospc, "Failed(No space left on device)") \
	XX(-ENOSR, f_nosr, "Failed(Out of streams resources)") \
	XX(-ENOSTR, f_nostr, "Failed(Device not a stream)") \
	XX(-ENOSYS, f_nosys, "Failed(Function not implemented)") \
	XX(-ENOTBLK, f_notblk, "Failed(Block device required)") \
	XX(-ENOTCONN, f_notconn, "Failed(Transport endpoint is not connected)") \
	XX(-ENOTDIR, f_notdir, "Failed(Not a directory)") \
	XX(-ENOTEMPTY, f_notempty, "Failed(Directory not empty)") \
	XX(-ENOTNAM, f_notnam, "Failed(Not a XENIX named type file)") \
	XX(-ENOTRECOVERABLE, f_notrecoverable, "Failed(State not recoverable)") \
	XX(-ENOTSOCK, f_notsock, "Failed(Socket operation on non-socket)") \
	XX(-ENOTSUP, f_notsup, "Failed(Operation not supported)") \
	XX(-ENOTTY, f_notty, "Failed(Inappropriate ioctl for device)") \
	XX(-ENOTUNIQ, f_notuniq, "Failed(Name not unique on network)") \
	XX(-ENXIO, f_nxio, "Failed(No such device or address)") \
	XX(-EOPNOTSUPP, f_opnotsupp, "Failed(Operation not supported)") \
	XX(-EOVERFLOW,  \
	   f_overflow,  \
	   "Failed(Value too large for defined data type)") \
	XX(-EOWNERDEAD, f_ownerdead, "Failed(Owner died)") \
	XX(-EPERM, f_perm, "Failed(Operation not permitted)") \
	XX(-EPFNOSUPPORT, f_pfnosupport, "Failed(Protocol family not supported)") \
	XX(-EPIPE, f_pipe, "Failed(Broken pipe)") \
	XX(-EPROTO, f_proto, "Failed(Protocol error)") \
	XX(-EPROTONOSUPPORT, f_protonosupport, "Failed(Protocol not supported)") \
	XX(-EPROTOTYPE, f_prototype, "Failed(Protocol wrong type for socket)") \
	XX(-ERANGE, f_range, "Failed(Numerical result out of range)") \
	XX(-EREMCHG, f_remchg, "Failed(Remote address changed)") \
	XX(-EREMOTE, f_remote, "Failed(Object is remote)") \
	XX(-EREMOTEIO, f_remoteio, "Failed(Remote I/O error)") \
	XX(-ERESTART,  \
	   f_restart,  \
	   "Failed(Interrupted system call should be restarted)") \
	XX(-ERFKILL, f_rfkill, "Failed(Operation not possible due to RF-kill)") \
	XX(-EROFS, f_rofs, "Failed(Read-only file system)") \
	XX(-ESHUTDOWN,  \
	   f_shutdown,  \
	   "Failed(Cannot send after transport endpoint shutdown)") \
	XX(-ESOCKTNOSUPPORT,  \
	   f_socktnosupport,  \
	   "Failed(Socket type not supported)") \
	XX(-ESPIPE, f_spipe, "Failed(Illegal seek)") \
	XX(-ESRCH, f_srch, "Failed(No such process)") \
	XX(-ESRMNT, f_srmnt, "Failed(Srmount error)") \
	XX(-ESTALE, f_stale, "Failed(Stale NFS file handle)") \
	XX(-ESTRPIPE, f_strpipe, "Failed(Streams pipe error)") \
	XX(-ETIME, f_time, "Failed(Timer expired)") \
	XX(-ETIMEDOUT, f_timedout, "Failed(Connection timed out)") \
	XX(-ETOOMANYREFS,  \
	   f_toomanyrefs,  \
	   "Failed(Too many references: cannot splice)") \
	XX(-ETXTBSY, f_txtbsy, "Failed(Text file busy)") \
	XX(-EUCLEAN, f_uclean, "Failed(Structure needs cleaning)") \
	XX(-EUNATCH, f_unatch, "Failed(Protocol driver not attached)") \
	XX(-EUSERS, f_users, "Failed(Too many users)") \
	XX(-EWOULDBLOCK, f_wouldblock, "Failed(Resource temporarily unavailable)") \
	XX(-EXDEV, f_xdev, "Failed(Invalid cross-device link)") \
	XX(-EXFULL, f_xfull, "Failed(Exchange full)") \

/* Function */
#define ir_unused(x) ((void)(x))

/* Others */
#define IR_INLINE __inline__
#define IR_IOBJECT_ID "ir/iobject"

#ifndef ERFKILL
#define ERFKILL -1000
#endif

/* ------------------------- Public type definition ------------------------- */
typedef struct ir_iobject_s ir_iobject_t;
typedef struct ir_object_s ir_object_t;
typedef struct ir_refcount_s ir_refcount_t;
typedef struct ir_weakptr_s ir_weakptr_t;

#define IR_REPLACE(idx, name, ...) ir_result_##name = idx,
typedef enum {
	IR_RESULT_LIST(IR_REPLACE)
} ir_result_e;
#undef IR_REPLACE

/* ---------------------- Public function declaration ---------------------- */
const char *
ir_strresult(char *buffer, const int buffer_size, const ir_result_e result);

#ifdef __cplusplus
}
#endif

#endif /* _IR_IR_IR_H_ */
