#!/usr/bin/env bash

echo "It's a solved task performed by Aplachkina Ekaterina"
echo "--"
echo "some examples:"
g++ -o read read_csv.cpp
echo -e "file.csv before:"
cat file.csv
echo -e " "
echo -e "after:"
./read file.csv
sleep 3

echo -e "-------------------------"

echo -e "minus.csv before:"
cat minus.csv
echo -e " "
echo -e "after:"
./read minus.csv
sleep 3

echo -e "-------------------------"

echo -e "mul.csv before:"
cat mul.csv
echo -e " "
echo -e "after:"
./read mul.csv
sleep 3

echo -e "-------------------------"

echo -e "div.csv before:"
cat div.csv
echo -e " "
echo -e "after:"
./read div.csv
sleep 3

echo -e "-------------------------"

echo -e "blank.csv before:"
cat blank.csv
echo -e " "
echo -e "after:"
./read blank.csv
sleep 3

echo -e "-------------------------"

echo -e "single.csv before:"
cat single.csv
echo -e " "
echo -e "after:"
./read single.csv
sleep 3

echo -e "-------------------------"

echo -e "num.csv before:"
cat num.csv
echo -e " "
echo -e "after:"
./read num.csv
sleep 3

echo -e "-------------------------"

echo -e "fail.csv before:"
cat fail.csv
echo -e " "
echo -e "after:"
./read fail.csv
sleep 3

echo -e "-------------------------"

echo -e "wrong.csv before:"
cat wrong.csv
echo -e " "
echo -e "after:"
./read wrong.csv

echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo "end of presentation"