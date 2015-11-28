#include "queue.h"
#include <string.h>

#define SIZE 200

int main() {
    char msg[SIZE];
    int commands, number;
    
    FILE *fp = fopen("/dev/cdev_example","r");
    
    printf("Welcome to user-kernel interacting program!..\n");

    if (fp==NULL) {
        perror("READ ERROR");
        exit(1);
    }
    else {
		
		printf("Opening character driver device is sucessful!\n");
		while(commands!=4) {	
			printf("1) Enqueue 2) Dequeue 3) Print 4) quit > ");
			scanf("%d",&commands);
			
			if (commands==1) {
				printf("Please input integer...> ");
				scanf("%d",&number);
				
				sprintf(msg,"enqueue %d",number);
				fputs(msg,fp);

			}
		}		
    }
    
    fclose(fp);
    return 0;
}

