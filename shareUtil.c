//#include "shareUtil.h"

static uint32_t rdtsc(){
	uint32_t ret = 0;
	__asm__ __volatile__ ("rdtsc"
						 : "=a" (ret));
	return ret;
}

static char *randString(char *str, size_t size){
    const char charset[] = 
    	"?!.-#$0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   
    if (size) {
        --size;
        srand(rdtsc());
        
        for (register int32_t i = 0; i < size; ++i) {
            int32_t key = rand() % (sizeof(charset) - 1);
            str[i] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}