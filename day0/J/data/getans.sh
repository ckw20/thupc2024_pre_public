g++ ../ei/nlog.cpp -o nlog -std=c++17 -O2

for ((i = 1; i <= 7; ++i))
do
    time ./nlog < $i.in > $i.ans
done