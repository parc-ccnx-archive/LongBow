#!/bin/sh

GIT_BRANCH=`git branch | awk '/\*/ { print $2; }'`

export DISTILLERY_GITHUB_USER=isolis

echo setting branch to $GIT_BRANCH

git clone http://github.com/PARC/CCNx_Distillery
cd CCNx_Distillery
make update
cd src
rm -rf LongBow
ln -s ../.. LongBow

for dir in ls; do
  cd $dir
  git checkout $GIT_BRANCH
  cd ..
done

make all
make check
