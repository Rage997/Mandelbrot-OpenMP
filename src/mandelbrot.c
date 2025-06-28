#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#ifdef _OPENMP
    #include <omp.h>
#endif
#include "pngwriter.h"
#include "consts.h"

unsigned long get_time() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000000 + tp.tv_usec;
}

int main(int argc, char** argv) {
    double min_x = MIN_X;
    double max_x = MAX_X;
    double min_y = MIN_Y;
    double max_y = MAX_Y;
    int width = IMAGE_WIDTH;
    int height = IMAGE_HEIGHT;
    long max_iters = MAX_ITERS;

    if (argc >= 5) {
		min_x = atof(argv[1]);
		max_x = atof(argv[2]);
		min_y = atof(argv[3]);
		max_y = atof(argv[4]);
		if (argc >= 7) {
			width = atoi(argv[5]);
			height = atoi(argv[6]);
		}
		if (argc >= 8) {
			max_iters = atol(argv[7]);
		}
	}

    printf("Number of threads : %i\n", omp_get_max_threads());
    printf("MIN_X: %f, MAX_Y: %f\n", min_x, max_y);

    png_data* pPng = png_create(width, height);

    double fDeltaX = (max_x - min_x) / (double) width;
    double fDeltaY = (max_y - min_y) / (double) height;

    long nTotalIterationsCount = 0;
    unsigned long nTimeStart = get_time();

    #pragma omp parallel for reduction(+:nTotalIterationsCount)
    for (long j = 0; j < height; j++) {
        double cy = min_y + j * fDeltaY;
        for (long i = 0; i < width; i++) {
            double cx = min_x + i * fDeltaX;
            double x = cx, y = cy, x2 = x*x, y2 = y*y;
            long n;
            for (n = 0; n < max_iters && (x2 + y2 < 4); n++) {
                y = 2 * x * y + cy;
                x = x2 - y2 + cx;
                x2 = x * x;
                y2 = y * y;
                nTotalIterationsCount++;
            }
            int c = ((long) n * 255) / max_iters;
            png_plot(pPng, i, j, c, c, c);
        }
    }

    unsigned long nTimeEnd = get_time();
    printf("Total time: %g ms\n", (nTimeEnd - nTimeStart) / 1000.0);

    char filename[256];
    sprintf(filename, "../images/mandelbrot_minx_%f_maxy_%f.png", min_x, max_y);
    png_write(pPng, filename);
    return 0;
}
