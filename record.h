

#ifndef RECORD_H
#define RECORD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<iostream>
#include<memory>


class record
{
	private:
        std::unique_ptr<char[]> name=nullptr;
        int phone=-1;
        int group=-1;
	public:
        friend class command;
        friend class list;
        friend class tree;
        friend class uptree;
        friend class hash;
        friend class database;
                record()=default;
                record(const record & x);
                record(record && x);
                record & operator=(const record & x);
                record & operator=(record && x);
                ~record() {destroy();};
		const char* get_name() const
		{ return name.get();}
                int get_phone() const
                { return phone;}
                int get_group() const
                { return group;}
                int init(const char* n, int p,int g);
                int initname(const char* n);
		        void destroy()
                { phone=-1; group=-1; name=nullptr;};
                int operator==(const record & x);
                void swap(record & x);
		void print(FILE* out=stdout);
             int read(FILE* fp);

        
};

#endif // record.H
