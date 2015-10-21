/*
 * yeshup.c
 *
 * Wrapper for Linux to prevent child processes from becoming orphaned.
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
 * child_process arguments
 *
 * You can simply run:
 *
 * yeshup child_process arguments
 *
 * Written originally to implement a feature in SetCPU. Works in Linux only,
 * but should be compatible with most distributions, including Android.
 *
 * For a possible use case/scenario, see http://stackoverflow.com/a/13280892
 */

#include <linux/prctl.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv) {
     if(argc < 2)
          return 1;
     /* When my parent is killed, give me SIGHUP */
     prctl(PR_SET_PDEATHSIG, SIGHUP, 0, 0, 0);
     /* fork() wipes the parent death signal setting, but exec() does not! */
     return execvp(argv[1], &argv[1]);
}
