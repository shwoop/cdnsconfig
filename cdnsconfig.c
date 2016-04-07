#include <errno.h>
#include <error.h>
#include <sys/stat.h>
#include <unistd.h>

#define SCRIPT "/usr/local/bin/dnsconfig"

int main(int argc, char **argv) {
  struct stat st;
  argc = argc;        //avoid compiler warning

  if (geteuid() != 0)
    error(1, errno, "must be run as root\r\n");

  if (access(SCRIPT, X_OK) < 0)
    error(1, errno, "%s should have execute permission\r\n", SCRIPT);

  if (stat(SCRIPT, &st) < 0)
    error(1, errno, "unable to get stat of %s\r\n", SCRIPT);

  if (st.st_mode & S_ISUID)
    error(1, errno, "please remove setuid bit from %s\r\n", SCRIPT);

  argv[0] = SCRIPT;

  execvp(argv[0], &argv[0]);
}
