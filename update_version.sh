#!/bin/bash
VERSION=$(git describe --tags --always)
echo "#ifndef VERSION_H" > version.h
echo "#define VERSION_H" >> version.h
echo "const char version[] = \"$VERSION\";" >> version.h
echo "#endif" >> version.h
