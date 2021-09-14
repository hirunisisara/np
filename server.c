/*********************************************************************
	Practical1
	daytimetcpsrv.c
	From Stevens' Textbook

*********************************************************************/
#include	"utils.h"


int
main(int argc, char **argv)
{
	int			listenfd, connfd;
	socklen_t		len;
	struct sockaddr_in	servaddr, cliaddr;
	char			buff[MAXLINE];
	time_t			ticks;
	int yes = 1;
        int res = 0;
	const char	*ptr;

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		fprintf(stderr, "socket creation failed\n");
		exit (1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_TCP_PORT); /* server */

	if ( (bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0) 
	{
		fprintf(stderr, "bind failed\n");
		exit (1);
	}
		

	if ( listen(listenfd, LISTENQ) < 0) 
	{
		fprintf(stderr, "listen failed\n");
		exit (1);
	}
        

	for ( ; ; ) 
	{
		len = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (SA *) &cliaddr, &len)) < 0 ) 
		{
			fprintf(stderr, "accept failed\n");
			exit (1);
		}

		if( (ptr = inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff))) == NULL) 
		{
			fprintf(stderr, "inet_ntop error \n");
			exit (1);
		}
		
		printf("connection from %s, port %d\n", ptr, ntohs(cliaddr.sin_port));

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
			
		if ( write(connfd, buff, strlen(buff)) != strlen(buff)) 
		{
			fprintf(stderr, "accept failed\n");
			exit (1);
		}
			

		if ( close(connfd) == -1) 
		{
			fprintf(stderr, "accept failed\n");
			exit (1);
		}
	}
       
      // Get buffer size
      len = sizeof(buff);
      res = getsockopt(listenfd, SOL_SOCKET, SO_SNDBUF, &buff, &len);

      if(res == -1)
           printf("Error getsockopt one");
      else
           printf("send buffer size = %d\n", buff);

     // Set buffer size
      buff = 16000;

      printf("sets the send buffer to %d\n", buff);
      res = setsockopt(listenfd, SOL_SOCKET, SO_SNDBUF, &buff, sizeof(buff));

     if(res == -1)
     printf("Error setsockopt");


     return 0;
}

