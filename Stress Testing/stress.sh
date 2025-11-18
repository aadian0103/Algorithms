set -e
start=${1:-1}

CFLAGS="-std=c++23 -O2 -pipe -Wall -Wextra -Wshadow -Wconversion \
-Wno-sign-compare -DLOCAL -Wlogical-op -Wshift-overflow=2 \
-Wduplicated-cond -Wcast-qual -Wfloat-equal -Wformat=2 \
-Wcast-align -fmax-errors=1 -D_GLIBCXX_DEBUG"

echo "Compiling..."

g++-15 gen.cpp -O2 -o gen
g++-15 brute.cpp $CFLAGS -o brute
g++-15 sol.cpp $CFLAGS -o sol

for ((i = start; ; ++i)); do
    ./gen $i >debug_in
    ./sol <debug_in >my_out
    ./brute <debug_in >ans_out

    if ! diff -Z my_out ans_out >/dev/null; then
        break
    fi

    echo -e "\033[1;32mPassed test: $i\033[m"
done

echo -ne '\007'
echo -e "\033[1;45mWA FOUND\033[m"

echo -e "\033[0;46mInput:\033[m"
cat debug_in
echo ""

echo -e "\033[1;41mYour output:\033[m"
cat my_out
echo ""

echo -e "\033[1;42mCorrect output:\033[m"
cat ans_out
