#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "inc/libmalloc.h"

void big_boi()
{
	char **str = malloc(sizeof(char*) * 1000);
	for (int i = 0; i < 1000; i++)
	{
		str[i] = malloc(2000 - i * 2);
	}
	for (int i = 0; i < 500; i++)
	{
		free(str[i]);
	}
	for (int i = 0; i < 500; i++)
	{
		str[i] = malloc(4000 - i * 2);
	}
	for (int i = 0; i < 1000; i++)
	{
		free(str[i]);
	}
	free(str);
	str = malloc(sizeof(char *) * 1000);
	for (int i = 999; i >= 0; i--)
	{
		str[i] = malloc(2000 - i * 2);
	}
	for (int i = 0; i < 1000; i++)
	{
		free(str[i]);
 	}
	free(str);
	show_alloc_mem();
}

// int main(void)
// {
// 	char *str = malloc(32);
// 	printf("%p\n", str);
// 	free(str);
// 	for (int i = 0; i < 1024; i++)
// 	{
// 		str = malloc(32);
// 		//printf("%p\n", str);
// 	}
// 	printf("%p\n", str);
// 	free(str);
// 	//print_memory();
// }

#include <unistd.h>
#define M (1024 * 1024) 

void print (char * s) 
{ 
write (1, s, strlen (s)); 
} 

int main () 
{ 
malloc (1024); 
malloc (1024 * 32); 
malloc (1024 * 1024); 
malloc (1024 * 1024 * 16); 
malloc (1024 * 1024 * 128); 
show_alloc_mem (); 
return (0); 
} 