rm ./nQueenSolves.txt
touch ./nQueenSolves.txt
echo -e "Size\t\tSols\t\tTime" >> ./nQueenSolves.txt
for i in {1..20}
do
    OUTPUT="$(echo -e "$i\n-1" | ./nQueen -p)"
    echo $OUTPUT
    echo $OUTPUT >> ./nQueenSolves.txt
done

vim ./nQueenSolves.txt