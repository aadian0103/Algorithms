set -e

GREEN="\033[38;5;114m"
RED="\033[38;5;203m"
BLUE="\033[38;5;110m"
PEACH="\033[38;5;217m"
MINT="\033[38;5;150m"
RESET="\033[0m"
timeout=2

cleanup() {
    rm -f gen brute sol debug.in my.out ans.out diff_output
    echo -e "\n${BLUE}Cleaned up temporary files${RESET}"
}
trap cleanup EXIT

echo -e "${BLUE}Compiling...${RESET}"
g++-15 -std=c++23 -O2 gen.cpp -o gen
g++-15 -std=c++23 -O2 brute.cpp -o brute
g++-15 -std=c++23 -O2 sol.cpp -o sol

for ((i = 1; ; i++)); do
    ./gen >debug.in

    if ! timeout $timeout ./brute <debug.in >ans.out; then
        echo -e "\n${RED}TLE in brute force on test $i${RESET}"
        break
    fi

    if ! timeout $timeout ./sol <debug.in >my.out; then
        echo -e "\n${RED}TLE in solution on test $i${RESET}"
        break
    fi

    if ! diff -w my.out ans.out >/dev/null; then
        echo -e "\n${RED}WA FOUND${RESET}"

        echo -e "${BLUE}Input:${RESET}"
        cat debug.in
        echo ""

        echo -e "${PEACH}Your output:${RESET}"
        cat my.out
        echo ""

        echo -e "${MINT}Correct output:${RESET}"
        cat ans.out

        cp debug.in "fail$i.in"
        cp ans.out "fail$i.ans"
        cp my.out "fail$i.myout"

        break
    fi

    if ((i % 100 == 0 || i == 1)); then
        echo -e "${GREEN}Passed tests: $i${RESET}"
    fi

done

echo -ne '\007'
