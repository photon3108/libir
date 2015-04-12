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
	XX(1, s_false, "False") \
	XX(0, s_ok, "Ok/True") \
	\
	/* Failed */ \
	XX(-9000, f_unknown, "Unknown error") \
	XX(-9001, f_no_interface, "No interface") \
	\
	/* Failed: errno*/ \
	XX(-E2BIG, f_2big, "Argument list too long") \
	XX(-EACCES, f_acces, "Permission denied") \
	XX(-EADDRINUSE, f_addrinuse, "Address already in use") \
	XX(-EADDRNOTAVAIL, f_addrnotavail, "Cannot assign requested address") \
	XX(-EADV, f_adv, "Advertise error") \
	XX(-EAFNOSUPPORT, \
	   f_afnosupport, \
	   "Address family not supported by protocol") \
	XX(-EAGAIN, f_again, "Resource temporarily unavailable") \
	XX(-EALREADY, f_already, "Operation already in progress") \
	XX(-EBADE, f_bade, "Invalid exchange") \
	XX(-EBADF, f_badf, "Bad file descriptor") \
	XX(-EBADFD, f_badfd, "File descriptor in bad state") \
	XX(-EBADMSG, f_badmsg, "Bad message") \
	XX(-EBADR, f_badr, "Invalid request descriptor") \
	XX(-EBADRQC, f_badrqc, "Invalid request code") \
	XX(-EBADSLT, f_badslt, "Invalid slot") \
	XX(-EBFONT, f_bfont, "Bad font file format") \
	XX(-EBUSY, f_busy, "Device or resource busy") \
	XX(-ECANCELED, f_canceled, "Operation canceled") \
	XX(-ECHILD, f_child, "No child processes") \
	XX(-ECHRNG, f_chrng, "Channel number out of range") \
	XX(-ECOMM, f_comm, "Communication error on send") \
	XX(-ECONNABORTED, f_connaborted, "Software caused connection abort") \
	XX(-ECONNREFUSED, f_connrefused, "Connection refused") \
	XX(-ECONNRESET, f_connreset, "Connection reset by peer") \
	XX(-EDEADLK, f_deadlk, "Resource deadlock avoided") \
	XX(-EDEADLOCK, f_deadlock, "Resource deadlock avoided") \
	XX(-EDESTADDRREQ, f_destaddrreq, "Destination address required") \
	XX(-EDOM, f_dom, "Numerical argument out of domain") \
	XX(-EDOTDOT, f_dotdot, "RFS specific error") \
	XX(-EDQUOT, f_dquot, "Disk quota exceeded") \
	XX(-EEXIST, f_exist, "File exists") \
	XX(-EFAULT, f_fault, "Bad address") \
	XX(-EFBIG, f_fbig, "File too large") \
	XX(-EHOSTDOWN, f_hostdown, "Host is down") \
	XX(-EHOSTUNREACH, f_hostunreach, "No route to host") \
	XX(-EIDRM, f_idrm, "Identifier removed") \
	XX(-EILSEQ, f_ilseq, "Invalid or incomplete multibyte or wide character") \
	XX(-EINPROGRESS, f_inprogress, "Operation now in progress") \
	XX(-EINTR, f_intr, "Interrupted system call") \
	XX(-EINVAL, f_inval, "Invalid argument") \
	XX(-EIO, f_io, "Input/output error") \
	XX(-EISCONN, f_isconn, "Transport endpoint is already connected") \
	XX(-EISDIR, f_isdir, "Is a directory") \
	XX(-EISNAM, f_isnam, "Is a named type file") \
	XX(-EKEYEXPIRED, f_keyexpired, "Key has expired") \
	XX(-EKEYREJECTED, f_keyrejected, "Key was rejected by service") \
	XX(-EKEYREVOKED, f_keyrevoked, "Key has been revoked") \
	XX(-EL2HLT, f_l2hlt, "Level 2 halted") \
	XX(-EL2NSYNC, f_l2nsync, "Level 2 not synchronized") \
	XX(-EL3HLT, f_l3hlt, "Level 3 halted") \
	XX(-EL3RST, f_l3rst, "Level 3 reset") \
	XX(-ELIBACC, f_libacc, "Can not access a needed shared library") \
	XX(-ELIBBAD, f_libbad, "Accessing a corrupted shared library") \
	XX(-ELIBEXEC, f_libexec, "Cannot exec a shared library directly") \
	XX(-ELIBMAX, f_libmax, "Attempting to link in too many shared libraries") \
	XX(-ELIBSCN, f_libscn, ".lib section in a.out corrupted") \
	XX(-ELNRNG, f_lnrng, "Link number out of range") \
	XX(-ELOOP, f_loop, "Too many levels of symbolic links") \
	XX(-EMEDIUMTYPE, f_mediumtype, "Wrong medium type") \
	XX(-EMFILE, f_mfile, "Too many open files") \
	XX(-EMLINK, f_mlink, "Too many links") \
	XX(-EMSGSIZE, f_msgsize, "Message too long") \
	XX(-EMULTIHOP, f_multihop, "Multihop attempted") \
	XX(-ENAMETOOLONG, f_nametoolong, "File name too long") \
	XX(-ENAVAIL, f_navail, "No XENIX semaphores available") \
	XX(-ENETDOWN, f_netdown, "Network is down") \
	XX(-ENETRESET, f_netreset, "Network dropped connection on reset") \
	XX(-ENETUNREACH, f_netunreach, "Network is unreachable") \
	XX(-ENFILE, f_nfile, "Too many open files in system") \
	XX(-ENOANO, f_noano, "No anode") \
	XX(-ENOBUFS, f_nobufs, "No buffer space available") \
	XX(-ENOCSI, f_nocsi, "No CSI structure available") \
	XX(-ENODATA, f_nodata, "No data available") \
	XX(-ENODEV, f_nodev, "No such device") \
	XX(-ENOENT, f_noent, "No such file or directory") \
	XX(-ENOEXEC, f_noexec, "Exec format error") \
	XX(-ENOKEY, f_nokey, "Required key not available") \
	XX(-ENOLCK, f_nolck, "No locks available") \
	XX(-ENOLINK, f_nolink, "Link has been severed") \
	XX(-ENOMEDIUM, f_nomedium, "No medium found") \
	XX(-ENOMEM, f_nomem, "Cannot allocate memory") \
	XX(-ENOMSG, f_nomsg, "No message of desired type") \
	XX(-ENONET, f_nonet, "Machine is not on the network") \
	XX(-ENOPKG, f_nopkg, "Package not installed") \
	XX(-ENOPROTOOPT, f_noprotoopt, "Protocol not available") \
	XX(-ENOSPC, f_nospc, "No space left on device") \
	XX(-ENOSR, f_nosr, "Out of streams resources") \
	XX(-ENOSTR, f_nostr, "Device not a stream") \
	XX(-ENOSYS, f_nosys, "Function not implemented") \
	XX(-ENOTBLK, f_notblk, "Block device required") \
	XX(-ENOTCONN, f_notconn, "Transport endpoint is not connected") \
	XX(-ENOTDIR, f_notdir, "Not a directory") \
	XX(-ENOTEMPTY, f_notempty, "Directory not empty") \
	XX(-ENOTNAM, f_notnam, "Not a XENIX named type file") \
	XX(-ENOTRECOVERABLE, f_notrecoverable, "State not recoverable") \
	XX(-ENOTSOCK, f_notsock, "Socket operation on non-socket") \
	XX(-ENOTSUP, f_notsup, "Operation not supported") \
	XX(-ENOTTY, f_notty, "Inappropriate ioctl for device") \
	XX(-ENOTUNIQ, f_notuniq, "Name not unique on network") \
	XX(-ENXIO, f_nxio, "No such device or address") \
	XX(-EOPNOTSUPP, f_opnotsupp, "Operation not supported") \
	XX(-EOVERFLOW, f_overflow, "Value too large for defined data type") \
	XX(-EOWNERDEAD, f_ownerdead, "Owner died") \
	XX(-EPERM, f_perm, "Operation not permitted") \
	XX(-EPFNOSUPPORT, f_pfnosupport, "Protocol family not supported") \
	XX(-EPIPE, f_pipe, "Broken pipe") \
	XX(-EPROTO, f_proto, "Protocol error") \
	XX(-EPROTONOSUPPORT, f_protonosupport, "Protocol not supported") \
	XX(-EPROTOTYPE, f_prototype, "Protocol wrong type for socket") \
	XX(-ERANGE, f_range, "Numerical result out of range") \
	XX(-EREMCHG, f_remchg, "Remote address changed") \
	XX(-EREMOTE, f_remote, "Object is remote") \
	XX(-EREMOTEIO, f_remoteio, "Remote I/O error") \
	XX(-ERESTART, f_restart, "Interrupted system call should be restarted") \
	XX(-ERFKILL, f_rfkill, "Operation not possible due to RF-kill") \
	XX(-EROFS, f_rofs, "Read-only file system") \
	XX(-ESHUTDOWN,  \
	   f_shutdown,  \
	   "Cannot send after transport endpoint shutdown") \
	XX(-ESOCKTNOSUPPORT, f_socktnosupport, "Socket type not supported") \
	XX(-ESPIPE, f_spipe, "Illegal seek") \
	XX(-ESRCH, f_srch, "No such process") \
	XX(-ESRMNT, f_srmnt, "Srmount error") \
	XX(-ESTALE, f_stale, "Stale NFS file handle") \
	XX(-ESTRPIPE, f_strpipe, "Streams pipe error") \
	XX(-ETIME, f_time, "Timer expired") \
	XX(-ETIMEDOUT, f_timedout, "Connection timed out") \
	XX(-ETOOMANYREFS, f_toomanyrefs, "Too many references: cannot splice") \
	XX(-ETXTBSY, f_txtbsy, "Text file busy") \
	XX(-EUCLEAN, f_uclean, "Structure needs cleaning") \
	XX(-EUNATCH, f_unatch, "Protocol driver not attached") \
	XX(-EUSERS, f_users, "Too many users") \
	XX(-EWOULDBLOCK, f_wouldblock, "Resource temporarily unavailable") \
	XX(-EXDEV, f_xdev, "Invalid cross-device link") \
	XX(-EXFULL, f_xfull, "Exchange full") \

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
ir_result_get_name(
	const ir_result_e result, char *buffer, const int buffer_size);
const char *
ir_result_get_description(
	const ir_result_e result, char *buffer, const int buffer_size);

#ifdef __cplusplus
}
#endif

#endif /* _IR_IR_IR_H_ */
