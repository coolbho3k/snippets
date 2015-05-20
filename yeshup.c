/*
 * yeshup.c
 *
 * Wrapper to prevent child processes from becoming orphaned.
 *
 * In Linux, when a parent process calls another process and the parent crashes
 * or is killed, the child process becomes an "orphan process."	yeshup signals
 * child processes to exit cleanly if the parent dies for whatever reason,
 * preventing orphan processes from accumulating on a system.
 *
 * Usage: Simply append "yeshup " to the beginning of your command when
 * spawning your child process, including all arguments normally. For example,
 * instead of running:
 *
 * ls -l
 *
 * You can simply run:
 *
 * yeshup ls -l
 *
 * Written originally for implement a feature in SetCPU. Works in Linux only,
 * but should be compatible with most recent distributions, including Android.
 *
 * For a possible use case/scenario, see http://stackoverflow.com/a/13280892
 */

#include <linux/prctl.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv) {
     if(argc < 2)
          return 1;
     prctl(PR_SET_PDEATHSIG, SIGHUP, 0, 0, 0);
     return execvp(argv[1], &argv[1]);
}