#!/bin/bash

echo -e "\n\n\t ----Fast BFS----\n\n"

echo -e "\n\nSize: 1\n\n"; echo -e "1\n3\n-1\nn" | ./nQueen
echo -e "\n\nSize: 2\n\n"; echo -e "2\n3\n-1\nn" | ./nQueen
echo -e "\n\nSize: 3\n\n"; echo -e "3\n3\n-1\nn" | ./nQueen
echo -e "\n\nSize: 4\n\n"; echo -e "4\n3\n-1\nn" | ./nQueen
echo -e "\n\nSize: 5\n\n"; echo -e "5\n3\n-1\nn" | ./nQueen
echo -e "\n\nSize: 6\n\n"; echo -e "6\n3\n-1\nn" | ./nQueen
# echo -e "\n\nSize: 7\n\n"; echo -e "7\n3\n-1\nn" | ./nQueen

echo -e "\n\n\t ----BFS----\n\n"

echo -e "\n\nSize: 1\n\n"; echo -e "1\n0\n-1\nn" | ./nQueen
echo -e "\n\nSize: 2\n\n"; echo -e "2\n0\n-1\nn" | ./nQueen
echo -e "\n\nSize: 3\n\n"; echo -e "3\n0\n-1\nn" | ./nQueen
echo -e "\n\nSize: 4\n\n"; echo -e "4\n0\n-1\nn" | ./nQueen
echo -e "\n\nSize: 5\n\n"; echo -e "5\n0\n-1\nn" | ./nQueen
echo -e "\n\nSize: 6\n\n"; echo -e "6\n0\n-1\nn" | ./nQueen
# echo -e "\n\nSize: 7\n\n"; echo -e "7\n0\n-1\nn" | ./nQueen