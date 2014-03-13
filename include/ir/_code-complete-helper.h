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

/* Never include this header file. */

typedef enum {
 ir_result_s_false = 1, ir_result_s_ok = 0, ir_result_f_unknown = -9000, ir_result_f_no_interface = -9001, ir_result_f_2big = -7, ir_result_f_acces = -13, ir_result_f_addrinuse = -98, ir_result_f_addrnotavail = -99, ir_result_f_adv = -68, ir_result_f_afnosupport = -97, ir_result_f_again = -11, ir_result_f_already = -114, ir_result_f_bade = -52, ir_result_f_badf = -9, ir_result_f_badfd = -77, ir_result_f_badmsg = -74, ir_result_f_badr = -53, ir_result_f_badrqc = -56, ir_result_f_badslt = -57, ir_result_f_bfont = -59, ir_result_f_busy = -16, ir_result_f_canceled = -125, ir_result_f_child = -10, ir_result_f_chrng = -44, ir_result_f_comm = -70, ir_result_f_connaborted = -103, ir_result_f_connrefused = -111, ir_result_f_connreset = -104, ir_result_f_deadlk = -35, ir_result_f_deadlock = -35, ir_result_f_destaddrreq = -89, ir_result_f_dom = -33, ir_result_f_dotdot = -73, ir_result_f_dquot = -122, ir_result_f_exist = -17, ir_result_f_fault = -14, ir_result_f_fbig = -27, ir_result_f_hostdown = -112, ir_result_f_hostunreach = -113, ir_result_f_idrm = -43, ir_result_f_ilseq = -84, ir_result_f_inprogress = -115, ir_result_f_intr = -4, ir_result_f_inval = -22, ir_result_f_io = -5, ir_result_f_isconn = -106, ir_result_f_isdir = -21, ir_result_f_isnam = -120, ir_result_f_keyexpired = -127, ir_result_f_keyrejected = -129, ir_result_f_keyrevoked = -128, ir_result_f_l2hlt = -51, ir_result_f_l2nsync = -45, ir_result_f_l3hlt = -46, ir_result_f_l3rst = -47, ir_result_f_libacc = -79, ir_result_f_libbad = -80, ir_result_f_libexec = -83, ir_result_f_libmax = -82, ir_result_f_libscn = -81, ir_result_f_lnrng = -48, ir_result_f_loop = -40, ir_result_f_mediumtype = -124, ir_result_f_mfile = -24, ir_result_f_mlink = -31, ir_result_f_msgsize = -90, ir_result_f_multihop = -72, ir_result_f_nametoolong = -36, ir_result_f_navail = -119, ir_result_f_netdown = -100, ir_result_f_netreset = -102, ir_result_f_netunreach = -101, ir_result_f_nfile = -23, ir_result_f_noano = -55, ir_result_f_nobufs = -105, ir_result_f_nocsi = -50, ir_result_f_nodata = -61, ir_result_f_nodev = -19, ir_result_f_noent = -2, ir_result_f_noexec = -8, ir_result_f_nokey = -126, ir_result_f_nolck = -37, ir_result_f_nolink = -67, ir_result_f_nomedium = -123, ir_result_f_nomem = -12, ir_result_f_nomsg = -42, ir_result_f_nonet = -64, ir_result_f_nopkg = -65, ir_result_f_noprotoopt = -92, ir_result_f_nospc = -28, ir_result_f_nosr = -63, ir_result_f_nostr = -60, ir_result_f_nosys = -38, ir_result_f_notblk = -15, ir_result_f_notconn = -107, ir_result_f_notdir = -20, ir_result_f_notempty = -39, ir_result_f_notnam = -118, ir_result_f_notrecoverable = -131, ir_result_f_notsock = -88, ir_result_f_notsup = -95, ir_result_f_notty = -25, ir_result_f_notuniq = -76, ir_result_f_nxio = -6, ir_result_f_opnotsupp = -95, ir_result_f_overflow = -75, ir_result_f_ownerdead = -130, ir_result_f_perm = -1, ir_result_f_pfnosupport = -96, ir_result_f_pipe = -32, ir_result_f_proto = -71, ir_result_f_protonosupport = -93, ir_result_f_prototype = -91, ir_result_f_range = -34, ir_result_f_remchg = -78, ir_result_f_remote = -66, ir_result_f_remoteio = -121, ir_result_f_restart = -85, ir_result_f_rfkill = -132, ir_result_f_rofs = -30, ir_result_f_shutdown = -108, ir_result_f_socktnosupport = -94, ir_result_f_spipe = -29, ir_result_f_srch = -3, ir_result_f_srmnt = -69, ir_result_f_stale = -116, ir_result_f_strpipe = -86, ir_result_f_time = -62, ir_result_f_timedout = -110, ir_result_f_toomanyrefs = -109, ir_result_f_txtbsy = -26, ir_result_f_uclean = -117, ir_result_f_unatch = -49, ir_result_f_users = -87, ir_result_f_wouldblock = -11, ir_result_f_xdev = -18, ir_result_f_xfull = -54,
} ir_result_e;
