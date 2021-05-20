#include "record.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define LEN 1234
//-g -pg -Wall -Wextra -Werror
int record::init(const char *n,int p,int g)
{
        phone=p;
        group=g;
	if(n)
	{
                name=std::make_unique<char[]> (strlen(n)+1);
		if(!name) return -1;
                strcpy(name.get(),n);
	}
	else name=nullptr;
	return 0;
}

int record::initname(const char *n)
{
    if(n)
    {
            name=std::make_unique<char[]> (strlen(n)+1);
            if(!name) return -1;
            strcpy(name.get(),n);
    }
    else name=nullptr;
    return 0;
}

int record::read(FILE* fp)
{
        char buf[LEN];
        destroy();
        if(fscanf(fp,"%s%d%d",buf,&phone,&group)!=3)
        {
                if(feof(fp)) return 1;
                return -1;
        }
        if(init(buf,phone,group))
        return -2;
        return 0;
}


record::record(const record & x)
{ 
        init(x.get_name(),x.phone,x.group);
}
	  
record::record(record && x)
{ 
        phone=x.phone;
        name=std::move(x.name);
        x.phone=0;
	x.name=nullptr;
}
int record ::operator==(const record & x)
{

        if(strcmp(get_name(),x.get_name())==0 && phone==x.phone && group==x.group)
        return 1;
        return 0;
}
record & record::operator=(const record & x)
{
        destroy();
        init(x.get_name(),x.phone,x.group);
	return *this;
}

record & record::operator=(record && x)
{
        destroy();
        phone=x.phone;
        name=std::move(x.name);
	x.name=nullptr;
        x.phone=0;
	return *this;
}


void record::swap(record & x)
{
	int b;
        b=x.phone;
        x.phone=phone;
        phone=b;
        name.swap(x.name);
}
	
void record::print(FILE* out)
{
 fprintf(out," %s  %d  %d\n",get_name(),phone,group);
}
