/*
  The oSIP library implements the Session Initiation Protocol (SIP -rfc2543-)
  Copyright (C) 2001  Aymeric MOIZARD jack@atosc.org
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdlib.h>
#include <stdio.h>

#include <osip/port.h>
#include <osip/smsg.h>
#include "msg.h"

int
msg_setallow (sip_t * sip, char *hvalue)
{
  allow_t *allow;
  int i;

  i = allow_init (&allow);
  if (i != 0)
    return -1;
  i = allow_parse (allow, hvalue);
  if (i != 0)
    {
      allow_free(allow);
      sfree(allow);
      return -1;
    }

#ifdef USE_TMP_BUFFER
  sip->message_property = 2;
#endif
  list_add (sip->allows, allow, -1);
  return 0;
}

int
msg_getallow (sip_t * sip, int pos, allow_t ** dest)
{
  allow_t *allow;

  *dest = NULL;
  if (list_size (sip->allows) <= pos)
    return -1;                  /* does not exist */
  allow = (allow_t *) list_get (sip->allows, pos);
  *dest = allow;
  return pos;
}
