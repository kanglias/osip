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
msg_setaccept_language (sip_t * sip, char *hvalue)
{
  accept_language_t *accept_language;
  int i;

  i = accept_language_init (&accept_language);
  if (i != 0)
    return -1;
  i = accept_language_parse (accept_language, hvalue);
  if (i != 0)
    {
      accept_language_free(accept_language);
      sfree(accept_language);
      return -1;
    }

#ifdef USE_TMP_BUFFER
  sip->message_property = 2;
#endif
  list_add (sip->accept_languages, accept_language, -1);
  return 0;
}

int
msg_getaccept_language (sip_t * sip, int pos, accept_language_t ** dest)
{
  accept_language_t *accept_language;

  *dest = NULL;
  if (list_size (sip->accept_languages) <= pos)
    return -1;                  /* does not exist */
  accept_language = (accept_language_t *) list_get (sip->accept_languages, pos);
  *dest = accept_language;
  return pos;
}
