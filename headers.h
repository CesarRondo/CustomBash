/*
By:
Cesar Rondo Rodriguez
email: c.rondoro12@gmail.com
*/
//Header file:

char *getCommand (char *buffer, int buffLen);
void removeChar(char *str, char c);
char **getArguments(char *buffer, int buffLen);
void printTime();
void signalHandler(int sigCode);
void handleCD(char **argArr);
int runCommand(char *command,char ** argArr);
int findRedirect(char *buffer, int buffLen);
void redirect(char *buffer);