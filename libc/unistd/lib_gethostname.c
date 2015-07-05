/****************************************************************************
 * libc/unistd/lib_gethostname.c
 *
 *   Copyright (C) 2015 Stavros Polymenis. All rights reserved.
 *   Author: Stavros Polymenis <sp@orbitalfox.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <string.h>
#include <unistd.h>
#include <unistd.h>

#include <arch/irq.h>

/* This file is only compiled if network support is enabled */

#ifdef CONFIG_NET

/* Further, in the protected and kernel build modes where kernel and
 * application code are separated, the hostname is a common system property
 * and must reside only in the kernel.  In that case, these accessor
 * functions call only be called from user space is only via kernel system
 * calls.
 */

#if (!defined(CONFIG_BUILD_PROTECTED) && !defined(CONFIG_BUILD_KERNEL)) || \
      defined(__KERNEL__)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* The default host name is a system configuration setting.  This may be
 * changed via sethostname(), however.
 */

#ifndef CONFIG_NET_HOSTNAME
#  define CONFIG_NET_HOSTNAME ""
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* This is the system hostname */

static char g_hostname[HOST_NAME_MAX + 1] = CONFIG_NET_HOSTNAME;

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: gethostname
 *
 * Description:
 *   The gethostname() function will return the standard host name for the
 *   current machine. The namelen argument will specify the size of the
 *   array pointed to by the name argument. The returned name will be null-
 *   terminated, except that if namelen is an insufficient length to hold the
 *   host name, then the returned name will be truncated and it is
 *   unspecified whether the returned name is null-terminated.
 *
 *   Host names are limited to {HOST_NAME_MAX} bytes.
 *
 * Input Parameters:
 *   name - The user-provided buffer to receive the host name.
 *   namelen - The size of the user provided buffer in bytes.
 *
 * Returned Value:
 *   Upon successful completion, 0 will be returned; otherwise, -1 will be
 *   returned.  No errors are defined;  errno variable is not set.
 *
 ****************************************************************************/

int gethostname(FAR char *name, size_t namelen)
{
  irqstate_t flags;

  /* Return the host name, truncating to fit into the user provided buffer.
   * The hostname is global resource.  There is a microscopic possibility
   * that it could change while we are copying it.
   */

  flags = irqsave();
  strncpy(name, g_hostname, namelen);
  irqrestore(flags);

  return 0;
}

/****************************************************************************
 * Name: sethostname
 *
 * Description:
 *
 *   sethostname() sets the hostname to the value given in the character
 *   array name. The len argument specifies the number of bytes in name.
 *   (Thus, name does not require a terminating null byte.)
 *
 * Conforming To
 *   SVr4, 4.4BSD (these interfaces first appeared in 4.2BSD). POSIX.1-2001
 *   specifies gethostname() but not sethostname().
 *
 * Input Parameters:
 *   name - The user buffer to providing the new host name.
 *   namelen - The size of the user buffer in bytes.
 *
 * Returned Value:
 *   Upon successful completion, 0 will be returned; otherwise, -1 will be
 *   returned.  No errors are defined;  errno variable is not set.
 *
 ****************************************************************************/

int sethostname(FAR const char *name, size_t size)
{
  irqstate_t flags;

  /* Save the new host name, truncating to HOST_NAME_MAX if necessary.  This
   * internal copy is always NUL terminated  .The hostname is global resource.
   * There is a microscopic possibility that it could be accessed while we
   * are setting it.
   */

  flags = irqsave();
  strncpy(g_hostname, name, MIN(HOST_NAME_MAX, size));
  g_hostname[HOST_NAME_MAX] = '\0';
  irqrestore(flags);

  return 0;
}

#endif /* CONFIG_NET */
#endif /* (!CONFIG_BUILD_PROTECTED && !CONFIG_BUILD_KERNEL) || __KERNEL__ */