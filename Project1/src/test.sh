#!/bin/sh
# This is a comment

rm *.txt
make clean
make

./common /home/durzo/Programming/OperatingSystems/Project1/Documents/BlackBoxTesting/files/THEGODFATHER.txt /home/durzo/Programming/OperatingSystems/Project1/Documents/BlackBoxTesting/files/THEGODFATHER2.txt /home/durzo/Programming/OperatingSystems/Project1/student_out.txt

if diff -w /home/durzo/Programming/OperatingSystems/Project1/student_out.txt /home/durzo/Programming/OperatingSystems/Project1/Documents/BlackBoxTesting/files/correct_out.txt; then
    echo Test: Success-----------------------------------------------Success
else
    echo Test: Fail--------------------------------------------------Fail
fi
