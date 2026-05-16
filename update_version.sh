#!/bin/bash

VERSION=$(git describe --tags --always)
DATE=$(date '+%Y-%m-%d')

HISTORY=$(git tag -l --sort=-version:refname | while read tag; do
    MSG=$(git tag -l -n1 "$tag" | sed "s/^$tag *//")
    echo " *  $tag  -  $MSG"
done)

cat > version.h << EOF
#ifndef VERSION_H
#define VERSION_H

const char VERSION[] = "$VERSION";

/*
 *  Version History
 *  ---------------
$HISTORY
 */

#endif
EOF

echo "Generated version.h - $VERSION"
