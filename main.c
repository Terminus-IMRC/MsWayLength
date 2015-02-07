#define _BSD_SOURCE
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define X 5

char *buf;

void read_next_ms(int **ms)
{
	int i;
	char *buf_orig=buf;

	if(fgets(buf, 0xffff, stdin)==NULL){
		*ms=NULL;
		return;
	}

	for(i=0; i<X*X; i++){
		long int b;
		char *buf_cur;

		while(*buf==' ')
			buf++;
		buf_cur=buf;
		b=strtol(buf, &buf, 10);
		if(buf==buf_cur){
			fprintf(stderr, "error: invalid input: insufficient number of numbers on a line\n");
			exit(EXIT_FAILURE);
		}else if((b==LONG_MAX)||(b==LONG_MIN)){
			fprintf(stderr, "error: strtol: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		(*ms)[i]=(int)b;
	}

	buf=buf_orig;

	return;
}

int main()
{
	int i;
	int *ms;
	int *ms_xhash, *ms_yhash;
	long double len;

	ms=(int*)malloc((X*X)*sizeof(int));
	if(ms==NULL){
		fprintf(stderr, "error: failed to malloc ms\n");
		exit(EXIT_FAILURE);
	}

	ms_xhash=(int*)malloc((X*X)*sizeof(int));
	if(ms_xhash==NULL){
		fprintf(stderr, "error: failed to malloc ms_xhash\n");
		exit(EXIT_FAILURE);
	}

	ms_yhash=(int*)malloc((X*X)*sizeof(int));
	if(ms_yhash==NULL){
		fprintf(stderr, "error: failed to malloc ms_yhash\n");
		exit(EXIT_FAILURE);
	}

	buf=(char*)malloc(0xffff*sizeof(char));
	if(buf==NULL){
		fprintf(stderr, "error: failed to malloc buf\n");
		exit(EXIT_FAILURE);
	}

	read_next_ms(&ms);
	while(ms!=NULL){
		for(i=0; i<X*X; i++){
			ms_xhash[ms[i]-1]=i%X;
			ms_yhash[ms[i]-1]=i/X;
		}

		len=0.0;
		for(i=0; i<X*X-1; i++)
			len+=sqrtl(powl(ms_xhash[i+1]-ms_xhash[i], 2)+powl(ms_yhash[i+1]-ms_yhash[i], 2));

		printf("%Lf\n", len);

		read_next_ms(&ms);
	}

	return 0;
}
