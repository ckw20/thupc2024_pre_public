g++ ../ei/nsqrtlog.cpp -o std -std=c++14
g++ chk.cpp -o chk -std=c++14

for ((i = 1; i <= 7; ++i))
do
    time ./std < $i.in > $i.ans
    ./chk $i.in $i.ans $i.ans
done
