
#include <stdio.h>
#include <float.h>
#include <stdlib.h>

#include "rpn.h"

#define MAXCOLS 80
#define MAXROWS 40

char plot[MAXROWS][MAXCOLS];

void clearPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      plot[i][j] = ' ';
    }
  }
}

void printPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      printf("%c", plot[i][j]);
    }
    printf("\n");
  }
}

void plotXY(int x, int y, char c) {
  if ( x <0 || x>=MAXCOLS || y < 0 || y >=MAXROWS) return;
  plot[MAXROWS-1-y][x]=c;
}

void createPlot( char * funcFile, double minX, double maxX) {
  int nvals = MAXCOLS;
  double yy[MAXCOLS];
  double xx[MAXCOLS];
  clearPlot();

  for (int i = 0; i < MAXCOLS ; i++) {
  	double x = minX + (maxX-minX) * i / MAXCOLS; // X-value
	double y = rpn_eval(funcFile,x); // Y-value
	xx[i] = x;
	yy[i] = y;
  }

  double minY = DBL_MAX/2;
  double maxY = DBL_MIN/2;
  

  int xline;
  for (int i = 0 ; i < MAXCOLS ; i++) {
  	if (yy[i] > maxY) {
		maxY = yy[i];
	}
	if (yy[i] < minY) {
		minY = yy[i];
	}
  }
  
  int yline = MAXCOLS/2;
  xline = (int)((yy[40]-minY)*MAXROWS/(maxY-minY));
  for (int i = 0; i < MAXCOLS; i++) {
  	plotXY(i,xline, '_');
  } 
  for (int i = 0; i < MAXCOLS; i++) {
  	plotXY(yline, i, '|');
  }

  for (int i = 0; i < MAXCOLS; i++) {
  	int x = i; // X plotted value
	int y = (int) ((yy[i] - minY) * MAXROWS / (maxY - minY)); // Y plotted value
	plotXY(x, y, '*');

  }
  //Compute maximum and minimum y in vector yy
  
  //Plot x axis

  //Plot y axis

  // Plot function. Use scaling.
  // minX is plotted at column 0 and maxX is plotted ar MAXCOLS-1
  // minY is plotted at row 0 and maxY is plotted at MAXROWS-1

  printPlot();

}

int main(int argc, char ** argv)
{
  printf("RPN Plotter.\n");
  
  if (argc < 4) {
    printf("Usage: plot func-file xmin xmax\n");
    exit(1);
  }

  char * funcName = argv[1];
  double xmin = atof(argv[2]);
  double xmax = atof(argv[3]);
  createPlot(funcName, xmin, xmax);
}
