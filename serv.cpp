#include "database.h"


int serv (int PORT, database &bas, char *alf, command &com)
{
	int i, err, ret, opt = 1;
	int sock, new_sock;
	fd_set active_set, read_set;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	char buf[1000];
	socklen_t size;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) return -1;
	setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

	addr.sin_family = AF_INET;
	addr.sin_port = htons (PORT);
	addr.sin_addr.s_addr = htonl (INADDR_ANY);
	err = bind (sock, (struct sockaddr *)&addr, sizeof(addr));
	if(err < 0) return -1;

	err = listen (sock, 20);
	if(err < 0) return -1;

	FD_ZERO (&active_set);
	FD_SET (sock, &active_set);
	
	printf("it's alive!\n");
	while(true)
	{
		read_set = active_set;
		if (select (FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0)
			return -4;

		for (i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET (i, &read_set))
			{
				if(i == sock)
				{
					size = sizeof(client);
					new_sock = accept (sock, (struct sockaddr *)&client, &size);
					if(new_sock < 0) return -5;

					printf ( "SERVER: connect from host %s, port %d.\n",	inet_ntoa(client.sin_addr), (unsigned int)ntohs(client.sin_port));
					FD_SET (new_sock, &active_set);
				}
				else
				{

					err = Readf(i, buf);
					if(err < 0)
					{
						printf("something bad with server\n");
						close(i);
						FD_CLR(i, &active_set);
					}
					else
					{
						printf("\n < %d bytes of %s\n", err, buf);
						//Printf(i, "get command\n");
						//printf("1\n");
						ret = com.parser(buf,alf);	
						//printf("2\n");
						if(ret==-7)
						{
						//printf("alarm\n");
						com.destroy();
						Printf(i,"%s\n",buf);
						ret = com.parser(buf,alf);
						//com.print();					
						}
						if (ret < 0)
				        	{  	//Printf(i, "bad command %d\n",ret);
							if(ret<-200)
							{
							Printf(i, "quit");
							printf("Client left\n");
							close (i);
				        		FD_CLR (i, &active_set);
							if(ret==-243)
							{
				        		printf ( "SERVER: close\n");
				        		return close (sock), 0;
							}
							}
							Printf (i, "bad_command");
							com.destroy();
							
						}
				        else
				        {
							//Printf(i, "START COMMAND\n");
				            		bas.docommand (com, i);
							Printf(i, "done");
							com.destroy();
							
				        }
					}
				}
			}
		}
	}
}


