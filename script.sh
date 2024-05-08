#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

function create_files_and_set_permissions() {
#	local file1="$1"
#	local file2="$2"
    
#	echo > "$file1"
#	chmod 644 "$file1"
#	echo > "$file2"
#	chmod 644 "$file2"
	echo -e "ceci est\nun test\n" > infile.txt
	echo > outfile_bash.txt
	chmod 644 outfile_bash.txt
	echo > stdout_bash.txt
	chmod 644 stdout_bash.txt
	echo > stderr1_bash.txt
	chmod 644 stderr1_bash.txt
	echo > stderr2_bash.txt
	chmod 644 stderr2_bash.txt
	echo > outfile_minishell.txt
	chmod 644 outfile_minishell.txt
	echo > stdout_minishell.txt
	chmod 644 stdout_minishell.txt
	echo > stderr1_minishell.txt
	chmod 644 stderr1_minishell.txt
	echo > stderr2_minishell.txt
	chmod 644 stderr2_minishell.txt
}

function delete_files() {
	if [ -f "infile.txt" ] # to check if the given path exists and is a regular file
	then
		chmod 644 infile.txt
		rm infile.txt
	fi
	if [ -f "outfile_bash.txt" ]
	then
		chmod 644 outfile_bash.txt
		rm outfile_bash.txt
	fi
	if [ -f "outfile_minishell.txt" ]
	then
		chmod 644 outfile_minishell.txt
		rm outfile_minishell.txt
	fi
	if [ -f "stdout_bash.txt" ]
	then
		chmod 644 stdout_bash.txt
		rm stdout_bash.txt
	fi
	if [ -f "stderr1_bash.txt" ]
	then
		chmod 644 stderr1_bash.txt
		rm stderr1_bash.txt
	fi
	if [ -f "stderr2_bash.txt" ]
	then
		chmod 644 stderr2_bash.txt
		rm stderr2_bash.txt
	fi
		if [ -f "stdout_minishell.txt" ]
	then
		chmod 644 stdout_minishell.txt
		rm stdout_minishell.txt
	fi
	if [ -f "stderr1_minishell.txt" ]
	then
		chmod 644 stderr1_minishell.txt
		rm stderr1_minishell.txt
	fi
	if [ -f "stderr2_minishell.txt" ]
	then
		chmod 644 stderr2_minishell.txt
		rm stderr2_minishell.txt
	fi
}

function error() {
	stderr1_bash="$1"
	stdout_bash="$2"
	stderr2_bash="$3"
	stderr1_minishell="$4"
	outfile_minishell="$5"
	stdout_minishell="$6"
	stderr2_minishell="$7"
	diff -q $stdout_bash $outfile_minishell
	diff_stdout=$?
	diff -q $stderr1_bash $stderr1_minishell
	diff_stderr1=$?
	diff -q $stderr2_bash $stderr2_minishell
	diff_stderr2=$?
#	if diff $stdout_bash $outfile_minishell > /dev/null
	if [ "$diff_stdout" -ne 0 ]
	then
		flag=1
		error+="stdout_bash :\n"
		error+=$(awk '{print "\t"$0}' $stdout_bash)
		error+="\noutfile_minishell :\n"
		error+=$(awk '{print "\t"$0}' $outfile_minishell)
		error+="\n\n"
	#	echo "stdout_bash :"
	#	awk '{print "\t"$0}' $stdout_bash
	#	echo "outfile_minishell :"
	#	awk '{print "\t"$0}' $outfile_minishell
	fi
	if [ "$diff_stderr1" -ne 0 ]
	then
		flag=1
		error+="stderr1_bash :\n"
		error+=$(awk '{print "\t"$0}' $stderr1_bash)
		error+="stderr1_minishell :\n"
		error+=$(awk '{print "\t"$0}' $stderr1_minishell)
		error+="\n"
	fi
	if [ "$diff_stderr2" -ne 0 ]
	then
		flag=1
		error+="stderr2_bash :\n"
		error+=$(awk '{print "\t"$0}' $stderr2_bash)
		error+="stderr2_minishell :\n"
		error+=$(awk '{print "\t"$0}' $stderr2_minishell)
		error+="\n"
	fi
	if [ "$8" != "$9" ]
	then
		flag=1
		error+="status_exit_bash : "
		error+=$(echo $8)
		error+="\nstatus_exit_minishell : "
		error+=$(echo $9)
		error+="\n"
	#	echo "status_output_bash : "
	#	printf "\t" && echo $6
	#	echo "status_output_minishell :"
	#	printf "\t" && echo $7
	#	echo -e
	fi
	if [ "$flag" == 1 ]
	then
		message+="${RED} KO${NC}"
		flag=0
	else
		message+="${GREEN} OK${NC}"
		flag=0
	fi
}

function display_files_content() {
	stderr1_bash="$1"
	stdout_bash="$2"
	stderr2_bash="$3"
	stderr1_minishell="$4"
	outfile_minishell="$5"
	stdout_minishell="$6"
	stderr2_minishell="$7"

	echo "stderr1_bash :"
	awk '{print "\t"$0}' $stderr1_bash
	echo "stdout_bash :"
#	printf "\t" && cat stdout_bash.txt
	awk '{print "\t"$0}' $stdout_bash
	echo "stderr2_bash :"
#	cat $stderr_bash
	awk '{print "\t"$0}' $stderr2_bash
#	echo -n "status_output_bash : " && cat $status_output_bash
#	echo -n "status_output_bash : " && awk '{print $0}' <<< "$status_output_bash"
#	awk -v var="$status_output_bash" 'BEGIN {print var}'
	printf "status_output_bash : " && echo $8
	echo -e
	echo "stderr1_minishell :"
	awk '{print "\t"$0}' $stderr1_minishell
	echo "outfile_minishell :"
	awk '{print "\t"$0}' $outfile_minishell
	echo "stderr2_minishell :"
	awk '{print "\t"$0}' $stderr2_minishell
	printf "status_output_minishell : " && echo $9
	echo -e
}

function delete_test_files() {
	if [ -f "temp/minishell_test1.txt" ]
	then
		chmod 644 temp/minishell_test1.txt
		rm temp/minishell_test1.txt
	fi
	if [ -d "temp" ]
	then
		chmod 777 temp
		rm -r temp
	fi
}

mkdir temp
chmod 777 temp
clear

#test1 : < infile.txt cat | cat > outfile.txt
test="test1\t< infile.txt cat | cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test1.txt
chmod 644 temp/minishell_test1.txt
# Get the file descriptor of minishell_test1.txt
exec 3> temp/minishell_test1.txt
# Run minishell and pipe the command into it
echo "< infile.txt cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test1.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test2 : <infile.txt cat | cat > outfile.txt
test="test2\t<infile.txt cat | cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test2.txt
chmod 644 temp/minishell_test2.txt
exec 3> temp/minishell_test2.txt
echo "<infile.txt cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test2.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test3 : < infile.txt cat| cat > outfile.txt
test="test3\t< infile.txt cat| cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test3.txt
chmod 644 temp/minishell_test3.txt
exec 3> temp/minishell_test3.txt
echo "< infile.txt cat| cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test3.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test4 : < infile.txt cat |cat > outfile.txt
test="test4\t< infile.txt cat |cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test4.txt
chmod 644 temp/minishell_test4.txt
exec 3> temp/minishell_test4.txt
echo "< infile.txt cat |cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test4.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test5 : < infile.txt cat | cat >outfile.txt
test="test5\t< infile.txt cat | cat >outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test5.txt
chmod 644 temp/minishell_test5.txt
exec 3> temp/minishell_test5.txt
echo "< infile.txt cat | cat >outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test5.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test6 : <infile.txt cat|cat >outfile.txt
test="test6\t<infile.txt cat|cat >outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test6.txt
chmod 644 temp/minishell_test6.txt
exec 3> temp/minishell_test6.txt
echo "<infile.txt cat|cat >outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test6.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test7 : <\tinfile.txt cat | cat > outfile.txt
test="test7\t<\tinfile.txt cat | cat > outfile.txt\t\t"
message=$test
echo > temp/minishell_test7.txt
chmod 644 temp/minishell_test7.txt
exec 3> temp/minishell_test7.txt
echo "<	infile.txt cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test7.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test8 : <\t\tinfile.txt cat | cat > outfile.txt
test="test8\t<\t\tinfile.txt cat | cat > outfile.txt\t"
message=$test
echo > temp/minishell_test8.txt
chmod 644 temp/minishell_test8.txt
exec 3> temp/minishell_test8.txt
echo "<		infile.txt cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test8.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test9 : < infile.txt\tcat | cat > outfile.txt
test="test9\t< infile.txt\tcat | cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test9.txt
chmod 644 temp/minishell_test9.txt
exec 3> temp/minishell_test9.txt
echo "<infile.txt	cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test9.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test10 : < infile.txt\t\tcat | cat > outfile.txt
test="test10\t< infile.txt\t\tcat | cat > outfile.txt\t\t"
message=$test
echo > temp/minishell_test10.txt
chmod 644 temp/minishell_test10.txt
exec 3> temp/minishell_test10.txt
echo "<infile.txt		cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test10.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test11 : < infile.txt cat\t| cat > outfile.txt
test="test11\t< infile.txt cat\t| cat > outfile.txt\t\t"
message=$test
echo > temp/minishell_test11.txt
chmod 644 temp/minishell_test11.txt
exec 3> temp/minishell_test11.txt
echo "<infile.txt cat	| cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test11.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test12 : < infile.txt cat\t\t| cat > outfile.txt
test="test12\t< infile.txt cat\t\t| cat > outfile.txt\t"
message=$test
echo > temp/minishell_test12.txt
chmod 644 temp/minishell_test12.txt
exec 3> temp/minishell_test12.txt
echo "<infile.txt cat		| cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test12.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test13 : < infile.txt cat |\tcat > outfile.txt
test="test13\t< infile.txt cat |\tcat > outfile.txt\t\t"
message=$test
echo > temp/minishell_test13.txt
chmod 644 temp/minishell_test13.txt
exec 3> temp/minishell_test13.txt
echo "<infile.txt cat |	cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test13.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test14 : < infile.txt cat |\t\tcat > outfile.txt
test="test14\t< infile.txt cat |\t\tcat > outfile.txt\t"
message=$test
echo > temp/minishell_test14.txt
chmod 644 temp/minishell_test14.txt
exec 3> temp/minishell_test14.txt
echo "<infile.txt cat |		cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test14.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test15 : < infile.txt cat | cat\t> outfile.txt
test="test15\t< infile.txt cat | cat\t> outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test15.txt
chmod 644 temp/minishell_test15.txt
exec 3> temp/minishell_test15.txt
echo "<infile.txt cat |	cat	> outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test15.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test16 : < infile.txt cat | cat\t\t> outfile.txt
test="test16\t< infile.txt cat | cat\t\t> outfile.txt\t\t"
message=$test
echo > temp/minishell_test16.txt
chmod 644 temp/minishell_test16.txt
exec 3> temp/minishell_test16.txt
echo "<infile.txt cat |	cat		> outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test16.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test17 : < infile.txt cat | cat >\toutfile.txt
test="test17\t< infile.txt cat | cat >\toutfile.txt\t\t"
message=$test
echo > temp/minishell_test17.txt
chmod 644 temp/minishell_test17.txt
exec 3> temp/minishell_test17.txt
echo "<infile.txt cat |	cat	>	outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test17.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test18 : < infile.txt cat | cat >\t\toutfile.txt
test="test18\t< infile.txt cat | cat >\t\toutfile.txt\t"
message=$test
echo > temp/minishell_test18.txt
chmod 644 temp/minishell_test18.txt
exec 3> temp/minishell_test18.txt
echo "<infile.txt cat |	cat	>		outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test18.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test19 : < infile.txt cat | cat > outfile.txt\t\t
test="test19\t< infile.txt cat | cat > toutfile.txt\t\t\t"
message=$test
echo > temp/minishell_test19.txt
chmod 644 temp/minishell_test19.txt
exec 3> temp/minishell_test19.txt
echo "<infile.txt cat |	cat	> outfile.txt		" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test19.txt Tests/test1.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test20 : << infile.txt cat | cat > outfile.txt
test="test20\t<< infile.txt cat | cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test20.txt
chmod 644 temp/minishell_test20.txt
exec 3> temp/minishell_test20.txt
echo "<< infile.txt cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test20.txt Tests/test20.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test21 : <<infile.txt cat | cat > outfile.txt
test="test21\t<<infile.txt cat | cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test21.txt
chmod 644 temp/minishell_test21.txt
exec 3> temp/minishell_test21.txt
echo "<<infile.txt cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test21.txt Tests/test20.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test22 : << infile.txt cat| cat > outfile.txt
test="test22\t<< infile.txt cat| cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test22.txt
chmod 644 temp/minishell_test22.txt
exec 3> temp/minishell_test22.txt
echo "<< infile.txt cat| cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test22.txt Tests/test20.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test23 : << infile.txt cat |cat > outfile.txt
test="test23\t<< infile.txt cat |cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test23.txt
chmod 644 temp/minishell_test23.txt
exec 3> temp/minishell_test23.txt
echo "<< infile.txt cat |cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test23.txt Tests/test20.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test24 : << infile.txt cat | cat >outfile.txt
test="test24\t<< infile.txt cat | cat >outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test24.txt
chmod 644 temp/minishell_test24.txt
exec 3> temp/minishell_test24.txt
echo "<< infile.txt cat | cat >outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test24.txt Tests/test20.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test25 : <<\tinfile.txt cat | cat > outfile.txt
test="test25\t<<\tinfile.txt cat | cat > outfile.txt\t\t"
message=$test
echo > temp/minishell_test25.txt
chmod 644 temp/minishell_test25.txt
exec 3> temp/minishell_test25.txt
echo "<<	infile.txt cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test25.txt Tests/test20.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""


#test26 : <<\t\tinfile.txt cat | cat > outfile.txt
test="test26\t<<\t\tinfile.txt cat | cat > outfile.txt\t"
message=$test
echo > temp/minishell_test26.txt
chmod 644 temp/minishell_test26.txt
exec 3> temp/minishell_test26.txt
echo "<<		infile.txt cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test26.txt Tests/test20.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test27 : < infile.txt cat | cat >> outfile.txt
test="test27\t< infile.txt cat | cat >> outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test27.txt
chmod 644 temp/minishell_test27.txt
exec 3> temp/minishell_test27.txt
echo "< infile.txt cat | cat >> outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test27.txt Tests/test27.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test100 : < infile.txt 'cat' | cat > outfile.txt
test="test100\t< infile.txt 'cat' | cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test100.txt
chmod 644 temp/minishell_test100.txt
exec 3> temp/minishell_test100.txt
echo "< infile.txt 'cat' | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test100.txt Tests/test100.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""

#test101 : < infile.txt ' ' cat | cat > outfile.txt
test="test101\t< infile.txt ' ' cat | cat > outfile.txt\t\t\t"
message=$test
echo > temp/minishell_test101.txt
chmod 644 temp/minishell_test101.txt
exec 3> temp/minishell_test101.txt
echo "< infile.txt ' ' cat | cat > outfile.txt" | ./minishell 3 2>&1 >/dev/null
status_output_minishell=$?
if [ $status_output_minishell -eq 0 ] &&
	diff temp/minishell_test101.txt Tests/test100.txt > /dev/null
then
	message+="${GREEN} OK${NC}"
else
	message+="${RED} KO${NC}"
fi
echo -e "$message"
message=""


delete_test_files



: <<BLOCK_COMMENT
#test2 : outfile doesn't exist
test="test2\toutfile doesn't exist\t\t"
message=$test
create_files_and_set_permissions
rm outfile_bash.txt
rm outfile_minishell.txt
< infile.txt cat -e 2>stderr1_bash.txt | cat -e > outfile_bash.txt >stdout_bash.txt 2>stderr2_bash.txt
status_output_bash=$?
./minishell infile.txt "cat -e" 2>stderr1_minishell "cat -e" outfile_minishell.txt >stdout_minishell.txt 2>stderr2_minishell.txt
status_output_minishell=$?
#display_files_content stderr1_bash.txt stdout_bash.txt stderr2_bash.txt stderr1_minishell.txt outfile_minishell.txt stdout_minishell.txt stderr2_minishell.txt "$status_output_bash" "$status_output_minishell"
error stderr1_bash.txt stdout_bash.txt stderr2_bash.txt stderr1_minishell.txt outfile_minishell.txt stdout_minishell.txt stderr2_minishell.txt "$status_output_bash" "$status_output_minishell"
if [ $status_output_bash == $status_output_minishell ] &&
	diff stdout_bash.txt outfile_minishell.txt > /dev/null &&
	[ $(wc -c < "stdout_minishell.txt") -eq 0 ] &&
	diff stderr1_bash.txt stderr1_minishell.txt > /dev/null &&
	diff stderr2_bash.txt stderr2_minishell.txt > /dev/null
then
	echo -e "${GREEN}$test : \n\tinfile exists\n\toutfile doesn't exist\n\tcmd1 : \"cat -e\"\n\tcmd2 : \"cat -e\"\n${NC}" >> test.txt
else
	echo -e "${RED}$test : \n\tinfile exists\n\toutfile doesn't exist\n\tcmd1 : \"cat -e\"\n\tcmd2 : \"cat -e\"\n${NC}" >> test.txt 
fi
delete_files
echo -e "$message"
echo -e "$error"
message=""
error=""

#test3 : no permission on outfile
test="test3\tno permission on outfile\t"
message=$test
create_files_and_set_permissions
chmod 044 outfile_bash.txt
chmod 044 outfile_minishell.txt
substring="Permission denied"
#< infile.txt cat -e 2>stderr1_bash.txt | cat -e > outfile_bash.txt >stdout_bash.txt 2>stderr2_bash.txt
#status_output_bash=$?
./minishell infile.txt "cat -e" 2>stderr1_minishell.txt "cat -e" outfile_minishell.txt >stdout_minishell.txt 2>stderr2_minishell.txt
#display_files_content stderr1_bash.txt stdout_bash.txt stderr2_bash.txt stderr1_minishell.txt outfile_minishell.txt stdout_minishell.txt stderr2_minishell.txt "$status_output_bash" "$status_output_minishell"
status_output_minishell=$?
if grep "$substring" stderr2_minishell.txt >/dev/null &&
	[ $status_output_minishell == 1 ]
# && diff stdout_bash.txt outfile_minishell.txt > /dev/null to verify result of cmd2
then
	message+="${GREEN} OK${NC}"
	echo -e "${GREEN}$test : \n\tinfile exists\n\toutfile exists without any permissions\n\tcmd1 : \"cat -e\"\n\tcmd2 : \"cat -e\"\n${NC}" >> test.txt
else
	message+="${RED} KO${NC}"
	echo -e "${RED}$test : \n\tinfile exists\n\toutfile exists without any permissions\n\tcmd1 : \"cat -e\"\n\tcmd2 : \"cat -e\"\n${NC}" >> test.txt
fi
delete_files
echo -e "$message"
message=""


#test4 : infile doesn't exist
test="test4\tinfile doesn't exist\t\t"
message=$test
create_files_and_set_permissions
rm infile.txt
substring="No such file or directory"
#< infile.txt cat -e 2>stderr1_bash.txt | cat -e > outfile_bash.txt >stdout_bash.txt 2>stderr2_bash.txt
./minishell infile.txt "cat -e" 2>stderr1_minishell.txt "cat -e" outfile_minishell.txt >stdout_minishell.txt 2>stderr2_minishell.txt
if grep "$substring" stderr2_minishell.txt >/dev/null &&
	[ $status_output_minishell == 0 ]
# && diff stdout_bash.txt outfile_minishell.txt > /dev/null to verify result of cmd2
then
	message+="${GREEN} OK${NC}"
	echo -e "${GREEN}$test : \n\tinfile doesn't exist\n\toutfile exists\n\tcmd1 : \"cat -e\"\n\tcmd2 : \"wc -l\"\n${NC}" >> test.txt
else
	message+="${RED} KO${NC}"
	echo -e "${RED}$test : \n\tinfile doesn't exist\n\toutfile exists\n\tcmd1 : \"cat -e\"\n\tcmd2 : \"wc -l\"\n${NC}" >> test.txt
fi
delete_files
echo -e "$message"
message=""

: <<BLOCK_COMMENT

#test5 : no permission on infile
test="test5"
message=$test
create_files_and_set_permissions
chmod 044 infile.txt
output_bash=$(< infile.txt ls -l | wc -l > outfile_bash.txt 2>&1 >/dev/null)
output_minishell=$(./minishell infile.txt "ls -l" "wc -l" outfile_minishell.txt 2>&1)
#if grep "$substring" stderr_minishell.txt >/dev/null # && diff stdout_bash.txt outfile_minishell.txt > /dev/null to verify result of cmd2
if diff outfile_bash.txt outfile_minishell.txt > /dev/null && [ $result_executing_bash == $result_executing_minishell ]
then
	message+="${RED} KO${NC}"
	echo -e "${RED}$test : \n\tinfile exists\n\tinfile exists without any permissions\n\tcmd1 : \"ls -l\"\n\tcmd2 : \"wc -l\"\n${NC}" >> test.txt
else
	message+="${GREEN} OK${NC}"
	echo -e "${GREEN}$test : \n\tinfile exists\n\tinfile exists without any permissions\n\tcmd1 : \"ls -l\"\n\tcmd2 : \"wc -l\"\n${NC}" >> test.txt
fi
delete_files
echo -e "$message"
message=""

#test6 : cmd1 invalid
test="test6"
message=$test
create_files_and_set_permissions
< infile.txt invalid | wc -l > outfile_bash.txt
error_output_bash=$?
./minishell infile.txt "invalid" "wc -l" outfile_minishell.txt
error_output_minishell=$?
if diff outfile_bash.txt outfile_minishell.txt > /dev/null && [ $error_output_bash == $error_output_minishell ]
then
	message+="${GREEN} OK${NC}"
	echo -e "${GREEN}$test : \n\tinfile exists\n\toutfile exists\n\tcmd1 : \"invalid\"\n\tcmd2 : \"wc -l\"\n${NC}" >> test.txt
else
	message+="${RED} KO${NC}"
	echo -e "${RED}$test : \n\tinfile exists\n\toutfile exists\n\tcmd1 : \"invalid\"\n\tcmd2 : \"wc -l\"\n${NC}" >> test.txt
fi
delete_files
echo -e "$message"
message=""

#test7 : cmd2 invalid
test="test7"
message=$test
create_files_and_set_permissions
< infile.txt cat -e | invalid > outfile_bash.txt
error_output_bash=$?
#echo $error_output_bash
./minishell infile.txt "cat -e" "invalid" outfile_minishell.txt
error_output_minishell=$?
#echo $error_output_minishell
if diff outfile_bash.txt outfile_minishell.txt > /dev/null && [ $error_output_bash == $error_output_minishell ]
then
	message+="${GREEN} OK${NC}"
	echo -e "${GREEN}$test : \n\tinfile exists\n\toutfile exists\n\tcmd1 : \"cat -e\"\n\tcmd2 : \"invalid\"\n${NC}" >> test.txt
else
	message+="${RED} KO${NC}"
	echo -e "${RED}$test : \n\tinfile exists\n\toutfile exists\n\tcmd1 : \"cat -e\"\n\tcmd2 : \"invalid\"\n${NC}" >> test.txt
fi
delete_files
echo -e "$message"
message=""

#test8 : to build
test="test8"
message=$test
create_files_and_set_permissions
< infile.txt cat -e | invalid > outfile_bash.txt
error_output_bash=$?
#echo $error_output_bash
./minishell infile.txt "cat -e" "invalid" outfile_minishell.txt
error_output_minishell=$?
#echo $error_output_minishell
if diff outfile_bash.txt outfile_minishell.txt > /dev/null && [ $error_output_bash == $error_output_minishell ]
then
	message+="${GREEN} OK${NC}"
	echo -e "${GREEN}$test : \n\tinfile exists\n\toutfile exists\n\tcmd1 : \"cat -e\"\n\tcmd2 : \"invalid\"\n${NC}" >> test.txt
else
	message+="${RED} KO${NC}"
	echo -e "${RED}$test : \n\tinfile exists\n\toutfile exists\n\tcmd1 : \"cat -e\"\n\tcmd2 : \"invalid\"\n${NC}" >> test.txt
fi
delete_files
echo -e "$message"
message=""

BLOCK_COMMENT

exit