/* C/Fortran interface is different on different machines. 
 * You may need to tweak this.
 */


#if defined(IBM)
#define wtime wtime
#elif defined(CRAY)
#define wtime WTIME
#else
#define wtime wtime_
#endif
