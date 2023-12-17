g++ val.cpp -o val -std=c++11

for ((i = 1; i <= 7; ++i))
do
    ./val < $i.in
done
