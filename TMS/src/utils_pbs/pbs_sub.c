
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <grp.h>

#ifdef sun
#include <sys/stream.h>
#endif /* sun */

#if defined(HAVE_SYS_IOCTL_H)
#include <sys/ioctl.h>
#endif /* HAVE_SYS_IOCTL_H */

#if defined(HAVE_SYS_TTY_H)
#include <sys/tty.h>
#endif

#if defined(FD_SET_IN_SYS_SELECT_H)
#  include <sys/select.h>
#endif

#include "cmds.h"
#include "net_connect.h"
#include "log.h"
#include "port_forwarding.h"
#include "csv.h"
#include "pbs_server_config.h"

#include "pbs_sub.h"

/* DefaultFilterPath is used to fall back on in order to maintain backwards compatibility.
   the new preferred path for the submit filter is ${libexecdir}/pbs_submit_filter */

/* NOTE:  submitfilter specified using SUBMITFILTER in $TORQUEHOME/torque.cfg */

static char *DefaultFilterPath = "/usr/local/sbin/pbs_submit_filter";

static char *DefaultXauthPath = "/usr/bin/xauth";

#define SUBMIT_FILTER_ADMIN_REJECT_CODE -1

#define MAX_QSUB_PREFIX_LEN 32

#define MAX_PROCS_DIGITS  15 /* A 15 digit number is a lot of processors. 100 trillion 
                                     will this be enough for the future? */

static char PBS_DPREFIX_DEFAULT[] = "#PBS";

#define MAX_ERROR_MSG_SIZE 1024

char PBS_ERROR_MSG[MAX_ERROR_MSG_SIZE];
char tmp_err_msg[256];
char PBS_Filter[256];
char PBS_InitDir[256];
char PBS_RootDir[256];
char PBS_WorkDir[256];

char xauth_path[256];
char default_ckpt[256];

int validate_path = 1;
int rerunnable_by_default = 1;
int fault_tolerant_by_default = 0;
int interactivechild = 0;
int x11child = 0;

int do_dir(char *);
int parse_file(int, char **, int);
int have_terminal = TRUE;

char *checkpoint_strings = "n,c,s,u,none,shutdown,periodic,enabled,interval,depth,dir";


/* initializes PBS_ERROR_MSG*/
void initialize_pbs_error_msg(char PBS_ERROR_MSG[]) {
  int i=0;
  for(; i < MAX_ERROR_MSG_SIZE; i++) {
    PBS_ERROR_MSG[i] = '\0';
  } 
}

/* adapted from openssh */

static char *x11_get_proto(

  char *EMsg)  /* O (optional,minsize=1024) */

  {
  char line[512];
  char proto[512], data[512], screen[512];
  char *authstring;
  FILE *f;
  int  got_data = 0;
  char *display, *p;

  struct stat st;

  proto[0]  = '\0';
  data[0]   = '\0';
  screen[0] = '\0';

  if (EMsg != NULL)
    EMsg[0] = '\0';

  if ((display = getenv("DISPLAY")) == NULL)
    {
    sprintf(PBS_ERROR_MSG, "pbs_submit: DISPLAY not set\n");

    return(NULL);
    }

  if (stat(xauth_path, &st))
    {
    perror("pbs_submit: xauth: ");

    return(NULL);
    }

  /* Try to get Xauthority information for the display. */

  if (strncmp(display, "localhost:", 10) == 0)
    {
    /*
     * Handle FamilyLocal case where $DISPLAY does
     * not match an authorization entry.  For this we
     * just try "xauth list unix:displaynum.screennum".
     * XXX: "localhost" match to determine FamilyLocal
     *      is not perfect.
     */

    snprintf(line, sizeof(line), "%s list unix:%s 2>/dev/null",
             xauth_path,
             display + 10);
    }
  else
    {
    snprintf(line, sizeof(line), "%s list %.200s 2>/dev/null",
             xauth_path,
             display);
    }

  p = strchr(display, ':');

  if (p != NULL)
    p = strchr(p, '.');

  if (p != NULL)
    strncpy(screen, p + 1, sizeof(screen));
  else
    strcpy(screen, "0");

  if (getenv("PBSDEBUG") != NULL)
    sprintf(PBS_ERROR_MSG, "x11_get_proto: %s\n",
            line);

  f = popen(line, "r");

  if (f == NULL)
    {
    sprintf(PBS_ERROR_MSG, "execution of '%s' failed, errno=%d (%s)\n",
            line,
            errno,
            pbse_to_txt(errno));
    }
  else if (fgets(line, sizeof(line), f) == 0)
    {
    sprintf(PBS_ERROR_MSG, "cannot read data from '%s', errno=%d (%s)\n",
            line,
            errno,
            pbse_to_txt(errno));
    }
  else if (sscanf(line, "%*s %511s %511s",
                  proto,
                  data) != 2)
    {
    sprintf(PBS_ERROR_MSG, "cannot parse output from '%s'\n",
            line);
    }
  else
    {
    /* SUCCESS */

    got_data = 1;
    }

  if (f != NULL)
    pclose(f);

#if 0 /* we aren't inspecting the returned xauth data yet */
  /*
   * If we didn't get authentication data, just make up some
   * data.  The forwarding code will check the validity of the
   * response anyway, and substitute this data.  The X11
   * server, however, will ignore this fake data and use
   * whatever authentication mechanisms it was using otherwise
   * for the local connection.
   */
  if (!got_data)
    {
    u_int32_t _rand = 0;
    int i;

    sprintf(PBS_ERROR_MSG, "Warning: No xauth data; using fake authentication data for X11 forwarding.\n");
    strncpy(proto, "MIT-MAGIC-COOKIE-1", sizeof proto);

    for (i = 0; i < 16; i++)
      {
      if (i % 4 == 0)
        _rand = rand();

      snprintf(data + 2 * i, sizeof data - 2 * i, "%02x", _rand & 0xff);

      _rand >>= 8;
      }
    }

#endif

  if (!got_data)
    {
    /* FAILURE */

    return(NULL);
    }

  authstring = malloc(strlen(proto) + strlen(data) + strlen(screen) + 4);

  if (authstring == NULL)
    {
    /* FAILURE */

    return(NULL);
    }

  sprintf(authstring, "%s:%s:%s",
    proto,
    data,
    screen);

  return(authstring);
  }  /* END x11_get_proto() */




char *smart_strtok(

  char  *line,          /* I */
  char  *delims,        /* I */
  char **ptrPtr,        /* O */
  int    ign_backslash) /* I */

  {
  char *head = NULL;
  char *start = NULL;

  int dindex;
  int ignchar;
  int ignore;

  int sq_count = 0;
  int dq_count = 0;
  int sb_count = 0;

  char *tmpLine = NULL;
  int   tmpLineSize;
  int   tindex;

  char *ptr;

  if (line != NULL)
    {
    *ptrPtr = line;
    }
  else if (ptrPtr == NULL)
    {
    /* FAILURE */

    return(head);
    }

  start = *ptrPtr;

  tmpLineSize = (line == NULL) ? strlen(*ptrPtr + 1) : strlen(line) + 1;
  tmpLine = (char *)malloc(tmpLineSize * sizeof(char));

  tmpLine[0] = '\0';

  tindex = 0;

  ignchar = FALSE;

  ptr = *ptrPtr;

  while (*ptr != '\0')
    {
    if (*ptr == '\'')
      {
      sq_count++;

      if ((head != NULL) && !(sq_count % 2) && !(dq_count % 2))
        {
        ptr++;

        ignchar = TRUE;
        }
      else 
        {
        ignore = TRUE;

        if (ign_backslash == TRUE)
          {
          /* check if backslash precedes delimiter */

          if ((ptr > start) && (*(ptr-1) == '\\'))
            {
            /* check if backslash is backslashed */

            if ((ptr > start + 1) && (*(ptr-2) != '\\'))
              {
              /* delimiter is backslashed, ignore */

              ignore = FALSE;
              
              sq_count--;
              }
            }
          }

        if (ignore == TRUE)
          {
          ptr++;

          ignchar = TRUE;
          }
        }
      }
    else if (*ptr == '\"')
      {
      dq_count++;

      if ((head != NULL) && !(sq_count % 2) && !(dq_count % 2))
        {
        ptr++;

        ignchar = TRUE;
        }
      else 
        {
        ignore = TRUE;

        if (ign_backslash == TRUE)
          {
          /* check if backslash precedes delimiter */

          if ((ptr > start) && (*(ptr-1) == '\\'))
            {
            /* check if backslash is backslashed */

            if ((ptr > start + 1) && (*(ptr-2) != '\\'))
              {
              /* delimiter is backslashed, ignore */

              ignore = FALSE;
              
              dq_count--;
              }
            }
          }

        if (ignore == TRUE)
          {
          ptr++;

          ignchar = TRUE;
          }
        }
      }
    else if (*ptr == '[' )
      {
      sb_count = 1;
      }
    else if (*ptr == ']')
      {
      sb_count = 0;
      }
    else if (*ptr == '{')
      {
      sb_count = 1;
      }
    else if (*ptr == '}')
      {
      sb_count = 0;
      }
    else if (!(sq_count % 2) && !(dq_count % 2) && (sb_count == 0))
      {
      /* not in quotations, locate delimiter */

      for (dindex = 0; delims[dindex] != '\0'; dindex++)
        {
        if (*ptr != delims[dindex])
          continue;

        if ((ign_backslash == TRUE) && (head != NULL))
          {
          /* check if backslash precedes delimiter */
          if ((ptr > head) && (*(ptr-1) == '\\'))
            {
            /* check if backslash is backslashed */

            if ((ptr > head + 1) && (*(ptr-1) != '\\'))
              {
              /* delimiter is backslashed, ignore */

              continue;
              }
            }
          }

        /* delimiter found */

        *ptr = '\0';
        
        ptr++;
        
        if (head != NULL)
          {
          *ptrPtr = ptr;

          tmpLine[tindex] = '\0';
          
          if (tindex > 0)
            strcpy(head,tmpLine);
          
          free(tmpLine);

          return(head);
          }

        ignchar = TRUE;

        break;
        } /* END for (dindex) */
      }

    if ((ignchar != TRUE) && (*ptr != '\0'))
      {
      if (head == NULL)
        head = ptr;

      tmpLine[tindex++] = ptr[0];

      ptr++;
      }

    ignchar = FALSE;
    } /* END while (*ptr != '\0') */

  tmpLine[tindex] = '\0';

  if (tindex > 0)
    strcpy(head,tmpLine);

  free(tmpLine);

  *ptrPtr = ptr;

  return(head);
  } /* END smart_strtok */





int get_name_value(start, name, value)
char  *start;
char **name;
char **value;
  {
  static char *tok_ptr;
  char *curr_ptr;
  char *equals;

  /* we've reached the end */
  if ((start == NULL) &&
      (*tok_ptr == '\0'))
    return(0);

  curr_ptr = smart_strtok(start,",",&tok_ptr,FALSE);

  if ((curr_ptr == NULL))
    return(0);
     
  if ((*curr_ptr == '=') || 
      (*curr_ptr == '\0'))
    {
    /* no name, fail */
    return(-1);
    }

  /* skip leading spaces */
  while (isspace((int)*curr_ptr) && (*curr_ptr))
    curr_ptr++;

  *name = curr_ptr;

  equals = *name;

  /* skip over name */
  while ((*equals) && (!isspace((int)*equals)) && (*equals != '='))
    equals++;

  /* strip blanks */
  while ((*equals) && (isspace((int)*equals)))
    *equals++ = '\0';

  if (*equals != '=')
    return (-1); /* should have found a = as first non blank */

  *equals++ = '\0';

  /* skip leading white space */
  while (isspace((int)*equals) && *equals)
    equals++;

  if (*equals == '\0')
    return(-1);

  *value = equals;

  return (1);
  }






char *set_dir_prefix(

  char *prefix,
  int   diropt)

  {
  char *s;

  if (notNULL(prefix))
    {
    return(prefix);
    }

  if (diropt == TRUE)
    {
    return("");
    }

  if ((s = getenv("PBS_DPREFIX")) != NULL)
    {
    return(s);
    }

  return(PBS_DPREFIX_DEFAULT);
  }  /* END set_dir_prefix() */





int isexecutable(

  char *s)  /* I */

  {
  char *c;

  c = s;

  if ((*c == ':') || ((*c == '#') && (*(c + 1) == '!')))
    {
    return(FALSE);
    }

  while (isspace(*c))
    c++;

  if (notNULL(c))
    {
    return(*c != '#');
    }

  return(FALSE);
  }




char *ispbsdir(

  char *s,
  char *prefix)

  {
  char *it;
  int l;

  it = s;

  while (isspace(*it)) it++;

  l = strlen(prefix);

  if ((l > 0) && (strncmp(it, prefix, l) == 0))
    {
    return(it + l);
    }

  return((char *)NULL);
  }



#define MMAX_VERIFY_BYTES 50

int istext(

  FILE   *fd,      /* I */
  int    *IsText)  /* O (optional) */

  {
  int i;
  int c;

  if (IsText != NULL)
    *IsText = FALSE;

  if (fd == NULL)
    {
    return(0);
    }

  if (fd == stdin)
    {
    return(1);
    }

  /* read first characters to ensure this is ASCII text */

  for (i = 0;i < MMAX_VERIFY_BYTES;i++)
    {
    c = fgetc(fd);

    if (c == EOF)
      break;

    if (!isprint(c) && !isspace(c))
      {
      fseek(fd, 0, SEEK_SET);

      return(0);
      }
    }  /* END for (i) */

  if (IsText != NULL)
    *IsText = TRUE;

  fseek(fd, 0, SEEK_SET);

  return(1);
  }  /* END FileIsText() */




/* return 3, 4, 5, 6, -1 on FAILURE, 0 on success */

int get_script(

  int    ArgC,    /* I */
  char **ArgV,    /* I */
  FILE  *file,    /* I */
  char  *script,  /* O (minsize=X) */
  char  *prefix)  /* I */

  {
  char  s[MAX_LINE_LEN + 1];
  char *sopt;
  int   exec = FALSE;
  char *cont = NULL;
  char  tmp_name[] = "/tmp/pbs_submit.XXXXXX";
  FILE *TMP_FILE;
  char *in;
  int   tmpfd;

  int   index;

  /* START WRAPPER */

  char cfilter[MAXPATHLEN + 1024];

  char tmp_name2[] = "/tmp/pbs_submit.XXXXXX";

  struct stat  sfilter;
  FILE        *filesaved;
  FILE        *filter_pipe;
  int          rc;

  /* if the submitfilter exists, run it.                               */

  /* check that the file is text */

  if (istext(file, NULL) == 0)
    {
    sprintf(PBS_ERROR_MSG,
            "pbs_submit:  file must be an ascii script\n");

    return(4);
    }

  if (stat(PBS_Filter, &sfilter) != -1)
    {
    /* run the copy through the submit filter. */

    if ((tmpfd = mkstemp(tmp_name2)) < 0)
      {
      sprintf(PBS_ERROR_MSG,
              "pbs_submit: could not create filter o/p %s\n",
              tmp_name2);

      return(4);
      }

    close(tmpfd);

    strcpy(cfilter, PBS_Filter);

    for (index = 1;index < ArgC;index++)
      {
      if (ArgV[index] != NULL)
        {
        strcat(cfilter, " ");

        strcat(cfilter, ArgV[index]);
        }
      }    /* END for (index) */

    strcat(cfilter, " >");

    strcat(cfilter, tmp_name2);

    filter_pipe = popen(cfilter, "w");

    while ((in = fgets(s, MAX_LINE_LEN, file)) != NULL)
      {
      if (fputs(in, filter_pipe) < 0)
        {
        sprintf(PBS_ERROR_MSG, "pbs_submit: error writing to filter stdin\n");

        unlink(tmp_name2);

        return(3);
        }
      }

    rc = pclose(filter_pipe);

    if (WEXITSTATUS(rc) == (unsigned char)SUBMIT_FILTER_ADMIN_REJECT_CODE)
      {
      sprintf(PBS_ERROR_MSG, "pbs_submit: Your job has been administratively rejected by the queueing system.\n");
      strcat(PBS_ERROR_MSG, "pbs_submit: There may be a more detailed explanation prior to this notice.\n");

      unlink(tmp_name2);

      return(3);
      }

    if (WEXITSTATUS(rc))
      {
      sprintf(PBS_ERROR_MSG, "pbs_submit: submit filter returned an error code, aborting job submission.\n");

      unlink(tmp_name2);

      return(3);
      }

    /* get rid of the i/p copy. */

    /* preserve the original pointer. */

    filesaved = file;

    /* open the filtered script. */

    if ((file = fopen(tmp_name2, "r")) == NULL)
      {
      sprintf(PBS_ERROR_MSG, "pbs_submit: could not open filter o/p %s\n",
              tmp_name2);

      unlink(tmp_name2);

      file = filesaved;

      return(3);
      }

    /* Get rid of the filtered o/p; data remains accessible until    */
    /* file is closed.                                               */

    unlink(tmp_name2);

    /* Complete redirection.                                         */

    fclose(filesaved);
    }  /* END if (stat(PBS_Filter,&sfilter) != -1) */

  /* END WRAPPER */

  if ((tmpfd = mkstemp(tmp_name)) < 0)
    {
    sprintf(PBS_ERROR_MSG, "pbs_submit: could not create copy of script %s\n",
            tmp_name);

    return(4);
    }

  if ((TMP_FILE = fdopen(tmpfd, "w+")) == NULL)
    {
    sprintf(PBS_ERROR_MSG, "pbs_submit: could not create copy of script %s\n",
            tmp_name);
    
    unlink(tmp_name);

    return(4);
    }

  while ((in = fgets(s, MAX_LINE_LEN, file)) != NULL)
    {
    int len;

    /* replace DOS EOL ('^M') characters */

    len = strlen(in);

    if ((len >= 2) && (in[len - 2] == '\r') && (in[len - 1] == '\n'))
      {
      in[len - 2] = '\n';
      in[len - 1] = '\0';
      }

    if (!exec && ((sopt = ispbsdir(s, prefix)) != NULL))
      {
      while ((*(cont = in + strlen(in) - 2) == '\\') && (*(cont + 1) == '\n'))
        {
        /* next line is continuation of this line */

        *cont = '\0';  /* clear newline from our copy */

        if (fputs(in, TMP_FILE) < 0)
          {
          sprintf(PBS_ERROR_MSG, "pbs_submit: error writing copy of script, %s\n",
                  tmp_name);

          fclose(TMP_FILE);

          unlink(tmp_name);

          return(3);
          }

        in = cont;

        if ((in = fgets(in, MAX_LINE_LEN - (in - s), file)) == NULL)
          {
          sprintf(PBS_ERROR_MSG, "pbs_submit: unexpected end-of-file or read error in script\n");

          fclose(TMP_FILE);

          unlink(tmp_name);

          return(6);
          }
        }    /* END while ((*(cont = in + strlen(in) - 2) == '\\') && (*(cont + 1) == '\n')) */

      if (do_dir(sopt) != 0)
        {
        return(-1);
        }
      }      /* END if (!exec && ((sopt = ispbsdir(s,prefix)) != NULL)) */
    else if (!exec && isexecutable(s))
      {
      exec = TRUE;
      }

    if (fputs(in, TMP_FILE) < 0)
      {
      sprintf(PBS_ERROR_MSG, "pbs_submit: error writing copy of script, %s\n",
              tmp_name);

      fclose(TMP_FILE);

      unlink(tmp_name);

      return(3);
      }
    }   /* END while ((in = fgets(s,MAX_LINE_LEN,file)) != NULL) */

  fclose(TMP_FILE);

  if (ferror(file))
    {
    sprintf(PBS_ERROR_MSG, "pbs_submit: error reading script file\n");

    return(5);
    }

  strcpy(script, tmp_name);
  
  return 0;
  }  /* END get_script() */





int make_argv(

  int  *argc,
  char *argv[],
  char *line)

  {
  char *l, *b, *c, *buffer;
  int len;
  char quote;

  buffer = malloc(strlen(line) + 1);

  if (buffer == NULL)
    {
    sprintf(PBS_ERROR_MSG, "pbs_submit: out of memory\n");
    return 2; //old code : exit(2);
    }

  *argc = 0;

  argv[(*argc)++] = "pbs_submit";

  l = line;
  b = buffer;

  while (isspace(*l))
    l++;

  c = l;

  while (*c != '\0')
    {
    if ((*c == '"') || (*c == '\''))
      {
      quote = *c;
      c++;

      while ((*c != quote) && *c)
        *b++ = *c++;

      if (*c == '\0')
        {
        sprintf(PBS_ERROR_MSG, "pbs_submit: unmatched %c\n",
                *c);

        return 1 ;//old code : exit(1);
        }

      c++;
      }
    else if (*c == '\\')
      {
      c++;

      *b++ = *c++;
      }
    else if (isspace(*c))
      {
      len = c - l;

      assert(len > 0);

      if (argv[*argc] != NULL)
        free(argv[*argc]);

      argv[*argc] = (char *)malloc(len + 1);

      if (argv[*argc] == NULL)
        {
        sprintf(PBS_ERROR_MSG, "pbs_submit: out of memory\n");

        return 2; //odl code : exit(2);
        }

      *b = '\0';

      strcpy(argv[(*argc)++], buffer);

      while (isspace(*c))
        c++;

      l = c;

      b = buffer;
      }
    else
      {
      *b++ = *c++;
      }
    }

  if (c != l)
    {
    len = c - l;

    assert(len > 0);

    if (argv[*argc] != NULL)
      free(argv[*argc]);

    argv[*argc] = (char *) malloc(len + 1);

    if (argv[*argc] == NULL)
      {
      sprintf(PBS_ERROR_MSG, "pbs_submit: out of memory\n");
      return 2; //old exit(2);
      }

    *b = '\0';

    strcpy(argv[(*argc)++], buffer);
    }

  free(buffer);

  return 0;
  }  /* END make_argv() */




int do_dir(

  char *opts)

  {
  static int opt_pass = 1;
  int argc;

#define MAX_ARGV_LEN 128
  static char *vect[MAX_ARGV_LEN + 1];

  if (opt_pass == 1)
    {
    argc = 0;

    while (argc < MAX_ARGV_LEN + 1)
      vect[argc++] = NULL;
    }

  int res = make_argv(&argc, vect, opts);
  if(res) {
    return res; 
  };

  return(parse_file(argc, vect, opt_pass++));
  }  /* END do_dir() */



/* globals */


struct termios oldtio;

struct attrl *attrib = NULL;
char *new_jobname;                  /* return from submit request */
char dir_prefix[MAX_QSUB_PREFIX_LEN + 1];
char path_out[MAXPATHLEN + 1];
char destination[PBS_MAXDEST];
static char server_out[PBS_MAXSERVERNAME + PBS_MAXPORTNUM + 2];
char server_host[PBS_MAXHOSTNAME + 1];
char pbs_submit_host[PBS_MAXHOSTNAME + 1];
char  owner_uid[MAXPATHLEN + 1];

long cnt2server_retry = -100;

/* state booleans for protecting already-set options */
int a_opt = FALSE;
int b_opt = FALSE;
int c_opt = FALSE;
int e_opt = FALSE;
int f_opt = FALSE;
int h_opt = FALSE;
int j_opt = FALSE;
int k_opt = FALSE;
int l_opt = FALSE;
int m_opt = FALSE;
int o_opt = FALSE;
int p_opt = FALSE;
int q_opt = FALSE;
int r_opt = FALSE;
int t_opt = FALSE;
int T_opt = FALSE;
int u_opt = FALSE;
int v_opt = FALSE;
int z_opt = FALSE;
int A_opt = FALSE;
int C_opt = FALSE;
int F_opt = FALSE;
int M_opt = FALSE;
int N_opt = FALSE;
int S_opt = FALSE;
int V_opt = FALSE;
int Depend_opt    = FALSE;
int Run_Inter_opt = FALSE;
int Stagein_opt   = FALSE;
int Stageout_opt  = FALSE;
int Grouplist_opt = FALSE;
int Forwardx11_opt = FALSE;
int Umask_opt = FALSE;
char *v_value = NULL;


char *copy_env_value(

  char *dest,      /* destination  */
  char *pv,        /* value string */
  int   quote_flg) /* non-zero then assume single word (quoting on) */

  {
  int go = 1;
  int q_ch = 0;

  while (*dest)
    ++dest;

  while (go && *pv)
    {
    switch (*pv)
      {

      case '"':

      case '\'':

        if (q_ch)
          {
          /* local quoting is in progress */

          if (q_ch == (int)*pv)
            {
            q_ch = 0;  /* end quote */
            }
          else
            {
            *dest++ = '\\'; /* escape quote */
            *dest++ = *pv;
            }
          }
        else if (quote_flg)
          {
          /* global quoting is on */

          *dest++ = '\\';  /* escape quote */
          *dest++ = *pv;
          }
        else
          {
          q_ch = (int) * pv;  /* turn local quoting on */
          }

        break;

      case '\\':

        *dest++ = '\\';  /* escape back-slash */
        *dest++ = *pv;

        break;

      case '\n':

        *dest++ = '\\';  /* escape newline */
        *dest++ = *pv;

        break;

      case ',':

        if (q_ch || quote_flg)
          {
          *dest++ = '\\';
          *dest++ = *pv;
          }
        else
          {
          go = 0;  /* end of value string */
          }

        break;

      default:

        *dest++ = *pv;

        break;
      }

    pv++;
    }  /* END while (go && *pv) */

  *dest = '\0';

  if (q_ch)
    return(NULL); /* error-unterminated quote */

  return(pv);
  }




int set_job_env(

  char **envp)  /* I */

  {
  char **evp;
  char *job_env;
  char *s, *c, *env, l;
  unsigned   len;
  int   rc = 0;

  int   eindex;

  const char *EList[] =
    {
    "HOME",
    "LANG",
    "LOGNAME",
    "MAIL",
    "PATH",
    "SHELL",
    "TZ",
    NULL
    };

  /* Calculate how big to make the variable string. */

  len = PBS_MAXHOSTNAME * 2 + MAXPATHLEN;

  if (v_opt)
    {
    len += strlen(v_value);
    }

  if (V_opt)
    {
    evp = envp;

    while (notNULL(*evp))
      {
      /* add 1 for ',' */
      len += strlen(*evp) + 1;

      evp++;
      }
    }

  for (eindex = 0;EList[eindex] != NULL;eindex++)
    {
    env = getenv(EList[eindex]);

    if (env == NULL)
      continue;

    /* prepend 'PBS_O_' to each var and add '2' for ',' and '=' */

    len += strlen(env) + strlen(EList[eindex]) + strlen("PBS_O_") + 2;
    }  /* END for (eindex) */

  if (PBS_InitDir[0] != '\0')
    {
    len += strlen("PBS_O_INITDIR=") + strlen(PBS_InitDir) + 1;
    }

  if (PBS_RootDir[0] != '\0')
    {
    len += strlen("PBS_O_ROOTDIR=") + strlen(PBS_RootDir) + 1;
    }

  if (PBS_WorkDir[0] != '\0')
    {
    len += strlen("PBS_O_WORKDIR=") + strlen(PBS_WorkDir) + 1;
    }

  len += strlen("PBS_SERVER=") + 1;

  len++; /* Terminating '0' */

  if ((job_env = (char *)malloc(len)) == NULL)
    {
    return(FALSE);
    }

  *job_env = '\0';

  /* Send the required variables with the job. */

  c = getenv("HOME");

  strcat(job_env, "PBS_O_HOME=");

  if (c != NULL)
    strcat(job_env, c);
  else
    strcat(job_env, "/");

  c = getenv("LANG");

  if (c != NULL)
    {
    strcat(job_env, ",PBS_O_LANG=");
    strcat(job_env, c);
    }

  c = getenv("LOGNAME");

  if (c != NULL)
    {
    strcat(job_env, ",PBS_O_LOGNAME=");
    strcat(job_env, c);
    }

  c = getenv("PATH");

  if (c != NULL)
    {
    strcat(job_env, ",PBS_O_PATH=");
    strcat(job_env, c);
    }

  c = getenv("MAIL");

  if (c != NULL)
    {
    strcat(job_env, ",PBS_O_MAIL=");
    strcat(job_env, c);
    }

  c = getenv("SHELL");

  if (c != NULL)
    {
    strcat(job_env, ",PBS_O_SHELL=");
    strcat(job_env, c);
    }

  c = getenv("TZ");

  if (c != NULL)
    {
    strcat(job_env, ",PBS_O_TZ=");
    strcat(job_env, c);
    }

  if (pbs_submit_host[0] != '\0' ||
     (rc = gethostname(pbs_submit_host, PBS_MAXHOSTNAME + 1)) == 0)
    {
    if ((rc = get_fullhostname(pbs_submit_host, pbs_submit_host, PBS_MAXHOSTNAME, NULL)) == 0)
      {
      strcat(job_env, ",PBS_O_HOST=");
      strcat(job_env, pbs_submit_host);
      }   
    }
    
  if (rc != 0)
    {
    sprintf(PBS_ERROR_MSG, "pbs_submit: cannot get (full) local host name\n");
    return 3;//exit(3);
    }
    
  if (server_host[0] != '\0')
    {
    if (get_fullhostname(server_host, server_host, PBS_MAXHOSTNAME, NULL) == 0)
      {
      strcat(job_env,",PBS_SERVER=");
      strcat(job_env,server_host);
      }
    else
      {
      sprintf(PBS_ERROR_MSG,"pbs_submit: cannot get full server host name\n");
      return 3; //exit(3);
      }
    }
  else
    {
    c = pbs_default();
    if (*c != '\0')
      {
      strncpy(server_host, c, sizeof(server_host));
      strcat(job_env,",PBS_SERVER=");
      strcat(job_env,server_host);
      }
    else
      {
      strcat(job_env,",PBS_SERVER=");
      strcat(job_env,pbs_submit_host);
      }
    }

  if (owner_uid[0] != '\0')
    {
    strcat(job_env, ",PBS_O_UID=");
    strcat(job_env, owner_uid);
    }

  /* load init dir into env if specified */

  if (PBS_InitDir[0] != '\0')
    {
    /* load init dir into env */

    strcat(job_env, ",PBS_O_INITDIR=");

    strcat(job_env, PBS_InitDir);
    }

  if (PBS_RootDir[0] != '\0')
    {
    /* load init dir into env */

    strcat(job_env, ",PBS_O_ROOTDIR=");

    strcat(job_env, PBS_RootDir);
    }

  /* get current working directory, use $PWD if available, it is more */
  /* NFS automounter "friendly".  But must double check that is right */

  /* load work dir into env if specified */

  if (PBS_WorkDir[0] != '\0')
    {
    /* load work dir into env */

    strcat(job_env, ",PBS_O_WORKDIR=");

    strcat(job_env, PBS_WorkDir);
    }
  else
    {
    s = job_env + strlen(job_env);

    strcat(job_env, ",PBS_O_WORKDIR=");

    c = getenv("PWD");

    if (c != NULL)
      {

      struct stat statbuf;
      dev_t dev;
      ino_t ino;

      if (stat(c, &statbuf) < 0)
        {
        c = NULL; /* cannot stat, cannot trust it */
        }
      else
        {
        dev = statbuf.st_dev;
        ino = statbuf.st_ino;

        if (stat(".", &statbuf) < 0)
          {
          /* compare against "." */

          perror("pbs_submit: cannot stat current directory: ");
          return 3; //old: exit(3);

          }

        if (!memcmp(&dev, &statbuf.st_dev, sizeof(dev_t)) &&
            !memcmp(&ino, &statbuf.st_ino, sizeof(ino_t)))
          {
          strcat(job_env, c);
          }
        else
          {
          c = NULL;
          }
        }
      }    /* END if (c != NULL) */

    if (c == NULL)
      {
      /* fall back to using the cwd */
      c = job_env + strlen(job_env);

      if (getcwd(c, MAXPATHLEN + 1) == NULL)
        *s = '\0';
      }
    }

  /* Send these variables with the job. */
  /* POSIX requirement: If a variable is given without a value, supply the
     value from the environment. */

  /* MY requirement:    There can be no white space in -v value. */

  if (v_opt)
    {
    c = v_value;

state1:         /* goto label : Initial state comes here */

    switch (*c)
      {

      case ',':

      case '=':

        return FALSE;

        /*NOTREACHED*/

        break;

      case '\0':

        goto final;

        /*NOTRREACHED*/

        break;
      }

    s = c;

    /* pass through to next case */

state2:         /* goto label : Variable name */

    switch (*c)
      {

      case ',':

      case '\0':

        goto state3;

        /*NOTREACHED*/

        break;

      case '=':
        /* if we just have the '=' and no value after it then we look in
         the environment same as if the '=' was not there */

        if ((c[1] == ',') || (c[1] == '\0'))
          {
          *c = '\0';
          c++;
          goto state3;

          /*NOTREACHED*/
          }

        goto state4;

        /*NOTREACHED*/

        break;

      default:

        c++;

        goto state2;

        /*NOTREACHED*/

        break;
      }  /* END switch (*c) */

state3:         /* No value - get it from pbs_submit environment */

    l = *c;

    *c = '\0';

    env = getenv(s);

    if (env == NULL)
      {
      env = "";
      }

    if (strlen(job_env) + 2 + strlen(s) + 2*strlen(env) >= len)
      {
      /* increase size of job env buffer */

      len += 2 * strlen(env) + 1;

      job_env = (char *)realloc(job_env, len);

      if (job_env == NULL)
        {
          free(job_env); 
          return(FALSE);
        }
      }

    strcat(job_env, ",");

    strcat(job_env, s);
    strcat(job_env, "=");

    if (copy_env_value(job_env, env, 1) == NULL)
      {
      return(FALSE);
      }

    if (l == ',')
      c++;

    goto state1;

state4:         /* goto label - Value specified */

    *c++ = '\0';

    if (strlen(job_env) + 2 + strlen(s) + 2*strlen(c) >= len)
      {
      /* increase size of job env buffer */

      len += 2 * strlen(c) + 1;

      job_env = (char *)realloc(job_env, len);

      if (job_env == NULL)
        {
         free(job_env);
        return(FALSE);
        }
      }

    strcat(job_env, ",");

    strcat(job_env, s);
    strcat(job_env, "=");

    if ((c = copy_env_value(job_env, c, 0)) == NULL)
      {
      return(FALSE);
      }

    goto state1;
    }  /* END if (v_opt) */

final:

  if (V_opt != 0)
    {
    /* Send every environment variable with the job. */

    evp = envp;

    while (notNULL(*evp))
      {
      s = *evp;

      while ((*s != '=') && *s)
        ++s;

      if (!*s)
        {
        evp++;

        continue;
        }

      *s = '\0';  /* NOTE: *s is clobbering our current, real, environ */

      if (strlen(job_env) + 2 + strlen(*evp) + 2*strlen(s + 1) >= len)
        {
        /* increase size of job env buffer */

        len += 2 * strlen(s + 1) + 1;

        job_env = (char *)realloc(job_env, len);

        /*if (job_env == NULL)
          {
          *s = '='; // restore our existing environ 

          return(FALSE);
          }*/
        }

      strcat(job_env, ",");

      strcat(job_env, *evp);
      strcat(job_env, "=");

      copy_env_value(job_env, s + 1, 1);

      *s = '='; /* restore our existing environ */

      evp++;
      }
    }    /* END if (V_opt) */

  set_attr(&attrib, ATTR_v, job_env);

  free(job_env);

  return(TRUE);
  }  /* END set_job_env() */


/** 
 * Process command line options.
 *
 * @see main() - parent
 *
 * NOTE:  return 0 on success 
 * NOTE:  only run submitfilter if pass < 10 
 */ 

int parse_file(

  int    argc,  /* I */
  char **argv,  /* I */
  int    pass)  /* I */

  {
  int i;
  int c;
  int errflg = 0;
  int passet;
  time_t after;
  char a_value[80];
  char *keyword;
  char *valuewd;
  char *pc;
  char *pdepend;

  char tmpLine[1024];

  char *ptr;

  struct stat sfilter;

  int nitems;
  char search_string[256];

#if !defined(PBS_NO_POSIX_VIOLATION)
#define GETOPT_ARGS "a:A:b:c:C:d:D:e:fhj:k:l:m:M:N:o:p:P:q:r:S:t:T:u:v:Vw:W:Xxz:"
#else
#define GETOPT_ARGS "a:A:c:C:e:hj:k:l:m:M:N:o:p:q:r:S:u:v:VW:z"
#endif /* PBS_NO_POSIX_VIOLATION */

  /* The following macro, together the value of passet (pass + 1) is used */
  /* to enforce the following rules: 1. option on the command line take */
  /* precedence over those in script directives.   2. With in the command */
  /* line or within the script, the last occurance of an option takes */
  /* precedence over the earlier occurance.    */

#define if_cmd_line(x) if ((pass == 0) || (x != 1))

  passet = pass + 1;

  if (pass > 0)
    {
#ifdef linux
    optind = 0;  /* prime getopt's starting point */
#else
    optind = 1;  /* prime getopt's starting point */
#endif
    }
  
  while ((c = getopt(argc, argv, GETOPT_ARGS)) != EOF)
    {
    
    switch (c)
      {
      case 'a':

        if_cmd_line(a_opt)
          {
          a_opt = passet;

          if ((after = cvtdate(optarg)) < 0)
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -a value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          sprintf(a_value, "%ld",

                  (long)after);

          set_attr(&attrib, ATTR_a, a_value);
          }

        break;

      case 'A':

        if_cmd_line(A_opt)
          {
          A_opt = passet;

          set_attr(&attrib, ATTR_A, optarg);
          }

        break;

      case 'b':

        if_cmd_line(b_opt)
          {
          b_opt = passet;

          cnt2server_retry = atoi(optarg);
          }

        break;

      case 'c': //TODO: to check pbs version in this case
 
      #if 0
        if_cmd_line(c_opt)
          {
          c_opt = passet;

          /* remove whitespace */

          while (isspace((int)*optarg))
            optarg++;

          if (strlen(optarg) == 0)
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -c value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          pc = optarg;

          /* OLD FORMAT:  -c { n | s | c | c=X }
           * New format: -c [ { <old format items> | <new items> } ',' ]
           * new items: none | shutdown | checkpoint | name=xyz | dir=xyz | interval=X
           */
#if 0 

          if (strlen(optarg) == 1)
          {
            if ((*pc != 'n') && (*pc != 's') && (*pc != 'c'))
            {
              fprintf(stderr, "qsub: illegal -c value\n");
              
              errflg++;

              break;
            }
          }
          else
          {
            if (strncmp(optarg, "c=", 2) != 0)
            {
              fprintf(stderr, "qsub: illegal -c value\n");
              errflg++;

              break;
            }

            pc += 2;

            if (*pc == '\0')
            {
              fprintf(stderr, "qsub: illegal -c value\n");

              errflg++;

              break;
            }
            while (isdigit(*pc))
              pc++;

            if (*pc != '\0')
            {
              fprintf(stderr, "qsub: illegal -c value\n");
              errflg++;

              break;
            }
          }

#else
          nitems = csv_length(optarg);

          for (i = 0; i < nitems; i++)
            {
            if ((ptr = csv_nth(optarg, i)) != NULL)
              {
              strcpy(search_string, ptr);
              ptr = strchr(search_string, '=');

              if (ptr)
                *ptr = 0;
              else
                ptr = &search_string[strlen(search_string)];

              while (ptr > search_string && *(ptr - 1) == ' ')
                *--ptr = 0;

              if (csv_find_string(checkpoint_strings, search_string) == NULL)
                {
                sprintf(tmp_err_msg, "pbs_submit: illegal -c value \"%s\"\n", ptr);
                strcat(PBS_ERROR_MSG, tmp_err_msg);
                errflg++;
                goto err;
                }
              }
            }

#endif
          set_attr(&attrib, ATTR_c, optarg);
          }  /* END if_cmd_line() */
#endif
        break;

      case 'C':

        if_cmd_line(C_opt)
          {
          C_opt = passet;

          strcpy(dir_prefix, optarg);
          }

        break;

      case 'd':

        if (optarg != NULL)
          {
          if (optarg[0] != '/')
            {
            /* make '-d' relative to current directory, not $HOME */

            char tmpPWD[1024];

            char *mypwd;

            mypwd = getcwd(tmpPWD, sizeof(tmpPWD));

            if (mypwd == NULL)
              {
              sprintf(tmp_err_msg, "pbs_submit: unable to get cwd: %d (%s)\n",
                      errno,
                      strerror(errno));
              strcat(PBS_ERROR_MSG, tmp_err_msg);
              errflg++;

              /* we don't want to return yet, but we also don't want a segfault either */

              /* NOTE:  if cwd cannot be resolved, set errflag which will cause exit later */

              tmpPWD[0] = '\0';

              mypwd = tmpPWD;
              }

            if ((strlen(mypwd) + strlen(optarg)) >= sizeof(PBS_InitDir))
              {
              sprintf(tmp_err_msg, "pbs_submit: -d arg is longer than %ld characters\n",
                      (long)sizeof(PBS_InitDir));
              strcat(PBS_ERROR_MSG, tmp_err_msg);
              errflg++;
              }

            snprintf(PBS_InitDir, sizeof(PBS_InitDir), "%s/%s",

                     mypwd,
                     optarg);
            }  /* END if (optarg[0] != '/') */
          else
            {
            if (strlen(optarg) >= sizeof(PBS_InitDir))
              {
              sprintf(tmp_err_msg, "pbs_submit: -d arg is longer than %ld characters\n",
                      (long)sizeof(PBS_InitDir));
              strcat(PBS_ERROR_MSG, tmp_err_msg);
              errflg++;
              }

            strncpy(PBS_InitDir, optarg, sizeof(PBS_InitDir));
            } /* end optarg[1] != '/' */

          if (validate_path != 0)
            {
            /* validate local existence of '-d' working directory */
            if (chdir(PBS_InitDir) == -1)
              {
                sprintf(tmp_err_msg, "pbs_submit: cannot chdir to '%s' errno: %d (%s)\n",
                      optarg,
                      errno,
                      strerror(errno));
                strcat(PBS_ERROR_MSG, tmp_err_msg);
              errflg++;
              }
            }
          }    /* END if (optarg != NULL) */
        else
          {
          sprintf(tmp_err_msg, "pbs_submit: illegal -d value\n");
          strcat(PBS_ERROR_MSG, tmp_err_msg);
          errflg++;
          }

        break;

      case 'D':

        if (optarg != NULL)
          {
          strncpy(PBS_RootDir, optarg, sizeof(PBS_RootDir));
          }
        else
          {
          sprintf(tmp_err_msg, "pbs_submit: illegal -D value\n");
          strcat(PBS_ERROR_MSG, tmp_err_msg);
          errflg++;
          }

        break;

      case 'e':

        if_cmd_line(e_opt)
          {
          int rc = 0;
          e_opt = passet;

          if (pbs_submit_host[0] != '\0')
            rc = prepare_path(optarg,path_out,pbs_submit_host);
          else
            rc = prepare_path(optarg,path_out,NULL);

          if ((rc == 0) || (rc == 3))
            {
            set_attr(&attrib, ATTR_e, path_out);
            }
          else
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -e value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;
            }
          }
        break;
        
#if !defined(PBS_NO_POSIX_VIOLATION)
      
      case 'f': //TODO: to check pbs version in this case
     
        #if 0 
          if_cmd_line(f_opt)
          {
          f_opt = passet;
          
          set_attr(&attrib, ATTR_f, "TRUE");
          }
        #endif

        break;
      
#endif

      case 'h':

        if_cmd_line(h_opt)
          {
          h_opt = passet;

          set_attr(&attrib, ATTR_h, "u");
          }

        break;

      case 'j':

        /* FORMAT:  {oe|eo|n} */

        if_cmd_line(j_opt)
          {
          j_opt = passet;

          if (strcmp(optarg, "oe") != 0 &&
              strcmp(optarg, "eo") != 0 &&
              strcmp(optarg, "n") != 0)
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -j value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          set_attr(&attrib, ATTR_j, optarg);
          }

        break;

      case 'k':

        /* FORMAT:  {o|e} */

        if_cmd_line(k_opt)
          {
          k_opt = passet;

          if (strcmp(optarg, "o") != 0 &&
              strcmp(optarg, "e") != 0 &&
              strcmp(optarg, "oe") != 0 &&
              strcmp(optarg, "eo") != 0 &&
              strcmp(optarg, "n") != 0)
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -k value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          set_attr(&attrib, ATTR_k, optarg);
          }

        break;

      case 'l':

        l_opt = passet;

        /* a ,procs= in the node spec is illegal. Validate the node spec */
        if(strstr(optarg, ",procs="))
          {
          printf("illegal node spec: %s\n", optarg);
          return(-1);
          }

          /* Normal evaluation of batch job resources. */
          if(attrib)
            {
            if(attrib->resource)
              {
              /* right here we are looking for a +procs=x in the node spec */
              char *proc_ptr = NULL;
              char *patch_ptr;
              /* struct attrl *proc_attrib = NULL; */
              char  proc_val[MAX_PROCS_DIGITS + 1]; 
              int i = 0;

              proc_val[0] = 0; /* Initialize */

              proc_ptr = strstr(attrib->value, "procs=");
              if(proc_ptr)
                {
                /* we have the procs keyword in the node_spec. We need to take it out and
                   install it to the Resource_List */
                patch_ptr = proc_ptr;
                /* Get the procs value */
                patch_ptr = strchr(patch_ptr, '=');
                if(patch_ptr == NULL)
                  {
                  return(-1);
                  }
                else
                  {
                  patch_ptr++;
                  while(*patch_ptr != '+' && !isspace((int) *patch_ptr) && *patch_ptr != '\0'
                        && i < MAX_PROCS_DIGITS)
                    {
                    proc_val[i++] = *patch_ptr++;
                    }
                  proc_val[i] = 0;

                  /* we have a procs=x in our node spec. Add the resources */
                  sprintf(tmpLine, "procs=%s", proc_val);
                  if (set_resources(&attrib, tmpLine, (pass == 0)) != 0)
                    {                                                                  
                    sprintf(tmp_err_msg, "pbs_submit: illegal -l value\n");
                    strcat(PBS_ERROR_MSG, tmp_err_msg);
                    errflg++;
                    }
                  }

                while(*patch_ptr != '+' && !isspace((int) *patch_ptr) && *patch_ptr != '\0')
                  {
                  patch_ptr++;
                  }

                /* remove the procs=x from the node spec.
                   If patch_ptr has a '+' then the procs=x
                   is followed by more specificaitons. Remove
                   the procs=x from the spec and splice the rest
                   of the specification back together
                 */
                if(*patch_ptr == '+')
                  {
                  
                  patch_ptr++;
                  *proc_ptr = 0;
                  strcat(attrib->value, patch_ptr);
                  }
                else
                  {
                  /* Remove the procs=x from the node spec.
                     If we are here procs=x is at the end
                     of the node specification
                   */
                  if(*(proc_ptr - 1)  == '+')
                    {
                    proc_ptr--;
                    }
                  *proc_ptr = 0;
                  }
                } /* END if(proc_ptr)*/
              } /* END if(attrib->resource ) */
            } /* END if(attrib) */

          if (set_resources(&attrib, optarg, (pass == 0)) != 0)
            {                                                                  
            sprintf(tmp_err_msg, "pbs_submit: illegal -l value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg); 
            errflg++;
            }


          if (strstr(optarg, "walltime") != NULL)
            {

            struct attrl *attr;
            char   *ptr;

            /* if walltime range specified, break into minwclimit and walltime resources */

            for (attr = attrib;attr != NULL;attr = attr->next)
              {
              if (!strcmp(attr->name, "walltime"))
                {
                if ((ptr = strchr(attr->value, '-')))
                  {

                  *ptr = '\0';

                  ptr++;

                  /* set minwclimit to min walltime range value */

                  snprintf(tmpLine, sizeof(tmpLine), "minwclimit=%s",
                           attr->value);

                  if (set_resources(&attrib, tmpLine, (pass == 0)) != 0)
                    {
                    sprintf(tmp_err_msg, "pbs_submit: illegal -l value\n");
                    strcat(PBS_ERROR_MSG, tmp_err_msg);
                    errflg++;
                    }

                  /* set walltime to max walltime range value */

                  strcpy(tmpLine, ptr);

                  strcpy(attr->value, tmpLine);
                  }

                break;
                }
              }  /* END for (attr) */
            }

        break;

      case 'm':

        if_cmd_line(m_opt)
          {
          /* FORMAT: {a|b|e|n} */

          m_opt = passet;

          while (isspace((int)*optarg))
            optarg++;

          if (strlen(optarg) == 0)
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -m value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          if (strcmp(optarg, "n") != 0)
            {
            pc = optarg;

            while (*pc)
              {
              if ((*pc != 'a') && (*pc != 'b') && (*pc != 'e'))
                {
                sprintf(tmp_err_msg, "pbs_submit: illegal -m value\n");
                strcat(PBS_ERROR_MSG, tmp_err_msg);
                errflg++;

                break;
                }

              pc++;
              }
            }    /* END if (strcmp(optarg,"n") != 0) */

          set_attr(&attrib, ATTR_m, optarg);
          }

        break;

      case 'M':

        if_cmd_line(M_opt)
          {
          M_opt = passet;

          if (parse_at_list(optarg, FALSE, FALSE))
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -M value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          set_attr(&attrib, ATTR_M, optarg);
          }

        break;

      case 'N':
        
        if_cmd_line(N_opt)
          {
          N_opt = passet;
          
          /* NOTE:  did enforce alpha start previously - relax this constraint
                    allowing numeric job names (CRI - 6/26/07) */
          
          if (check_job_name(optarg, 0) == 0)
            {
            set_attr(&attrib, ATTR_N, optarg);
            }
          else
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -N value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;
            }
          }

        break;

      case 'o':

        if_cmd_line(o_opt)
          {
          int rc = 0;
          o_opt = passet;

          if (pbs_submit_host[0] != '\0')
            rc = prepare_path(optarg,path_out,pbs_submit_host);
          else
            rc = prepare_path(optarg,path_out,NULL);

          if ((rc == 0) || (rc == 3))
            {
            set_attr(&attrib, ATTR_o, path_out);
            }
          else
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -o value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;
            }
          }

        break;

      case 'p':

        if_cmd_line(p_opt)
          {
          p_opt = passet;

          while (isspace((int)*optarg))
            optarg++;

          pc = optarg;

          if ((*pc == '-') || (*pc == '+'))
            pc++;

          if (strlen(pc) == 0)
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -p value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          while (*pc != '\0')
            {
            if (!isdigit(*pc))
              {
              sprintf(tmp_err_msg, "pbs_submit: illegal -p value\n");
              strcat(PBS_ERROR_MSG, tmp_err_msg);
              errflg++;

              break;
              }

            pc++;
            }

          i = atoi(optarg);

          if ((i < -1024) || (i > 1023))
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -p value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          set_attr(&attrib, ATTR_p, optarg);
          }

        break;

#if !defined(PBS_NO_POSIX_VIOLATION)

      case 'P': //TODO: to check pbs version in this case
       #if 0
        if (strlen(optarg) > 0)
          {
          char *user;
          char *group;
          char *colon;

          // make sure this is the super user *
          if (geteuid() != (uid_t)0)
            {
            sprintf(tmp_err_msg, "pbs_submit: Must be the super user to submit a proxy job\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;
            }
          user = optarg;
          colon = strchr(user,':');

          if (colon != NULL)
            {
            group = colon+1;
            *colon = '\0';
            set_attr(&attrib, ATTR_g, group);
            }

          set_attr(&attrib, ATTR_P, user);
          }
        else
          {
          sprintf(tmp_err_msg, "pbs_submit: -P requires a user name\n");
          strcat(PBS_ERROR_MSG, tmp_err_msg);
          errflg++;
          }
    #endif 
        break;

#endif /* PBS_NO_POSIX_VIOLATION */

      case 'q':

        if_cmd_line(q_opt)
          {
          q_opt = passet;

          strcpy(destination, optarg);
          }

        break;

      case 'r':

        if_cmd_line(r_opt)
          {
          r_opt = passet;

          if (strlen(optarg) != 1)
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -r value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          if ((*optarg != 'y') && (*optarg != 'n'))
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -r value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          set_attr(&attrib, ATTR_r, optarg);
          }

        break;

      case 'S':

        if_cmd_line(S_opt)
          {
          S_opt = passet;

          if (parse_at_list(optarg, TRUE, TRUE))
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -S value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          set_attr(&attrib, ATTR_S, optarg);
          }

        break;

#if !defined(PBS_NO_POSIX_VIOLATION)

      case 't':

        if_cmd_line(t_opt)
          {
          t_opt = passet;
#if 0
          /* validate before sending request to server? */
          set_attr(&attrib, ATTR_t, optarg);
#endif
          }

        break;

      case 'T':

        if_cmd_line(T_opt)
          {
          T_opt = passet;

          /* validate before sending request to server? */
#if 0
          set_attr(&attrib,ATTR_jobtype,optarg);
#endif
          }

        break;

#endif

      case 'u':

        if_cmd_line(u_opt)
          {
          u_opt = passet;

          if (parse_at_list(optarg, TRUE, FALSE))
            {
            sprintf(tmp_err_msg, "pbs_submit: illegal -u value\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          set_attr(&attrib, ATTR_u, optarg);
          }

        break;

      case 'v':

        if_cmd_line(v_opt)
          {
          v_opt = passet;

          if (v_value != NULL)
            free(v_value);

          v_value = (char *)malloc(strlen(optarg) + 1);

          if (v_value == NULL)
            {
            sprintf(tmp_err_msg, "pbs_submit: out of memory\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;

            break;
            }

          strcpy(v_value, optarg);
          }

        break;

      case 'V':

        if_cmd_line(V_opt)
          {
          V_opt = passet;
          }

        break;

      case 'w':

        if (optarg != NULL)
          {
          strncpy(PBS_WorkDir, optarg, sizeof(PBS_WorkDir));
          }
        else
          {
          sprintf(tmp_err_msg, "pbs_submit: illegal -w value\n");
          strcat(PBS_ERROR_MSG, tmp_err_msg);
          errflg++;
          }

        break;

      case 'W':

        while (isspace((int)*optarg))
          optarg++;

        if (strlen(optarg) == 0)
          {
          /* value is empty */

          sprintf(tmp_err_msg, "pbs_submit: illegal -W value\n");
          strcat(PBS_ERROR_MSG, tmp_err_msg);
          errflg++;

          break;
          }

        i = get_name_value(optarg, &keyword, &valuewd);

        if (i != 1)
          {
          char tmpLine[65536];

          /* assume resource manager extension */

          snprintf(tmpLine, sizeof(tmpLine), "x=%s",
                   optarg);

          i = get_name_value(tmpLine, &keyword, &valuewd);
          }

        while (i == 1)
          {
          if (!strcmp(keyword, ATTR_depend))
            {
            if_cmd_line(Depend_opt)
              {
              int rtn = 0;
              Depend_opt = passet;

              pdepend = malloc(PBS_DEPEND_LEN);

              if ((pdepend == NULL) ||
                   (rtn = parse_depend_list(valuewd,pdepend,PBS_DEPEND_LEN)))
                {
                /* cannot parse 'depend' value */

                if (rtn == 2)
                  {
                  sprintf(tmp_err_msg,"pbs_submit: -W value exceeded max length (%d)\n",
                    PBS_DEPEND_LEN);
                  strcat(PBS_ERROR_MSG, tmp_err_msg);
                  }
                else
                  {
                  sprintf(tmp_err_msg,"pbs_submit: illegal -W value\n");
                  strcat(PBS_ERROR_MSG, tmp_err_msg);
                  }

                errflg++;

                break;
                }

              set_attr(&attrib, ATTR_depend, pdepend);
              }
            }
          else if (!strcmp(keyword, ATTR_stagein))
            {
            if_cmd_line(Stagein_opt)
              {
              Stagein_opt = passet;

              if (parse_stage_list(valuewd))
                {
                /* cannot parse 'stagein' value */

                sprintf(tmp_err_msg, "pbs_submit: illegal -W value\n");
                strcat(PBS_ERROR_MSG, tmp_err_msg);
                errflg++;

                break;
                }

              set_attr(&attrib, ATTR_stagein, valuewd);
              }
            }
          else if (!strcmp(keyword, ATTR_stageout))
            {
            if_cmd_line(Stageout_opt)
              {
              Stageout_opt = passet;

              if (parse_stage_list(valuewd))
                {
                /* cannot parse 'stageout' value */

                sprintf(tmp_err_msg, "pbs_submit: illegal -W value\n");
                strcat(PBS_ERROR_MSG, tmp_err_msg);
                errflg++;

                break;
                }

              set_attr(&attrib, ATTR_stageout, valuewd);
              }
            }
#if 0
          else if (!strcmp(keyword, ATTR_t))
            {
            if_cmd_line(t_opt)
              {
              t_opt = passet;

              set_attr(&attrib, ATTR_t, valuewd);
              }
            }
#endif
          else if (!strcmp(keyword, ATTR_g))
            {
            if_cmd_line(Grouplist_opt)
              {
              Grouplist_opt = passet;

              if (parse_at_list(valuewd, TRUE, FALSE))
                {
                /* cannot parse 'grouplist' value */

                sprintf(tmp_err_msg, "pbs_submit: illegal -W value\n");
                strcat(PBS_ERROR_MSG, tmp_err_msg);
                errflg++;

                break;
                }

              set_attr(&attrib, ATTR_g, valuewd);
              }
            }
          else if (!strcmp(keyword, ATTR_umask))
            {
            int len;
            len = strlen(valuewd);
            if (valuewd[0] == '0')
              --len;

            if (len > 3)
              {
              sprintf(tmp_err_msg, "Invalid umask value, too many digits: %s\n", 
                      valuewd); 
              strcat(PBS_ERROR_MSG, tmp_err_msg);
              errflg++;
             
              break;
              } 

            Umask_opt = passet;
            if (valuewd[0] == '0')
              {
              /* value is octal, convert to decimal */
              long mask;
              char buf[4];

              mask = strtol(valuewd, NULL, 8);
              snprintf(buf, 4, "%ld", mask); 

              /* value is octal, convert to decimal */
              set_attr(&attrib,ATTR_umask,buf); 
              }
            else
              {
              set_attr(&attrib,ATTR_umask,valuewd);
              }
            }
#if 0
          else if (!strcmp(keyword, ATTR_f)) //TODO: to check pbs version in this case
            {
            
            switch (valuewd[0])
              {
            
              /* accept 1, TRUE,true,YES,yes, 0, FALSE, false, NO, no */
              case 1:
              case 'T':
              case 't':
              case 'Y':
              case 'y':
                f_opt = passet;
                set_attr(&attrib, ATTR_f, "TRUE");
                break;
                
              case 0:
              case 'F':
              case 'f':
              case 'N':
              case 'n':
                f_opt = passet;
                set_attr(&attrib, ATTR_f, "FALSE");
                break;
              
              default:
                sprintf(tmp_err_msg, "invalid %s value: %s\n", ATTR_f, valuewd);
                strcat(PBS_ERROR_MSG, tmp_err_msg);
                errflg++;
              }
              
            }
#endif
          else
            {
            /* generic job attribute specified */

            set_attr(&attrib, keyword, valuewd);
            }

          i = get_name_value(NULL, &keyword, &valuewd);
          }  /* END while (i == 1) */

        if (i == -1)
          {
          sprintf(tmp_err_msg, "pbs_submit: illegal -W value\n");
          strcat(PBS_ERROR_MSG, tmp_err_msg);
          errflg++;
          }

        break;

#if !defined(PBS_NO_POSIX_VIOLATION)

      case 'X':

        if_cmd_line(Forwardx11_opt)
          {
          Forwardx11_opt = passet;

          if (!getenv("DISPLAY"))
            {
            sprintf(tmp_err_msg, "pbs_submit: DISPLAY not set\n");
            strcat(PBS_ERROR_MSG, tmp_err_msg);
            errflg++;
            }
          }

        break;

      case 'x':

        if_cmd_line(Run_Inter_opt)
          {
          Run_Inter_opt = passet;
          }

        break;
        
#endif

      case 'z':

        if_cmd_line(z_opt)
        z_opt = passet;

        break;

      case '?':

      default :

        errflg++;

        break;
      }
    }  /* END while ((c = getopt(argc,argv,GETOPT_ARGS)) != EOF) */

err:
  if (!errflg && pass)
    {
    errflg = (optind != argc);
    
    if (errflg)
    {
      sprintf(PBS_ERROR_MSG, "pbs_submit: directive error: ");
      for (optind = 1;optind < argc;optind++)
        strcat(PBS_ERROR_MSG, argv[optind]);
      strcat(PBS_ERROR_MSG, "\n");
    }
    }

  return(errflg);
  }  /* END parse_file() */




/*
 * set_opt_defaults - if not already set, set certain job attributes to
 * their default value
 */

void
set_opt_defaults(void)

  {
  if (c_opt == FALSE)
    set_attr(&attrib, ATTR_c, default_ckpt);

  if (h_opt == FALSE)
    set_attr(&attrib, ATTR_h, NO_HOLD);

  if (j_opt == FALSE)
    set_attr(&attrib, ATTR_j, NO_JOIN);

  if (k_opt == FALSE)
    set_attr(&attrib, ATTR_k, NO_KEEP);

  if (m_opt == FALSE)
    set_attr(&attrib, ATTR_m, MAIL_AT_ABORT);

  if (p_opt == FALSE)
    set_attr(&attrib, ATTR_p, "0");

  if (r_opt == FALSE)
    {
    if (rerunnable_by_default)
      set_attr(&attrib, ATTR_r, "TRUE");
    else
      set_attr(&attrib, ATTR_r, "FALSE");
    }
  
  if (f_opt == FALSE) //TODO: to check pbs vesrion in this case
#if 0  
    {
    if (fault_tolerant_by_default)
      set_attr(&attrib, ATTR_f, "TRUE");
    else
      set_attr(&attrib, ATTR_f, "FALSE");
    }
#endif
  return;
  }  /* END set_opt_defaults() */


#define TCONST_CFGFILE "torque.cfg"

int load_config(

  char *config_buf, /* O */
  int   BufSize)    /* I */

  {
  FILE *config_stream;

  char home_dir[MAXPATHLEN];

  int  length = strlen(PBS_SERVER_HOME) + strlen(TCONST_CFGFILE) + 1;

  char *ptr;

  if (length >= MAXPATHLEN)
    {
    /* FAILURE */

    return(1);
    }

  home_dir[0] = '\0';

  strcat(home_dir, PBS_SERVER_HOME);

  strcat(home_dir, "/");

  strcat(home_dir, TCONST_CFGFILE);

  if ((config_stream = fopen(home_dir, "r")) == NULL)
    {
    /* FAILURE */

    return(1);
    }

  if ((fread(config_buf, BufSize, 1, config_stream) <= 0) && (ferror(config_stream) != 0))
    {
     fclose(config_stream);
    /* FAILURE */
    
    return(1);
    }

  ptr = config_buf;

  while ((ptr = strchr(ptr, '#')) != NULL)
    {
    ptr++;

    for (;(*ptr != '\0') && (*ptr != '\n');ptr++)
      {
      *ptr = ' ';
      }
    }   /* END while ((ptr = strchr(ptr,'#')) != NULL) */

   fclose(config_stream);
  /* SUCCESS */

  return 0;
  }  /* END load_config() */





char *get_param(

  char *param,      /* I */
  char *config_buf) /* I */

  {
  char tmpLine[1024];

  char *param_val;
  char *new_val = NULL;

  /* FORMAT:  <PARAM> <WS> <VALUE> \n */

  /* NOTE:  does not support comments */

  /* if (strcasestr() == NULL) */

  /* NOTE: currently case-sensitive (FIXME) */

  if ((param_val = strstr(config_buf, param)) == NULL)
    {
    return(NULL);
    }

  strncpy(tmpLine, param_val, sizeof(tmpLine));

  strtok(tmpLine, " \t\n");

  if ((new_val = (char *)strtok(NULL, "\t \n")) == NULL)
    {
    return(NULL);
    }

  return(new_val);
  }  /* END get_param() */



#define SUBMIT_FILTER_PATH "/usr/local/sbin/torque_submitfilter"


/** 
 * pbs_prepare_script  
 *
 * @see parse_file() - child
 */

int pbs_prepare_script(

    int   argc,        /* I */
    char  **argv,      /* I */
    char  **envp,      /* I */
    char  script_tmp[],/* O */
    char  destination_cpy[], /* O */
    char  server_out_cpy[], /* O */
    struct attrl **attrib_cpy /* O */)
{

  int errflg;                         /* option error */
  static char script[MAXPATHLEN + 1] = ""; /* name of script file */
  char *bnp;
  FILE *f;                            /* FILE pointer to the script */
  char *q_n_out;                      /* queue part of destination */
  char *s_n_out;                      /* server part of destination */
  /* server:port to send request to */
  int   connect;                      /* return from pbs_connect */

  struct stat statbuf;

  struct sigaction act;

  char config_buf[MAX_LINE_LEN];      /* Buffer holds config file */
  char *param_val;                    /* value of parameter returned from config */

  char *submit_args_str = NULL;       /* buffer to hold args */
  int   argi, argslen = 0;
 
  initialize_pbs_error_msg(PBS_ERROR_MSG);

  if ((param_val = getenv("PBS_CLIENTRETRY")) != NULL)
  {
    cnt2server_retry = atoi(param_val);
  }

  /* set the submit_args */

  for (argi = 1;argi < argc;argi++)
  {
    argslen += strlen(argv[argi]) + 1;
  }

  if (argslen > 0)
  {
    submit_args_str = malloc(sizeof(char) * argslen);

    if (submit_args_str == NULL)
    {
      sprintf(PBS_ERROR_MSG, "pbs_submit: out of memory\n");
      return 2;
    }

    *submit_args_str = '\0';

    for (argi = 1;argi < argc;argi++)
    {
      strcat(submit_args_str, argv[argi]);

      if (argi != argc - 1)
      {
        strcat(submit_args_str, " ");
      }
    }
  }

  /* check TORQUE config settings */
  strncpy(PBS_Filter, SUBMIT_FILTER_PATH, 255);

  /* check to see if PBS_Filter exists.  If not then fall back to the default hard-coded file */

  if (stat(PBS_Filter, &statbuf) == -1)
  {
    strncpy(PBS_Filter, DefaultFilterPath, 255);
  }

  strncpy(xauth_path, DefaultXauthPath, 255);

  strncpy(default_ckpt, CHECKPOINT_UNSPECIFIED, sizeof(default_ckpt));

  validate_path = 1;  /* boolean - by default verify '-d' working dir locally */

  server_host[0]  = '\0';
  pbs_submit_host[0]    = '\0';
  owner_uid[0]    = '\0';

  if (getenv("PBSDEBUG") != NULL)
  {
    sprintf(PBS_ERROR_MSG, "xauth_path=%s\n",
        xauth_path);
  }

  if (load_config(config_buf, sizeof(config_buf)) == 0)
  {
    if ((param_val = get_param("QSUBSLEEP", config_buf)) != NULL)
    {
      sleep(atoi(param_val));
    }

    if ((param_val = get_param("SUBMITFILTER", config_buf)) != NULL)
    {
      strncpy(PBS_Filter, param_val, sizeof(PBS_Filter));
      PBS_Filter[sizeof(PBS_Filter) - 1] = '\0';
    }

    if ((param_val = get_param("SERVERHOST", config_buf)) != NULL)
    {
      strncpy(server_host, param_val, sizeof(server_host));
      server_host[sizeof(server_host) - 1] = '\0';
    }

    if ((param_val = get_param("QSUBHOST", config_buf)) != NULL)
    {
      strncpy(pbs_submit_host, param_val, sizeof(pbs_submit_host));
      pbs_submit_host[sizeof(pbs_submit_host) - 1] = '\0';
    }

    if ((param_val = get_param("QSUBSENDUID", config_buf)) != NULL)
    {
      sprintf(owner_uid, "%d", (int)getuid());
    }

    if ((param_val = get_param("QSUBSENDGROUPLIST", config_buf)) != NULL)
    {
      gid_t group_id = getgid();
      struct group *gpent = getgrgid(group_id);

      if (gpent != NULL)
      {
        set_attr(&attrib, ATTR_g, gpent->gr_name);
      }
    }

    if ((param_val = get_param("QSUBSENDGROUPLIST", config_buf)) != NULL)
    {
      gid_t group_id = getgid();
      struct group *gpent = getgrgid(group_id);

      if (gpent != NULL)
      {
        set_attr(&attrib, ATTR_g, gpent->gr_name);
      }
    }

    if ((param_val = get_param("XAUTHPATH", config_buf)) != NULL)
    {
      strncpy(xauth_path, param_val, sizeof(xauth_path));
      xauth_path[sizeof(xauth_path) - 1] = '\0';
    }

    if ((param_val = get_param("CLIENTRETRY", config_buf)) != NULL)
    {
      if (cnt2server_retry == -100)
        cnt2server_retry = atoi(param_val);
    }

    if ((param_val = get_param("VALIDATEGROUP", config_buf)) != NULL)
    {
      if (getgrgid(getgid()) == NULL)
      {
        sprintf(PBS_ERROR_MSG, "pbs_submit: cannot validate submit group.\n");
        return 1;
      }
    }

    if ((param_val = get_param("DEFAULTCKPT", config_buf)) != NULL)
    {
      strncpy(default_ckpt, param_val, sizeof(default_ckpt));
    }

    if ((param_val = get_param("VALIDATEPATH", config_buf)) != NULL)
    {
      if (!strcasecmp(param_val, "false"))
        validate_path = 0;
    }
    if ((param_val = get_param("RERUNNABLEBYDEFAULT", config_buf)) != NULL)
    {
      if (!strcasecmp(param_val, "false"))
        rerunnable_by_default = 0;
    }
    if ((param_val = get_param("FAULT_TOLERANT_BY_DEFAULT", config_buf)) != NULL)
    {
      if (!strcasecmp(param_val, "true"))
        fault_tolerant_by_default = 1;
    }
  }    /* END if (load_config(config_buf,sizeof(config_buf)) == 0) */

  /* NOTE:  load config before processing opts since config may modify how opts are handled */
  
  errflg = parse_file(argc, argv, 0);  /*get cmd-line options */

  if (errflg || ((optind + 1) < argc))
  {

    if (submit_args_str != NULL)
    {
      free(submit_args_str);
    }

    return 2;
  }

  /* check to see if PBS_Filter exists.  If not then fall back to the old hard-coded file */

  if (stat(PBS_Filter, &statbuf) == -1)
  {
    strncpy(PBS_Filter, DefaultFilterPath, 255);
  }

  if (optind < argc)
    strcpy(script, argv[optind]);

  /* store the saved args string in "submit_args" attribute */

#if 0
  if (submit_args_str != NULL)
  {
    set_attr(&attrib, ATTR_submit_args, submit_args_str);
    free(submit_args_str);
  }
#endif
  /* end setting submit_args */

  if (Forwardx11_opt)
  {
    char *x11authstr;

    /* get the DISPLAY's auth proto, data, and screen number */

    if ((x11authstr = x11_get_proto(NULL)) != NULL)
    {
      /* stuff this info into the job */
#if 0
      set_attr(&attrib, ATTR_forwardx11, x11authstr);
      if (getenv("PBSDEBUG") != NULL)
        sprintf(PBS_ERROR_MSG, "x11auth string: %s\n",
            x11authstr);
#endif
    }
    else
    {
      sprintf(PBS_ERROR_MSG, "pbs_submit: Failed to get xauth data (check $DISPLAY variable)\n");
      return 1;
    }
  }

  /* if script is empty, get standard input */
  if (!strcmp(script, "") || !strcmp(script, "-"))
  {
    if (!N_opt)
      set_attr(&attrib, ATTR_N, "STDIN");

    if ((errflg = get_script(
            argc,
            argv,
            stdin,
            script_tmp,    /* O */
            set_dir_prefix(dir_prefix, C_opt))) > 0)
    {
      unlink(script_tmp);
      return 1;
    }

    if (errflg < 0)
    {
      unlink(script_tmp);
      return 1;
    }
  }    /* END if (!strcmp(script,"") || !strcmp(script,"-")) */
  else
  {
    /* non-empty script, read it for directives */
    if (stat(script, &statbuf) < 0)
    {
      sprintf(PBS_ERROR_MSG, "pbs_submit: script file '%s' cannot be loaded - %s\n",
          script,
          strerror(errno));
      return 1;
    }

    if (!S_ISREG(statbuf.st_mode))
    {
      sprintf(PBS_ERROR_MSG, "pbs_submit: script not a file\n");
      return 1;
    }

    if ((f = fopen(script, "r")) != NULL)
    {
      if ((errflg = get_script(
        argc,
        argv,
        f,
        script_tmp, /* O */
        set_dir_prefix(dir_prefix, C_opt))) > 0)
      {
        unlink(script_tmp);
        return 1;
      }
      
      if (!N_opt)
      {
        if ((bnp = strrchr(script, (int)'/')))
          bnp++;
        else
          bnp = script;
        if (check_job_name(bnp, 0) == 0)
        {
          set_attr(&attrib, ATTR_N, bnp);
        }
        else
        {
          sprintf(PBS_ERROR_MSG, "pbs_submit: cannot form a valid job name from the script name\n");
          return 1;
        }
      }

      if (errflg < 0)
      {
        unlink(script_tmp);
        return 1;
      }
    }    /* END if ((f = fopen(script,"r")) != NULL) */
    else
    {
      perror("pbs_submit: opening script file:");

      unlink(script_tmp);
      return 8;
    }
  }    /* END else (!strcmp(script,"") || !strcmp(script,"-")) */

  set_opt_defaults();  /* set option default values */

  server_out[0] = '\0';

  if (parse_destination_id(destination, &q_n_out, &s_n_out))
  {
    sprintf(PBS_ERROR_MSG, "pbs_submit: illegally formed destination: %s\n",
        destination);

    unlink(script_tmp);
    return 2;
  }

  if (notNULL(s_n_out))
  {
    strcpy(server_out, s_n_out);
  }

  /* connect to the server */

  if (cnt2server_retry != -100)
    //cnt2server_conf(cnt2server_retry); /* set number of seconds to retry */

  connect = cnt2server(server_out);

  if (connect <= 0)
  {
    sprintf(PBS_ERROR_MSG, "pbs_submit: cannot connect to server %s (errno=%d) %s\n",
        pbs_server,
        pbs_errno,
        pbse_to_txt(pbs_errno));

    if (getenv("PBSDEBUG") != NULL)
    {
      sprintf(PBS_ERROR_MSG, "pbs_submit: pbs_server daemon may not be running on host %s or hostname in file '$TORQUEHOME/server_name' may be incorrect)\n",
          pbs_server);
    }

    unlink(script_tmp);
    return pbs_errno;
  }

  /* Get required environment variables to be sent to the server. */

  if (!set_job_env(envp))
  {
    sprintf(PBS_ERROR_MSG, "pbs_submit: cannot send environment with the job\n");

    unlink(script_tmp);
    return 3;
  }

  strcpy(destination_cpy, destination);
  strcpy(server_out_cpy, server_out);

  *attrib_cpy = attrib; 

  return 0;
}  


int get_pbs_error_msg(char error_msg[]) {
  if(PBS_ERROR_MSG[0]!='\0') {
    strcpy(error_msg, PBS_ERROR_MSG);
    return 0;
  } else {
    return 1;
  }
}


