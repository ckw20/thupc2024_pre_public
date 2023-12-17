g++ simprand.cpp -o simprand -std=c++14
g++ antigen.cpp -o antigen -std=c++14
# ./simprand 500000 50 > 2.in
# ./simprand 500000 90 > 3.in
# ./simprand 500000 95 > 4.in
# ./simprand 500000 100 > 5.in
# ./simprand 500000 89 > 6.in
./antigen 500000 > 7.in
