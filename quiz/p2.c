/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *    This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* int verify_password (const char *); */

int main (void)
{
  int verified = 0;
  char user_key[10];

  /* Read user's credentials. */

  printf ("Enter password: ");
  scanf ("%s", user_key);

  /* Verify credentials. */

  verified = strcmp(user_key, "foo");

  if (!verified)
    {
      printf ("Access granted\n");
      exit (1);
    }

  printf ("Access denied.\n");

  /* Priviledged code follows... */

  return 0;
}


