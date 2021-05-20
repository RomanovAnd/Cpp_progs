 #include <stdio.h>
#include <string.h>
#include "database.h"
#include <time.h>
#include <stdlib.h>
int main(int argc,char **argv)
{
       FILE *atxt;
       char alphabet[256]={0};
       char *a;
       command x;
       database d;
       double t;
       int ret,n1,n2,PORT;
       if(argc !=5 || !(n1 = atoi(argv[2])) || !(n2 = atoi(argv[3])) || !(PORT = atoi(argv[4])) ) 
       {
		   printf("usage ./server    file    big_phone_hash     small_phone_hash_in_group_tree     port \n");
           return 1;
       }
       if(n1<0 || n2<0){ printf("bad hashmodeule"); return 1;}
       a=argv[1];
       alphabet[(unsigned char)(' ')]=1;
       alphabet[(unsigned char)('(')]=1;
       alphabet[(unsigned char)(')')]=1;
       alphabet[(unsigned char)(',')]=1;
       alphabet[(unsigned char)(';')]=1;
       alphabet[(unsigned char)('\n')]=1;
       alphabet[(unsigned char)('\t')]=1;
       t=clock();
       d.initi(n1,n2);
       if(!(atxt=fopen(a,"r")))
       {
           printf("error cannot open file\n");
           return 1;
         }
       if(d.read(atxt)<0) {printf("something is bad\n"); return 1;}
       t=clock()-t;
       printf("reading time:: %f \n",t/CLOCKS_PER_SEC);
                    
       ret = serv (PORT,d,alphabet,x);
		if (ret<0)
		{
			printf("some error %d \n",ret);
			return 4;
		}
       t=clock()-t;
       printf("commands work time:: %f \n",t/CLOCKS_PER_SEC);
       fclose(atxt);
       return 0;
}

