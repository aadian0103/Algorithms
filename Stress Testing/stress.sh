set -e
start=${1:-1}

CFLAGS="-std=c++23 -O2 -pipe -Wall -Wextra -Wshadow -Wconversion \
-Wno-sign-compare -DLOCAL -Wlogical-op -Wshift-overflow=2 \
-Wduplicated-cond -Wcast-qual -Wfloat-equal -Wformat=2 \
-Wcast-align -fmax-errors=1 -D_GLIBCXX_DEBUG"

GREEN="\033[38;5;114m"
RED="\033[38;5;203m"
BLUE="\033[38;5;110m"
PEACH="\033[38;5;217m"
MINT="\033[38;5;150m"
RESET="\033[0m"

cleanup() {
    rm -f gen brute sol debug_in my_out ans_out
}

echo -e "${BLUE}Compiling...${RESET}"

g++-15 $CFLAGS gen.cpp -o gen
g++-15 $CFLAGS brute.cpp -o brute
g++-15 $CFLAGS sol.cpp -o sol

for ((i = start; ; ++i)); do
    ./gen >debug_in
    ./sol <debug_in >my_out
    ./brute <debug_in >ans_out

    if ! diff -w my_out ans_out >/dev/null; then
        break
    fi

    echo -e "${GREEN}Passed test: $i${RESET}"
done

echo -ne '\007'
echo -e "${RED}WA FOUND${RESET}"

echo -e "${BLUE}Input:${RESET}"
cat debug_in
echo ""

echo -e "${PEACH}Your output:${RESET}"
cat my_out
echo ""

echo -e "${MINT}Correct output:${RESET}"
cat ans_out

cleanup
