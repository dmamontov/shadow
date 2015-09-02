#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <shadow.h>

uid_t name_to_uid(char const *name)
{
  if (!name) {
    return -1;
  }
  long const buflen = sysconf(_SC_GETPW_R_SIZE_MAX);
  if (buflen == -1) {
    return -1;
  }

  char buf[buflen];
  struct passwd pwbuf, *pwbufp;
  if (0 != getpwnam_r(name, &pwbuf, buf, buflen, &pwbufp) || !pwbufp) {
    return -1;
  }

  return pwbufp->pw_uid;
}

int main(int argc, char **argv){
    struct passwd *userinfo;
    struct spwd *passw;
    uid_t userid;

    userinfo = getpwuid(name_to_uid(argv[1]));
    if (userinfo != NULL){

        passw = getspnam(userinfo->pw_name);

        if (passw != NULL){
            printf("user login: %s\n",userinfo->pw_name);
            printf("user home: %s\n",userinfo->pw_dir);
            printf("user shell: %s\n",userinfo->pw_shell);
            printf("user password: %s\n",userinfo->pw_passwd);
            printf("user shadow password: %s\n",passw->sp_pwdp);
            printf("user last change: %ld\n",passw->sp_lstchg);
        };

    };

    return 0;
};
