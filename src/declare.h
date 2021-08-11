#ifndef DECLARE_HEADER
#define DECLARE_HEADER

FILE* getstyrefile(char* filepath, char* mode);
void parseargs(int *c, char *arg);
char* fgetline(FILE *fp, int line);
char* ffindline(FILE *fp, char *text, int *linenumber);
char* getinsidequotes(char *text);
char* getusername();
char* styresplit(char *text, int sec);

//void D(char *arg);
void e(char *arg);
void G(char* arg);
void L(char* arg);
void S(char* arg);
void E(char* arg);
void g();
void l();
void s(char *arg);
void e2(FILE *fp, char *subname);

#endif 
