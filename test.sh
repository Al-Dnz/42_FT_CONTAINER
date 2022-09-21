#/bin/bash

COLOR='\033[1;36m'

cd ./defense_tools
cd ./MLI_tester 
./do.sh vector stack map
cd ../mazoise_tester
./Run_tests.sh vector stack map

echo "${COLOR}BONUS (SET CONTAINER):${NC}\n"
./Run_tests.sh set

cd ../..
./time_test.sh