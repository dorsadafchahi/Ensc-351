#include "button.h"

//function to get value of a GPIO file
int getGPIOvalue(){
    FILE *file = fopen(USER_BUTTON_VALUE, "r");
    if (file == NULL){
        printf("Error opening file %s\n", USER_BUTTON_VALUE);
        exit(1);
    }
    int value = fgetc(file);
    fclose(file);
    return value;
}

//function to write to file
void writetoFile(const char* value){
	FILE *pFile = fopen(USER_BUTTON_DIRECTION, "w");
    if (pFile == NULL) {
        printf("ERROR: Unable to open file %s.\n", USER_BUTTON_DIRECTION);
        exit(1);
    }
	fprintf(pFile, "%s", value);
	fclose(pFile);
}

//given function to run a linux command in C
void runCommand(char* command) {    
    // Execute the shell command (output into pipe)    
    FILE *pipe = popen(command, "r");    
    // Ignore output of the command; but consume it     
    // so we don't get an error when closing the pipe.    
    char buffer[1024];    
    while (!feof(pipe) && !ferror(pipe)) {        
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)            
        break;        
        // printf("--> %s", buffer);  // Uncomment for debugging    
    }    
    // Get the exit code from the pipe; non-zero is an error:    
    int exitCode = WEXITSTATUS(pclose(pipe));    
    if (exitCode != 0) {        
        perror("Unable to execute command:");        
        printf("  command:   %s\n", command);        
        printf("  exit code: %d\n", exitCode);    
    } 
}
