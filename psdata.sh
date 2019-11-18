#!/usr/bin/env bash
# Figure out some data of the process



#pstree | less
#cat /proc/$$/status | less
#cat /proc/$$/environ | less
echo "PID: $$"
cat /proc/$$/cmdline
echo
echo "PPID: $PPID"
cat /proc/$PPID/cmdline
echo
cat /proc/sys/kernel/pid_max
echo