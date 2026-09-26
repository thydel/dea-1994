/* 
 * main.c --
 *
 * Main to run the Tcl shell.  This file is a useful template for custom
 * applications that wish to have Tcl as the top level command language.
 *---------------------------------------------------------------------------
 * Copyright 1991 Karl Lehenbauer and Mark Diekhans.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies.  Karl Lehenbauer and
 * Mark Diekhans make no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without express or
 * implied warranty.
 */

#include "tclExtdInt.h"
#include "patchlevel.h"

#include "cmd.h"

extern errno;

/*
 * These globals are used by the infox command.
 */

extern char *tclxVersion;        /* Extended Tcl version number.            */
extern char *tclxPatchlevel;     /* Extended Tcl patch level.               */

extern char *tclAppName;         /* Application name                        */
extern char *tclAppLongname;     /* Long, natural language application name */
extern char *tclAppVersion;      /* Version number of the application       */

/*
 * If set to be a pointer to the procedure Tcl_RecordAndEval, will link in
 * history
 */
extern int (*tclShellCmdEvalProc) ();

int
main(argc, argv)
    int     argc;
    char  **argv;
{
    Tcl_Interp *interp;
    char       *defaultFile;


    /*
     * Set values to return from the infox command.
     */
    tclxVersion = ckalloc (strlen (TCL_VERSION) + 
                           strlen (TCL_EXTD_VERSION_SUFFIX) + 1);
    strcpy (tclxVersion, TCL_VERSION);
    strcat (tclxVersion, TCL_EXTD_VERSION_SUFFIX);

    tclxPatchlevel = "PATCHLEVEL";

    /*
     * Path name for default file.  A version number is normally appended.
     *        >>>> MAYBE MODIFIED FOR a specific application <<<
     */

    defaultFile = ckalloc (strlen (TCL_DEFAULT) + strlen (TCL_VERSION) +
                           strlen (TCL_EXTD_VERSION_SUFFIX) + 1);
    strcpy (defaultFile, TCL_DEFAULT);
    strcat (defaultFile, TCL_VERSION);
    strcat (defaultFile, TCL_EXTD_VERSION_SUFFIX);

    /*
     * Set application specific values to return from the infox command.
     *        >>>> MAYBE MODIFIED FOR a specific application <<<
     */
    tclAppName = "TclX";
    tclAppLongname = "Extended Tcl Shell";
    tclAppVersion = tclxVersion;

    /*
     * If history is to be used, then set the eval procedure pointer that
     * Tcl_CommandLoop so that history will be recorded.  This reference
     * also brings in history from Tcl.a.
     */
#ifndef TCL_NOHISTORY
     tclShellCmdEvalProc = Tcl_RecordAndEval;
#endif

    /* 
     * Create a Tcl interpreter for the session, with all extended commands
     * initialized.  This can be replaced with Tcl_CreateInterp followed
     * by a subset of the extended command initializaton procedures if 
     * desired.
     */
    interp = Tcl_CreateExtendedInterp();

    /*
     *   >>>>>> INITIALIZE APPLICATION SPECIFIC COMMANDS HERE <<<<<<
     */

    Tcl_CreateCommand(interp, "frame", cmd_frame, (ClientData) 0,
	    (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "frame_fill", cmd_frame_fill, (ClientData) 0,
	    (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "plane_extract", cmd_plane_extract, (ClientData) 0,
	    (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "plane", cmd_plane, (ClientData) 0,
	    (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "dump", cmd_dump, (ClientData) 0,
	    (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "dump_next", cmd_dump_next, (ClientData) 0,
	    (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "trans", cmd_trans, (ClientData) 0,
	    (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "trans_next", cmd_trans_next, (ClientData) 0,
	    (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand(interp, "trans_extract", cmd_trans_extract, (ClientData) 0,
	    (Tcl_CmdDeleteProc *) NULL);

    /*
     * Load the tcl startup code, this should pull in all of the tcl
     * procs, paths, command line processing, autoloads, packages, etc.
     * If Tcl was invoked interactively, Tcl_Startup will give it
     * a command loop .
     */

    Tcl_Startup (interp, argc, argv, defaultFile);

    /* 
     * Delete the interpreter (not neccessary under Unix, but we do
     * it if TCL_MEM_DEBUG is set to better enable us to catch memory
     * corruption problems)
     */

#ifdef TCL_MEM_DEBUG
    Tcl_DeleteInterp(interp);
    ckfree (defaultFile);
    ckfree (tclxVersion);
#endif

#ifdef TCL_SHELL_MEM_LEAK
    printf (" >>> Dumping active memory list to mem.lst <<<\n");
    if (Tcl_DumpActiveMemory ("mem.lst") != TCL_OK)
        panic ("error accessing `mem.lst': %s", strerror (errno));
#endif

    exit(0);
}

