#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size(char* string) {
	return strlen(string);
}

int main ()
{
	char* src = "http://www.tutorialspoint.com";
	char* dest = malloc(sizeof(char) * (strlen(src) + 1));

	printf("%d\n", strlen(src));
	printf("%d\n", size(dest));
	
	printf("Before memcpy dest = %s\n", dest);
	memcpy(dest, src, strlen(src)+1);
	printf("After memcpy dest = %s\n", dest);
	
	return(0);
}
