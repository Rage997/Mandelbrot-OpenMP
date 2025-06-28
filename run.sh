#!/bin/bash

cd src || exit 1

if [ ! -f mandelbrot ]; then
    echo "Executable not found. Run ./compile.sh first."
    exit 1
fi

./mandelbrot && echo "✅ Mandelbrot set generation completed." || echo "❌ Error running Mandelbrot generator."