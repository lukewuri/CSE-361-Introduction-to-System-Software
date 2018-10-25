#!/bin/bash
files=("answer.txt" "code/task1" "code/task2" "code/task3" "code/task4")
pushd `dirname $0` > /dev/null
CURR_PATH=`pwd -P` 
TEST_PATH="$CURR_PATH/.."
popd > /dev/null

i=0
while [ "x${files[$i]}" != "x" ]
do
    file=${files[$i]}
    my_file="$CURR_PATH/$file"
    student_file="$TEST_PATH/$file"
    if [ -e $student_file ]
    then
        res=`diff -w $my_file $student_file`
        if [ $? -eq 0 ]
        then
            printf "Diffing $file: PASS\n"
        else
            printf "Diffing $file: FAIL (files differ)\n"
            # echo `diff $my_file $student_file >& diff.txt`
            # printf "Diff output: "  
            # cat diff.txt
            # printf "\n" 
        fi
    else
        printf "Diffing $file: FAIL\n"
        printf "$file does not exist.\n"
    fi
    i=$i+1
done
