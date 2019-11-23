#!/usr/bin/env bash
# Figure out some data of the process

GR='\033[0;32m' # Green
NC='\033[0m' # No Color

function proccat() {
    echo -n -e "${GR}$1:${NC} "
    cat $1
    echo
}

#pstree | less
#cat /proc/$$/status | less
#cat /proc/$$/environ | less
echo "PID: $$"
echo "PPID: $PPID"
proccat /proc/$$/cmdline
proccat /proc/$PPID/cmdline
proccat /proc/sys/kernel/pid_max
