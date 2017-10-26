#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#ifdef USE_FLOAT
typedef float data_t;
#define M_PI 3.141592654f
#define INPUT_FORMAT "%f%*[ \t]%f%*[ \t]%f"
#define OUTPUT_FORMAT "%f %f %f\n"
#else
typedef double data_t;
#define M_PI 3.141592654
#define INPUT_FORMAT "%lf%*[ \t]%lf%*[ \t]%lf"
#define OUTPUT_FORMAT "%lf %lf %lf\n"
#endif

typedef data_t town[3];
typedef struct {
    size_t nb;
    town *data;
} towns;

towns read_towns(const char fname[])
{
    FILE * fd = fopen(fname,"r");
    size_t curr=0;
    char c;
    towns the_towns = { 1 , malloc(sizeof(town)) };

    while(!feof(fd))
    {
        if(the_towns.nb==curr)
        {
            the_towns.nb*=2;
            the_towns.data=realloc(the_towns.data,the_towns.nb*sizeof(town));
        }
        if(fscanf(fd,INPUT_FORMAT,&the_towns.data[curr][0],&the_towns.data[curr][1],&the_towns.data[curr][2]) !=3 )
        {
            while(!feof(fd))
            {
                c=(char)fgetc(fd);
                if(c=='\n' || c=='\r') break;
            }
        }
        else
        {
            the_towns.data[curr][0]*=M_PI/180;
            the_towns.data[curr][1]*=M_PI/180;
            ++curr;
        }
    }
    fclose(fd);
    the_towns.data=realloc(the_towns.data,curr*sizeof(town));
    the_towns.nb=curr;
    /*
    for(curr=0;curr<the_towns.nb;curr++)
        fprintf(stderr,OUTPUT_FORMAT,the_towns.data[curr][0],the_towns.data[curr][1],the_towns.data[curr][2]);
    */
    return the_towns;
}


towns run(towns t,data_t xmin, data_t ymin, data_t xmax, data_t ymax, data_t step,data_t range)
{
    size_t i,j;
    size_t k;
    size_t rangex=( (xmax - xmin )/step ),
        rangey=( (ymax - ymin )/step );
    int nb = 1+  rangex*rangey;
    towns tout = { nb , malloc(sizeof(town)*nb) };;

#pragma omp parallel for private(i,j,k)
    for(i=0;i<rangex;i++)
        for(j=0;j<rangey;j++)
        {
            tout.data[i*rangey+j][0]=(xmin+step*i)*180/M_PI;
            tout.data[i*rangey+j][1]=(ymin+step*j)*180/M_PI;
            tout.data[i*rangey+j][2]=0.;
            for(k=0;k<t.nb;k++)
            {
                data_t tmp =
                    6368.* acos(cos(xmin+step*i)*cos( t.data[k][0] ) * cos((ymin+step*j)-t.data[k][1]) + sin(xmin+step*i)*sin(t.data[k][0]));
                if( tmp < range )
                    tout.data[i*rangey+j][2]+= t.data[k][2]  / (1 + tmp) ;
            }
        }
    return tout;
}

void display(towns t,data_t xmin, data_t ymin, data_t xmax, data_t ymax, data_t step)
{
    size_t rangex=( (xmax - xmin )/step ),
        rangey=( (ymax - ymin )/step );
    size_t i,j;
    FILE *fd = fopen("out.dat","w");
    for(i=0;i<rangex;i++)
    {
        for(j=0;j<rangey;j++)
            fprintf(fd, OUTPUT_FORMAT,t.data[i*rangey+j][0],t.data[i*rangey+j][1],t.data[i*rangey+j][2]);
        fprintf(fd, "\n");
    }
}

int main(int argc, char * argv[])
{
    double start = omp_get_wtime();
    if(argc != 8) return 1;
    {
        towns t = read_towns(argv[1]);
        data_t xmin = atof(argv[2])*M_PI/180.,
               ymin =atof(argv[3])*M_PI/180.,
               xmax=atof(argv[4])*M_PI/180.,
               ymax=atof(argv[5])*M_PI/180.,
               step=atof(argv[6])*M_PI/180.,
               range=atof(argv[7]);
        towns out = run(t,xmin,ymin,xmax,ymax,step,range);
        display(out,xmin,ymin,xmax,ymax,step);
    }
    double stop = omp_get_wtime();
    printf("%lf\n", stop -start);
    return 0;
}
