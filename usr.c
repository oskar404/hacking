#define _XOPEN_SOURCE 700 /* to get getpwent(), enpwent() .. */
/* man feature_test_macros is your friend */
#define _GNU_SOURCE   /* for program_invocation_short_name (non standard glibc) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>


typedef void (*TestFunction)(const char*);


void usage()
{
    printf("usage: %s [-p|-u <user>|-g <group>]\n\n",
            program_invocation_short_name);
    printf("  Inspect user ids, group ids + /etc/passwd ..\n\n");
    printf("  -p       list /etc/passwd - getpwent()\n");
    printf("  -u user  get user data\n");
    printf("  -g group get group data\n");
    printf("\n");
    exit(EXIT_FAILURE);
}


void read_passwd(const char* arg)
{
    printf("list: /etc/passwd\n");
    struct passwd *pwd;

    while ((pwd = getpwent()) != NULL)
    {
        printf("%-20s uid:%5ld gid:%5ld home:%s\n",
                pwd->pw_name, (long)pwd->pw_uid, (long)pwd->pw_gid, pwd->pw_dir);
    }
    endpwent();
}


void dump_user(const char* arg)
{
    struct passwd *pwd;

    if ((pwd = getpwnam(arg)) != NULL)
    {
        printf("name:   %s\n", pwd->pw_name);
        printf("passwd: %s\n", pwd->pw_passwd);
        printf("uid:    %ld\n", (long)pwd->pw_uid);
        printf("gid:    %ld\n", (long)pwd->pw_gid);
        printf("gecos:  %s\n", pwd->pw_gecos);
        printf("dir:    %s\n", pwd->pw_dir);
        printf("shell:  %s\n", pwd->pw_shell);
    }
    else
    {
        printf("user '%s' not found\n", arg);
    }
}


void dump_group(const char* arg)
{
    struct group *grp;

    if ((grp = getgrnam(arg)) != NULL)
    {
        printf("name:   %s\n", grp->gr_name);
        printf("passwd: %s\n", grp->gr_passwd);
        printf("gid:    %ld\n", (long)grp->gr_gid);
        for (int i = 0; grp->gr_mem[i] != NULL; ++i)
        {
            printf("member: %s\n", grp->gr_mem[i]);
        }
    }
    else
    {
        printf("user '%s' not found\n", arg);
    }
}


int main(int argc, char* argv[])
{
    TestFunction tester = &read_passwd;
    int opt;
    char* arg = "";

    while ((opt = getopt(argc, argv, "hpu:g:")) != -1) {
        switch (opt) {
        case 'p':
            tester = &read_passwd;
            break;
        case 'u':
            tester = &dump_user;
            arg = optarg;
            break;
        case 'g':
            tester = &dump_group;
            arg = optarg;
            break;
        case 'h':
            usage();
            break;
        default: /* '?' */
            usage();
        }
    }

    if (optind < argc)
        usage();

    /* Run the test */
    (*tester)(arg);

    return 0;
}
