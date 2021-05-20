#include <stdio.h>
#include <stdlib.h>
#include "record.h"

//#include "list_node.h"
#ifndef COMMAND_H
#define COMMAND_H
#define DLINA 400
enum CMD_TYPE
{
    CMD_NONE,
    CMD_QUIT,
    CMD_STOP,
    CMD_INSERT,
    CMD_DELETE,
    CMD_SELECT
};
enum COND_TYPE
{
    COND_NONE,
    COND_EQ,  //=
    COND_NE,  //<>
    COND_LT,  //<
    COND_GT,  //>
    COND_LE,  //<=
    COND_GE,  //>=
    COND_LIKE
};
enum OP_TYPE
{
    OP_NONE,
    OP_AND, 
    OP_OR     
};
enum SOD_TYPE
{
    SOD_NONE,
    SOD_WHERE, 
    SOD_ALL     
};
enum TAKE_IT
{
    TAKE_NONE,
    TAKE_ALL,
    TAKE_PHONE,
    TAKE_NAME,
    TAKE_GROUP
};
enum ARG_T
{
    ARG_NONE,
    ARG_PHONE,
    ARG_NAME,
    ARG_GROUP
};
class command:public record
{
    private:
        
        CMD_TYPE type=CMD_NONE;
    
        COND_TYPE c_name=COND_NONE;
        COND_TYPE c_phone=COND_NONE;
        COND_TYPE c_group=COND_NONE;
    
        OP_TYPE oper=OP_NONE;
        
        TAKE_IT take1=TAKE_NONE;
        TAKE_IT take2=TAKE_NONE;
        
        ARG_T arg1=ARG_NONE;
        ARG_T arg2=ARG_NONE;
        
      //  char argum1[DLINA]=nullptr;
      //  char argum2[DLINA]=nullptr;
        
    public:
        friend class record;
        friend class list;
        friend class database;
        command()=default;
        
        ~command()
        {
          destroy();    
        }
        
        void destroy()
        {
           type=CMD_NONE; 
           c_name=COND_NONE;
           c_phone=COND_NONE;
           c_group=COND_NONE;
           oper=OP_NONE;
           take1=TAKE_NONE;
           take2=TAKE_NONE;
           arg1=ARG_NONE;
           arg2=ARG_NONE;
           //name=nullptr;
           phone=-1;
           group=-1;
           //for(int i=0;i<1234;i++)
           //length[i]=0;
        }
        
        int parser(char * s,char *alphabet)
        {
          int i,j=0,p=0,k=1;
          char stroka[800];
          int length[600]={0};
          for(i=0;s[i];i++)
          {
              if(alphabet[(unsigned char)s[i]]==0)
                  break;
          }
          for(;s[i];i++)
          {     
              if(alphabet[(unsigned char)s[i]]==0)
              { 
                  stroka[j]=s[i];
                  j++;
                  k=0;
              }
              else
              { 
                  if(k==0)
                  {
				  stroka[j]='\0';
				  j++;
                  length[p]=j;
                  p++;
                  k=1;
                  }
              }
            }
            if(k==0)
            {
				stroka[j]='\0';
				j++;
                length[p]=j;
			}
	    	length[p+1]=0;
		length[p+2]=0;
		length[p+3]=0;
		stroka[j+1]=0;
		stroka[j+2]=0;
		stroka[j+3]=0;
            //////разделили на словцы

            i=0;
	    //printf("%s ",stroka);
	  //  for(;length[i];i++)
	  //  {printf("%s ",stroka+length[i]);}
	  //  printf("\n");
	  //  i=0;
            if(strcmp(stroka,"select")==0||strcmp(stroka,"delete")==0)
            {
                
                if(strcmp(stroka,"delete")==0)
                {
                type=CMD_DELETE;
                //i++;
                return w_Select(stroka,length,i);
				}
				if(strcmp(stroka,"select")==0)
                type=CMD_SELECT;
                if(strcmp(stroka+length[i],"*")==0)
                {
                   take1=TAKE_ALL;
                   i++;
                    return w_Select(stroka,length,i);
                }
                
                if(strcmp(stroka+length[i],"name")==0)
                {
                   take1=TAKE_NAME;
                   i++;
                   if(strcmp(stroka+length[i],"group")==0)
                   {
                      take2=TAKE_GROUP;
                      i++;
                      if(strcmp(stroka+length[i],"phone")==0)
                      {
                         take1=TAKE_ALL;
                         take2=TAKE_NONE;
                         i++;
                         return w_Select(stroka,length,i);
                      }
                      return w_Select(stroka,length,i);
                   }
                   if(strcmp(stroka+length[i],"phone")==0)
                   {
                      take2=TAKE_PHONE;
                      i++;
                      if(strcmp(stroka+length[i],"group")==0)
                      {
                         take1=TAKE_ALL;
                         take2=TAKE_NONE;
                         i++;
                         return w_Select(stroka,length,i);
                      }
                      return w_Select(stroka,length,i);
                   }
                   return w_Select(stroka,length,i);
                }
                else
                if(strcmp(stroka+length[i],"group")==0)
                {
                   take1=TAKE_GROUP;
                   i++;
                   if(strcmp(stroka+length[i],"name")==0)
                   {
                      take2=TAKE_NAME;
                      i++;
                      if(strcmp(stroka+length[i],"phone")==0)
                      {
                         take2=TAKE_NONE;
                         take1=TAKE_ALL;
                         i++;
                         return w_Select(stroka,length,i);
                      }
                      return w_Select(stroka,length,i);
                   }


                   if(strcmp(stroka+length[i],"phone")==0)
                   {
                      take2=TAKE_PHONE;
                      i++;
                      if(strcmp(stroka+length[i],"name")==0)
                      {
                         take1=TAKE_ALL;
                         take2=TAKE_NONE;
                         i++;

                         return w_Select(stroka,length,i);
                      }
                      return w_Select(stroka,length,i);
                   }

                  return w_Select(stroka,length,i);
                }
                else
                if(strcmp(stroka+length[i],"phone")==0)
                {
                   take1=TAKE_PHONE;
                   i++;
                   if(strcmp(stroka+length[i],"group")==0)
                   {
                      take2=TAKE_GROUP;
                      i++;
                      if(strcmp(stroka+length[i],"name")==0)
                      {
                          take1=TAKE_ALL;
                         take2=TAKE_NONE;
                         i++;
                        return w_Select(stroka,length,i);
                      }
                      return w_Select(stroka,length,i);
                   }
                   if(strcmp(stroka+length[i],"name")==0)
                   {
                      take2=TAKE_NAME;
                      i++;
                      if(strcmp(stroka+length[i],"group")==0)
                      {
                          take1=TAKE_ALL;
                         take2=TAKE_NONE;
                         i++;
                        return w_Select(stroka,length,i);
                      }
                     return w_Select(stroka,length,i);
                   }
                  return w_Select(stroka,length,i);
                }
                
                return -4; // ужас
            }
            else
            {
               if(strcmp(stroka,"insert")==0)
               {
                   type=CMD_INSERT;
                    //i++;
                    //printf("%s\n",stroka+length[i]);
                    if(length[i+1]!=0)
                    {
                        name=std::make_unique<char[]> (length[i+1]-length[i]);
                        strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                        i++;
                    }
                    //printf("%s\n",stroka+length[i]);
                    if(length[i+1]!=0)
                    {
                        if(!sscanf(stroka+length[i],"%d",&phone)) return -2;
                        i++;
                    }
                   // printf("%s\n",stroka+length[i]);
                    if(length[i+1]!=0)
                    {
                        if(!sscanf(stroka+length[i],"%d",&group)) return -3;
                        i++;
                    }
                    return 1;
               }
               else
               {
                   if(strcmp(stroka,"quit")==0||strcmp(stroka,"stop")==0)
                   {
					   if (strcmp(stroka, "quit") == 0)
					   {
						   type = CMD_QUIT;
						   return -272;
					   }
					   if (strcmp(stroka, "stop") == 0)
					   {
						   type = CMD_STOP;
						   return -243;
					   }
                   }
                   return -10;
               }
            }
            
            return -1;
        }
		
		int w_Select(char *stroka,int *length,int i)
		{
			 //printf("%s\n",stroka+length[i]);
             if(strcmp(stroka+length[i],"where")==0)
             {

                    i++;
                    if(strcmp(stroka+length[i],"phone")==0) 
                    {
                        arg1=ARG_PHONE;
                        i++;
                        if(strcmp(stroka+length[i],"=")==0)
                        {
                            c_phone=COND_EQ;
                           i++;
                           sscanf(stroka+length[i],"%d",&phone);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],">")==0)
                        {
                            c_phone=COND_GT;
                           i++;
                           sscanf(stroka+length[i],"%d",&phone);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],"<")==0)
                        {
                            c_phone=COND_LT;
                           i++;
                           sscanf(stroka+length[i],"%d",&phone);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],"<>")==0)
                        {
                           c_phone=COND_NE;
                           i++;
                           sscanf(stroka+length[i],"%d",&phone);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],">=")==0)
                        {
                            c_phone=COND_GE;
                           i++;
                           sscanf(stroka+length[i],"%d",&phone);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],"<=")==0)
                        {
                            c_phone=COND_LE;
                           i++;
                           sscanf(stroka+length[i],"%d",&phone);
                           i++;
                        }
                        else return -6;

                        //место для ошибки
                    }
                 
                    else {
                    if(strcmp(stroka+length[i],"group")==0)
                    {
                        arg1=ARG_GROUP;
                        i++;
                        if(strcmp(stroka+length[i],"=")==0)
                        {
                            c_group=COND_EQ;
                           i++;
                           sscanf(stroka+length[i],"%d",&group);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],">")==0)
                        {
                            c_group=COND_GT;
                           i++;
                           sscanf(stroka+length[i],"%d",&group);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],"<")==0)
                        {
                            c_group=COND_LT;
                           i++;
                           sscanf(stroka+length[i],"%d",&group);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],"<>")==0)
                        {
                           c_group=COND_NE;
                           i++;
                           sscanf(stroka+length[i],"%d",&group);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],">=")==0)
                        {
                            c_group=COND_GE;
                           i++;
                           sscanf(stroka+length[i],"%d",&group);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],"<=")==0)
                        {
                            c_group=COND_LE;
                           i++;
                           sscanf(stroka+length[i],"%d",&group);
                           i++;
                        }
                        else return -6;

                        //место для ошибки
                    }
                    else {


                    if(strcmp(stroka+length[i],"name")==0)
                    {
                        arg1=ARG_NAME;
                        i++;
                        if(strcmp(stroka+length[i],"=")==0)
                        {
                            c_name=COND_EQ;
                           i++;
                           name=std::make_unique<char[]> (length[i+1]-length[i]);
                           strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],">")==0)
                        {
                            c_name=COND_GT;
                           i++;
                           name=std::make_unique<char[]> (length[i+1]-length[i]);
                           strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],"<")==0)
                        {
                            c_name=COND_LT;
                           i++;
                           name=std::make_unique<char[]> (length[i+1]-length[i]);
                           strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],"<>")==0)
                        {
                           c_name=COND_NE;
                           i++;
                           name=std::make_unique<char[]> (length[i+1]-length[i]);
                           strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],">=")==0)
                        {
                           c_name=COND_GE;
                           i++;
                           name=std::make_unique<char[]> (length[i+1]-length[i]);
                           strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],"<=")==0)
                        {
                           c_name=COND_LE;
                           i++;
                           name=std::make_unique<char[]> (length[i+1]-length[i]);
                           strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                           i++;
                        }
                        else
                        if(strcmp(stroka+length[i],"like")==0)
                        {
                           c_name=COND_LIKE;
                           i++;
                           name=std::make_unique<char[]> (length[i+1]-length[i]);
                           strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                           i++;
                        }
                        else return -6;
                        
                        //место для ошибки
                    }
                    else return -8;
                    }
                    }
              if(strcmp(stroka+length[i],"and")==0 || strcmp(stroka+length[i],"or")==0)
              {

                  if(strcmp(stroka+length[i],"and")==0)
                  oper=OP_AND;
                  if(strcmp(stroka+length[i],"or")==0)
                  oper=OP_OR;
                  i++;
                  if(strcmp(stroka+length[i],"phone")==0)
                  {
                      arg2=ARG_PHONE;
                      i++;
                      if(strcmp(stroka+length[i],"=")==0)
                      {
                          c_phone=COND_EQ;
                         i++;
                         sscanf(stroka+length[i],"%d",&phone);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],">")==0)
                      {
                          c_phone=COND_GT;
                         i++;
                         sscanf(stroka+length[i],"%d",&phone);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],"<")==0)
                      {
                          c_phone=COND_LT;
                         i++;
                         sscanf(stroka+length[i],"%d",&phone);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],"<>")==0)
                      {
                         c_phone=COND_NE;
                         i++;
                         sscanf(stroka+length[i],"%d",&phone);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],">=")==0)
                      {
                          c_phone=COND_GE;
                         i++;
                         sscanf(stroka+length[i],"%d",&phone);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],"<=")==0)
                      {
                          c_phone=COND_LE;
                         i++;
                         sscanf(stroka+length[i],"%d",&phone);
                         i++;
                      }
                      else return -6;

                      //место для ошибки
                  }
                  else {
                  if(strcmp(stroka+length[i],"group")==0)
                  {
                      arg2=ARG_GROUP;
                      i++;
                      if(strcmp(stroka+length[i],"=")==0)
                      {
                          c_group=COND_EQ;
                         i++;
                         sscanf(stroka+length[i],"%d",&group);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],">")==0)
                      {
                          c_group=COND_GT;
                         i++;
                         sscanf(stroka+length[i],"%d",&group);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],"<")==0)
                      {
                          c_group=COND_LT;
                         i++;
                         sscanf(stroka+length[i],"%d",&group);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],"<>")==0)
                      {
                         c_group=COND_NE;
                         i++;
                         sscanf(stroka+length[i],"%d",&group);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],">=")==0)
                      {
                          c_group=COND_GE;
                         i++;
                         sscanf(stroka+length[i],"%d",&group);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],"<=")==0)
                      {
                          c_group=COND_LE;
                         i++;
                         sscanf(stroka+length[i],"%d",&group);
                         i++;
                      }
                      else return -6;

                      //место для ошибки
                  }
                  else {
                  if(strcmp(stroka+length[i],"name")==0)
                  {
                      arg2=ARG_NAME;
                      i++;
                      if(strcmp(stroka+length[i],"=")==0)
                      {
                          c_name=COND_EQ;
                         i++;
                         name=std::make_unique<char[]> (length[i+1]-length[i]);
                         strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],">")==0)
                      {
                          c_name=COND_GT;
                         i++;
                         name=std::make_unique<char[]> (length[i+1]-length[i]);
                         strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],"<")==0)
                      {
                          c_name=COND_LT;
                         i++;
                         name=std::make_unique<char[]> (length[i+1]-length[i]);
                         strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],"<>")==0)
                      {
                         c_name=COND_NE;
                         i++;
                         name=std::make_unique<char[]> (length[i+1]-length[i]);
                         strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],">=")==0)
                      {
                         c_name=COND_GE;
                         i++;
                         name=std::make_unique<char[]> (length[i+1]-length[i]);
                         strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],"<=")==0)
                      {
                         c_name=COND_LE;
                         i++;
                         name=std::make_unique<char[]> (length[i+1]-length[i]);
                         strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                         i++;
                      }
                      else
                      if(strcmp(stroka+length[i],"like")==0)
                      {
                         c_name=COND_LIKE;
                         i++;
                         name=std::make_unique<char[]> (length[i+1]-length[i]);
                         strncpy(name.get(),stroka+length[i],length[i+1]-length[i]);
                         i++;
                      }
                      else return -6;
                      //место для ошибки
                  }
                  else return -7;
                }
              }
             }
             else 
             {  if(length[i+1]!=0)
				 {
				  return -9;}
				  return 1;}

             }
             else
             {  
				 if(length[i+1]!=0)
				 {
				//	 printf("%c\n",stroka[length[i]]);
			//		 printf("%d  %d\n",length[i],length[i+1]);
			//	 printf("incorrect command !!!! \n\n\n");
				 return -5;}
			 }
            return 1;
        }
        
        
                void print_parse(FILE *out=stdout)
		{
			switch(type)
			{
				case CMD_NONE:
                                fprintf(out,"NONE \n");
				break;
				case CMD_QUIT:
                                fprintf(out,"quit;\n");
				break;
				case CMD_STOP:
                                fprintf(out,"stop;\n");
				break;
				case CMD_INSERT:
                                fprintf(out,"insert ");
                                fprintf(out,"(%s,%d,%d);\n",get_name(),phone,group);
                               // fprintf(out,";\n");
				break;
				case CMD_DELETE:
                                fprintf(out,"delete ");
                               /* switch(take1)
                                {
                                    case TAKE_ALL:
                                    fprintf(out,"* ");
                                    break;
                                    case TAKE_NONE:
                                    break;
                                    case TAKE_PHONE:
                                    fprintf(out,"phone ");
                                    break;
                                    case TAKE_GROUP:
                                    fprintf(out,"group ");
                                    break;
                                    case TAKE_NAME:
                                    fprintf(out,"name ");
                                    break;
                                }
                                switch(take2)
                                {
                                    case TAKE_ALL:
                                    fprintf(out,"* ");
                                    break;
                                    case TAKE_NONE:
                                    break;
                                    case TAKE_PHONE:
                                    fprintf(out,",phone ");
                                    break;
                                    case TAKE_GROUP:
                                    fprintf(out,",group ");
                                    break;
                                    case TAKE_NAME:
                                    fprintf(out,"name ");
                                    break;
                                }*/
                                if(arg1!=ARG_NONE)
                                {
                                    fprintf(out,"where ");
                                    switch(arg1)
                                    {
                                    case ARG_NONE:
                                        fprintf(out,"NONE ");
                                        break;
                                    case ARG_NAME:
                                        fprintf(out,"name ");
                                        switch(c_name)
                                        {
                                                case COND_NONE:
                                                fprintf(out,"NONE ");
                                                break;
                                                case COND_EQ:
                                                fprintf(out,"= ");
                                                break;
                                                case COND_NE:
                                                fprintf(out,"<> ");
                                                break;
                                                case COND_LT:
                                                fprintf(out,"< ");
                                                break;
                                                case COND_GT:
                                                fprintf(out,"> ");
                                                break;
                                                case COND_LE:
                                                fprintf(out,"<= ");
                                                break;
                                                case COND_GE:
                                                fprintf(out,">= ");
                                                break;
                                                case COND_LIKE:
                                                fprintf(out,"like ");
                                                break;
                                       }
                                        fprintf(out,"%s ",get_name());
                                        break;
                                    case ARG_GROUP:
                                        fprintf(out,"group ");
                                        switch(c_group)
                                        {
                                                case COND_NONE:
                                                fprintf(out,"NONE ");
                                                break;
                                                case COND_EQ:
                                                fprintf(out,"= ");
                                                break;
                                                case COND_NE:
                                                fprintf(out,"<> ");
                                                break;
                                                case COND_LT:
                                                fprintf(out,"< ");
                                                break;
                                                case COND_GT:
                                                fprintf(out,"> ");
                                                break;
                                                case COND_LE:
                                                fprintf(out,"<= ");
                                                break;
                                                case COND_GE:
                                                fprintf(out,">= ");
                                                break;
                                                case COND_LIKE:
                                                fprintf(out,"like ");
                                                break;
                                       }
                                        fprintf(out,"%d ",group);
                                        break;
                                    case ARG_PHONE:
                                        fprintf(out,"phone ");
                                        switch(c_phone)
                                        {
                                                case COND_NONE:
                                                fprintf(out,"NONE ");
                                                break;
                                                case COND_EQ:
                                                fprintf(out,"= ");
                                                break;
                                                case COND_NE:
                                                fprintf(out,"<> ");
                                                break;
                                                case COND_LT:
                                                fprintf(out,"< ");
                                                break;
                                                case COND_GT:
                                                fprintf(out,"> ");
                                                break;
                                                case COND_LE:
                                                fprintf(out,"<= ");
                                                break;
                                                case COND_GE:
                                                fprintf(out,">= ");
                                                break;
                                                case COND_LIKE:
                                                fprintf(out,"like ");
                                                break;
                                       }
                                        fprintf(out,"%d ",phone);
                                        break;
                                    }
                                    if(oper!=OP_NONE && arg2!=ARG_NONE)
                                    {
                                        switch(oper)
                                        {
                                          case OP_OR:
                                            fprintf(out,"or ");
                                            break;
                                        case OP_AND:
                                            fprintf(out,"and ");
                                            break;
                                        case OP_NONE:
                                            fprintf(out,"NONE ");
                                            break;
                                        }
                                        switch(arg2)
                                        {
                                        case ARG_NONE:
                                            fprintf(out,"NONE ");
                                            break;
                                        case ARG_NAME:
                                            fprintf(out,"name ");
                                            switch(c_name)
                                            {
                                                    case COND_NONE:
                                                    fprintf(out,"NONE ");
                                                    break;
                                                    case COND_EQ:
                                                    fprintf(out,"= ");
                                                    break;
                                                    case COND_NE:
                                                    fprintf(out,"<> ");
                                                    break;
                                                    case COND_LT:
                                                    fprintf(out,"< ");
                                                    break;
                                                    case COND_GT:
                                                    fprintf(out,"> ");
                                                    break;
                                                    case COND_LE:
                                                    fprintf(out,"<= ");
                                                    break;
                                                    case COND_GE:
                                                    fprintf(out,">= ");
                                                    break;
                                                    case COND_LIKE:
                                                    fprintf(out,"like ");
                                                    break;
                                           }
                                            fprintf(out,"%s ",get_name());
                                            break;
                                        case ARG_GROUP:
                                            fprintf(out,"group ");
                                            switch(c_group)
                                            {
                                                    case COND_NONE:
                                                    fprintf(out,"NONE ");
                                                    break;
                                                    case COND_EQ:
                                                    fprintf(out,"= ");
                                                    break;
                                                    case COND_NE:
                                                    fprintf(out,"<> ");
                                                    break;
                                                    case COND_LT:
                                                    fprintf(out,"< ");
                                                    break;
                                                    case COND_GT:
                                                    fprintf(out,"> ");
                                                    break;
                                                    case COND_LE:
                                                    fprintf(out,"<= ");
                                                    break;
                                                    case COND_GE:
                                                    fprintf(out,">= ");
                                                    break;
                                                    case COND_LIKE:
                                                    fprintf(out,"like ");
                                                    break;
                                           }
                                            fprintf(out,"%d ",group);
                                            break;
                                        case ARG_PHONE:
                                            fprintf(out,"phone ");
                                            switch(c_phone)
                                            {
                                                    case COND_NONE:
                                                    fprintf(out,"NONE ");
                                                    break;
                                                    case COND_EQ:
                                                    fprintf(out,"= ");
                                                    break;
                                                    case COND_NE:
                                                    fprintf(out,"<> ");
                                                    break;
                                                    case COND_LT:
                                                    fprintf(out,"< ");
                                                    break;
                                                    case COND_GT:
                                                    fprintf(out,"> ");
                                                    break;
                                                    case COND_LE:
                                                    fprintf(out,"<= ");
                                                    break;
                                                    case COND_GE:
                                                    fprintf(out,">= ");
                                                    break;
                                                    case COND_LIKE:
                                                    fprintf(out,"like ");
                                                    break;
                                           }
                                            fprintf(out,"%d ",phone);
                                            break;
                                        }
                                    }


                                }
                                fprintf(out,";\n");
                                break;
				case CMD_SELECT:
                                fprintf(out,"select ");
                                switch(take1)
                                {
                                    case TAKE_ALL:
                                    fprintf(out,"* ");
                                    break;
                                    case TAKE_NONE:
                                    break;
                                    case TAKE_PHONE:
                                    fprintf(out,"phone ");
                                    break;
                                    case TAKE_GROUP:
                                    fprintf(out,"group ");
                                    break;
                                    case TAKE_NAME:
                                    fprintf(out,"name ");
                                    break;
                                }
                                switch(take2)
                                {
                                    case TAKE_ALL:
                                    fprintf(out,"* ");
                                    break;
                                    case TAKE_NONE:
                                    break;
                                    case TAKE_PHONE:
                                    fprintf(out,",phone ");
                                    break;
                                    case TAKE_GROUP:
                                    fprintf(out,",group ");
                                    break;
                                    case TAKE_NAME:
                                    fprintf(out,",name ");
                                    break;
                                }
                                if(arg1!=ARG_NONE)
                                {
                                    fprintf(out,"where ");
                                    switch(arg1)
                                    {
                                    case ARG_NONE:
                                        fprintf(out,"NONE ");
                                        break;
                                    case ARG_NAME:
                                        fprintf(out,"name ");
                                        switch(c_name)
                                        {
                                                case COND_NONE:
                                                fprintf(out,"NONE ");
                                                break;
                                                case COND_EQ:
                                                fprintf(out,"= ");
                                                break;
                                                case COND_NE:
                                                fprintf(out,"<> ");
                                                break;
                                                case COND_LT:
                                                fprintf(out,"< ");
                                                break;
                                                case COND_GT:
                                                fprintf(out,"> ");
                                                break;
                                                case COND_LE:
                                                fprintf(out,"<= ");
                                                break;
                                                case COND_GE:
                                                fprintf(out,">= ");
                                                break;
                                                case COND_LIKE:
                                                fprintf(out,"like ");
                                                break;
                                       }
                                        fprintf(out,"%s ",get_name());
                                        break;
                                    case ARG_GROUP:
                                        fprintf(out,"group ");
                                        switch(c_group)
                                        {
                                                case COND_NONE:
                                                fprintf(out,"NONE ");
                                                break;
                                                case COND_EQ:
                                                fprintf(out,"= ");
                                                break;
                                                case COND_NE:
                                                fprintf(out,"<> ");
                                                break;
                                                case COND_LT:
                                                fprintf(out,"< ");
                                                break;
                                                case COND_GT:
                                                fprintf(out,"> ");
                                                break;
                                                case COND_LE:
                                                fprintf(out,"<= ");
                                                break;
                                                case COND_GE:
                                                fprintf(out,">= ");
                                                break;
                                                case COND_LIKE:
                                                fprintf(out,"like ");
                                                break;
                                       }
                                        fprintf(out,"%d ",group);
                                        break;
                                    case ARG_PHONE:
                                        fprintf(out,"phone ");
                                        switch(c_phone)
                                        {
                                                case COND_NONE:
                                                fprintf(out,"NONE ");
                                                break;
                                                case COND_EQ:
                                                fprintf(out,"= ");
                                                break;
                                                case COND_NE:
                                                fprintf(out,"<> ");
                                                break;
                                                case COND_LT:
                                                fprintf(out,"< ");
                                                break;
                                                case COND_GT:
                                                fprintf(out,"> ");
                                                break;
                                                case COND_LE:
                                                fprintf(out,"<= ");
                                                break;
                                                case COND_GE:
                                                fprintf(out,">= ");
                                                break;
                                                case COND_LIKE:
                                                fprintf(out,"like ");
                                                break;
                                       }
                                        fprintf(out,"%d ",phone);
                                        break;
                                    }
                                    if(oper!=OP_NONE && arg2!=ARG_NONE)
                                    {
                                        switch(oper)
                                        {
                                          case OP_OR:
                                            fprintf(out,"or ");
                                            break;
                                        case OP_AND:
                                            fprintf(out,"and ");
                                            break;
                                        case OP_NONE:
                                            fprintf(out,"NONE ");
                                            break;
                                        }
                                        switch(arg2)
                                        {
                                        case ARG_NONE:
                                            fprintf(out,"NONE ");
                                            break;
                                        case ARG_NAME:
                                            fprintf(out,"name ");
                                            switch(c_name)
                                            {
                                                    case COND_NONE:
                                                    fprintf(out,"NONE ");
                                                    break;
                                                    case COND_EQ:
                                                    fprintf(out,"= ");
                                                    break;
                                                    case COND_NE:
                                                    fprintf(out,"<> ");
                                                    break;
                                                    case COND_LT:
                                                    fprintf(out,"< ");
                                                    break;
                                                    case COND_GT:
                                                    fprintf(out,"> ");
                                                    break;
                                                    case COND_LE:
                                                    fprintf(out,"<= ");
                                                    break;
                                                    case COND_GE:
                                                    fprintf(out,">= ");
                                                    break;
                                                    case COND_LIKE:
                                                    fprintf(out,"like ");
                                                    break;
                                           }
                                            fprintf(out,"%s ",get_name());
                                            break;
                                        case ARG_GROUP:
                                            fprintf(out,"group ");
                                            switch(c_group)
                                            {
                                                    case COND_NONE:
                                                    fprintf(out,"NONE ");
                                                    break;
                                                    case COND_EQ:
                                                    fprintf(out,"= ");
                                                    break;
                                                    case COND_NE:
                                                    fprintf(out,"<> ");
                                                    break;
                                                    case COND_LT:
                                                    fprintf(out,"< ");
                                                    break;
                                                    case COND_GT:
                                                    fprintf(out,"> ");
                                                    break;
                                                    case COND_LE:
                                                    fprintf(out,"<= ");
                                                    break;
                                                    case COND_GE:
                                                    fprintf(out,">= ");
                                                    break;
                                                    case COND_LIKE:
                                                    fprintf(out,"like ");
                                                    break;
                                           }
                                            fprintf(out,"%d ",group);
                                            break;
                                        case ARG_PHONE:
                                            fprintf(out,"phone ");
                                            switch(c_phone)
                                            {
                                                    case COND_NONE:
                                                    fprintf(out,"NONE ");
                                                    break;
                                                    case COND_EQ:
                                                    fprintf(out,"= ");
                                                    break;
                                                    case COND_NE:
                                                    fprintf(out,"<> ");
                                                    break;
                                                    case COND_LT:
                                                    fprintf(out,"< ");
                                                    break;
                                                    case COND_GT:
                                                    fprintf(out,"> ");
                                                    break;
                                                    case COND_LE:
                                                    fprintf(out,"<= ");
                                                    break;
                                                    case COND_GE:
                                                    fprintf(out,">= ");
                                                    break;
                                                    case COND_LIKE:
                                                    fprintf(out,"like ");
                                                    break;
                                           }
                                            fprintf(out,"%d ",phone);
                                            break;
                                        }
                                    }


                                }
                                fprintf(out,";\n");
				break;
			}
		}
		
                void printable(FILE * out=stdout)
		{
                    //printf("\n");
                 fprintf(out,"%20s ",get_name());
                 fprintf(out,"%20d ",phone);
                 fprintf(out,"%20d ",group);
                 switch(type)
                 {
                         case CMD_NONE:
                         fprintf(out,"|  NONE  |");
                         break;
                         case CMD_QUIT:
                         fprintf(out,"|  quit  |");
                         break;
                         case CMD_STOP:
                         fprintf(out,"|  stop  |");
                         break;
                         case CMD_INSERT:
                         fprintf(out,"| insert |");
                         break;
                         case CMD_DELETE:
                         fprintf(out,"| delete |");
                         break;
                         case CMD_SELECT:
                         fprintf(out,"| select |");
                         break;
		}
                 switch(c_name)
                 {
                         case COND_NONE:
                         fprintf(out,"| NONE |");
                         break;
                         case COND_EQ:
                         fprintf(out,"|   =  |");
                         break;
                         case COND_NE:
                         fprintf(out,"|  <>  |");
                         break;
                         case COND_LT:
                         fprintf(out,"|  <   |");
                         break;
                         case COND_GT:
                         fprintf(out,"|  >   |");
                         break;
                         case COND_LE:
                         fprintf(out,"|  <=  |");
                         break;
                         case COND_GE:
                         fprintf(out,"|  >=  |");
                         break;
                         case COND_LIKE:
                         fprintf(out,"| like |");
                         break;
                }
                 switch(c_phone)
                 {
                         case COND_NONE:
                         fprintf(out,"| NONE |");
                         break;
                         case COND_EQ:
                         fprintf(out,"|   =  |");
                         break;
                         case COND_NE:
                         fprintf(out,"|  <>  |");
                         break;
                         case COND_LT:
                         fprintf(out,"|  <   |");
                         break;
                         case COND_GT:
                         fprintf(out,"|  >   |");
                         break;
                         case COND_LE:
                         fprintf(out,"|  <=  |");
                         break;
                         case COND_GE:
                         fprintf(out,"|  >=  |");
                         break;
                         case COND_LIKE:
                         fprintf(out,"| like |");
                         break;
                }
                 switch(c_group)
                 {
                         case COND_NONE:
                         fprintf(out,"| NONE |");
                         break;
                         case COND_EQ:
                         fprintf(out,"|   =  |");
                         break;
                         case COND_NE:
                         fprintf(out,"|  <>  |");
                         break;
                         case COND_LT:
                         fprintf(out,"|   <  |");
                         break;
                         case COND_GT:
                         fprintf(out,"|   >  |");
                         break;
                         case COND_LE:
                         fprintf(out,"|  <=  |");
                         break;
                         case COND_GE:
                         fprintf(out,"|  >=  |");
                         break;
                         case COND_LIKE:
                         fprintf(out,"| like |");
                         break;
                }
                 switch(oper)
                 {
                 case OP_NONE:
                 fprintf(out,"| NONE |");
                 break;
                 case OP_AND:
                 fprintf(out,"| and  |");
                 break;
                 case OP_OR:
                 fprintf(out,"|  or  |");
                 break;
                 }
                 fprintf(out,"\n");
                }

            
};


#endif // COMMAND_H


#ifndef LIST_NODE_H
#define LIST_NODE_H
class list_node: public record
{
private:
    list_node *next=0;
    list_node *prev=0;
    list_node *fly=0;
public:
    friend class list;
    friend class tree;
    friend class node;
    friend class database;
    friend class hash_node;
    friend class hash;
    friend class uptree;
    friend class upnode;
    list_node * get_next() const
    { return next;}
    list_node * get_prev() const
    { return prev;}
    void set_next(list_node * next)
    {this->next=next;}
    void set_prev(list_node * prev)
    {this->prev=prev;}
};
#endif

#ifndef HASH_NODE_H
#define HASH_NODE_H
class hash_node
{
	private:
	hash_node *next=0;
	hash_node *prev=0;
	list_node *gg=0; 
	public:
	friend class hash;
	friend class database;
	friend class tree;
	friend class uptree;
	hash_node * getnext()
	{return next;}
	hash_node * getprev()
	{return prev;}
	list_node * getlistnode()
	{return gg;}
	~hash_node()
	{}
};

#endif //HASH-NODE-H



#ifndef HASH_H
#define HASH_H
class hash
{
	private:
	hash_node **array=0;
	int hashbase=0;
	public:
	friend class database;
	void setbase(int n)
	{
		int i;
		hashbase=n;
		array=new hash_node *[hashbase];
		for(i=0;i<hashbase;i++) array[i]=0;
	}
	void deletehash()
	{
		hash_node *u,*g;
		for(int i=0;i<hashbase;i++)
		{
			u=array[i];
			while(u)
			{
				g=u;
				u=u->next;
				delete g;
			}
		}
		delete[] array;
	}
	
	~hash()
	{
	deletehash();	
	}
	
	void print()
	{
		hash_node *u;
		int j;
		for(int i=0;i<hashbase;i++)
		{
			u=array[i];
			if(array[i]){ printf(" %d ",i);
			j=0;
			while(u)
			{
				printf("//// %s   %d   %d ",u->gg->get_name(),u->gg->get_phone(),u->gg->get_group());
				u=u->next;
				j++;
				if(j==5) break;
			}
			}
			if(array[i]) printf("\n");
		}
	}
	#ifdef ZACHET
	int hashmodule(int i)
	{
		return i%hashbase;
	}
#else
	int hashmodule(int i)
	{
		int j=0;
		while(i!=0)
		{
			j+=i%10;
			i/=10;
		}
		j=j%hashbase;
		return j;
	}
#endif
	hash_node* hashinit(list_node * tt)
	{
		int j=0;
		j=hashmodule(tt->get_phone());
		hash_node * h;
		h=new hash_node;
		h->gg=tt;
		if(array[j]) 
		{
			hash_node * p;
			p=array[j]->next;
			array[j]->next=h;
			h->prev=array[j];
			if(p) p->prev=h;
			h->next=p;
			return h;
		}
		else
		{
			array[j]=h;
			return array[j];
		}
	}
	
	void deletehashnode(hash_node *k)
	{
		int j=0;
		if(k)
		{
			hash_node *pre , *nex;
			pre=k->prev;
			nex=k->next;
			if(pre)
			{
			pre->next=nex;
			if(nex)
			nex->prev=pre;
			}
			else
			{
				j=hashmodule(k->gg->get_phone());
				
				if(!k->next)
				array[j]=0;
				else
				{
				array[j]=nex;
			    array[j]->prev=0;
				}
			}
			k->gg=0;
			delete k;
		 }
	}
};

#endif //HASH-H

#ifndef NODE_H
#define NODE_H


class node
{
private:
	unsigned char height=0;
	node* left=0;
	node* right=0;
	hash_node *gpk=0;
	node *blef=0;
public:
	node()=default;
	friend class tree;
	friend class uptree;
    friend class list;
    friend class list_node;
    friend class database;
    ~node()
    {height=0;  blef=0; left=0; right=0;}
	node * get_left() const
    {return left;}
     node * get_right() const
    {return right;}
    void set_right (node* right)
        {this -> right = right;}
    void set_left (node* left)
        {this -> left = left;}
        
   
};

#endif // TREE_NODE_H

#ifndef TREE_H
#define TREE_H

class tree
{
private:
    node *root=0;
    node *current=0;
public:
    friend class list;
    friend class database;
	void delete_tree(node * rr)
	{  
		if(!rr) return;
		delete_tree(rr->left);
		delete_tree(rr->right);
                node *p;
                while(rr)
                {
                p=rr;
                rr=rr->blef;
                p->gpk=0;
                delete p;
                }
	}
	void del_root()
	{
		root=0;
	}
	node * get_root()
	{ return root;}
	void set_root(node * gg)
	{ root=gg;}

    void print(node * rr,int k)
    {
	int i;
        if(rr)
        {
			node * u;
			u=rr;
			while(rr)
			{
			printf("%s %d ///////",((rr->gpk)->gg)->get_name(),balenciaga(rr));
			rr=rr->blef;
			}
			printf("\n");
			rr=u;
		}
    else return;
    k++;
    if(rr->left&&k<5)
    {
	for(i=k;i>0;i--)
        printf(" L ");
	print(rr->left,k);
	}
        if(rr->right&&k<5)
	{
	for(i=k;i>0;i--)
        printf(" R ");
	print(rr->right,k);	
	}
    }
	
    ~tree()
    {   
		delete_tree(root);
	}
   
unsigned char height(node* p)
{
    if(p) return p->height;
	return 0;
}

int balenciaga(node* p)
{
	return height(p->right)-height(p->left);
}

void newheight(node* p)
{
	unsigned char l = height(p->left);
	unsigned char r = height(p->right);
	if(l>r) p->height=l+1;
	else p->height=r+1;
}

node* rotateright(node* p) 
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	newheight(p);
	newheight(q);
	return q;
}

node* rotateleft(node* q) 
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	newheight(q);
	newheight(p);
	return p;
}

node* balance(node* p) 
{
	newheight(p);
	if( balenciaga(p)==2 )
	{
		if( balenciaga(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( balenciaga(p)==-2 )
	{
		if( balenciaga(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; 
}

node * nodefind(const char * buf,node * rr)
{
	if(!rr) return 0;
	if(strcmp(buf,(rr->gpk->gg)->get_name())==0)
        {
	return rr;
        }
	node *p;
        if(strcmp(buf,(rr->gpk->gg)->get_name())>0)
	{
                p=nodefind(buf,rr->right);
	}
	else
	{
                p=nodefind(buf,rr->left);
	}
	return p;
}


int treecheck(node * rr,const char * buf ,int ph, int gr)
{
	node * f;
        
        f=nodefind(buf,rr);
        if(!f) return 1;
	while(f)
	{
		if(strcmp((f->gpk->gg)->get_name(),buf)==0 && (f->gpk->gg)->phone==ph && (f->gpk->gg)->group==gr)
		return -1;
		f=f->blef;
	}
        return 1;
}

node* insert(node* p, hash_node *rr) 
{   
	if( !p )
	{ 
		node *k;
		k= new node;
		k->gpk=rr;
		k->height=1;
		return k;
	}
	if(strcmp((p->gpk->gg)->get_name(),rr->gg->get_name())==0)
	{
		node *k;
		k= new node;
		k->gpk=rr;
		k->blef=p->blef;
		p->blef=k;
		return p;
	}
	if(strcmp((p->gpk->gg)->get_name(),rr->gg->get_name())>0 )
	{
                p->left=insert(p->left,rr);
	}
	else
	{
                p->right=insert(p->right,rr);
	}
	return balance(p);
}


node * findopt(node * rr)
{
    node *p;
    if(rr->left)
    {
    rr=rr->left;
    p=rr;
    while(rr)
    {
		p=rr;
		rr=rr->right;
	}
	rr=p;
	}
    else
    {
    rr=rr->right;
    while(rr)
    {
		p=rr;
		rr=rr->left;
	}
	}
    return p;
}

node * delete_opt(node *rr,node *opt)
{
	//printf("kek\n");
	//printf("now here %s\n",(rr)->gg->get_name());
    if(rr->right)
    if(strcmp((rr->right)->gpk->gg->get_name(),opt->gpk->gg->get_name())==0)
        { //printf("wanna delete %s\n",(rr->right)->gg->get_name());
        // rr->right->gg=0;
         node * x;
         x=rr->right;
         if(x->right || x->left)
         {
			 if(x->right)
			 {
				 x->gpk=x->right->gpk;
				 x->right->gpk=0;
				 x->blef=x->right->blef;
				 x->height=1;
				 delete(x->right);
				 x->right=0;
				 return balance(rr);
			 }
			 else
			 {
				  x->gpk=x->left->gpk;
				  x->left->gpk=0;
				  x->blef=x->left->blef;
				  x->height=1;
				  delete(x->left);
				  x->left=0;
				  return balance(rr);
			 }
		 }
		 else
		 {
			 rr->right->gpk=0;
         delete rr->right;
         rr->right=0;
         return balance(rr);
         }
        }
    if(rr->left)
    if(strcmp((rr->left)->gpk->gg->get_name(),opt->gpk->gg->get_name())==0)
         {
		 // printf("wanna delete %s\n",(rr->left)->gg->get_name());
		  node * x;
         x=rr->left;
          if(x->right || x->left)
         {
			 if(x->right)
			 {
				 x->gpk=x->right->gpk;
				 x->right->gpk=0;
				 x->blef=x->right->blef;
				 x->height=1;
				 delete(x->right);
				 x->right=0;
				 return balance(rr);
			 }
			 else
			 {
				  x->gpk=x->left->gpk;
				  x->left->gpk=0;
				 x->blef=x->left->blef;
				  x->height=1;
				  delete(x->left);
				  x->left=0;
				  return balance(rr);
			 }
		 }
		 else
		 {
			 rr->left->gpk=0;
          delete rr->left;
          rr->left=0;
       //   printf("flag2\n");
          return balance(rr);}
          }

    if(strcmp(rr->gpk->gg->get_name(),opt->gpk->gg->get_name())<0)
    {
    rr->right=delete_opt(rr->right,opt);
	}
    else
    {
    rr->left=delete_opt(rr->left,opt);
	}

    return balance(rr);
}


 void delete_from_tree(node * rr,list_node *pp,hash &c)
	 {
							
			 if(!rr) return;
                             
			 if(strcmp(rr->gpk->gg->get_name(),pp->get_name())==0)
			 {
				 if(rr->gpk->gg->get_phone()==pp->get_phone() && rr->gpk->gg->get_group()==pp->get_group())
				 {
					  if(!rr->blef)
					  {
						  if(!rr->left && !rr->right)
						  { 
							  if(rr==get_root())
							  { 
								  c.deletehashnode(rr->gpk);
								  delete rr;
								  set_root(nullptr);
								  return;
							  }		
							     hash_node * fan;
							     fan=rr->gpk;
							     set_root(delete_opt(get_root(),rr));
							     c.deletehashnode(fan);	 
								 return;
						  }
							  node *k;
							  hash_node *uu;
                              hash_node * fan;
							     fan=rr->gpk;               
							  k=findopt(rr);
							  rr->blef=k->blef;
							  k->blef=0;
							  uu=k->gpk;
							  set_root(delete_opt(get_root(),k));
							  c.deletehashnode(fan);
							  rr->gpk=uu;
							  return;
					 }
					  else
					  {
					   node *ll;
					   hash_node *uu;
					   c.deletehashnode(rr->gpk);
					   ll=rr->blef;
					   uu=ll->gpk;
					   ll->gpk=rr->gpk;
					   rr->gpk=uu;
					   rr->blef=ll->blef;
					   ll->gpk=0;
					   ll->blef=0;
					   delete ll;
					   return;
					  }
					 }

						if(rr->blef)
						{
					     node *p;
						 p=rr;
						 rr=rr->blef;
						while(rr)
						{
										
					   if(rr->gpk->gg->get_phone()==pp->get_phone() && rr->gpk->gg->get_group()==pp->get_group())
					   {      
						   p->blef=rr->blef;
						   c.deletehashnode(rr->gpk);
						   rr->gpk=0;
						   rr->blef=0;
						   delete rr;
						   return;
					   }
						   p=rr;
						   rr=rr->blef;
						}
							return;
						}
							else return;
								}
                                 
                                
                             if(strcmp(rr->gpk->gg->get_name(),pp->get_name())<0)
                                 {
                                    delete_from_tree(rr->right,pp,c);
                                 }
                             else
                                 {
                                     delete_from_tree(rr->left,pp,c);
                                 }
                         }


};
#endif // TREE_H

#ifndef LIST_H
#define LIST_H

class list
{
private:
    list_node *head=0;
    list_node *current=0;
    friend class tree;
    friend class database;
    friend class uptree;
    friend class upnode;
public:
    void delete_list()
    {
		if(!head) return;
		current=head;
		while(head)
		{
				current=head;
				head=head->next;
				delete current;
		}
    }
   
		void print(FILE *out=stdout)
		{
			int p=0;
			if(!head) return;
			current=head;
			while(current)
			{
					current->print(out);
					current=current->next;
					p++;
					if(p==10) break;
			}
		}
		
		list_node* get_head()
		{
			if(head)
                return head;
                return nullptr;
        }
        
    ~list()
    {
                delete_list();
        }
        
    bool del_next()
    {
                if(!(current->next))
                return false;
                list_node *r;
                r=current->next;
                current->next=r->next;
                delete r;
                return true;
        }
		bool del_prev()
		{
                if(!(current->prev))
                return false;
                list_node *r;
                r=current->prev;
                current->prev=r->prev;
                delete r;
                return true;
        }
        bool del_head()
        {
                if(!head) return false;
                list_node *r;
                r=head->next;
                delete head;
                head=r;
                return true;
        }
		void go_next()
		{
            if(current)
            current=current->next;
        }
		void go_prev()
		{
            if(current)
            current=current->prev;
        }
        void set_head(list_node *h)
        {
            if(!head)
            head=h;
        }
        

        int insert(const char *string,int phone, int group)
        {
            if(!head)
            {
                list_node *p;
                p=new list_node;
                p->init(string,phone,group);
                head=p;
                return 1;
            }
            list_node *p;
            p=new list_node;
            p->init(string,phone,group);
            p->next=head;
            head->prev=p;
            head=p;
            return 1;
        }                     
};
#endif


#ifndef UPNODE_H
#define UPNODE_H


class upnode
{
private:
	unsigned char height=0;
	int group=0;
	upnode* left=0;
	upnode* right=0;
	tree tr;
	hash has;
public:
	upnode()=default;
	friend class tree;
	friend class uptree;
        friend class list;
    friend class list_node;
    friend class database;
    ~upnode()
    {  group=0; height=0;}
	upnode * get_left() const
    {return left;}
     upnode * get_right() const
    {return right;}
    void set_right (upnode* right)
        {this -> right = right;}
    void set_left (upnode* left)
        {this -> left = left;}
    int get_group()
    { return group;}    
   
};

#endif // TREE_NODE_H

#ifndef UPTREE_H
#define UPTREE_H

class uptree
{
private:
    upnode *root=0;
    upnode *current=0;
    int base=0;
public:
    friend class list;
    friend class database;
    void setbase(int n)
    {
		base=n;
	}
	void delete_tree(upnode * rr)
	{  
		if(!rr) return;
		delete_tree(rr->left);
		delete_tree(rr->right);
		if(rr==root) root=0;
        delete rr;
	}
	void del_root()
	{
		root=0;
	}
	upnode * get_root()
	{ return root;}
	void set_root(upnode * gg)
	{ root=gg;}

    void print(upnode * rr,int k)
    {
			int i;
        if(rr)
        {   printf("%d ",rr->group);
			if(rr->tr.get_root())
			printf("   %s %d ///////",rr->tr.get_root()->gpk->gg->get_name(),balenciaga(rr));
			printf("........\n");
			rr->tr.print(rr->tr.get_root(),0);
			printf("........\n");
			rr->has.print();
			
			printf("\n");
		}
		else return;
		k++;
		if(rr->left&&k<5)
		{
		for(i=k;i>0;i--)
			printf(" L ");
		print(rr->left,k);
		}
			if(rr->right&&k<5)
		{
		for(i=k;i>0;i--)
			printf(" R ");
		print(rr->right,k);	
		}
    }
	
    ~uptree()
    {   
		delete_tree(root);
	}
   
unsigned char height(upnode* p)
{
    if(p) return p->height;
	return 0;
}

int balenciaga(upnode* p)
{
	return height(p->right)-height(p->left);
}

void newheight(upnode* p)
{
	unsigned char l = height(p->left);
	unsigned char r = height(p->right);
	if(l>r) p->height=l+1;
	else p->height=r+1;
}

upnode* rotateright(upnode* p) 
{
	upnode* q = p->left;
	p->left = q->right;
	q->right = p;
	newheight(p);
	newheight(q);
	return q;
}

upnode* rotateleft(upnode* q) 
{
	upnode* p = q->right;
	q->right = p->left;
	p->left = q;
	newheight(q);
	newheight(p);
	return p;
}

upnode* balance(upnode* p) 
{
	newheight(p);
	if( balenciaga(p)==2 )
	{
		if( balenciaga(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( balenciaga(p)==-2 )
	{
		if( balenciaga(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; 
}

upnode * nodefind(int gr,upnode * rr)
{
	if(!rr){ return 0;}
	if(gr==rr->get_group())
	{  
			return rr;
	}
	upnode *p;
    if(gr > rr->get_group())
	{
			p=nodefind(gr,rr->right);
	}
	else
	{
			p=nodefind(gr,rr->left);
	}
	return p;
}
/*
void tree_list(upnode *rr,list_node * hh)
{
    upnode * f,*t;
    int i=1;
    f=nodefind(hh->get_group(),rr,i);
    t=new upnode;
    t->gg=hh;
    t->blef=f->blef;
    f->blef=t;
}
*/
int treecheck(const char * buf ,int ph, int gr)
{
	if(!root) return 1;
	upnode * f;
        f=nodefind(gr,root);
        
        if(!f)
        return 1;

      return  f->tr.treecheck(f->tr.get_root(),buf,ph,gr);    
}

upnode* insert(upnode* p, list_node *rr) 
{
	
	if( !p )
	{ 
		upnode *k;
		k= new upnode;
		k->group=rr->get_group();
		k->height=1;
		hash_node *jok;
		k->has.setbase(base);
		jok=k->has.hashinit(rr);
		k->tr.set_root(k->tr.insert(k->tr.get_root(),jok));
		return k;
	}
	
	if(p->group == rr->get_group())
	{
		hash_node *jok;
		jok=p->has.hashinit(rr);
		p->tr.set_root(p->tr.insert(p->tr.get_root(),jok));
		return p;
	}
	if(p->group > rr->get_group())
	{
                p->left=insert(p->left,rr);
	}
	else
	{
                p->right=insert(p->right,rr);
	}
	return balance(p);
}


upnode * findopt(upnode * rr)
{
    upnode *p;
    if(rr->left)
    {
    rr=rr->left;
    p=rr;
    while(rr)
    {
		p=rr;
		rr=rr->right;
	}
	rr=p;
	}
    else
    {
    rr=rr->right;
    while(rr)
    {
		p=rr;
		rr=rr->left;
	}
	}
    return p;
}

};
#endif // UPTREE_H
