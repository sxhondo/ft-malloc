#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr;


} 
