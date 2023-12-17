for ((rep = 1; rep <= 100; ++rep))
do
    ./grand 1000 > test.in
    ./nlog < test.in > test.out
    ./n2log < test.in > test.ans
    if diff test.out test.ans
    then
        echo AC $rep
    else
        echo "WA"
        exit 0
    fi
done
