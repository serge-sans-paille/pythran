/*****************************************************************/
/******     C  _  P  R  I  N  T  _  R  E  S  U  L  T  S     ******/
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>

void c_print_results( char   *name,
                      char   class,
                      int    n1, 
                      int    n2,
                      int    n3,
                      int    niter,
		      int    nthreads,
                      double t,
                      double mops,
		      char   *optype,
                      int    passed_verification,
                      char   *npbversion,
                      char   *compiletime,
                      char   *cc,
                      char   *clink,
                      char   *c_lib,
                      char   *c_inc,
                      char   *cflags,
                      char   *clinkflags,
		      char   *rand)
{
    char *evalue="1000";

    printf( "\n\n %s Benchmark Completed\n", name ); 

    printf( " Class           =                        %c\n", class );

    if( n2 == 0 && n3 == 0 )
        printf( " Size            =             %12d\n", n1 );   /* as in IS */
    else
        printf( " Size            =              %3dx%3dx%3d\n", n1,n2,n3 );

    printf( " Iterations      =             %12d\n", niter );
    
    printf( " Threads         =             %12d\n", nthreads );
 
    printf( " Time in seconds =             %12.2f\n", t );

    printf( " Mop/s total     =             %12.2f\n", mops );

    printf( " Operation type  = %24s\n", optype);

    if( passed_verification )
        printf( " Verification    =               SUCCESSFUL\n" );
    else
        printf( " Verification    =             UNSUCCESSFUL\n" );

    printf( " Version         =             %12s\n", npbversion );

    printf( " Compile date    =             %12s\n", compiletime );

    printf( "\n Compile options:\n" );

    printf( "    CC           = %s\n", cc );

    printf( "    CLINK        = %s\n", clink );

    printf( "    C_LIB        = %s\n", c_lib );

    printf( "    C_INC        = %s\n", c_inc );

    printf( "    CFLAGS       = %s\n", cflags );

    printf( "    CLINKFLAGS   = %s\n", clinkflags );

    printf( "    RAND         = %s\n", rand );
#ifdef SMP
    evalue = getenv("MP_SET_NUMTHREADS");
    printf( "   MULTICPUS = %s\n", evalue );
#endif

/*    printf( "\n\n" );
    printf( " Please send the results of this run to:\n\n" );
    printf( " NPB Development Team\n" );
    printf( " Internet: npb@nas.nasa.gov\n \n" );
    printf( " If email is not available, send this to:\n\n" );
    printf( " MS T27A-1\n" );
    printf( " NASA Ames Research Center\n" );
    printf( " Moffett Field, CA  94035-1000\n\n" );
    printf( " Fax: 415-604-3957\n\n" );*/
}
 
