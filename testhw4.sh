#!/bin/bash

run=./hw4

suffix=$1

prefix=./tests/

if [ ! -x $run ]
then
  echo "Error - cannot run '$run' (bad command or filename)"
  exit
fi

numTests=`ls $prefix/testInput*$suffix.txt | wc -w`

for i in `seq 1 $numTests`
do
  if [ ! -f $prefix/testInput$i$suffix.txt ]
  then
    echo "Error - cannot open $prefix/testInput$i$suffix.txt"
    exit
  fi

  if [ ! -f $prefix/puzzle$i$suffix.txt ]
  then
    echo "Error - cannot open $prefix/correctOutput$i$suffix.txt"
    exit
  fi

  if [ ! -f $prefix/correctOutput$i$suffix.txt ]
  then
    echo "Error - cannot open $prefix/correctOutput$i$suffix.txt"
    exit
  fi

  ./$run $prefix/puzzle$i$suffix.txt < $prefix/testInput$i$suffix.txt &> $prefix/testOutput$i$suffix.txt
  if diff $prefix/testOutput$i$suffix.txt $prefix/correctOutput$i$suffix.txt > /dev/null
  then
    echo Test $i passed
    rm $prefix/testOutput$i$suffix.txt
  else
    echo ***Test $i failed! See $prefix/diff$i$suffix.txt for differences
    diff $prefix/testOutput$i$suffix.txt $prefix/correctOutput$i$suffix.txt &> $prefix/diff$i$suffix.txt
  fi
done

