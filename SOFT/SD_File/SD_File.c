/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    SD_FILE.C
 *      Purpose: File manipulation example program
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2010 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <RTL.h>                      /* RTL kernel functions & defines      */
#include <stdio.h>                    /* standard I/O .h-file                */
#include <ctype.h>                    /* character functions                 */
#include <string.h>                   /* string and memory functions         */
#include "STM32_Init.h"               /* stm32 initialisation                */
#include "File_Config.h"
#include "SD_File.h"
//#include "LCD.h"

/* Command Functions */
static void cmd_capture (char *par);
static void cmd_type (char *par);
static void cmd_rename (char *par);
static void cmd_copy (char *par);
static void cmd_delete (char *par);
static void cmd_dir (char *par);
static void cmd_format (char *par);
static void cmd_help (char *par);
static void cmd_fill (char *par);

/* Local constants */
static const char intro[] =
  "\n\n\n\n\n\n\n\n"
  "+-----------------------------------------------------------------------+\n"
  "|                SD/MMC Card File Manipulation example                  |\n";
static const char help[] = 
  "+ command ------------------+ function ---------------------------------+\n"
  "| CAP \"fname\" [/A]          | captures serial data to a file            |\n"
  "|                           |  [/A option appends data to a file]       |\n"
  "| FILL \"fname\" [nnnn]       | create a file filled with text            |\n"
  "|                           |  [nnnn - number of lines, default=1000]   |\n"
  "| TYPE \"fname\"              | displays the content of a text file       |\n"
  "| REN \"fname1\" \"fname2\"     | renames a file 'fname1' to 'fname2'       |\n"
  "| COPY \"fin\" [\"fin2\"] \"fout\"| copies a file 'fin' to 'fout' file        |\n"
  "|                           |  ['fin2' option merges 'fin' and 'fin2']  |\n"
  "| DEL \"fname\"               | deletes a file                            |\n"
  "| DIR \"[mask]\"              | displays a list of files in the directory |\n"
  "| FORMAT [label [/FAT32]]   | formats Flash Memory Card                 |\n"
  "|                           | [/FAT32 option selects FAT32 file system] |\n"
  "| HELP  or  ?               | displays this help                        |\n"
  "+---------------------------+-------------------------------------------+\n";

static const SCMD cmd[] = {
  "CAP",    cmd_capture,
  "TYPE",   cmd_type,
  "REN",    cmd_rename,
  "COPY",   cmd_copy,
  "DEL",    cmd_delete,
  "DIR",    cmd_dir,
  "FORMAT", cmd_format,
  "HELP",   cmd_help,
  "FILL",   cmd_fill,
  "?",      cmd_help };

#define CMD_COUNT   (sizeof (cmd) / sizeof (cmd[0]))

/* Local variables */
static char in_line[160];

/* Local Function Prototypes */
static void init_display (void);
static void dot_format (U64 val, char *sp);
static char *get_entry (char *cp, char **pNext);
static void init_card (void);

/*----------------------------------------------------------------------------
 *        Initialize On Board LCD Module
 *---------------------------------------------------------------------------*/
static void init_display (void) {

}

/*----------------------------------------------------------------------------
 *        Process input string for long or short name entry
 *---------------------------------------------------------------------------*/
static char *get_entry (char *cp, char **pNext) {

}

/*----------------------------------------------------------------------------
 *        Print size in dotted fomat
 *---------------------------------------------------------------------------*/
static void dot_format (U64 val, char *sp) {

}

/*----------------------------------------------------------------------------
 *        Capture serial data to file
 *---------------------------------------------------------------------------*/
static void cmd_capture (char *par) {

}

/*----------------------------------------------------------------------------
 *        Create a file and fill it with some text
 *---------------------------------------------------------------------------*/
static void cmd_fill (char *par) {

}


/*----------------------------------------------------------------------------
 *        Read file and dump it to serial window
 *---------------------------------------------------------------------------*/
static void cmd_type (char *par) {

}

/*----------------------------------------------------------------------------
 *        Rename a File
 *---------------------------------------------------------------------------*/
static void cmd_rename (char *par) {

}

/*----------------------------------------------------------------------------
 *        Copy a File
 *---------------------------------------------------------------------------*/
static void cmd_copy (char *par) {

}

/*----------------------------------------------------------------------------
 *        Delete a File
 *---------------------------------------------------------------------------*/
static void cmd_delete (char *par) {

}

/*----------------------------------------------------------------------------
 *        Print a Flash Memory Card Directory
 *---------------------------------------------------------------------------*/
static void cmd_dir (char *par) {

}

/*----------------------------------------------------------------------------
 *        Format a Flash Memory Card
 *---------------------------------------------------------------------------*/
static void cmd_format (char *par) {

}

/*----------------------------------------------------------------------------
 *        Display Command Syntax help
 *---------------------------------------------------------------------------*/
static void cmd_help (char *par) {
  printf (help);
}

/*----------------------------------------------------------------------------
 *        Initialize a Flash Memory Card
 *---------------------------------------------------------------------------*/
static void init_card (void) {
  U32 retv;

  while ((retv = finit ()) != 0) {            /* Wait until the Card is ready*/
    if (retv == 1) {
      printf ("\nSD/MMC Init Failed");
      printf ("\nInsert Memory card and press key...\n");
      getkey ();
    }
    else {
      printf ("\nSD/MMC Card is Unformatted");
      strcpy (&in_line[0], "KEIL\r\n");
      cmd_format (&in_line[0]);
    }
  }
}

/*----------------------------------------------------------------------------
 *        Main: 
 *---------------------------------------------------------------------------*/
int main (void) {
  char *sp,*cp,*next;
  U32 i;

  stm32_Init();                               /* initialize the STM32        */
  init_display ();
  printf (intro);                             /* display example info        */
  printf (help);

  init_card ();
  while (1) {
    printf ("\nCmd> ");                       /* display prompt              */
    fflush (stdout);
                                              /* get command line input      */
    if (getline (in_line, sizeof (in_line)) == __FALSE) {
      continue;
    }

    sp = get_entry (&in_line[0], &next);
    if (*sp == 0) {
      continue;
    }
    for (cp = sp; *cp && *cp != ' '; cp++) {
      *cp = toupper (*cp);                    /* command to upper-case       */
    }
    for (i = 0; i < CMD_COUNT; i++) {
      if (strcmp (sp, (const char *)&cmd[i].val)) {
        continue;
      }
      init_card();                            /* check if card is removed    */
      cmd[i].func (next);                     /* execute command function    */
      break;
    }
    if (i == CMD_COUNT) {
      printf ("\nCommand error\n");
    }
  }
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
