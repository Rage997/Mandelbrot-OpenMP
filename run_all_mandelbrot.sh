#!/bin/bash

# Runs the script multiple times for different mandelbrot configurations.

cd src

# Classic view

./mandelbrot -2.0 1.0 -1.5 1.5

# Seahorse Valley

./mandelbrot -0.75 -0.7 -0.1 0.1

# Deep detail zoom

./mandelbrot -0.74877 -0.74872 0.065053 0.065103

# Additional interesting view

./mandelbrot -1.25 -1.2 0.1 0.15

echo "✅ All Mandelbrot renders complete."
