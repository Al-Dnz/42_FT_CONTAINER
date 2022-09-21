#/bin/bash
VIOLET='\033[1;35m'
NC='\033[0m'
SEED=10

make compile_time_prog

echo "${VIOLET}STD TIME:${NC}"
time -p ./std_time "$SEED" > /dev/null
echo "${VIOLET} \nFT TIME:${NC}"
time -p ./ft_time "$SEED" > /dev/null

rm ft_time
rm std_time