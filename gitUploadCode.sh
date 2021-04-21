#!/bin/sh

#$1 - comment

if [ $# -ne 1 ]
then
  echo "Wrong input! please use the following input: "
        echo "1 arg - comment"
  exit 1
fi


rm -rf build-jelyazka-Desktop-Debug/
rm source/*.pro.user

echo "git add --all"
git add --all

echo "git commit -m $1"
git commit -m "$1"

echo "git push origin"
git push origin
