#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr );
void *print_message_function2( void *ptr );

main()
{
     pthread_t thread1, thread2;
     char *message1 = "Thread 1";
     char *message2 = "Thread 2";
     int  iret1, iret2;

    /* Create independent threads each of which will execute function */

     pthread_create( &thread1, NULL, print_message_function, (void*) message1);
     pthread_create( &thread2, NULL, print_message_function2, (void*) message2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);
     printf("Thread 1 returned\n");

     pthread_join( thread2, NULL); 
     printf("Thread 2 returned\n");
     exit(0);
}

void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     // printf("%s \n", message);
     int i;
     for(i=0;i<10;++i) {
       printf("p1: %d\n", i);
     }
}

void *print_message_function2( void *ptr )
{
     char *message;
     message = (char *) ptr;
     // printf("%s \n", message);
     int i;
     for(i=0;i<20;++i) {
       printf("p2: %d\n", i);
     }
}
