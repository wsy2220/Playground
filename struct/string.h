typedef struct string{
	char *strp;
	size_t length; /* excluding '\0' */
	size_t nline;
	int stat;
} string;
int iseq_str(void *obj1, void *obj2);
void print_str(void *obj);
unsigned long getkey_str(string *str);
int getstat_str(void *obj);
void setstat_str(void *obj, int stat);
void free_str(void *obj);
