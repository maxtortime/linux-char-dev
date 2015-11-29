#include "queue.h"
#include <string.h>

#define SIZE 200

enum COMMANDS {ENQUEUE=1, DEQUEUE, PRINT, QUIT};

int main() {
    char msg[SIZE];
    char buffer[SIZE];

    int commands, number;
    
    FILE *fp = fopen("/dev/cdev_example","r+");
    
    printf("Welcome to user-kernel interacting program!..\n");

    if (fp==NULL) {
        perror("READ ERROR");
        exit(1);
    }
    else {
		printf("Opening character driver device is \
			sucessful!\n");

		while(commands!=QUIT) {	
			printf("1) Enqueue 2) Dequeue 3) Print 4) quit > ");
			scanf("%d",&commands);
			
			switch(commands) {
				case ENQUEUE:
					printf("Please input integer...> ");
					scanf("%d",&number);
				
					sprintf(msg,"enqueue %d",number);
				
					fprintf(fp,"%s",msg);
					fgets(buffer,SIZE,fp);
					printf("%s",buffer);
					break;
				case DEQUEUE:
					fprintf(fp,"dequeue");
					fgets(buffer,SIZE,fp);
					printf("%s",buffer);
					break;
				case PRINT:
					fprintf(fp,"print");
					fgets(buffer,SIZE,fp);
					printf("%s",buffer);
					break;
				default:
					perror("Error: ");
					exit(1);
			}
		}		
    }
    
    fclose(fp);
    return 0;
}

