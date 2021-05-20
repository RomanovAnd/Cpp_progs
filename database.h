#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include <time.h>
#include "Printf.h"
#define KLEN 800
#ifndef DATABASE_H
#define DATABASE_H
class database
{
	private:
	list lis;
	tree a;
	hash c;
	uptree b;
	list_node *stack=0;
	int filedescr=0;
	public:
        void initi(int n1,int n2)
        {
		c.setbase(n1);
		b.setbase(n2);
	}
	void print_tree()
	{
		a.print(a.get_root(),0);
	}
	
	void print_list()
	{
		lis.print();
	}
	
	void print_hash()
	{
		c.print();
	}
	void print_grtr()
	{
		b.print(b.get_root(),0);
	}
	void set_fd(int p)
	{
		filedescr = p;
	}
	void docommand(command &x, int qwer)
	{
		set_fd(qwer);
		switch (x.type)
		{
		case CMD_NONE:
			break;
		case CMD_STOP:
			break;
		case CMD_DELETE:
			delete_some(x);
			break;
		case CMD_INSERT:
			int i;
			i = b.treecheck(x.get_name(), x.phone, x.group);
			if (i > 0)
			{
				lis.insert(x.get_name(), x.phone, x.group);
				hash_node *zxc;
				zxc = c.hashinit(lis.get_head());
				a.set_root(a.insert(a.get_root(), zxc));
				b.set_root(b.insert(b.get_root(), lis.get_head()));
			}
			break;
		case CMD_SELECT:
			select(x);
			break;
		case CMD_QUIT:
			break;
		}
	}

	void select(command &x)
	{
		int p = 0, g = 0;
		switch (x.arg1)
		{
		case ARG_NONE:
			list_node *rr;
			rr = lis.get_head();
			while (rr)
			{
                     switch(x.take1)
                     {
                         case TAKE_ALL:   Printf(filedescr,"%s %d %d",rr->get_name(),rr->phone,rr->group); break;
                         case TAKE_GROUP: Printf(filedescr,"%d ",rr->group); break;
                         case TAKE_PHONE: Printf(filedescr,"%d ",rr->phone); break;
                         case TAKE_NAME:  Printf(filedescr,"%s ",rr->get_name()); break;
                         case TAKE_NONE: break;
                     }
                     switch(x.take2)
                     {
                        case TAKE_ALL: break;
                         case TAKE_GROUP: Printf(filedescr,"%d \n",rr->group); break;
                         case TAKE_PHONE: Printf(filedescr,"%d \n",rr->phone); break;
                         case TAKE_NAME:  Printf(filedescr,"%s \n",rr->get_name()); break;
                         case TAKE_NONE:  Printf(filedescr,"\n"); break;
                     }
                             rr=rr->next;
                             }
                             return;
                             break;
			case ARG_GROUP:
				switch(x.c_group)
				{
					case COND_NONE: break;
					case COND_EQ: p=1; break;  //=
					case COND_NE: p=2; break;  //<>
					case COND_LT: p=3; break; //<
					case COND_GT: p=4; break;  //>
					case COND_LE: p=5; break;  //<=
					case COND_GE: p=6; break;  //>=
					case COND_LIKE: p=7; break;
				}
				break;
			case ARG_PHONE:
				switch(x.c_phone)
				{
					case COND_NONE: break;
					case COND_EQ: p=8; break;  //=
					case COND_NE: p=9; break;  //<>
					case COND_LT: p=10; break; //<
					case COND_GT: p=11; break;  //>
					case COND_LE: p=12; break;  //<=
					case COND_GE: p=13; break;  //>=
					case COND_LIKE: p=14; break;
				}
				break;
			case ARG_NAME:
				switch(x.c_name)
				{
					case COND_NONE: break;
					case COND_EQ: p=15; break;  //=
					case COND_NE: p=16; break;  //<>
					case COND_LT: p=17; break; //<
					case COND_GT: p=18; break;  //>
					case COND_LE: p=19; break;  //<=
					case COND_GE: p=20; break;  //>=
					case COND_LIKE: p=21; break;
				}
				break;	
			}
			 switch(x.arg2)
			 {
			case ARG_NONE: break;
			case ARG_GROUP:
				switch(x.c_group)
				{
					case COND_NONE: break;
					case COND_EQ: g=1; break;  //=
					case COND_NE: g=2; break;  //<>
					case COND_LT: g=3; break; //<
					case COND_GT: g=4; break;  //>
					case COND_LE: g=5; break;  //<=
					case COND_GE: g=6; break;  //>=
					case COND_LIKE: g=7; break;
				}
				break;
			case ARG_PHONE:
				switch(x.c_phone)
				{
					case COND_NONE: break;
					case COND_EQ: g=8; break;  //=
					case COND_NE: g=9; break;  //<>
					case COND_LT: g=10; break; //<
					case COND_GT: g=11; break;  //>
					case COND_LE: g=12; break;  //<=
					case COND_GE: g=13; break;  //>=
					case COND_LIKE: g=14; break;
				}
				break;
			case ARG_NAME:
				switch(x.c_name)
				{
					case COND_NONE: break;
					case COND_EQ: g=15; break;  //=
					case COND_NE: g=16; break;  //<>
					case COND_LT: g=17; break; //<
					case COND_GT: g=18; break;  //>
					case COND_LE: g=19; break;  //<=
					case COND_GE: g=20; break;  //>=
					case COND_LIKE: g=21; break;
				}
				break;	
			}
			switch(x.oper)
			{
				case OP_AND: select_and(x,p,g); break; 
				case OP_OR: select_or(x,p,g); break;
				case OP_NONE: select_none(x,p); break;
			}
		 }
		 
		  int read(FILE *fp)
          {
            //int ret;
            lis.delete_list();
            //list_node *next,*prev=nullptr;
            int ph,gr,i;
            char buf[KLEN];
            while(fscanf(fp,"%s%d%d",buf,&ph,&gr))
            {
			   if(feof(fp)) return 1;
			   i=b.treecheck(buf,ph,gr);
			   if(i>0)
			   {
					   lis.insert(buf,ph,gr);
					   hash_node *jok;
					   jok=c.hashinit(lis.get_head());
					   a.set_root(a.insert(a.get_root(),jok));
					   b.set_root(b.insert(b.get_root(),lis.get_head())); 
			   }
            }
                    return 0;
          }
        
        
		 void addinstack(list_node * p)
		 {
			 if(!stack)
			 {
				 stack=p;
			 }
			 else
			 {
			 p->fly=stack;
			 stack=p;
			}
		 }
		 
		 void printstack(command &x)
		 {
			 if(stack)
			 {
				 list_node * k,*u;
				 k=stack;
				 while(k)
				 {
					 u=k;
					 switch(x.take1)
					{
					case TAKE_ALL:   Printf(filedescr,"%s %d %d",u->get_name(),u->phone,u->group);  break;
					case TAKE_GROUP: Printf(filedescr,"%d ",u->group); break;
					case TAKE_PHONE: Printf(filedescr,"%d ",u->phone); break;
					case TAKE_NAME:  Printf(filedescr,"%s ",u->get_name()); break;
					case TAKE_NONE: break;
					}
					switch(x.take2)
					{
					case TAKE_ALL: break;
					case TAKE_GROUP: Printf(filedescr,"%d \n",u->group); break;
					case TAKE_PHONE: Printf(filedescr,"%d \n",u->phone); break;
					case TAKE_NAME:  Printf(filedescr,"%s \n",u->get_name()); break;
					case TAKE_NONE:  Printf(filedescr,"\n"); break;
					}
					k=k->fly;
					u->fly=0;   	 
				 }
				 stack=0;
			 }
		 }
		 
		 void killstack()
		 {
			  if(stack)
			 {
				 list_node * k,*u;
				 k=stack;
				
				 while(k)
				 {
					u=k;
					k=k->fly;
					u->fly=0;
					a.delete_from_tree(a.get_root(),u,c);
					delete_from_group_tree(b.get_root(),u);
					delete_node(u);
				 }
				
				 stack=0;
				
			 }
		 }
		 
		 void delete_from_group_tree(upnode * rr,list_node * ww) // =
		 {
		   if(!rr) return;
		   if(rr->get_group()==ww->get_group() && rr->tr.get_root())
		   {
			  rr->tr.delete_from_tree(rr->tr.get_root(),ww,rr->has);
		   }
		   if( ww->get_group()  >  rr->get_group() )
			{
			   delete_from_group_tree(rr->right,ww);
			}
			 else
			{
		       delete_from_group_tree(rr->left,ww);
			}
		    return;
		 }
		 
		 int cmp(list_node * x,command &y,int s)
		 {
			 switch(s)
			 {
				case 0: return 1; break;
				case 8: if(x->phone == y.phone) return 1; else return -1;
				case 9: if(x->phone != y.phone) return 1; else return -1;
				case 10: if(x->phone < y.phone) return 1; else return -1;
				case 11: if(x->phone > y.phone) return 1; else return -1;
				case 12: if(x->phone <= y.phone) return 1; else return -1;
				case 13: if(x->phone >= y.phone) return 1; else return -1;
				
				case 1: if(x->group == y.group) return 1; else return -1;
				case 2: if(x->group != y.group) return 1; else return -1;
				case 3: if(x->group < y.group) return 1; else return -1;
				case 4: if(x->group > y.group) return 1; else return -1;
				case 5: if(x->group <= y.group) return 1; else return -1;
				case 6: if(x->group >= y.group) return 1; else return -1;
				
				case 15: if(strcmp(x->get_name(),y.get_name())==0) return 1; else return -1;
				case 16: if(strcmp(x->get_name(),y.get_name())!=0) return 1; else return -1;
				case 17: if(strcmp(x->get_name(),y.get_name())<0) return 1; else return -1;
				case 18: if(strcmp(x->get_name(),y.get_name())>0) return 1; else return -1;
				case 19: if(strcmp(x->get_name(),y.get_name())<=0) return 1; else return -1;
				case 20: if(strcmp(x->get_name(),y.get_name())>=0) return 1; else return -1;
				case 21: if(like(x->get_name(),y.get_name())>0) return 1; else return -1;
				case 22: if(like(x->get_name(),y.get_name())<=0) return 1; else return -1;
			 }
			 return 1;
		 }
		 void select_and(command &x,int p, int g)
		 {
			 list_node * rr;
			 rr=lis.get_head();
			 if(!rr) return;
			 if(p<8 || g<8)
			 {
				 if(p<8)
				 {
					 switch(p)
					 {
						 case 1:  upfind_1(b.get_root(),x,g); printstack(x); break; //=
						 case 2:  upfind_2(b.get_root(),x,g); printstack(x); break;
						 case 3:  upfind_3(b.get_root(),x,g); printstack(x); break; //<
						 case 4:  upfind_4(b.get_root(),x,g); printstack(x); break;  //>
						 case 5:  upfind_5(b.get_root(),x,g); printstack(x); break;  //<=
						 case 6:  upfind_6(b.get_root(),x,g); printstack(x); break;  //>= 
					 }
					 return;
				 }
				 else
				 {
					 switch(g)
					 {
						 case 1:  upfind_1(b.get_root(),x,p); printstack(x); break; //=
						 case 2:  upfind_2(b.get_root(),x,p); printstack(x); break;
						 case 3:  upfind_3(b.get_root(),x,p); printstack(x); break; //<
						 case 4:  upfind_4(b.get_root(),x,p); printstack(x); break;  //>
						 case 5:  upfind_5(b.get_root(),x,p); printstack(x); break;  //<=
						 case 6:  upfind_6(b.get_root(),x,p); printstack(x); break;  //>= 
					 }
					 return;
				 }
			  }
			 else
				 {
					 if(p>=15)
						 {
							 switch(p)
							 {
							 case 15: find_1(a.get_root(),x,g); printstack(x); break; //=
							 case 16: find_2(a.get_root(),x,g); printstack(x); break;
							 case 17: find_3(a.get_root(),x,g); printstack(x); break; //<
							 case 18: find_4(a.get_root(),x,g); printstack(x); break;  //>
							 case 19: find_5(a.get_root(),x,g); printstack(x); break;  //<=
							 case 20: find_6(a.get_root(),x,g); printstack(x); break;  //>=
							 case 21: find_7(a.get_root(),x,g); printstack(x); break;  //>=
							 }
							 return;
						 }
					 if(g>=15)
						 {
							 switch(g)
							 {
							 case 15: find_1(a.get_root(),x,p); printstack(x);  break; //=
							 case 16: find_2(a.get_root(),x,p); printstack(x); break;
							 case 17: find_3(a.get_root(),x,p); printstack(x); break; //<
							 case 18: find_4(a.get_root(),x,p); printstack(x); break;  //>
							 case 19: find_5(a.get_root(),x,p); printstack(x); break;  //<=
							 case 20: find_6(a.get_root(),x,p); printstack(x); break;  //>=
							 case 21: find_7(a.get_root(),x,p); printstack(x); break;  //>=
							 }
							 return;
						 }
					  if(p==8)
					  {
						  find_hash_eqv(x,g); printstack(x);
						  return;
					  }
					  else
					  {
						  find_hash_eqv(x,p); printstack(x);
						  return;
					  }

					 }
		 }
		 void select_or(command &x,int p, int g)
		 {
                    // printf("kk\n");
			 list_node * rr;
			 rr=lis.get_head();
			 if(!rr) return;
			 if(p<8 || g<8)
			 {
				 if(p<8)
				 {
					 switch(p)
					 {
						 case 1:  upfind_1(b.get_root(),x,reverse(g)); select_none(x,g);  printstack(x); break; //=
						 case 2:  upfind_2(b.get_root(),x,reverse(g)); select_none(x,g);  printstack(x); break;
						 case 3:  upfind_3(b.get_root(),x,reverse(g)); select_none(x,g);  printstack(x); break; //<
						 case 4:  upfind_4(b.get_root(),x,reverse(g)); select_none(x,g);  printstack(x); break;  //>
						 case 5:  upfind_5(b.get_root(),x,reverse(g)); select_none(x,g);  printstack(x); break;  //<=
						 case 6:  upfind_6(b.get_root(),x,reverse(g)); select_none(x,g);  printstack(x); break;  //>= 
					 }
					 return;
				 }
				 else
				 {
					 switch(g)
					 {
						 case 1:  upfind_1(b.get_root(),x,reverse(p)); select_none(x,p);  printstack(x); break; //=
						 case 2:  upfind_2(b.get_root(),x,reverse(p)); select_none(x,p);  printstack(x); break;
						 case 3:  upfind_3(b.get_root(),x,reverse(p)); select_none(x,p);  printstack(x); break; //<
						 case 4:  upfind_4(b.get_root(),x,reverse(p)); select_none(x,p);  printstack(x); break;  //>
						 case 5:  upfind_5(b.get_root(),x,reverse(p)); select_none(x,p);  printstack(x); break;  //<=
						 case 6:  upfind_6(b.get_root(),x,reverse(p)); select_none(x,p);  printstack(x); break;  //>= 
					 }
					 return;
				 }
			  }
			else
			{
				if(p==8)
                {
					  find_hash_eqv(x,reverse(g));
					  select_none(x,g);
					  return;
				}
			    else
			    {
					  find_hash_eqv(x,reverse(p));
					  select_none(x,p);
					  return;
			    }
				if(p>=15)
				{
					 switch(p)
					 {
					 case 15: find_1(a.get_root(),x,reverse(g));
					 select_none(x,g);
					 break; //=
					 case 16: find_2(a.get_root(),x,reverse(g));
					 select_none(x,g); 
					 break;
					 case 17: find_3(a.get_root(),x,reverse(g));
					 select_none(x,g); 
					 break; //<
					 case 18: find_4(a.get_root(),x,reverse(g));
					 select_none(x,g);
					 break;  //>
					 case 19: find_5(a.get_root(),x,reverse(g));
					 select_none(x,g);
					 break;  //<=
					 case 20: find_6(a.get_root(),x,reverse(g));
					 select_none(x,g);
					 break;  //>=
					 case 21: find_7(a.get_root(),x,reverse(g));
					 select_none(x,g);
					 break;  //>=
					 }
					return;
				}
				if(g>=15)
				{
					 switch(g)
					 {
					 case 15: find_1(a.get_root(),x,reverse(p));
					 select_none(x,p);
					 break; //=
					 case 16: find_2(a.get_root(),x,reverse(p));
					 select_none(x,p);
					 break;
					 case 17: find_3(a.get_root(),x,reverse(p));
					 select_none(x,p); 
					 break; //<
					 case 18: find_4(a.get_root(),x,reverse(p));
					 select_none(x,p);
					 break;  //>
					 case 19: find_5(a.get_root(),x,reverse(p));
					 select_none(x,p);
					 break;  //<=
					 case 20: find_6(a.get_root(),x,reverse(p));
					 select_none(x,p);
					 break;  //>=
					 case 21: find_7(a.get_root(),x,reverse(p));
					 select_none(x,p);
					 break;  //>=
					 }
					return;
				}
				
				
			}
		 }
		 int reverse(int g)
		 {
			 switch(g)
			 {
				 case 1: return 2;
				 case 2: return 1;
				 case 3: return 6;
				 case 4: return 5;
				 case 5: return 4;
				 case 6: return 3;
				 
				 case 8: return 9;
				 case 9: return 8;
				 case 10: return 13;
				 case 11: return 12;
				 case 12: return 11;
				 case 13: return 10;
				 
				 case 15: return 16;
				 case 16: return 15;
				 case 17: return 20;
				 case 18: return 19;
				 case 19: return 18;
				 case 20: return 17;
				 case 21: return 22;
				 case 22: return 21;
			 }
			 return 0;
		 } 
		 void select_none(command &x,int p)
		 {
			list_node * rr;
		    rr=lis.get_head();
		   if(!rr) return;
			 if(p<15 && p>8)
			 {
				while(rr)
				{
			   if(cmp(rr,x,p)>0)
					{
                        addinstack(rr);  
					}
				 rr=rr->next;
				 }
				 printstack(x);
			 }
			 else
			 {
				 switch(p)
				{
				 case 8:  find_hash_eqv(x,0);         printstack(x); break;
				 case 1:  upfind_1(b.get_root(),x,0); printstack(x); break; //=
				 case 2:  upfind_2(b.get_root(),x,0); printstack(x); break;
				 case 3:  upfind_3(b.get_root(),x,0); printstack(x); break; //<
				 case 4:  upfind_4(b.get_root(),x,0); printstack(x); break;  //>
				 case 5:  upfind_5(b.get_root(),x,0); printstack(x); break;  //<=
				 case 6:  upfind_6(b.get_root(),x,0); printstack(x); break;  //>= 
				 case 15: find_1(a.get_root(),x,0);   printstack(x); break; //=
				 case 16: find_2(a.get_root(),x,0);   printstack(x); break;
				 case 17: find_3(a.get_root(),x,0);   printstack(x); break; //<
				 case 18: find_4(a.get_root(),x,0);   printstack(x); break;  //>
				 case 19: find_5(a.get_root(),x,0);   printstack(x); break;  //<=
				 case 20: find_6(a.get_root(),x,0);   printstack(x); break;  //>=
				 case 21: find_7(a.get_root(),x,0);   printstack(x); break;  
				}
			 }
		}
                 void delete_some(command &x)
                 {
                     int p=0,g=0;
                     switch(x.arg1)
                     {
                    case ARG_NONE:
                    list_node *rr,*gg;
                    rr=lis.get_head();
                         while(rr)
                         {
                                 gg=rr;
                                 rr=rr->next;
                                 a.delete_from_tree(a.get_root(),gg,c);
								delete_from_group_tree(b.get_root(),gg);
								delete_node(gg);
                         }
                         return;
                         break;
                    case ARG_GROUP:
						switch(x.c_group)
						{
							case COND_NONE: break;
							case COND_EQ: p=1; break;  //=
							case COND_NE: p=2; break;  //<>
							case COND_LT: p=3; break; //<
							case COND_GT: p=4; break;  //>
							case COND_LE: p=5; break;  //<=
							case COND_GE: p=6; break;  //>=
							case COND_LIKE: p=7; break;
						}
						break;
                    case ARG_PHONE:
						switch(x.c_phone)
						{
							case COND_NONE: break;
							case COND_EQ: p=8; break;  //=
							case COND_NE: p=9; break;  //<>
							case COND_LT: p=10; break; //<
							case COND_GT: p=11; break;  //>
							case COND_LE: p=12; break;  //<=
							case COND_GE: p=13; break;  //>=
							case COND_LIKE: p=14; break;
						}
						break;
                    case ARG_NAME:
						switch(x.c_name)
						{
							case COND_NONE: break;
							case COND_EQ: p=15; break;  //=
							case COND_NE: p=16; break;  //<>
							case COND_LT: p=17; break; //<
							case COND_GT: p=18; break;  //>
							case COND_LE: p=19; break;  //<=
							case COND_GE: p=20; break;  //>=
							case COND_LIKE: p=21; break;
						}
						break;
                    }
                     switch(x.arg2)
                     {
                    case ARG_NONE: break;
                    case ARG_GROUP:
                            switch(x.c_group)
                            {
                                    case COND_NONE: break;
                                    case COND_EQ: g=1; break;  //=
                                    case COND_NE: g=2; break;  //<>
                                    case COND_LT: g=3; break; //<
                                    case COND_GT: g=4; break;  //>
                                    case COND_LE: g=5; break;  //<=
                                    case COND_GE: g=6; break;  //>=
                                    case COND_LIKE: g=7; break;
                            }
                            break;
                    case ARG_PHONE:
                            switch(x.c_phone)
                            {
                                    case COND_NONE: break;
                                    case COND_EQ: g=8; break;  //=
                                    case COND_NE: g=9; break;  //<>
                                    case COND_LT: g=10; break; //<
                                    case COND_GT: g=11; break;  //>
                                    case COND_LE: g=12; break;  //<=
                                    case COND_GE: g=13; break;  //>=
                                    case COND_LIKE: g=14; break;
                            }
                            break;
                    case ARG_NAME:
                            switch(x.c_name)
                            {
                                    case COND_NONE: break;
                                    case COND_EQ: g=15; break;  //=
                                    case COND_NE: g=16; break;  //<>
                                    case COND_LT: g=17; break; //<
                                    case COND_GT: g=18; break;  //>
                                    case COND_LE: g=19; break;  //<=
                                    case COND_GE: g=20; break;  //>=
                                    case COND_LIKE: g=21; break;
                            }
                            break;
                    }
                    switch(x.oper)
                    {
                            case OP_AND: delete_and(x,p,g); break;
                            case OP_OR: delete_or(x,p,g); break;
                            case OP_NONE: delete_none(x,p); break;
                    }
                 }
	 void delete_and(command &x,int p, int g)
	 {
			 list_node * rr;
			 rr=lis.get_head();
			 if(!rr) return;
			 if(p<8 || g<8)
			 {
				 if(p<8)
				 {
					 switch(p)
					 {
						 case 1:  upfind_1(b.get_root(),x,g); killstack(); break; //=
						 case 2:  upfind_2(b.get_root(),x,g); killstack(); break;
						 case 3:  upfind_3(b.get_root(),x,g); killstack(); break; //<
						 case 4:  upfind_4(b.get_root(),x,g); killstack(); break;  //>
						 case 5:  upfind_5(b.get_root(),x,g); killstack(); break;  //<=
						 case 6:  upfind_6(b.get_root(),x,g); killstack(); break;  //>= 
					 }
					 return;
				 }
				 else
				 {
					 switch(g)
					 {
						 case 1:  upfind_1(b.get_root(),x,p); killstack(); break; //=
						 case 2:  upfind_2(b.get_root(),x,p); killstack(); break;
						 case 3:  upfind_3(b.get_root(),x,p); killstack(); break; //<
						 case 4:  upfind_4(b.get_root(),x,p); killstack(); break;  //>
						 case 5:  upfind_5(b.get_root(),x,p); killstack(); break;  //<=
						 case 6:  upfind_6(b.get_root(),x,p); killstack(); break;  //>= 
					 }
					 return;
				 }
			  }
			 else
				 {
					 if(p>=15)
						 {
							 switch(p)
							 {
							 case 15: find_1(a.get_root(),x,g); killstack(); break; //=
							 case 16: find_2(a.get_root(),x,g); killstack(); break;
							 case 17: find_3(a.get_root(),x,g); killstack(); break; //<
							 case 18: find_4(a.get_root(),x,g); killstack(); break;  //>
							 case 19: find_5(a.get_root(),x,g); killstack(); break;  //<=
							 case 20: find_6(a.get_root(),x,g); killstack(); break;  //>=
							 case 21: find_7(a.get_root(),x,g); killstack(); break;  //>=
							 }
							 return;
						 }
					 if(g>=15)
						 {
							 switch(g)
							 {
							 case 15: find_1(a.get_root(),x,p); killstack(); break; //=
							 case 16: find_2(a.get_root(),x,p); killstack(); break;
							 case 17: find_3(a.get_root(),x,p); killstack(); break; //<
							 case 18: find_4(a.get_root(),x,p); killstack(); break;  //>
							 case 19: find_5(a.get_root(),x,p); killstack(); break;  //<=
							 case 20: find_6(a.get_root(),x,p); killstack(); break;  //>=
							 case 21: find_7(a.get_root(),x,p); killstack(); break;  //>=
							 }
							 return;
						 }
					  if(p==8)
					  {
						  find_hash_eqv(x,g); killstack();
						  return;
					  }
					  else
					  {
						  find_hash_eqv(x,p); killstack();
						  return;
					  }

					 }
		 }
		 void delete_or(command &x,int p, int g)
		  {
                    // printf("kk\n");
			 list_node * rr;
			 rr=lis.get_head();
			 if(!rr) return;
			 if(p<8 || g<8)
			 {
				 if(p<8)
				 {
					 switch(p)
					 {
						 case 1:  upfind_1(b.get_root(),x,reverse(g)); delete_none(x,g);   break; //=
						 case 2:  upfind_2(b.get_root(),x,reverse(g)); delete_none(x,g);   break;
						 case 3:  upfind_3(b.get_root(),x,reverse(g)); delete_none(x,g);   break; //<
						 case 4:  upfind_4(b.get_root(),x,reverse(g)); delete_none(x,g);   break;  //>
						 case 5:  upfind_5(b.get_root(),x,reverse(g)); delete_none(x,g);   break;  //<=
						 case 6:  upfind_6(b.get_root(),x,reverse(g)); delete_none(x,g);   break;  //>= 
					 }
					 return;
				 }
				 else
				 {
					 switch(g)
					 {
						 case 1:  upfind_1(b.get_root(),x,reverse(p)); delete_none(x,p);   break; //=
						 case 2:  upfind_2(b.get_root(),x,reverse(p)); delete_none(x,p);   break;
						 case 3:  upfind_3(b.get_root(),x,reverse(p)); delete_none(x,p);   break; //<
						 case 4:  upfind_4(b.get_root(),x,reverse(p)); delete_none(x,p);   break;  //>
						 case 5:  upfind_5(b.get_root(),x,reverse(p)); delete_none(x,p);   break;  //<=
						 case 6:  upfind_6(b.get_root(),x,reverse(p)); delete_none(x,p);   break;  //>= 
					 }
					 return;
				 }
			  }
			else
			{
				if(p==8)
                {
					  find_hash_eqv(x,reverse(g));
					  delete_none(x,g); 
					  return;
				}
			    else
			    {
					  find_hash_eqv(x,reverse(p));
					  delete_none(x,p); 
					  return;
			    }
				if(p>=15)
				{
					 switch(p)
					 {
					 case 15: find_1(a.get_root(),x,reverse(g));
					 delete_none(x,g);
					 break; //=
					 case 16: find_2(a.get_root(),x,reverse(g));
					 delete_none(x,g); 
					 break;
					 case 17: find_3(a.get_root(),x,reverse(g));
					 delete_none(x,g); 
					 break; //<
					 case 18: find_4(a.get_root(),x,reverse(g));
					 delete_none(x,g);
					 break;  //>
					 case 19: find_5(a.get_root(),x,reverse(g));
					 delete_none(x,g);
					 break;  //<=
					 case 20: find_6(a.get_root(),x,reverse(g));
					 delete_none(x,g);
					 break;  //>=
					 case 21: find_7(a.get_root(),x,reverse(g));
					 delete_none(x,g);
					 break;  //>=
					 }
					return;
				}
				if(g>=15)
				{
					 switch(g)
					 {
					 case 15: find_1(a.get_root(),x,reverse(p));
					 delete_none(x,p);
					 break; //=
					 case 16: find_2(a.get_root(),x,reverse(p));
					 delete_none(x,p);
					 break;
					 case 17: find_3(a.get_root(),x,reverse(p));
					 delete_none(x,p);
					 break; //<
					 case 18: find_4(a.get_root(),x,reverse(p));
					 delete_none(x,p);
					 break;  //>
					 case 19: find_5(a.get_root(),x,reverse(p));
					 delete_none(x,p);
					 break;  //<=
					 case 20: find_6(a.get_root(),x,reverse(p));
					 delete_none(x,p);
					 break;  //>=
					 case 21: find_7(a.get_root(),x,reverse(p));
					 delete_none(x,p);
					 break;  //>=
					 }
					return;
				}	
			}
		 }
                 
                 void delete_none(command &x,int p)
                {
					list_node * rr;
					rr=lis.get_head();
				   if(!rr) return;
					 if(p<15 && p>8)
					 {
						while(rr)
						{
					        if(cmp(rr,x,p)>0)
							{
								addinstack(rr);  
							}
						 rr=rr->next;
						 }
						 killstack();
					 }
					 else
					 {
						 switch(p)
						{
						 case 8:  find_hash_eqv(x,0);         killstack(); break;
						 case 1:  upfind_1(b.get_root(),x,0); killstack(); break; //=
						 case 2:  upfind_2(b.get_root(),x,0); killstack(); break;
						 case 3:  upfind_3(b.get_root(),x,0); killstack(); break; //<
						 case 4:  upfind_4(b.get_root(),x,0); killstack(); break;  //>
						 case 5:  upfind_5(b.get_root(),x,0); killstack(); break;  //<=
						 case 6:  upfind_6(b.get_root(),x,0); killstack(); break;  //>= 
						 case 15: find_1(a.get_root(),x,0);   killstack(); break; //=
						 case 16: find_2(a.get_root(),x,0);   killstack(); break;
						 case 17: find_3(a.get_root(),x,0);   killstack(); break; //<
						 case 18: find_4(a.get_root(),x,0);   killstack(); break;  //>
						 case 19: find_5(a.get_root(),x,0);   killstack(); break;  //<=
						 case 20: find_6(a.get_root(),x,0);   killstack(); break;  //>=
						 case 21: find_7(a.get_root(),x,0);   killstack(); break;  
						}
					 }
				}
                 
                 void delete_node(list_node *rr)
                 {

                     if(rr)
                     {
                     if(rr==lis.get_head())
                     {
                         if(rr->next)
                         {
                         //lis.set_head(rr->next);
                        // rr->next=0;
					     lis.head=rr->next;
						 rr->next=0;
						 lis.head->prev=0;
                         delete rr;
                         }
                         else
                         {
                         lis.delete_list();
                         }
                     }
                     else
                     {
                        if(rr->next)
                        {
                           list_node * k, *j;
                           k=rr->next;
                           j=rr->prev;
                           k->prev=j;
                           j->next=k;
                           rr->next=0;
                           rr->prev=0;
                           delete rr;
                        }
                        else
                        {
                          list_node *k;
                          k=rr->prev;
                          rr->prev=0;
                          k->next=0;
                          delete rr;
                        }

                     }
                    }
                 }


                 void find_1(node * rr,command &x,int g) // =
                 {
                       if(!rr) return;
                       if(strcmp(rr->gpk->gg->get_name(),x.get_name())==0)
                       {
                         while(rr)
                        {
                         if(cmp(rr->gpk->gg,x,g)>0)
                         {
                         addinstack(rr->gpk->gg);
                         }
                         rr=rr->blef;
                        }
                         return;
                       }
                         if(strcmp(x.get_name(),rr->gpk->gg->get_name())>0)
                        {
                           find_1(rr->right,x,g);
                        }
                         else
                        {
                           find_1(rr->left,x,g);
                        }
                         return;
						}
						
                         void find_2(node * rr,command &x,int g) //<>
                         {
                               if(!rr) return;
                               if(strcmp(rr->gpk->gg->get_name(),x.get_name())!=0)
                               {
                                 node *k;
                                    k=rr;
                                 while(rr)
                                {
                                 if(cmp(rr->gpk->gg,x,g)>0)
                                 {
                                 addinstack(rr->gpk->gg);
                                 }
                                 rr=rr->blef;
                                }
                                 rr=k;
                               }
							   find_2(rr->right,x,g);
							   find_2(rr->left,x,g);
                                 return;
                         }
                void find_3(node * rr,command &x,int g) // name <
                {
                        if(!rr) return;
                         if(strcmp(x.get_name(),rr->gpk->gg->get_name())>0)
                        {
                         node *k;
                         k=rr;
                         while(rr)
                        {
                         if(cmp(rr->gpk->gg,x,g)>0)
                         {
                         addinstack(rr->gpk->gg);
                         }
                         rr=rr->blef;
                        }
                         rr=k;
                          find_3(rr->right,x,g);
                        }
                    
                           find_3(rr->left,x,g);
                        
                         return;
                   }
                         void find_4(node * rr,command &x,int g) // name >
                         {
                                 if(!rr) return;
                                  if(strcmp(x.get_name(),rr->gpk->gg->get_name())<0)
                                 {
                                  node *k;
                                  k=rr;
                                  while(rr)
                                 {
                                  if(cmp(rr->gpk->gg,x,g)>0)
                                  {
                                 addinstack(rr->gpk->gg);
                                  }
                                  rr=rr->blef;
                                 }
                                  rr=k;
                                  find_4(rr->left,x,g);
                                 }
                                  
                                    find_4(rr->right,x,g);
                                 
                                  return;
                            }
                         void find_5(node * rr,command &x,int g) // name <=
                         {
                                 if(!rr) return;
                                  if(strcmp(x.get_name(),rr->gpk->gg->get_name())>=0)
                                 {
                                  node *k;
                                  k=rr;
                                  while(rr)
                                 {
                                  if(cmp(rr->gpk->gg,x,g)>0)
                                  {
                                  addinstack(rr->gpk->gg);
                                  }
                                  rr=rr->blef;
                                 }
                                  rr=k;
                                  find_5(rr->right,x,g);
                                 }
                                 
                                 
                                    find_5(rr->left,x,g);                         
                               //  if(strcmp(x.get_name(),(rr)->gg->get_name())>=0)
                                 //   find_5(rr->right,x,g);
                                 
                                  return;
                            }
                         void find_6(node * rr,command &x,int g) // name >=
                         {
                                 if(!rr) return;
                                  if(strcmp(x.get_name(),rr->gpk->gg->get_name())<=0)
                                 {
                                  node *k;
                                  k=rr;
                                  while(rr)
                                 {
                                  if(cmp(rr->gpk->gg,x,g)>0)
                                  {
                                 addinstack(rr->gpk->gg);
                                  }
                                  rr=rr->blef;
                                 }
                                  rr=k;
                                  find_6(rr->left,x,g);
                                 }
                                  
                                 //if(strcmp(x.get_name(),(rr)->gg->get_name())<=0)
                                   // find_6(rr->left,x,g);
                                
                                    find_6(rr->right,x,g);
                                 
                                  return;
                            }

							
							void find_7(node * rr,command &x,int g) // name like
                         {
                                 if(!rr) return;
                                  if(like(rr->gpk->gg->get_name(),x.get_name())>0)
                                 {
                                  node *k;
                                  k=rr;
                                  while(rr)
                                 {
                                  if(cmp(rr->gpk->gg,x,g)>0)
                                  {
                                 addinstack(rr->gpk->gg);
                                  }
                                  rr=rr->blef;
                                 }
                                  rr=k;
								}
                                  find_7(rr->left,x,g);
                                 
                                  
                                 //if(strcmp(x.get_name(),(rr)->gg->get_name())<=0)
                                   // find_6(rr->left,x,g);
                                
                                    find_7(rr->right,x,g);
                                 
                                  return;
                            }

        int likes(const char *s, const char *t,int *buf1,int* buf2)
       {
        int *tmp;
        int i, j, q, m, len = strlen(s)+1,l=strlen(t);
	
        for(i = 1; i < len; i++)
            buf1[i] = 0;
        buf1[0] = 1;

        for(j = 0; j < l; j++)
        {
            q = 0;

            switch(t[j])
            {
            case '%':
                for(m = 0; m < len; m++)
                {
                    if(buf1[m])
                        break;
                    else
                        buf2[m] = 0;
                }
                if(m < len)
                {
                    q = 1;
                    for( ; m < len; m++)
                        buf2[m] = 1;
                }
                break;
            case '_':
                buf2[0] = 0;
                for(m = 1; m < len; m++)
                    if(buf1[m - 1]) buf2[m] = q = 1;
                    else buf2[m] = 0;
                break;
            case '\\':
                j++;
                switch(t[j])
                {
                case '%':
                    buf2[0] = 0;
                    for(m = 1; m < len; m++)
                    {
                        if(buf1[m - 1] && s[m - 1] == '%')
                        {
                            buf2[m] = 1;
                            q = 1;
                        }
                        else
                            buf2[m] = 0;
                    }
                    break;
                case '_':
                    buf2[0] = 0;
                    for(m = 1; m < len; m++)
                    {
                        if(buf1[m - 1] && s[m - 1] == '_')
                        {
                            buf2[m] = 1;
                            q = 1;
                        }
                        else
                            buf2[m] = 0;
                    }
                    break;
                case '\\':
                    buf2[0] = 0;
                    for(m = 1; m < len; m++)
                    {
                        if(buf1[m - 1] && s[m - 1] == '\\')
                        {
                            buf2[m] = 1;
                            q = 1;
                        }
                        else
                            buf2[m] = 0;
                    }
                    break;
                }
                break;
            default:
                buf2[0] = 0;
                for(m = 1; m < len; m++)
                {
                    if(buf1[m - 1] && s[m - 1] == t[j])
                    {
                        buf2[m] = 1;
                        q = 1;
                    }
                    else
                        buf2[m] = 0;
                }
            }
            if(!q)
                return 0;
            tmp = buf1;
            buf1 = buf2;
            buf2 = tmp;
        }
        return buf1[len - 1];
    }
                            
	
	int like(const char * stroka,const char * obr )
	{
		
                int buf1[KLEN]={0};
		int buf2[KLEN]={0};
		
		if(likes(stroka,obr,buf1,buf2)==1) return 1;
	        return -1;
	}
	
	
void  find_hash_eqv(command &x,int g)
{
	int j=0;
	j=c.hashmodule(x.get_phone());
	hash_node *u;
	u=c.array[j];
	while(u)
	{
		if(u->gg->get_phone()==x.get_phone() && cmp(u->gg,x,g)>0)
		{
			addinstack(u->gg);
		}
		u=u->next;
	}
}

void  find_hash_eqv_group(upnode * rr,command &x,int g)
{
	int j=0;
	j=rr->has.hashmodule(x.get_phone());
	hash_node *u;
	u=rr->has.array[j];
	while(u)
	{
		if(u->gg->get_phone()==x.get_phone() && cmp(u->gg,x,g)>0)
		{
			addinstack(u->gg);
		}
		u=u->next;
	}
}

	 void upfind_1(upnode * rr,command &x,int g) // =
	 {
		   if(!rr) return;
		   if(rr->get_group()==x.get_group() && rr->tr.get_root())
		   {
			switch(g)
			{
				 case 8: find_hash_eqv_group(rr,x,0); break;
				 case 15: find_1(rr->tr.get_root(),x,0); break; //=
				 case 16: find_2(rr->tr.get_root(),x,0); break;
				 case 17: find_3(rr->tr.get_root(),x,0); break; //<
				 case 18: find_4(rr->tr.get_root(),x,0); break;  //>
				 case 19: find_5(rr->tr.get_root(),x,0); break;  //<=
				 case 20: find_6(rr->tr.get_root(),x,0); break;  //>=
				 case 21: find_7(rr->tr.get_root(),x,0); break; 
				 default: selal(rr->tr.get_root(),x,g);
			}
		   }
		   if(x.get_group()  >  rr->get_group())
			{
			   upfind_1(rr->right,x,g);
			}
			 else
			{
		       upfind_1(rr->left,x,g);
			}
		 return;
	}
     void upfind_2(upnode * rr,command &x,int g) // !=
	 {
		   if(!rr) return;
		   if(rr->get_group()!=x.get_group() && rr->tr.get_root())
		   {
			switch(g)
			{
				 case 8: find_hash_eqv_group(rr,x,0); break;
				 case 15: find_1(rr->tr.get_root(),x,0); break; //=
				 case 16: find_2(rr->tr.get_root(),x,0); break;
				 case 17: find_3(rr->tr.get_root(),x,0); break; //<
				 case 18: find_4(rr->tr.get_root(),x,0);break;  //>
				 case 19: find_5(rr->tr.get_root(),x,0);break;  //<=
				 case 20: find_6(rr->tr.get_root(),x,0);break;  //>=
				 case 21: find_7(rr->tr.get_root(),x,0);break; 
				 default: selal(rr->tr.get_root(),x,g);
			}
		   }
		  
			   upfind_2(rr->right,x,g);
			
		       upfind_2(rr->left,x,g);
			
		 return;
	}   
	void upfind_3(upnode * rr,command &x,int g) // <
	 {
		   if(!rr) return;
		   if(rr->get_group()<x.get_group() && rr->tr.get_root())
		   {
			switch(g)
			{
				 case 8: find_hash_eqv_group(rr,x,0); break;
				 case 15: find_1(rr->tr.get_root(),x,0); break; //=
				 case 16: find_2(rr->tr.get_root(),x,0); break;
				 case 17: find_3(rr->tr.get_root(),x,0); break; //<
				 case 18: find_4(rr->tr.get_root(),x,0);break;  //>
				 case 19: find_5(rr->tr.get_root(),x,0);break;  //<=
				 case 20: find_6(rr->tr.get_root(),x,0);break;  //>=
				 case 21: find_7(rr->tr.get_root(),x,0);break; 
				 default: selal(rr->tr.get_root(),x,g);
			}
			upfind_3(rr->right,x,g);
		   }
		       upfind_3(rr->left,x,g);
			
		 return;
	}                      
	void upfind_4(upnode * rr,command &x,int g) // >
	 {
		   if(!rr) return;
		   if(rr->get_group()>x.get_group() && rr->tr.get_root())
		   {
			switch(g)
			{
				 case 8: find_hash_eqv_group(rr,x,0); break;
				 case 15: find_1(rr->tr.get_root(),x,0); break; //=
				 case 16: find_2(rr->tr.get_root(),x,0); break;
				 case 17: find_3(rr->tr.get_root(),x,0); break; //<
				 case 18: find_4(rr->tr.get_root(),x,0);break;  //>
				 case 19: find_5(rr->tr.get_root(),x,0);break;  //<=
				 case 20: find_6(rr->tr.get_root(),x,0);break;  //>=
				 case 21: find_7(rr->tr.get_root(),x,0);break; 
				 default: selal(rr->tr.get_root(),x,g);
			}
			upfind_4(rr->left,x,g);
		   }
		       upfind_4(rr->right,x,g);
			
		 return;
	} 
	 void upfind_5(upnode * rr,command &x,int g) // <=
	 {
		   if(!rr) return;
		   if(rr->get_group()<=x.get_group() && rr->tr.get_root())
		   {
			switch(g)
			{
				 case 8: find_hash_eqv_group(rr,x,0); break;
				 case 15: find_1(rr->tr.get_root(),x,0); break; //=
				 case 16: find_2(rr->tr.get_root(),x,0); break;
				 case 17: find_3(rr->tr.get_root(),x,0); break; //<
				 case 18: find_4(rr->tr.get_root(),x,0);break;  //>
				 case 19: find_5(rr->tr.get_root(),x,0);break;  //<=
				 case 20: find_6(rr->tr.get_root(),x,0);break;  //>=
				 case 21: find_7(rr->tr.get_root(),x,0);break; 
				 default: selal(rr->tr.get_root(),x,g);
			}
			upfind_5(rr->right,x,g);
		   }
		       upfind_5(rr->left,x,g);
		 return;
	}   
	void upfind_6(upnode * rr,command &x,int g) // >=
	 {
		   if(!rr) return;
		   if(rr->get_group()>=x.get_group() && rr->tr.get_root())
		   {
			switch(g)
			{
				 case 8:  find_hash_eqv_group(rr,x,0); break;
				 case 15: find_1(rr->tr.get_root(),x,0); break; //=
				 case 16: find_2(rr->tr.get_root(),x,0); break;
				 case 17: find_3(rr->tr.get_root(),x,0); break; //<
				 case 18: find_4(rr->tr.get_root(),x,0);break;  //>
				 case 19: find_5(rr->tr.get_root(),x,0);break;  //<=
				 case 20: find_6(rr->tr.get_root(),x,0);break;  //>=
				 case 21: find_7(rr->tr.get_root(),x,0);break; 
				 default: selal(rr->tr.get_root(),x,g);
			}
			upfind_6(rr->left,x,g);
		   }
		       upfind_6(rr->right,x,g);
			
		 return;
	}   
	void selal(node * rr,command &x,int g)
	{
		if(!rr) return;
		
			 node *k;
		  k=rr;
		  while(rr)
		 {
		  if(cmp(rr->gpk->gg,x,g)>0)
		  {
		   addinstack(rr->gpk->gg);
		  }
		  rr=rr->blef;
		 }
		  rr=k;
		
		selal(rr->right,x,g);
		selal(rr->left,x,g);
	}
};
 #endif //DATABASE_H
int serv (int PORT, database &bas, char *alf, command &com);
