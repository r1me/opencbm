/*
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 *
 *  Copyright 2004 Spiro Trikaliotis
*/

/*! ************************************************************** 
** \file sys/vdd/dll/cbmfile.c \n
** \author Spiro Trikaliotis \n
** \version $Id: cbmfile.c,v 1.1 2004-12-22 14:43:22 strik Exp $ \n
** \n
** \brief Function for handling the CBM_FILE to BX conversions
**
****************************************************************/

#include <windows.h>

/*! Mark: We are in user-space (for debug.h) */
#define DBG_USERMODE

/*! Mark: We are building the DLL */
#define DBG_DLL

/*! The name of the executable */
#define DBG_PROGNAME "OPENCBMVDD.DLL"

#include "debug.h"

#include "vdd.h"

#include <stdlib.h>


#define MAX_CBMFILE_VALUES 10

static CBM_FILE CbmFile[MAX_CBMFILE_VALUES];
static BOOL CbmfileValuesInitialized = FALSE;

static void
init_cbmfiles(void)
{
    if (!CbmfileValuesInitialized)
    {
        int i;

        for (i = 0; i < MAX_CBMFILE_VALUES; i++)
        {
            CbmFile[i] = INVALID_HANDLE_VALUE;
        }

        CbmfileValuesInitialized = TRUE;
    }
}

CBM_FILE vdd_cbmfile_get(WORD a)
{
    CBM_FILE ret;

    init_cbmfiles();

    if (a < MAX_CBMFILE_VALUES)
    {
        ret = CbmFile[a];
    }
    else
    {
        ret = INVALID_HANDLE_VALUE;
    }

    return ret;
}

WORD vdd_cbmfile_store(CBM_FILE cbmfile)
{
    WORD i;

    init_cbmfiles();

    i = 0;

    while (i < MAX_CBMFILE_VALUES && CbmFile[i] != INVALID_HANDLE_VALUE)
    {
        i++;
    }

    if (i < MAX_CBMFILE_VALUES && CbmFile[i] == INVALID_HANDLE_VALUE)
    {
        CbmFile[i] = cbmfile; 
    }
    else
    {
        i = -1;
    }

    return i;
}

CBM_FILE vdd_cbmfile_delete(WORD a)
{
    CBM_FILE cbmfile;

    init_cbmfiles();

    if (CbmFile[a] != INVALID_HANDLE_VALUE)
    {
        cbmfile = CbmFile[a];
        CbmFile[a] = INVALID_HANDLE_VALUE;
    }
    else
    {
        cbmfile = INVALID_HANDLE_VALUE;
    }

    return cbmfile;
}
