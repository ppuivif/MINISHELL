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
#	if [ -f "temp/minishell_test1.txt" ]
#	then
#		chmod 644 temp/minishell_test1.txt
#		rm temp/minishell_test1.txt
#	fi
	if [ -d "temp" ]
	then
		chmod 777 temp
		rm -r temp
	fi
}

function delete_test_file() {
	file="$1"

	if [ -f $file ]
	then
		chmod 644 $file
		rm $file
	fi
}

function delete_stderr_file() {
	file="$1"

	if [ -f $file ]
	then
		chmod 644 $file
		rm $file
	fi
}

run_test() {
    test_index=$1
    command=$2
	file_test=$3
    status=$4
    test="test$test_index\t$command\t"
    message=$test
    echo > "temp/minishell_test$test_index.txt"
    chmod 644 "temp/minishell_test$test_index.txt"
	exec 3> "temp/minishell_test$test_index.txt"
    echo "$command" | ./minishell 3 2>&1 >/dev/null
	status_output_minishell=$?
    if [ $status_output_minishell -eq $status ] && diff "temp/minishell_test$test_index.txt" "Tests/test$file_test.txt" > /dev/null
	then
        status_message="${GREEN} OK${NC}"
		delete_test_file "temp/minishell_test$test_index.txt"
    else
        status_message="${RED} KO${NC}"
		flag=$((flag + 1))
    fi
	# Calculate the length of the message
    message_length=${#message}
    # Calculate the number of spaces needed for alignment
    num_spaces=$((60 - message_length))
    #num_tabs=$((25 - message_length))
    # Create a string of spaces
	#tabs=$(printf "%${num_tabs}s" "" | tr ' ' '\t')
  #  spaces=$(printf "%-${num_spaces}s" "")
    spaces=$(printf "%-30s" "")
    # Print the message with aligned status
	if [ "$display" == "wrong_only" ]
	then
		if [ "$status_message" == "${RED} KO${NC}" ]
		then
			echo -e "${message}${spaces}${status_message}"
		fi
	else
			echo -e "${message}${spaces}${status_message}"
	fi
	#echo -e "$message"
}

: <<BLOCK_COMMENT
run_test() {
    test_index=$1
    command=$2
	file_test=$3
    status=$4
    test="test$test_index\t$command\t"
    message=$test
    echo > "temp/minishell_test$test_index.txt"
    chmod 644 "temp/minishell_test$test_index.txt"
    exec 3> "temp/minishell_test$test_index.txt"
    echo "$command"
	eval "$command"
    status_output_minishell=$?
    if [ $status_output_minishell -eq $status ] && diff "temp/minishell_test$test_index.txt" "Tests/test$file_test.txt" > /dev/null
	then
        status_message="${GREEN} OK${NC}"
    else
        status_message="${RED} KO${NC}"
		flag=$((flag + 1))
    fi
	# Calculate the length of the message
    message_length=${#message}
    # Calculate the number of spaces needed for alignment
    num_spaces=$((60 - message_length))
    # Create a string of spaces
    spaces=$(printf "%-${num_spaces}s" "")
    # Print the message with aligned status
	if [ "$display" == "wrong_only" ]
	then
		if [ "$status_message" == "${RED} KO${NC}" ]
		then
			echo -e "${message}${spaces}${status_message}"
		fi
	else
			echo -e "${message}${spaces}${status_message}"
	fi
	#echo -e "$message"
}
BLOCK_COMMENT

run_test_syntax_error() {
    test_index=$1
    command=$2
    status=$3
#	file_test=$3
    test="test$test_index\t$command\t"
    message=$test
	substring="syntax error"
    echo > "temp/minishell_test$test_index.txt"
    chmod 644 "temp/minishell_test$test_index.txt"
    echo > "temp/stderr2_minishell$test_index.txt"
    chmod 644 "temp/stderr2_minishell$test_index.txt"
	exec 3> "temp/minishell_test$test_index.txt"
    echo "$command" | ./minishell 3 1>/dev/null 2>"temp/stderr2_minishell$test_index.txt"
    status_output_minishell=$?
	if [ $status_output_minishell -eq $status ] &&
#	if [ $status_output_minishell -ne 0 ] &&
		grep "$substring" temp/stderr2_minishell$test_index.txt >/dev/null &&
		[ $(wc -c < "temp/minishell_test$test_index.txt") -eq 0 ]
	then
        status_message="${GREEN} OK${NC}"
		delete_test_file "temp/minishell_test$test_index.txt"
		delete_stderr_file "temp/stderr2_minishell$test_index.txt"
    else
        status_message="${RED} KO${NC}"
		flag=$((flag + 1))
    fi
	# Calculate the length of the message
    message_length=${#message}
    # Calculate the number of spaces needed for alignment
 #   num_spaces=$((60 - message_length))
    num_spaces=$((60 - 90))
    # Create a string of spaces
 #   spaces=$(printf "%-${num_spaces}s"	"")
    spaces=$(printf "%-30s"	"")
    # Print the message with aligned status
	if [ "$display" == "wrong_only" ]
	then
		if [ "$status_message" == "${RED} KO${NC}" ]
		then
			echo -e "${message}${spaces}${status_message}"
		fi
	else
			echo -e "${message}${spaces}${status_message}"
	fi
	#echo -e "$message"
}

mkdir temp
chmod 777 temp
flag=0
clear

# Function to handle the first choice
choice_one() {
	display="all"
}

# Function to handle the second choice
choice_two() {
    display="wrong_only"
}

echo "To display all tests choice 1"
echo "To display only wrong tests choice 2"
read -p "Enter your choice (1 or 2): " choice

# Handle the user's choice
case $choice in
    1)
        choice_one
        ;;
    2)
        choice_two
        ;;
#do not run    
	*)
        echo -e "${RED}Invalid choice. Please enter 1 or 2.${NC}"
        ;;
esac

run_test 1 "< infile.txt cat | cat > outfile.txt" 1 0
run_test 2 "<infile.txt cat | cat > outfile.txt" 1 0
run_test 3 "< infile.txt cat| cat > outfile.txt" 1 0
run_test 4 "< infile.txt cat |cat > outfile.txt" 1 0
run_test 5 "< infile.txt cat | cat >outfile.txt" 1 0
run_test 6 "<infile.txt cat|cat >outfile.txt" 1 0
run_test 7 "<	infile.txt cat | cat > outfile.txt" 1 0
run_test 8 "<		infile.txt cat | cat > outfile.txt" 1 0
run_test 9 "< infile.txt cat	| cat > outfile.txt" 1 0
run_test 10 "< infile.txt cat		| cat > outfile.txt" 1 0
run_test 11 "< infile.txt cat |	cat > outfile.txt" 1 0
run_test 12 "< infile.txt cat |		cat > outfile.txt" 1 0
run_test 13 "< infile.txt cat |	cat > outfile.txt" 1 0
run_test 14 "< infile.txt cat |		cat > outfile.txt" 1 0
run_test 15 "< infile.txt cat | cat	> outfile.txt" 1 0
run_test 16 "< infile.txt cat | cat		> outfile.txt" 1 0
run_test 17 "< infile.txt cat | cat >	outfile.txt" 1 0
run_test 18 "< infile.txt cat | cat >		outfile.txt" 1 0
run_test 19 "< infile.txt cat | cat > outfile.txt	" 1 0
run_test 20 "< infile.txt cat | cat > outfile.txt		" 1 0

run_test 21 "<< limiter cat | cat > outfile.txt" 21 0
run_test 22 "<<limiter cat | cat > outfile.txt" 21 0 \"" 1512 0
run_test 1513 "
run_test 36 "<< limiter cat | cat		> outfile.txt" 21 0
run_test 37 "<< limiter cat | cat >	outfile.txt" 21 0
run_test 38 "<< limiter cat | cat >		outfile.txt" 21 0
run_test 39 "<< limiter cat | cat > outfile.txt	" 21 0
run_test 40 "<< limiter cat | cat > outfile.txt		" 21 0

run_test 41 "< infile.txt cat | cat >> outfile.txt" 41 0
run_test 42 "<infile.txt cat | cat >> outfile.txt" 41 0
run_test 43 "< infile.txt cat| cat >> outfile.txt" 41 0
run_test 44 "< infile.txt cat |cat >> outfile.txt" 41 0
run_test 45 "< infile.txt cat | cat>> outfile.txt" 41 0
run_test 46 "< infile.txt cat | cat >>outfile.txt" 41 0
run_test 47 "<infile.txt cat|cat >>outfile.txt" 41 0
run_test 48 "< infile.txt cat | cat >> outfile.txt" 41 0
run_test 49 "<	infile.txt cat | cat >> outfile.txt" 41 0
run_test 50 "<		infile.txt cat | cat >> outfile.txt" 41 0
run_test 51 "< infile.txt cat	| cat >> outfile.txt" 41 0
run_test 52 "< infile.txt cat		| cat >> outfile.txt" 41 0
run_test 53 "< infile.txt cat |	cat >> outfile.txt" 41 0
run_test 54 "< infile.txt cat |		cat >> outfile.txt" 41 0
run_test 55 "< infile.txt cat | cat	>> outfile.txt" 41 0
run_test 56 "< infile.txt cat | cat		>> outfile.txt" 41 0
run_test 57 "< infile.txt cat | cat >>	outfile.txt" 41 0
run_test 58 "< infile.txt cat | cat >>		outfile.txt" 41 0
run_test 59 "< infile.txt cat | cat >> outfile.txt	" 41 0
run_test 60 "< infile.txt cat | cat >> outfile.txt		" 41 0

run_test 61 "<< limiter cat | cat >> outfile.txt" 61 0
run_test 62 "<<limiter cat | cat >> outfile.txt" 61 0
run_test 63 "<< limiter cat| cat >> outfile.txt" 61 0
run_test 64 "<< limiter cat |cat >> outfile.txt" 61 0
run_test 65 "<< limiter cat | cat>> outfile.txt" 61 0
run_test 66 "<< limiter cat | cat >>outfile.txt" 61 0
run_test 67 "<<limiter cat|cat >>outfile.txt" 61 0
run_test 68 "<< limiter cat | cat >> outfile.txt" 61 0
run_test 69 "<<	limiter cat | cat >> outfile.txt" 61 0
run_test 70 "<<		limiter cat | cat >> outfile.txt" 61 0
run_test 71 "<< limiter cat	| cat >> outfile.txt" 61 0
run_test 72 "<< limiter cat		| cat >> outfile.txt" 61 0
run_test 73 "<< limiter cat |	cat >> outfile.txt" 61 0
run_test 74 "<< limiter cat |		cat >> outfile.txt" 61 0
run_test 75 "<< limiter cat | cat	>> outfile.txt" 61 0
run_test 76 "<< limiter cat | cat		>> outfile.txt" 61 0
run_test 77 "<< limiter cat | cat >>	outfile.txt" 61 0
run_test 78 "<< limiter cat | cat >>		outfile.txt" 61 0
run_test 79 "<< limiter cat | cat >> outfile.txt	" 61 0
run_test 80 "<< limiter cat | cat >> outfile.txt		" 61 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 1 to 80\n"
else
	echo -e "end of test serie from 1 to 80"
fi

run_test 81 "< infile.txt < infile.txt" 81 0
run_test 82 "<infile.txt < infile.txt" 81 0
run_test 83 "< infile.txt <infile.txt" 81 0
run_test 84 "<infile.txt <infile.txt" 81 0
run_test 85 "<infile.txt<infile.txt" 81 0
run_test 86 "<infile.txt<infile.txt" 81 0
run_test 87 " <	infile.txt < infile.txt" 81 0
run_test 88 " < infile.txt	< infile.txt" 81 0
run_test 89 " < infile.txt <	infile.txt" 81 0
run_test 90 " < infile.txt < infile.txt	" 81 0
run_test 91 "< infile.txt < infile.txt < infile.txt" 91 0
run_test 92 "<infile.txt < infile.txt < infile.txt" 91 0
run_test 93 "< infile.txt <infile.txt < infile.txt" 91 0
run_test 94 "< infile.txt < infile.txt <infile.txt" 91 0
run_test 95 "< infile.txt < infile.txt < infile.txt" 91 0
run_test 96 "<infile.txt <infile.txt < infile.txt" 91 0
run_test 97 "<infile.txt <infile.txt <infile.txt" 91 0
run_test 98 "<infile.txt<infile.txt <infile.txt" 91 0
run_test 99 "<infile.txt<infile.txt<infile.txt" 91 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 81 to 99\n"
else
	echo -e "end of test serie from 81 to 99"
fi

run_test 100 "> outfile.txt > outfile.txt" 100 0
run_test 101 ">outfile.txt > outfile.txt" 100 0
run_test 102 "> outfile.txt >outfile.txt" 100 0
run_test 103 ">outfile.txt >outfile.txt" 100 0
run_test 104 ">outfile.txt>outfile.txt" 100 0
run_test 105 ">outfile.txt>outfile.txt" 100 0
run_test 106 " >	outfile.txt > outfile.txt" 100 0
run_test 107 " > outfile.txt	> outfile.txt" 100 0
run_test 108 " > outfile.txt >	outfile.txt" 100 0
run_test 109 " > outfile.txt > outfile.txt	" 100 0
run_test 110 "> outfile.txt > outfile.txt > outfile.txt" 110 0
run_test 111 ">outfile.txt > outfile.txt > outfile.txt" 110 0
run_test 112 "> outfile.txt >outfile.txt > outfile.txt" 110 0
run_test 113 "> outfile.txt > outfile.txt >outfile.txt" 110 0
run_test 114 "> outfile.txt > outfile.txt > outfile.txt" 110 0
run_test 115 ">outfile.txt >outfile.txt > outfile.txt" 110 0
run_test 116 ">outfile.txt >outfile.txt >outfile.txt" 110 0
run_test 117 ">outfile.txt>outfile.txt >outfile.txt" 110 0
run_test 118 ">outfile.txt>outfile.txt>outfile.txt" 110 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 100 to 118\n"
else
	echo -e "end of test serie from 100 to 118"
fi

run_test 120 "<< limiter1 << limiter2" 120 0
run_test 121 "<<limiter1 << limiter2" 120 0
run_test 122 "<< limiter1 <<limiter2" 120 0
run_test 123 "<<limiter1 <<limiter2" 120 0
run_test 124 "<<limiter1<<limiter2" 120 0
run_test 125 "<<limiter1<<limiter2" 120 0
run_test 126 " <<	limiter1 << limiter2" 120 0
run_test 127 " << limiter1	<< limiter2" 120 0
run_test 128 " << limiter1 <<	limiter2" 120 0
run_test 129 " << limiter1 << limiter2	" 120 0
run_test 130 "<< limiter1 << limiter2 << limiter3" 130 0
run_test 131 "<<limiter1 << limiter2 << limiter3" 130 0
run_test 132 "<< limiter1 <<limiter2 << limiter3" 130 0
run_test 133 "<< limiter1 << limiter2 <<limiter3" 130 0
run_test 134 "<< limiter1 << limiter2 << limiter3" 130 0
run_test 135 "<<limiter1 <<limiter2 << limiter3" 130 0
run_test 136 "<<limiter1 <<limiter2 <<limiter3" 130 0
run_test 137 "<<limiter1<<limiter2 <<limiter3" 130 0
run_test 138 "<<limiter1<<limiter2<<limiter3" 130 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 120 to 138\n"
else
	echo -e "end of test serie from 120 to 138"
fi

run_test 140 ">> outfile.txt >> outfile.txt" 140 0
run_test 141 ">>outfile.txt >> outfile.txt" 140 0
run_test 142 ">> outfile.txt >>outfile.txt" 140 0
run_test 143 ">>outfile.txt >>outfile.txt" 140 0
run_test 144 ">>outfile.txt>>outfile.txt" 140 0
run_test 145 ">>outfile.txt>>outfile.txt" 140 0
run_test 146 " >>	outfile.txt >> outfile.txt" 140 0
run_test 147 " >> outfile.txt	>> outfile.txt" 140 0
run_test 148 " >> outfile.txt >>	outfile.txt" 140 0
run_test 149 " >> outfile.txt >> outfile.txt	" 140 0
run_test 150 ">> outfile.txt >> outfile.txt >> outfile.txt" 150 0
run_test 151 ">>outfile.txt >> outfile.txt >> outfile.txt" 150 0
run_test 152 ">> outfile.txt >>outfile.txt >> outfile.txt" 150 0
run_test 153 ">> outfile.txt >> outfile.txt >>outfile.txt" 150 0
run_test 154 ">> outfile.txt >> outfile.txt >> outfile.txt" 150 0
run_test 155 ">>outfile.txt >>outfile.txt >> outfile.txt" 150 0
run_test 156 ">>outfile.txt >>outfile.txt >>outfile.txt" 150 0
run_test 157 ">>outfile.txt>>outfile.txt >>outfile.txt" 150 0
run_test 158 ">>outfile.txt>>outfile.txt>>outfile.txt" 150 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 140 to 158\n"
else
	echo -e "end of test serie from 140 to 158"
fi

run_test 160 "< 'infile.txt'" 160 0
run_test 161 "< \"infile.txt\"" 160 0
run_test 162 "< '\"infile.txt\"'" 162 0
run_test 163 "< \"'infile.txt'\"" 163 0
run_test 164 "< '\"'infile.txt'\"'" 164 0
run_test 165 "< \"'\"infile.txt\"'\"" 165 0
run_test 166 "> 'outfile.txt'" 166 0
run_test 167 "> \"outfile.txt\"" 166 0
run_test 168 "> '\"outfile.txt\"'" 168 0
run_test 169 "> \"'outfile.txt'\"" 169 0
run_test 170 "> '\"'outfile.txt'\"'" 170 0
run_test 171 "> \"'\"outfile.txt\"'\"" 171 0
run_test 172 "<< 'limiter'" 172 0
run_test 173 "<< \"limiter\"" 172 0
run_test 174 "<< '\"limiter\"'" 174 0
run_test 175 "<< \"'limiter'\"" 175 0
run_test 176 "<< '\"'limiter'\"'" 176 0
run_test 177 "<< \"'\"limiter\"'\"" 177 0
run_test 178 "<< '<limiter'" 178 0
run_test 179 "<< \"<limiter\"" 179 0

run_test 190 ">> 'outfile.txt'" 190 0
run_test 191 ">> \"outfile.txt\"" 190 0
run_test 192 ">> '\"outfile.txt\"'" 192 0
run_test 193 ">> \"'outfile.txt'\"" 193 0
run_test 194 ">> '\"'outfile.txt'\"'" 194 0
run_test 195 ">> \"'\"outfile.txt\"'\"" 195 0

if [ "$display" == "all" ]
then
	echo -e "end of test serie from 160 to 183\n"
else
	echo -e "end of test serie from 160 to 183"
fi


run_test 200 "\"< infile.txt\"" 200 0
run_test 210 "\"<< limiter\"" 210 0
run_test 220 "\"> output.txt\"" 220 0
run_test 230 "\">> output.txt\"" 230 0

if [ "$display" == "all" ]
then
	echo -e "end of test serie from 200 to 250\n"
else
	echo -e "end of test serie from 200 to 250"
fi








run_test 500 "'ls' -l" 500 0
run_test 501 "'ls' '-l'" 500 0
run_test 502 "\"ls\" -l" 500 0
run_test 503 "\"ls\" \"-l\"" 500 0
run_test 504 "\"ls\" '-l'" 500 0
run_test 505 "'ls' \"-l\"" 500 0

run_test 550 "ls -l | cat -e" 550 0
run_test 551 "ls '-l' | cat -e" 550 0
run_test 552 "ls -l | 'cat' -e" 550 0
run_test 553 "ls -l | cat '-e'" 550 0
run_test 554 "'ls' '-l' | cat -e" 550 0
run_test 555 "'ls' '-l' | 'cat' -e" 550 0
run_test 556 "'ls' '-l' | cat '-e'" 550 0
run_test 557 "'ls' '-l' | 'cat' '-e'" 550 0
run_test 558 "ls -l | 'cat' '-e'" 550 0
run_test 559 "ls -l | cat '-e'" 550 0
run_test 560 "ls '-l' | 'cat' -e" 550 0
run_test 561 "ls '-l' | cat '-e'" 550 0
run_test 562 "ls '-l' | 'cat' '-e'" 550 0
run_test 563 "ls -l | 'cat' '-e'" 550 0

run_test 564 "\"ls\" -l | cat -e" 550 0
run_test 565 "ls \"-l\" | cat -e" 550 0
run_test 566 "ls -l | \"cat\" -e" 550 0
run_test 567 "ls -l | cat \"-e\"" 550 0
run_test 568 "\"ls\" \"-l\" | cat -e" 550 0
run_test 569 "\"ls\" \"-l\" | \"cat\" -e" 550 0
run_test 570 "\"ls\" \"-l\" | cat \"-e\"" 550 0
run_test 571 "\"ls\" \"-l\" | \"cat\" \"-e\"" 550 0
run_test 572 "\"ls\" -l | \"cat\" \"-e\"" 550 0
run_test 573 "\"ls\" -l | cat \"-e\"" 550 0
run_test 574 "ls \"-l\" | \"cat\" -e" 550 0
run_test 575 "ls \"-l\" | cat \"-e\"" 550 0
run_test 576 "ls \"-l\" | \"cat\" \"-e\"" 550 0
run_test 577 "ls -l | \"cat\" \"-e\"" 550 0

run_test 578 "\"ls\" '-l' | cat -e" 550 0
run_test 579 "\"ls\" -l | 'cat' -e" 550 0
run_test 580 "\"ls\" -l | cat '-e'" 550 0
run_test 581 "\"ls\" '-l' | 'cat' -e" 550 0
run_test 582 "\"ls\" '-l' | cat '-e'" 550 0
run_test 583 "\"ls\" '-l' | 'cat' '-e'" 550 0
run_test 584 "\"ls\" -l | 'cat' '-e'" 550 0

run_test 585 "'ls' \"-l\" | cat -e" 550 0
run_test 586 "ls \"-l\" | 'cat' -e" 550 0
run_test 587 "ls \"-l\" | cat '-e'" 550 0
run_test 588 "'ls' \"-l\" | 'cat' -e" 550 0
run_test 589 "'ls' \"-l\" | cat '-e'" 550 0
run_test 590 "'ls' \"-l\" | 'cat' '-e'" 550 0
run_test 591 "ls -l | \"cat\" '-e'" 550 0
run_test 592 "'ls' -l | \"cat\" -e" 550 0
run_test 593 "ls '-l' | \"cat\" -e" 550 0
run_test 594 "'ls' '-l' | \"cat\" -e" 550 0
run_test 595 "'ls' '-l' | \"cat\" '-e'" 550 0
run_test 596 "ls '-l' | \"cat\" '-e'" 550 0
run_test 597 "'ls' -l | \"cat\" '-e'" 550 0
run_test 598 "'ls' -l | cat \"-e\"" 550 0
run_test 599 "ls '-l' | cat \"-e\"" 550 0
run_test 600 "ls -l | 'cat' \"-e\"" 550 0
run_test 601 "'ls' '-l' | cat \"-e\"" 550 0
run_test 602 "'ls' '-l' | 'cat' \"-e\"" 550 0
run_test 603 "ls '-l' | 'cat' \"-e\"" 550 0

run_test 604 "\"ls\" \"-l\" | cat -e" 550 0
run_test 605 "\"ls\" \"-l\" | 'cat' -e" 550 0
run_test 606 "\"ls\" \"-l\" | cat '-e'" 550 0
run_test 607 "\"ls\" \"-l\" | 'cat' '-e'" 550 0

run_test 608 "\"ls\" -l | \"cat\" -e" 550 0
run_test 609 "\"ls\" '-l' | \"cat\" -e" 550 0
run_test 610 "\"ls\" -l | \"cat\" '-e'" 550 0
run_test 611 "\"ls\" '-l' | \"cat\" '-e'" 550 0

run_test 612 "\"ls\" -l | cat \"-e\"" 550 0
run_test 613 "\"ls\" '-l' | cat \"-e\"" 550 0
run_test 614 "\"ls\" '-l' | 'cat' \"-e\"" 550 0
run_test 615 "\"ls\" -l | 'cat' \"-e\"" 550 0

run_test 616 "ls \"-l\" | \"cat\" -e" 550 0
run_test 617 "'ls' \"-l\" | \"cat\" -e" 550 0
run_test 618 "ls \"-l\" | \"cat\" '-e'" 550 0
run_test 619 "'ls' \"-l\" | \"cat\" '-e'" 550 0

run_test 620 "ls -l | \"cat\" \"-e\"" 550 0
run_test 621 "'ls' -l | \"cat\" \"-e\"" 550 0
run_test 622 "ls '-l' | \"cat\" \"-e\"" 550 0
run_test 623 "'ls' '-l' | \"cat\" \"-e\"" 550 0

run_test 624 "\"ls\" \"-l\" | \"cat\" -e" 550 0
run_test 625 "\"ls\" \"-l\" | \"cat\" '-e'" 550 0

run_test 626 "\"ls\" \"-l\" | cat \"-e\"" 550 0
run_test 627 "\"ls\" \"-l\" | 'cat' \"-e\"" 550 0

run_test 628 "\"ls\" -l | \"cat\" \"-e\"" 550 0
run_test 629 "\"ls\" '-l' | \"cat\" \"-e\"" 550 0

run_test 630 "ls \"-l\" | \"cat\" \"-e\"" 550 0
run_test 631 "'ls' \"-l\" | \"cat\" \"-e\"" 550 0

run_test 632 "\"ls\" \"-l\" | \"cat\" \"-e\"" 550 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 500 to 632\n"
else
	echo -e "end of test serie from 500 to 632"
fi

#invalid command version provisoire a supprimer
run_test 650 "'ls -l'" 650 0
run_test 651 "\"ls -l\"" 651 0
run_test 652 "'\"ls -l\"'" 652 0
run_test 653 "\"'ls -l'\"" 653 0
run_test 654 "'ls'-l" 654 0
run_test 655 "ls'-l'" 655 0
run_test 656 "\"ls\"-l" 656 0
run_test 657 "ls\"-l\"" 657 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 650 to 657\n"
else
	echo -e "end of test serie from 650 to 657"
fi

run_test 700 "'ls -l cat -e'" 700 0
run_test 701 "\"ls -l cat -e\"" 701 0
run_test 702 "'\"ls -l cat -e\"'" 702 0
run_test 703 "\"'ls -l cat -e'\"" 703 0

run_test 704 "'ls'-l cat -e" 704 0
run_test 705 "ls'-l' cat -e" 705 0
run_test 706 "\"ls\"-l cat -e" 706 0
run_test 707 "ls\"-l\" cat -e" 707 0

run_test 708 "'ls -l' cat -e" 708 0
run_test 709 "\"ls -l\" cat -e" 709 0
run_test 710 "'\"ls -l\"' cat -e" 710 0
run_test 711 "\"'ls -l'\" cat -e" 711 0

run_test 712 "'ls -l'cat -e" 712 0
run_test 713 "\"ls -l\"cat -e" 713 0
run_test 714 "'\"ls -l\"'cat -e" 714 0
run_test 715 "\"'ls -l'\"cat -e" 715 0

run_test 716 "'ls -l' 'cat' -e" 716 0
run_test 717 "\"ls -l\" 'cat' -e" 717 0
run_test 718 "'\"ls -l\"' 'cat' -e" 718 0
run_test 719 "\"'ls -l'\" 'cat' -e" 719 0


run_test 720 "'ls -l' cat '-e'" 720 0
run_test 721 "\"ls -l\" cat '-e'" 721 0
run_test 722 "'\"ls -l\"' cat '-e'" 722 0
run_test 723 "\"'ls -l'\" cat '-e'" 723 0
run_test 724 "'ls -l' 'cat' '-e'" 724 0
run_test 725 "\"ls -l\" 'cat' '-e'" 725 0
run_test 726 "'\"ls -l\"' 'cat' '-e'" 726 0
run_test 727 "\"'ls -l'\" 'cat' '-e'" 727 0
run_test 728 "'ls -l' \"cat\" '-e'" 728 0
run_test 729 "\"ls -l\" \"cat\" '-e'" 729 0
run_test 730 "'\"ls -l\"' \"cat\" '-e'" 730 0
run_test 731 "\"'ls -l'\" \"cat\" '-e'" 731 0
run_test 732 "'ls -l' \"cat\" \"-e\"" 732 0
run_test 733 "\"ls -l\" \"cat\" \"-e\"" 733 0
run_test 734 "'\"ls -l\"' \"cat\" \"-e\"" 734 0
run_test 735 "\"'ls -l'\" \"cat\" \"-e\"" 735 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 700 to 735\n"
else
	echo -e "end of test serie from 700 to 735"
fi

run_test 736 "'ls -l'cat '-e'" 736 0
run_test 737 "\"ls -l\"cat '-e'" 737 0
run_test 738 "'\"ls -l\"'cat '-e'" 738 0
run_test 739 "\"'ls -l'\"cat '-e'" 739 0
run_test 740 "'ls -l'cat \"-e\"" 740 0
run_test 741 "\"ls -l\"cat \"-e\"" 741 0
run_test 742 "'\"ls -l\"'cat \"-e\"" 742 0
run_test 743 "\"'ls -l'\"cat \"-e\"" 743 0
run_test 744 "'ls -l''cat' '-e'" 744 0
run_test 745 "\"ls -l\"'cat' '-e'" 745 0
run_test 746 "'\"ls -l\"''cat' '-e'" 746 0
run_test 747 "\"'ls -l'\"'cat' '-e'" 747 0
run_test 748 "'ls -l''cat' \"-e\"" 748 0
run_test 749 "\"ls -l\"'cat' \"-e\"" 749 0
run_test 750 "'\"ls -l\"''cat' \"-e\"" 750 0
run_test 751 "\"'ls -l'\"'cat' \"-e\"" 751 0
run_test 752 "'ls -l'\"cat\" '-e'" 752 0
run_test 753 "\"ls -l\"\"cat\" '-e'" 753 0
run_test 754 "'\"ls -l\"'\"cat\" '-e'" 754 0
run_test 755 "\"'ls -l'\"\"cat\" '-e'" 755 0
run_test 756 "'ls -l'\"cat\" \"-e\"" 756 0
run_test 757 "\"ls -l\"\"cat\" \"-e\"" 757 0
run_test 758 "'\"ls -l\"'\"cat\" \"-e\"" 758 0
run_test 759 "\"'ls -l'\"\"cat\" \"-e\"" 759 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 735 to 759\n"
else
	echo -e "end of test serie from 735 to 759"
fi

run_test 760 "'ls -l' cat'-e'" 760 0
run_test 761 "\"ls -l\" cat'-e'" 761 0
run_test 762 "'\"ls -l\"' cat'-e'" 762 0
run_test 763 "\"'ls -l'\" cat'-e'" 763 0
run_test 764 "'ls -l' 'cat''-e'" 764 0
run_test 765 "\"ls -l\" 'cat''-e'" 765 0
run_test 766 "'\"ls -l\"' 'cat''-e'" 766 0
run_test 767 "\"'ls -l'\" 'cat''-e'" 767 0
run_test 768 "'ls -l' \"cat\"'-e'" 768 0
run_test 769 "\"ls -l\" \"cat\"'-e'" 769 0
run_test 770 "'\"ls -l\"' \"cat\"'-e'" 770 0
run_test 771 "\"'ls -l'\" \"cat\"'-e'" 771 0
run_test 772 "'ls -l' \"cat\"\"-e\"" 772 0
run_test 773 "\"ls -l\" \"cat\"\"-e\"" 773 0
run_test 774 "'\"ls -l\"' \"cat\"\"-e\"" 774 0
run_test 775 "\"'ls -l'\" \"cat\"\"-e\"" 775 0
run_test 776 "\"ls\"'-l'cat\"-e\"" 776 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 760 to 776\n"
else
	echo -e "end of test serie from 760 to 776"
fi

run_test 1000 "'ls'-l'cat -e'" 1000 0
run_test 1001 "'ls'-l'cat  -e'" 1001 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 1000 to 1001\n"
else
	echo -e "end of test serie from 1000 to 1001"
fi

run_test 1100 "\\" 1100 0
run_test 1101 "\"\\\"" 1100 0
run_test 1102 "\"\\cat\"" 1102 0
run_test 1103 "'\'" 1103 0
run_test 1104 "'\cat'" 1104 0
run_test 1105 "(" 1105 0
run_test 1106 ")" 1106 0
run_test 1107 "()" 1107 0
run_test 1108 ";" 1108 0
run_test 1109 "\"'\"" 1109 0
run_test 1110 "@" 1110 0
run_test 1111 "\"@\"" 1110 0
run_test 1112 "*" 1112 0
run_test 1113 "\"*\"" 1112 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 1100 to 1200\n"
else
	echo -e "end of test serie from 1100 to 1200"
fi


export TEST="test_minishell"
run_test 1500 "\$TEST" 1500 0
run_test 1501 "\$DO_NOT_EXIST" 1501 0
run_test 1502 "'\$TEST'" 1502 0
run_test 1503 "\"\$TEST\"" 1503 0
run_test 1504 "'\"\$TEST\"'" 1504 0
run_test 1505 "\"'\"\$TEST\"'\"" 1505 0
run_test 1506 "\"'\$TEST'\"" 1506 0
run_test 1507 "'\"'\$TEST'\"'" 1507 0
run_test 1508 "\"\$TEST \$TEST\"" 1508 0
run_test 1509 "\" \$TEST\"" 1509 0
run_test 1510 "\"  \$TEST\"" 1510 0
run_test 1511 "\"\$TEST \"" 1511 0
run_test 1512 "\"\$TEST  \"" 1512 0
run_test 1513 "\" \$TEST \"" 1513 0
run_test 1514 "\"  \$TEST  \"" 1514 0
#run_test 1515 "\"	\$TEST\"" 1515 0 #pb with\t
#run_test 1516 "\"\t\t\$TEST\"" 1516 0 #pb with\t
#run_test 1517 "\"\$TEST\t\"" 1517 0 #pb with\t
#run_test 1518 "\"\$TEST\t\t\"" 1518 0 #pb with\t
#run_test 1519 "\"\t\$TEST\t\"" 1519 0 #pb with\t
#run_test 1520 "\"\t\t\$TEST\t\t\"" 1520 0 #pb with\t
#run_test 1521 "\" \$TEST\t\"" 1521 0 #pb with\t
#run_test 1522 "\"\t\$TEST \"" 1522 0 #pb with\t

run_test 1523 "\$\"TEST\"" 1523 0
run_test 1524 "\$'TEST'" 1524 0
run_test 1525 "\"\$ \"TEST\"\"" 1525 0
run_test 1526 "\"\$ 'TEST'\"" 1526 0

run_test 1530 "\" \$TEST \$TEST\"" 1530 0
run_test 1531 "\"  \$TEST \$TEST\"" 1531 0
run_test 1532 "\"\$TEST  \$TEST\"" 1532 0
run_test 1533 "\"\$TEST \$TEST \"" 1533 0
run_test 1534 "\"\$TEST \$TEST  \"" 1534 0
run_test 1535 "\" \$TEST  \$TEST\"" 1535 0
run_test 1536 "\" \$TEST  \$TEST \"" 1536 0
#run_test 1537 "\"\t\$TEST\t\$TEST\"" 1537 0//pb with\t
#run_test 1538 "\"\t\$TEST\t\$TEST\t\"" 1538 0//pb with\t
#run_test 1539 "\"\t\t\$TEST\t\t\$TEST\t\t\"" 1539 0//pb with\t
run_test 1540 "\$TEST\$TEST" 1540 0
run_test 1541 "\" \$TEST\$TEST\"" 1541 0
run_test 1542 "\"\$TEST\$TEST \"" 1542 0
run_test 1543 "\" \$TEST\$TEST \"" 1543 0
#run_test 1544 "\"	\$TEST\$TEST\"" 1544 0//pb with\t
#run_test 1545 "\"\$TEST\$TEST	\"" 1545 0//pb with\t
#run_test 1546 "\"	\$TEST\$TEST	\"" 1546 0//pb with\t

run_test 1550 "\"text\$TEST\"" 1550 0
run_test 1551 "\"text \$TEST\"" 1551 0
run_test 1552 "\" text \$TEST\"" 1552 0
run_test 1553 "\"text \$TEST \"" 1553 0
run_test 1554 "\"text \$TEST text\"" 1554 0
run_test 1555 "'text \$TEST text'" 1555 0
run_test 1556 "\"'text \$TEST text'\"" 1556 0
run_test 1557 "'\"text \$TEST text\"'" 1557 0
run_test 1558 "\"\$TEST text \$TEST\"" 1558 0

run_test 1559 "\"\$TEST cat\"" 1559 0
run_test 1560 "\"\$TEST cat \"" 1560 0
#run_test 1561 "\"\$TEST cat	\"" 1561 0//pb with\t

run_test 1562 "\$" 1562 0
run_test 1563 "\"\$ TEST\"" 1563 0
run_test 1564 "\$\"\"" 1564 0
run_test 1565 "\$''" 1565 0
run_test 1566 "\"\$\"\"\"" 1566 0
run_test 1567 "\"\$''\"" 1567 0
run_test 1568 "\"\$\" \"\"" 1568 0
run_test 1569 "\"\$' '\"" 1569 0
run_test 1570 "'\$'''" 1570 0
unset TEST
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 1500 to 1570\n"
else
	echo -e "end of test serie from 1500 to 1570"
fi

export INFILE="infile.txt"
run_test 1700 "< \$INFILE" 1700 0
run_test 1701 "< \$DO_NOT_EXIST" 1701 0
run_test 1702 "< '\$INFILE'" 1702 0
run_test 1703 "< \"\$INFILE\"" 1703 0
run_test 1704 "< '\"\$INFILE\"'" 1704 0
run_test 1705 "< \"'\"\$INFILE\"'\"" 1705 0
run_test 1706 "< \"\$INFILE \$INFILE\"" 1706 0
run_test 1707 "< \" \$INFILE\"" 1707 0
run_test 1708 "< \"  \$INFILE\"" 1708 0
run_test 1709 "< \"\$INFILE \"" 1709 0
run_test 1710 "< \"\$INFILE  \"" 1710 0
run_test 1711 "< \" \$INFILE \"" 1711 0
run_test 1712 "< \"  \$INFILE  \"" 1712 0
#run_test 1713 "< \"	\$INFILE\"" 1713 0
#run_test 1714 "< \"\$INFILE	\"" 1714 0
#run_test 1715 "< \"		\$INFILE\"" 1715 0
#run_test 1716 "< \"\$INFILE		\"" 1716 0
#run_test 1717 "< \"	\$INFILE	\"" 1717 0
#run_test 1718 "< \"		\$INFILE		\"" 1718 0
run_test 1719 "< \"INFILE \$INFILE\"" 1719 0
unset INFILE

export OUTFILE="outfile.txt"
run_test 1740 "> \$OUTFILE" 1740 0
run_test 1741 "> \$DO_NOT_EXIST" 1741 0
run_test 1742 "> '\$OUTFILE'" 1742 0
run_test 1743 "> \"\$OUTFILE\"" 1743 0
run_test 1744 "> '\"\$OUTFILE\"'" 1744 0
run_test 1745 "> \"'\"\$OUTFILE\"'\"" 1745 0
run_test 1746 "> \"\$OUTFILE \$OUTFILE\"" 1746 0
run_test 1747 "> \" \$OUTFILE\"" 1747 0
run_test 1748 "> \"  \$OUTFILE\"" 1748 0
run_test 1749 "> \"\$OUTFILE \"" 1749 0
run_test 1750 "> \"\$OUTFILE  \"" 1750 0
run_test 1751 "> \" \$OUTFILE \"" 1751 0
run_test 1752 "> \"  \$OUTFILE  \"" 1752 0
#run_test 1753 "> \"	\$OUTFILE\"" 1753 0
#run_test 1754 "> \"\$OUTFILE	\"" 1754 0
#run_test 1755 "> \"		\$OUTFILE\"" 1755 0
#run_test 1756 "> \"\$OUTFILE		\"" 1756 0
#run_test 1757 "> \"	\$OUTFILE	\"" 1757 0
#run_test 1758 "> \"		\$OUTFILE		\"" 1758 0
run_test 1759 "> \"OUTFILE \$OUTFILE\"" 1759 0
unset OUTFILE

export LIMITER="limiter"
run_test 1780 "<< \$LIMITER" 1780 0
run_test 1781 "<< \$DO_NOT_EXIST" 1781 0
run_test 1782 "<< '\$LIMITER'" 1782 0
run_test 1783 "<< \"\$LIMITER\"" 1782 0
run_test 1784 "<< '\"\$LIMITER\"'" 1784 0
run_test 1785 "<< \"'\"\$LIMITER\"'\"" 1785 0
run_test 1786 "<< \"\$LIMITER \$LIMITER\"" 1786 0
run_test 1787 "<< \" \$LIMITER\"" 1787 0
run_test 1788 "<< \"  \$LIMITER\"" 1788 0
run_test 1789 "<< \"\$LIMITER \"" 1789 0
run_test 1790 "<< \"\$LIMITER  \"" 1790 0
run_test 1791 "<< \" \$LIMITER \"" 1791 0
run_test 1792 "<< \"  \$LIMITER  \"" 1792 0
#run_test 1793 "<< \"	\$LIMITER\"" 1793 0
#run_test 1794 "<< \"\$LIMITER	\"" 1794 0
#run_test 1795 "<< \"		\$LIMITER\"" 1795 0
#run_test 1796 "<< \"\$LIMITER		\"" 1796 0
#run_test 1797 "<< \"	\$LIMITER	\"" 1797 0
#run_test 1798 "<< \"		\$LIMITER		\"" 1798 0
run_test 1799 "<< \"LIMITER \$LIMITER\"" 1799 0
unset LIMITER

export OUTFILE="outfile.txt"
run_test 1820 ">> \$OUTFILE" 1820 0
run_test 1821 ">> \$DO_NOT_EXIST" 1821 0
run_test 1822 ">> '\$OUTFILE'" 1822 0
run_test 1823 ">> \"\$OUTFILE\"" 1823 0
run_test 1824 ">> '\"\$OUTFILE\"'" 1824 0
run_test 1825 ">> \"'\"\$OUTFILE\"'\"" 1825 0
run_test 1826 ">> \"\$OUTFILE \$OUTFILE\"" 1826 0
run_test 1827 ">> \" \$OUTFILE\"" 1827 0
run_test 1828 ">> \"  \$OUTFILE\"" 1828 0
run_test 1829 ">> \"\$OUTFILE \"" 1829 0
run_test 1830 ">> \"\$OUTFILE  \"" 1830 0
run_test 1831 ">> \" \$OUTFILE \"" 1831 0
run_test 1832 ">> \"  \$OUTFILE  \"" 1832 0
#run_test 1833 ">> \"	\$OUTFILE\"" 1833 0
#run_test 1834 ">> \"\$OUTFILE	\"" 1834 0
#run_test 1835 ">> \"		\$OUTFILE\"" 1835 0
#run_test 1836 ">> \"\$OUTFILE		\"" 1836 0
#run_test 1837 ">> \"	\$OUTFILE	\"" 1837 0
#run_test 1838 ">> \"		\$OUTFILE		\"" 1838 0
unset OUTFILE

if [ "$display" == "all" ]
then
	echo -e "end of test serie from 1700 to 1900\n"
else
	echo -e "end of test serie from 1700 to 1900"
fi




run_test_syntax_error 2000 "<" 2
run_test_syntax_error 2001 "<<" 2
run_test_syntax_error 2002 "<<<" 2
run_test_syntax_error 2003 "<<<<" 2
run_test_syntax_error 2004 "<" 2
run_test_syntax_error 2005 "<<" 2
run_test_syntax_error 2006 "<<<" 2
run_test_syntax_error 2007 "<<<<" 2
run_test_syntax_error 2008 "<>" 2
run_test_syntax_error 2009 "><" 2
run_test_syntax_error 2010 "<><>" 2
run_test_syntax_error 2011 "><><" 2
run_test_syntax_error 2012 "<<>" 2
run_test_syntax_error 2013 "<<>>" 2
run_test_syntax_error 2014 "<<<>>>" 2
run_test_syntax_error 2015 "<<<<>>>>" 2
run_test_syntax_error 2016 ">><" 2
run_test_syntax_error 2017 ">><<" 2
run_test_syntax_error 2018 ">>><<<" 2
run_test_syntax_error 2019 ">>>><<<<" 2

run_test_syntax_error 2020 "ls <" 2
run_test_syntax_error 2021 "ls <<" 2
run_test_syntax_error 2022 "ls >" 2
run_test_syntax_error 2023 "ls >>" 2
run_test_syntax_error 2024 "ls<" 2
run_test_syntax_error 2025 "ls<<" 2
run_test_syntax_error 2026 "ls>" 2
run_test_syntax_error 2027 "ls>>" 2

run_test_syntax_error 2030 "|" 2
run_test_syntax_error 2031 " |" 2
run_test_syntax_error 2032 "  |" 2
run_test_syntax_error 2033 "| " 2
run_test_syntax_error 2034 "|  " 2
run_test_syntax_error 2035 " | " 2
run_test_syntax_error 2036 "  | " 2
run_test_syntax_error 2037 "  |  " 2
run_test_syntax_error 2038 "	|" 2
run_test_syntax_error 2039 "		|" 2
run_test_syntax_error 2040 "|	" 2
run_test_syntax_error 2041 "|		" 2
run_test_syntax_error 2042 "	|	" 2
run_test_syntax_error 2043 "		|		" 2

run_test_syntax_error 2050 "| ls" 2
run_test_syntax_error 2051 "|ls" 2
run_test_syntax_error 2052 " |ls" 2
run_test_syntax_error 2053 "ls |" 2
run_test_syntax_error 2054 "ls|" 2
run_test_syntax_error 2055 "ls| " 2

run_test_syntax_error 2060 "||" 2
run_test_syntax_error 2061 "| |" 2
run_test_syntax_error 2062 "|	|" 2
run_test_syntax_error 2063 "|||" 2
run_test_syntax_error 2064 "| | |" 2
run_test_syntax_error 2065 "|	|	|" 2
run_test_syntax_error 2066 "||||" 2
run_test_syntax_error 2067 "| | | |" 2
run_test_syntax_error 2068 "|	|	|	|" 2

run_test_syntax_error 2070 ">|" 2
run_test_syntax_error 2071 "<|" 2
run_test_syntax_error 2072 "|>" 2
run_test_syntax_error 2073 "|<" 2
run_test_syntax_error 2074 ">>|" 2
run_test_syntax_error 2075 "<<|" 2
run_test_syntax_error 2076 "|>>" 2
run_test_syntax_error 2077 "|<<" 2

run_test_syntax_error 2090 ">|>" 2
run_test_syntax_error 2091 "<|<" 2
run_test_syntax_error 2092 "<|>" 2
run_test_syntax_error 2093 ">|<" 2
run_test_syntax_error 2094 ">>|<<" 2
run_test_syntax_error 2095 "<<|>>" 2
run_test_syntax_error 2096 "<<|>>" 2
run_test_syntax_error 2097 ">>|<<" 2

run_test_syntax_error 2100 "|| ls" 2
run_test_syntax_error 2101 "||ls" 2
run_test_syntax_error 2102 "ls ||" 2
run_test_syntax_error 2103 "ls||" 2
run_test_syntax_error 2104 "||| ls" 2
run_test_syntax_error 2105 "|||ls" 2
run_test_syntax_error 2106 "ls |||" 2
run_test_syntax_error 2107 "ls|||" 2

run_test_syntax_error 2110 "ls || cat" 2
run_test_syntax_error 2111 "ls | | cat" 2
run_test_syntax_error 2112 "ls | cat |" 2
run_test_syntax_error 2113 "ls || cat |" 2


if [ "$display" == "all" ]
then
	echo -e "end of test serie from 2000 to 2113\n"
else
	echo -e "end of test serie from 2000 to 2113"
fi






run_test_syntax_error 3000 "<<< infile.txt" 2 #exit_status to confirm
run_test_syntax_error 3001 "<<<< infile.txt" 2
run_test_syntax_error 3002 "<<<<< infile.txt" 2
run_test_syntax_error 3003 "<<> infile.txt" 2
run_test_syntax_error 3004 "<<>> infile.txt" 2
run_test_syntax_error 3005 "<<>>> infile.txt" 2
run_test_syntax_error 3006 "<<>>>> infile.txt" 2
run_test_syntax_error 3007 "<<>< infile.txt" 2
run_test_syntax_error 3008 "<<><< infile.txt" 2
run_test_syntax_error 3009 "<<><<< infile.txt" 2
run_test_syntax_error 3010 "<<><<<< infile.txt" 2
run_test_syntax_error 3011 "<<><> infile.txt" 2
run_test_syntax_error 3012 "<<><>> infile.txt" 2
run_test_syntax_error 3013 "<<><>>> infile.txt" 2
run_test_syntax_error 3014 "<<><>>>> infile.txt" 2
run_test_syntax_error 3014 "<> infile.txt" 2
run_test_syntax_error 3015 "<>> infile.txt" 2
run_test_syntax_error 3016 "<>>> infile.txt" 2
run_test_syntax_error 3017 "<>>>> infile.txt" 2
run_test_syntax_error 3018 "<>>>>> infile.txt" 2
run_test_syntax_error 3019 "<>< infile.txt" 2
run_test_syntax_error 3020 "<><< infile.txt" 2
run_test_syntax_error 3021 "<><<< infile.txt" 2
run_test_syntax_error 3022 "<><<<< infile.txt" 2
run_test_syntax_error 3023 "<><> infile.txt" 2
run_test_syntax_error 3024 "<><>> infile.txt" 2
run_test_syntax_error 3025 "<><>>> infile.txt" 2
run_test_syntax_error 3026 "<><>>>> infile.txt" 2
run_test_syntax_error 3027 "<><>>>>> infile.txt" 2
run_test_syntax_error 3028 ">>> outfile.txt" 2
run_test_syntax_error 3029 ">>>> outfile.txt" 2
run_test_syntax_error 3030 ">>>>> outfile.txt" 2
run_test_syntax_error 3031 ">>>>>> outfile.txt" 2
run_test_syntax_error 3032 ">>< outfile.txt" 2
run_test_syntax_error 3033 ">><< outfile.txt" 2
run_test_syntax_error 3034 ">><<< outfile.txt" 2
run_test_syntax_error 3035 ">><<<< outfile.txt" 2
run_test_syntax_error 3036 ">><<<<< outfile.txt" 2
run_test_syntax_error 3037 ">><> outfile.txt" 2
run_test_syntax_error 3038 ">><>> outfile.txt" 2
run_test_syntax_error 3039 ">><>>> outfile.txt" 2
run_test_syntax_error 3040 ">><>>>> outfile.txt" 2
run_test_syntax_error 3041 ">><>>>>> outfile.txt" 2
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 3000 to 3041\n"
else
	echo -e "end of test serie from 3000 to 3041"
fi

run_test_syntax_error 3300 "< 'infile.txt" 2 #exit_status to confirm
run_test_syntax_error 3301 "< infile.txt'" 2
run_test_syntax_error 3302 "< \"infile.txt" 2
run_test_syntax_error 3303 "< infile.txt\"" 2
run_test_syntax_error 3304 "< 'infile.txt\"" 2
run_test_syntax_error 3305 "< 'infile.txt'\"" 2
#run_test_syntax_error 3306 "< \"infile.txt'\"" 2
run_test_syntax_error 3307 "< \"infile.txt\"'" 2
run_test_syntax_error 3308 "<< 'infile.txt" 2
run_test_syntax_error 3309 "<< infile.txt'" 2
run_test_syntax_error 3310 "<< \"infile.txt" 2
run_test_syntax_error 3311 "<< infile.txt\"" 2
run_test_syntax_error 3312 "<< 'infile.txt\"" 2
run_test_syntax_error 3313 "<< 'infile.txt'\"" 2
#run_test_syntax_error 3314 "<< \"infile.txt'\"" 2
run_test_syntax_error 3315 "<< \"infile.txt\"'" 2

run_test_syntax_error 3400 "> 'outfile.txt" 2
run_test_syntax_error 3401 "> outfile.txt'" 2
run_test_syntax_error 3402 "> \"outfile.txt" 2
run_test_syntax_error 3403 "> outfile.txt\"" 2
run_test_syntax_error 3404 "> 'outfile.txt\"" 2
run_test_syntax_error 3405 "> 'outfile.txt'\"" 2
#run_test_syntax_error 3406 "> \"outfile.txt'\"" 2
run_test_syntax_error 3407 "> \"outfile.txt\"'" 2
run_test_syntax_error 3408 ">> 'outfile.txt" 2
run_test_syntax_error 3409 ">> outfile.txt'" 2
run_test_syntax_error 3410 ">> \"outfile.txt" 2
run_test_syntax_error 3411 ">> outfile.txt\"" 2
run_test_syntax_error 3412 ">> 'outfile.txt\"" 2
run_test_syntax_error 3413 ">> 'outfile.txt'\"" 2
#run_test_syntax_error 3414 ">> \"outfile.txt'\"" 2
run_test_syntax_error 3415 ">> \"outfile.txt\"'" 2
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 3300 to 3415\n"
else
	echo -e "end of test serie from 3300 to 3415"
fi

run_test_syntax_error 4000 "'ls" 2 #exit_status to confirm
run_test_syntax_error 4001 "ls'" 2
run_test_syntax_error 4002 "\"ls" 2
run_test_syntax_error 4003 "ls\"" 2
run_test_syntax_error 4004 "'ls\"" 2
run_test_syntax_error 4005 "'ls'\"" 2
run_test_syntax_error 4006 "\"ls'" 2
run_test_syntax_error 4007 "\"ls\"'" 2
#run_test_syntax_error 4008 "''ls" 2
run_test_syntax_error 4009 "''ls'" 2
run_test_syntax_error 4010 "'''ls" 2
#run_test_syntax_error 4011 "'''ls'" 2
run_test_syntax_error 4012 "'''ls''" 2
#run_test_syntax_error 4013 "\"\"ls" 2
run_test_syntax_error 4014 "\"\"ls\"" 2
run_test_syntax_error 4015 "\"\"\"ls" 2
#run_test_syntax_error 4016 "\"\"\"ls\"" 2
run_test_syntax_error 4017 "\"\"\"ls\"\"" 2
#to continue


if [ "$display" == "all" ]
then
	echo -e "end of test serie from 4000 to 4017\n"
else
	echo -e "end of test serie from 4000 to 4017"
fi



run_test_syntax_error 4100 "cat 'ls" 2
run_test_syntax_error 4101 "cat ls'" 2
run_test_syntax_error 4102 "cat \"ls" 2
run_test_syntax_error 4103 "cat ls\"" 2
run_test_syntax_error 4104 "'cat' 'ls" 2
run_test_syntax_error 4105 "'cat' ls'" 2
run_test_syntax_error 4106 "'cat' ls'" 2
run_test_syntax_error 4107 "'cat' \"ls" 2
run_test_syntax_error 4108 "'cat' ls\"" 2
run_test_syntax_error 4109 ""cat" 'ls" 2
run_test_syntax_error 4110 ""cat" ls'" 2
run_test_syntax_error 4111 ""cat" ls'" 2
run_test_syntax_error 4112 ""cat" \"ls" 2
run_test_syntax_error 4113 ""cat" ls\"" 2
run_test_syntax_error 4114 "cat 'ls " 2
run_test_syntax_error 4115 "cat ls' " 2
run_test_syntax_error 4116 "cat \"ls " 2
run_test_syntax_error 4117 "cat ls\" " 2
run_test_syntax_error 4118 "cat 'ls  " 2
run_test_syntax_error 4119 "cat ls'  " 2
run_test_syntax_error 4120 "cat \"ls  " 2
run_test_syntax_error 4121 "cat ls\"  " 2
run_test_syntax_error 4122 "cat ' ls" 2
run_test_syntax_error 4123 "cat  ls'" 2
run_test_syntax_error 4124 "cat \" ls" 2
run_test_syntax_error 4125 "cat ls \"" 2
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 4100 to 4125\n"
else
	echo -e "end of test serie from 4100 to 4125"
fi

run_test_syntax_error 4300 "'" 2 #exit_status to confirm
run_test_syntax_error 4301 "\"" 2 #exit_status to confirm
run_test_syntax_error 4302 "\"\"\"" 2 #exit_status to confirm

if [ "$display" == "all" ]
then
	echo -e "end of test serie from 4300 to 4350\n"
else
	echo -e "end of test serie from 4300 to 4350"
fi



: <<BLOCK_COMMENT
#invalid command version definitive
run_test 650 "'ls -l'" 650 127
run_test 651 "\"ls -l\"" 651 127
run_test 652 "'\"ls -l\"'" 652 127
run_test 653 "\"'ls -l'\"" 653 127
run_test 654 "'ls'-l" 654 127
run_test 655 "ls'-l'" 655 127
run_test 656 "\"ls\"-l" 656 127
run_test 657 "ls\"-l\"" 657 127

run_test 700 "'ls -l cat -e'" 700 127
run_test 701 "\"ls -l cat -e\"" 701 127
run_test 702 "'\"ls -l cat -e\"'" 702 127
run_test 703 "\"'ls -l cat -e'\"" 703 127

run_test 704 "'ls'-l cat -e" 704 127
run_test 705 "ls'-l' cat -e" 705 127
run_test 706 "\"ls\"-l cat -e" 706 127
run_test 707 "ls\"-l\" cat -e" 707 127

run_test 708 "'ls -l' cat -e" 708 127
run_test 709 "\"ls -l\" cat -e" 709 127
run_test 710 "'\"ls -l\"' cat -e" 710 127
run_test 711 "\"'ls -l'\" cat -e" 711 127

run_test 712 "'ls -l'cat -e" 712 127
run_test 713 "\"ls -l\"cat -e" 713 127
run_test 714 "'\"ls -l\"'cat -e" 714 127
run_test 715 "\"'ls -l'\"cat -e" 715 127

run_test 716 "'ls -l' 'cat' -e" 716 127
run_test 717 "\"ls -l\" 'cat' -e" 717 127
run_test 718 "'\"ls -l\"' 'cat' -e" 718 127
run_test 719 "\"'ls -l'\" 'cat' -e" 719 127


run_test 720 "'ls -l' cat '-e'" 720 127
run_test 721 "\"ls -l\" cat '-e'" 721 127
run_test 722 "'\"ls -l\"' cat '-e'" 722 127
run_test 723 "\"'ls -l'\" cat '-e'" 723 127
run_test 724 "'ls -l' 'cat' '-e'" 724 127
run_test 725 "\"ls -l\" 'cat' '-e'" 725 127
run_test 726 "'\"ls -l\"' 'cat' '-e'" 726 127
run_test 727 "\"'ls -l'\" 'cat' '-e'" 727 127
run_test 728 "'ls -l' \"cat\" '-e'" 728 127
run_test 729 "\"ls -l\" \"cat\" '-e'" 729 127
run_test 730 "'\"ls -l\"' \"cat\" '-e'" 730 127
run_test 731 "\"'ls -l'\" \"cat\" '-e'" 731 127
run_test 732 "'ls -l' \"cat\" \"-e\"" 732 127
run_test 733 "\"ls -l\" \"cat\" \"-e\"" 733 127
run_test 734 "'\"ls -l\"' \"cat\" \"-e\"" 734 127
run_test 735 "\"'ls -l'\" \"cat\" \"-e\"" 735 127

run_test 736 "'ls -l'cat '-e'" 736 127
run_test 737 "\"ls -l\"cat '-e'" 737 127
run_test 738 "'\"ls -l\"'cat '-e'" 738 127
run_test 739 "\"'ls -l'\"cat '-e'" 739 127
run_test 740 "'ls -l'cat \"-e\"" 770 127
run_test 741 "\"ls -l\"cat \"-e\"" 741 127
run_test 742 "'\"ls -l\"'cat \"-e\"" 772 127
run_test 743 "\"'ls -l'\"cat \"-e\"" 743 127
run_test 744 "'ls -l''cat' '-e'" 744 127
run_test 745 "\"ls -l\"'cat' '-e'" 745 127
run_test 746 "'\"ls -l\"''cat' '-e'" 746 127
run_test 747 "\"'ls -l'\"'cat' '-e'" 747 127
run_test 748 "'ls -l''cat' \"-e\"" 748 127
run_test 749 "\"ls -l\"'cat' \"-e\"" 749 127
run_test 750 "'\"ls -l\"''cat' \"-e\"" 750 127
run_test 751 "\"'ls -l'\"'cat' \"-e\"" 751 127
run_test 752 "'ls -l'\"cat\" '-e'" 752 127
run_test 753 "\"ls -l\"\"cat\" '-e'" 753 127
run_test 754 "'\"ls -l\"'\"cat\" '-e'" 754 127
run_test 755 "\"'ls -l'\"\"cat\" '-e'" 755 127
run_test 756 "'ls -l'\"cat\" \"-e\"" 756 127
run_test 757 "\"ls -l\"\"cat\" \"-e\"" 757 127
run_test 758 "'\"ls -l\"'\"cat\" \"-e\"" 758 127
run_test 759 "\"'ls -l'\"\"cat\" \"-e\"" 759 127

run_test 760 "'ls -l' cat'-e'" 760 127
run_test 761 "\"ls -l\" cat'-e'" 761 127
run_test 762 "'\"ls -l\"' cat'-e'" 762 127
run_test 763 "\"'ls -l'\" cat'-e'" 763 127
run_test 764 "'ls -l' 'cat''-e'" 764 127
run_test 765 "\"ls -l\" 'cat''-e'" 765 127
run_test 766 "'\"ls -l\"' 'cat''-e'" 766 127
run_test 767 "\"'ls -l'\" 'cat''-e'" 767 127
run_test 768 "'ls -l' \"cat\"'-e'" 768 127
run_test 769 "\"ls -l\" \"cat\"'-e'" 769 127
run_test 770 "'\"ls -l\"' \"cat\"'-e'" 770 127
run_test 771 "\"'ls -l'\" \"cat\"'-e'" 771 127
run_test 772 "'ls -l' \"cat\"\"-e\"" 772 127
run_test 773 "\"ls -l\" \"cat\"\"-e\"" 773 127
run_test 774 "'\"ls -l\"' \"cat\"\"-e\"" 774 127
run_test 775 "\"'ls -l'\" \"cat\"\"-e\"" 775 127

BLOCK_COMMENT

# -g for greater than and -ge for greater than or equal to
if [ $flag -gt 0 ]
then
	echo -e "${RED}$flag errors were detected${NC}"
else
	echo -e "${GREEN}no error detected${NC}"
fi
#delete_test_files

: <<BLOCK_COMMENT

for i in {1..27}; do
    test_message="test$i\t< infile.txt cat | cat > outfile.txt\t"
    if [ ${#test_message} -gt $max_length ]; then
        max_length=${#test_message}
    fi
	done
for i in {1..27}; dorun_test 606 "\"ls\"-l" 606 127

    run_test $i "< infile.txt cat | cat > outfile.txt" $i
    test_message="test$i\t< infile.txt cat | cat > outfile.txt\t"
    padding=$((max_length - ${#test_message}))
    printf "%s%*s\n" "$test_message" $padding "$status_message"
done



	



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
test="test25\t<<	infile.txt cat | cat > outfile.txt\t\t"
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
chmod 644 temp/minishell_test101.txtdelete_test_files

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