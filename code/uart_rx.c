/**************************************************

file: demo_rx.c
purpose: simple demo that receives characters from
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_rx.c rs232.c -Wall -Wextra -o2 -o test_rx

**************************************************/

#include 
#include 

#ifdef _WIN32
#include 
#else
#include 
#endif

#include &quot;rs232.h&quot;

int main()
{
  int i, n,
      cport_nr=3,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=9600;       /* 9600 baud */

  unsigned char buf[4096];

  char mode[]={&#39;8&#39;,&#39;N&#39;,&#39;1&#39;,0};


  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf(&quot;Can not open comport\n&quot;);

    return(0);
  }

  while(1)
  {
    n = RS232_PollComport(cport_nr, buf, 4095);

    if(n &gt; 0)
    {
      buf[n] = 0;   /* always put a &quot;null&quot; at the end of a string! */

      for(i=0; i &lt; n; i++)
      {
        if(buf[i] &lt; 32)  /* replace unreadable control-codes by dots */
        {
          buf[i] = &#39;.&#39;;
        }
      }

      printf(&quot;received %i bytes: %s\n&quot;, n, (char *)buf);
    }

#ifdef _WIN32
    Sleep(100);
#else
    usleep(100000);  /* sleep for 100 milliSeconds */
#endif
  }

  return(0);
}
