#!/bin/bash

cd src
make clean
if make all; then
echo "✅ Code compiled successfully"
else
echo "❌ Compilation failed"
exit 1
fi