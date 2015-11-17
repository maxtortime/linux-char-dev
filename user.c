#include <stdio.h>
#include <stdlib.h>
#define SIZE 200

int main() {
    char msg[SIZE];
    FILE *fp = fopen("/dev/cdev_example","r");

    if (fp==NULL) {
        perror("READ ERROR");
        exit(1);
    }
    else {
       fputs("There There",fp);
       fgets(msg,200,fp);

       printf("%s",msg);
    }

    return 0;
}

