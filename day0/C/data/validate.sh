g++ validator.cpp -o validator -O2 -std=c++11
for ((i = 1; i <= 6; ++i))
do
    ./validator < $i.in
    echo test case $i validation pass.
done
rm validator
