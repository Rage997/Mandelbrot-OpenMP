all: mandelbrot

mandelbrot: mandelbrot.c pngwriter.c
	gcc -o $@ -I. -O3 $^ -lpng -fopenmp

clean:
	rm -rf mandelbrot



