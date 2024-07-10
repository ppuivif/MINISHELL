#!/bin/bash

# Define global variables for index range
start_index=0
end_index=0

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

function create_temp_directory() {
	mkdir temp
	chmod 777 temp
	flag=0
	clear
}

function create_files_and_set_permissions() {
	test_index=$1
	echo -e "ceci est\nun test1\n" > temp/infile1.txt
	echo -e "ceci est\nun test2\n" > temp/infile2.txt
	echo -e "ceci est\nun test3\n" > temp/infile3.txt
	echo > temp/outfile1.txt
	chmod 644 temp/outfile1.txt
	echo > temp/outfile2.txt
	chmod 644 temp/outfile2.txt
	echo > temp/outfile3.txt
	chmod 644 temp/outfile3.txt
	echo > "temp/$test_index-minishell_stdout.txt"
    chmod 644 "temp/$test_index-minishell_stdout.txt"
#	exec 100> "temp/minishell_stdout$test_index.txt"
	echo > "temp/$test_index-minishell_stderr.txt"
    chmod 644 "temp/$test_index-minishell_stderr.txt"
#	exec 101> "temp/minishell_stderr$test_index.txt"
	echo > "temp/$test_index-bash_stdout.txt"
    chmod 644 "temp/$test_index-bash_stdout.txt"
#	exec 200> "temp/bash_stdout$test_index.txt"
	echo > "temp/$test_index-bash_stderr.txt"
    chmod 644 "temp/$test_index-bash_stderr.txt"
#	exec 201> "temp/bash_stderr$test_index.txt"
	echo > "temp/tmp_to_read_command.txt"
    chmod 644 "temp/tmp_to_read_command.txt"
	exec 100< "temp/tmp_to_read_command.txt"
	echo > "temp/tmp_to_execute_valgrind.txt"
    chmod 644 "temp/tmp_to_execute_valgrind.txt"
	exec 101< "temp/tmp_to_execute_valgrind.txt"
}

function delete_infiles() {
	if [ -f "temp/infile1.txt" ] # to check if the given path exists and is a regular file
	then
		chmod 644 temp/infile1.txt
		rm temp/infile1.txt
	fi
	if [ -f "temp/infile2.txt" ]
	then
		chmod 644 temp/infile2.txt
		rm temp/infile2.txt
	fi
	if [ -f "temp/infile3.txt" ]
	then
		chmod 644 temp/infile3.txt
		rm temp/infile3.txt
	fi
}

function delete_outfiles() {
	if [ -f "temp/outfile1.txt" ]
	then
		chmod 644 temp/outfile1.txt
		rm temp/outfile1.txt
	fi
	if [ -f "temp/outfile2.txt" ]
	then
		chmod 644 temp/outfile2.txt
		rm temp/outfile2.txt
	fi
	if [ -f "temp/outfile3.txt" ]
	then
		chmod 644 temp/outfile3.txt
		rm temp/outfile3.txt
	fi
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

function delete_file() {
	file="$1"

	if [ -f $file ]
	then
		chmod 644 $file
		rm $file
	fi
}


execute_test() {
	test_type=$1
    test_index=$2
    command=$3
	file_test=$4
    exit_code_expected=$5
 	substring=$6
 	invalid_test=$7
	test="test$test_index\t$command\t"
    message=$test
    
	create_files_and_set_permissions $test_index

#: << BLOCK_COMMENT

	if [ "$test_type" == "heredoc1" ]
	then
	heredoc1_content="line1
line2"

	full_command="${command}
${heredoc1_content}
limiter1"
	else
		full_command="$command" 
	fi

	limiter="limiter"

	heredoc_input=$(cat << 'EOF'
echo -e "first_line\n"
EOF
)


	echo "$full_command" >"temp/tmp_to_read_command.txt"
#	echo "$heredoc_input" >"temp/tmp_to_read_command.txt"
#	cat "temp/tmp_to_read_command.txt"


#	eval "$full_command"
	eval "$full_command" 1>"temp/$test_index-bash_stdout.txt" 2>"temp/$test_index-bash_stderr.txt"
	exit_code_bash=$?
#	echo "exit_code_bash"
#	echo "$exit_code_bash"
	cat "temp/outfile1.txt" >"temp/$test_index-bash_outfile1.txt"
	cat "temp/outfile2.txt" >"temp/$test_index-bash_outfile2.txt"
	
	echo > temp/outfile1.txt
	echo > temp/outfile2.txt	
    
#	./minishell 100
	./minishell 100 1>"temp/$test_index-minishell_stdout.txt" 2>"temp/$test_index-minishell_stderr.txt"
	exit_code_minishell=$?
#	echo "exit_code_minishell"
#	echo "$exit_code_minishell"
	cat "temp/outfile1.txt" >"temp/$test_index-minishell_outfile1.txt"
	cat "temp/outfile2.txt" >"temp/$test_index-minishell_outfile2.txt"
	delete_file "temp/tmp_to_read_command.txt"
	exec 100>&-

	echo "$full_command" >"temp/tmp_to_execute_valgrind.txt"
	echo "exit" >>"temp/tmp_to_execute_valgrind.txt"


	if [ "$run_valgrind" == "yes" ]
	then
#	 	valgrind --suppressions=readline.supp --leak-check=full --track-fds=yes --trace-children=yes --error-exitcode=1 ./minishell 101
 		valgrind --suppressions=readline.supp --leak-check=full --trace-children=yes --error-exitcode=10 ./minishell 101 1>/dev/null 2>&1
#		beware : if minishell exit_code is 10, script will consider it as a valgrind_error	
		exit_code_valgrind=$?
#		echo "exit_code_valgrind"
#		echo "$exit_code_valgrind"
	else
		exit_code_valgrind=0
	fi


	diff_outfile1=$(diff "temp/$test_index-minishell_outfile1.txt" "temp/$test_index-bash_outfile1.txt" > /dev/null)
	diff_exit_outfile1=$?
	diff_outfile2=$(diff "temp/$test_index-minishell_outfile2.txt" "temp/$test_index-bash_outfile2.txt" > /dev/null)
	diff_exit_outfile2=$?
	diff_stdout=$(diff "temp/$test_index-minishell_stdout.txt" "temp/$test_index-bash_stdout.txt" > /dev/null)
	diff_exit_stdout=$?
	
	empty_substring=""
	if [ "$substring" = "$empty_substring" ] && [ ! -s "temp/$test_index-minishell_stderr.txt" ]
	then
		diff_empty_substring=0
	else
		diff_empty_substring=1
	fi
 	diff_stderr=$(grep "$substring" temp/$test_index-minishell_stderr.txt >/dev/null)
	diff_exit_stderr=$?
	
	if [ $diff_exit_outfile1 -eq 1 ]
	then
		status1="KO"
		error_detail1="${RED}outfile1.txt ${NC}"
		flag=$((flag + 1))
	else
		status1="OK"
		delete_file "temp/$test_index-minishell_outfile1.txt"
		delete_file "temp/$test_index-bash_outfile1.txt"
	fi
	
	if [ $diff_exit_outfile2 -eq 1 ]
	then
		status2="KO"
		error_detail2="${RED}outfile2.txt ${NC}"
		flag=$((flag + 1))
	else
		status2="OK"
		delete_file "temp/$test_index-minishell_outfile2.txt"
		delete_file "temp/$test_index-bash_outfile2.txt"
	fi
	
	if [ $diff_exit_stdout -eq 1 ]
	then
		status3="KO"
		error_detail3="${RED}std_output ${NC}"
		flag=$((flag + 1))
	else
		status3="OK"
		delete_file "temp/$test_index-minishell_stdout.txt"
		delete_file "temp/$test_index-bash_stdout.txt"
	fi
	
	if [ $diff_exit_stderr -eq 0 ] || [ $diff_empty_substring -eq 0 ]
#	if	grep "$substring" temp/minishell_stderr$test_index.txt >/dev/null
	then
		status4="OK"
		delete_file "temp/$test_index-minishell_stderr.txt"
		delete_file "temp/$test_index-bash_stderr.txt"
	else	
#		echo "$substring"
		status4="KO"
		error_detail4="${RED}stderr_output ${NC}"
		flag=$((flag + 1))
    fi

	if [ "$exit_code_minishell" -ne "$exit_code_bash" ]
	then
		status5="KO"
		error_detail5="${RED}exit_code ${NC}"
		flag=$((flag + 1))
	else
		status5="OK"
		status_message="${GREEN} OK${NC}"
    fi

	if [ $exit_code_valgrind -eq 10 ]
	then
		status6="KO"
		error_detail6="${RED}valgrind_error ${NC}"
		flag=$((flag + 1))
	else
		status6="OK"
		status_message="${GREEN} OK${NC}"
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
		if [ "$status1" == "KO" ] || [ "$status2" == "KO" ] || [ "$status3" == "KO" ] || [ "$status4" == "KO" ] || [ "$status5" == "KO" ] || [ "$status6" == "KO" ]
		then
			status_message="${RED} KO : ${NC}"
			echo -e "${message}${spaces}${test_index}${status_message}${error_detail1}${error_detail2}${error_detail3}${error_detail4}${error_detail5}${error_detail6}${invalid_test}"
		fi
	else
		if [ "$status1" == "KO" ] || [ "$status2" == "KO" ] || [ "$status3" == "KO" ] || [ "$status4" == "KO" ] || [ "$status5" == "KO" ] || [ "$status6" == "KO" ]
		then
			status_message="${RED} KO : ${NC}"
			echo -e "${message}${spaces}${test_index}${status_message}${error_detail1}${error_detail2}${error_detail3}${error_detail4}${error_detail5}${error_detail6}${invalid_test}"
		else
			status_message="${GREEN} OK${NC}"
			echo -e "${message}${spaces}${status_message}"
		fi
	fi
	substring=""
	delete_infiles
	delete_outfiles
	delete_file "temp/tmp_to_execute_valgrind.txt"
	exec 101>&-
}

create_temp_directory

run_test() {
	index=$2
	if (( index >= "$start_index" && index <= "$end_index" ))
	then
		execute_test "$@"
	fi
}

choice_one() {
	execute="all"
	start_index=1
	end_index=20000
}

choice_two() {
	execute="parsing"
	start_index=1
	end_index=4999
}

choice_three() {
	execute="execution"
	start_index=5000
	end_index=20000
}

choice_four() {
	execute="free_choice"
	read -p "Enter the start of the range: " start_index
    read -p "Enter the end of the range: " end_index
	echo ""
#	if [ start_index < 0 ] || [ end_index > 10000 ]
#	then
#		echo "Invalid range. Please enter valid numbers and ensure start is less than or equal to end."
#    fi
}

#: << BLOCK_COMMENT
echo "To execute all tests choice 1"
echo "To execute only parsing tests choice 2"
echo "To execute only tests choice 3"
echo "To execute specify tests choice 4"
read -p "Enter your choice : " choice
echo ""

# Handle the user's choice
case $choice in
    1)
        choice_one
        ;;
    2)
        choice_two
        ;;
    3)
        choice_three
        ;;
    4)
        choice_four
        ;;
#do not work    
	*)
        echo -e "${RED}Invalid choice. Please enter 1 or 2.${NC}"
        ;;
esac


choice_one() {
	run_valgrind="yes"
}

choice_two() {
    run_valgrind="no"
}

echo "To run valgrind_test choice 1"
echo "Not to run valgrind_test choice 2"
echo "Warning : running tests with valgrind will execute the script slower"  
read -p "Enter your choice (1 or 2): " choice
echo ""

# Handle the user's choice
case $choice in
    1)
        choice_one
        ;;
    2)
        choice_two
        ;;
#do not work    
	*)
        echo -e "${RED}Invalid choice. Please enter 1 or 2.${NC}"
        ;;
esac






#BLOCK_COMMENT

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
echo ""

# Handle the user's choice
case $choice in
    1)
        choice_one
        ;;
    2)
        choice_two
        ;;
#do not work    
	*)
        echo -e "${RED}Invalid choice. Please enter 1 or 2.${NC}"
        ;;
esac



run_test "simple" 1 "< temp/infile1.txt cat | cat > temp/outfile1.txt" 1 0
run_test "simple" 2 "<temp/infile1.txt cat | cat > temp/outfile1.txt" 1 0
run_test "simple" 3 "< temp/infile1.txt cat| cat > temp/outfile1.txt" 1 0
run_test "simple" 4 "< temp/infile1.txt cat |cat > temp/outfile1.txt" 1 0
run_test "simple" 5 "< temp/infile1.txt cat | cat >temp/outfile1.txt" 1 0
run_test "simple" 6 "<temp/infile1.txt cat|cat >temp/outfile1.txt" 1 0
run_test "simple" 7 "<	temp/infile1.txt cat | cat > temp/outfile1.txt" 1 0
run_test "simple" 8 "<		temp/infile1.txt cat | cat > temp/outfile1.txt" 1 0
run_test "simple" 9 "< temp/infile1.txt cat	| cat > temp/outfile1.txt" 1 0
run_test "simple" 10 "< temp/infile1.txt cat		| cat > temp/outfile1.txt" 1 0
run_test "simple" 11 "< temp/infile1.txt cat |	cat > temp/outfile1.txt" 1 0
run_test "simple" 12 "< temp/infile1.txt cat |		cat > temp/outfile1.txt" 1 0
run_test "simple" 13 "< temp/infile1.txt cat |	cat > temp/outfile1.txt" 1 0
run_test "simple" 14 "< temp/infile1.txt cat |		cat > temp/outfile1.txt" 1 0
run_test "simple" 15 "< temp/infile1.txt cat | cat	> temp/outfile1.txt" 1 0
run_test "simple" 16 "< temp/infile1.txt cat | cat		> temp/outfile1.txt" 1 0
run_test "simple" 17 "< temp/infile1.txt cat | cat >	temp/outfile1.txt" 1 0
run_test "simple" 18 "< temp/infile1.txt cat | cat >		temp/outfile1.txt" 1 0
run_test "simple" 19 "< temp/infile1.txt cat | cat > temp/outfile1.txt	" 1 0
run_test "simple" 20 "< temp/infile1.txt cat | cat > temp/outfile1.txt		" 1 0


#run_test "heredoc1" 21 "<< limiter1 cat" 21 0
#run_test "heredoc" 21 "<< limiter1 cat | cat > outfile1.txt" 21 0
#run_test_heredoc 22 "<<limiter1 cat | cat > outfile1.txt" 21 0
#run_test_heredoc 36 "<< limiter1 cat | cat		> outfile1.txt" 21 0
#run_test_heredoc 37 "<< limiter1 cat | cat >	outfile1.txt" 21 0
#run_test_heredoc 38 "<< limiter1 cat | cat >		outfile1.txt" 21 0
#run_test_heredoc 39 "<< limiter1 cat | cat > outfile1.txt	" 21 0
#run_test_heredoc 40 "<< limiter1 cat | cat > outfile1.txt		" 21 0

run_test "simple" 41 "< temp/infile1.txt cat | cat >> temp/outfile1.txt" 41 0
run_test "simple" 42 "<temp/infile1.txt cat | cat >> temp/outfile1.txt" 41 0
run_test "simple" 43 "< temp/infile1.txt cat| cat >> temp/outfile1.txt" 41 0
run_test "simple" 44 "< temp/infile1.txt cat |cat >> temp/outfile1.txt" 41 0
run_test "simple" 45 "< temp/infile1.txt cat | cat>> temp/outfile1.txt" 41 0
run_test "simple" 46 "< temp/infile1.txt cat | cat >>temp/outfile1.txt" 41 0
run_test "simple" 47 "<temp/infile1.txt cat|cat >>temp/outfile1.txt" 41 0
run_test "simple" 48 "< temp/infile1.txt cat | cat >> temp/outfile1.txt" 41 0
run_test "simple" 49 "<	temp/infile1.txt cat | cat >> temp/outfile1.txt" 41 0
run_test "simple" 50 "<		temp/infile1.txt cat | cat >> temp/outfile1.txt" 41 0
run_test "simple" 51 "< temp/infile1.txt cat	| cat >> temp/outfile1.txt" 41 0
run_test "simple" 52 "< temp/infile1.txt cat		| cat >> temp/outfile1.txt" 41 0
run_test "simple" 53 "< temp/infile1.txt cat |	cat >> temp/outfile1.txt" 41 0
run_test "simple" 54 "< temp/infile1.txt cat |		cat >> temp/outfile1.txt" 41 0
run_test "simple" 55 "< temp/infile1.txt cat | cat	>> temp/outfile1.txt" 41 0
run_test "simple" 56 "< temp/infile1.txt cat | cat		>> temp/outfile1.txt" 41 0
run_test "simple" 57 "< temp/infile1.txt cat | cat >>	temp/outfile1.txt" 41 0
run_test "simple" 58 "< temp/infile1.txt cat | cat >>		temp/outfile1.txt" 41 0
run_test "simple" 59 "< temp/infile1.txt cat | cat >> temp/outfile1.txt	" 41 0
run_test "simple" 60 "< temp/infile1.txt cat | cat >> temp/outfile1.txt		" 41 0

if (( "$start_index" >= 1 && "$start_index" <= 60 && "$end_index" >= 1 && "$end_index" <= 60 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 1 to 60\n"
	else
		echo -e "end of test serie from 1 to 60"
	fi
fi

: <<BLOCK_COMMENT


#run_test_heredoc 61 "<< limiter1 cat | cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 62 "<<limiter1 cat | cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 63 "<< limiter1 cat| cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 64 "<< limiter1 cat |cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 65 "<< limiter1 cat | cat>> temp/outfile1.txt" 61 0
#run_test_heredoc 66 "<< limiter1 cat | cat >>temp/outfile1.txt" 61 0
#run_test_heredoc 67 "<<limiter1 cat|cat >>temp/outfile1.txt" 61 0
#run_test_heredoc 68 "<< limiter1 cat | cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 69 "<<	limiter1 cat | cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 70 "<<		limiter1 cat | cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 71 "<< limiter1 cat	| cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 72 "<< limiter1 cat		| cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 73 "<< limiter1 cat |	cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 74 "<< limiter1 cat |		cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 75 "<< limiter1 cat | cat	>> temp/outfile1.txt" 61 0
#run_test_heredoc 76 "<< limiter1 cat | cat		>> temp/outfile1.txt" 61 0
#run_test_heredoc 77 "<< limiter1 cat | cat >>	temp/outfile1.txt" 61 0
#run_test_heredoc 78 "<< limiter1 cat | cat >>		temp/outfile1.txt" 61 0
#run_test_heredoc 79 "<< limiter1 cat | cat >> temp/outfile1.txt	" 61 0
#run_test_heredoc 80 "<< limiter1 cat | cat >> temp/outfile1.txt		" 61 0

if (( "$start_index" >= 61 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 61 to 80\n"
	else
		echo -e "end of test serie from 61 to 80"
	fi
fi

BLOCK_COMMENT

run_test "simple" 81 "< temp/infile1.txt < temp/infile2.txt" 81 0
run_test "simple" 82 "<temp/infile1.txt < temp/infile2.txt" 81 0
run_test "simple" 83 "< temp/infile1.txt <temp/infile2.txt" 81 0
run_test "simple" 84 "<temp/infile1.txt <temp/infile2.txt" 81 0
run_test "simple" 85 "<temp/infile1.txt<temp/infile2.txt" 81 0
run_test "simple" 86 "<temp/infile1.txt<temp/infile2.txt" 81 0
run_test "simple" 87 " <	temp/infile1.txt < temp/infile2.txt" 81 0
run_test "simple" 88 " < temp/infile1.txt	< temp/infile2.txt" 81 0
run_test "simple" 89 " < temp/infile1.txt <	temp/infile2.txt" 81 0
run_test "simple" 90 " < temp/infile1.txt < temp/infile2.txt	" 81 0
run_test "simple" 91 "< temp/infile1.txt < temp/infile2.txt < temp/infile3.txt" 91 0
run_test "simple" 92 "<temp/infile1.txt < temp/infile2.txt < temp/infile3.txt" 91 0
run_test "simple" 93 "< temp/infile1.txt <temp/infile2.txt < temp/infile3.txt" 91 0
run_test "simple" 94 "< temp/infile1.txt < temp/infile2.txt <temp/infile3.txt" 91 0
run_test "simple" 95 "< temp/infile1.txt < temp/infile2.txt < temp/infile3.txt" 91 0
run_test "simple" 96 "<temp/infile1.txt <temp/infile2.txt < temp/infile3.txt" 91 0
run_test "simple" 97 "<temp/infile1.txt <temp/infile2.txt <temp/infile3.txt" 91 0
run_test "simple" 98 "<temp/infile1.txt<temp/infile2.txt <temp/infile3.txt" 91 0
run_test "simple" 99 "<temp/infile1.txt<temp/infile2.txt<temp/infile3.txt" 91 0

if (( "$start_index" >= 81 && "$start_index" <= 99 && "$end_index" >= 81 && "$end_index" <= 99 ))
#if [ "$execution" == "all" ] || [ "$execution" == "parsing" ]
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 81 to 99\n"
	else
		echo -e "end of test serie from 81 to 99"
	fi
fi

run_test "simple" 100 "> temp/outfile1.txt > temp/outfile2.txt" 100 0
run_test "simple" 101 ">temp/outfile1.txt > temp/outfile2.txt" 100 0
run_test "simple" 102 "> temp/outfile1.txt >temp/outfile2.txt" 100 0
run_test "simple" 103 ">temp/outfile1.txt >temp/outfile2.txt" 100 0
run_test "simple" 104 ">temp/outfile1.txt>temp/outfile2.txt" 100 0
run_test "simple" 105 ">temp/outfile1.txt>temp/outfile2.txt" 100 0
run_test "simple" 106 " >	temp/outfile1.txt > temp/outfile2.txt" 100 0
run_test "simple" 107 " > temp/outfile1.txt	> temp/outfile2.txt" 100 0
run_test "simple" 108 " > temp/outfile1.txt >	temp/outfile2.txt" 100 0
run_test "simple" 109 " > temp/outfile1.txt > temp/outfile2.txt	" 100 0
run_test "simple" 110 "> temp/outfile1.txt > temp/outfile2.txt > temp/outfile3.txt" 110 0
run_test "simple" 111 ">temp/outfile1.txt > temp/outfile2.txt > temp/outfile3.txt" 110 0
run_test "simple" 112 "> temp/outfile1.txt >temp/outfile2.txt > temp/outfile3.txt" 110 0
run_test "simple" 113 "> temp/outfile1.txt > temp/outfile2.txt >temp/outfile3.txt" 110 0
run_test "simple" 114 "> temp/outfile1.txt > temp/outfile2.txt > temp/outfile3.txt" 110 0
run_test "simple" 115 ">temp/outfile1.txt >temp/outfile2.txt > temp/outfile3.txt" 110 0
run_test "simple" 116 ">temp/outfile1.txt >temp/outfile2.txt >temp/outfile3.txt" 110 0
run_test "simple" 117 ">temp/outfile1.txt>temp/outfile2.txt >temp/outfile3.txt" 110 0
run_test "simple" 118 ">temp/outfile1.txt>temp/outfile2.txt>temp/outfile3.txt" 110 0

if (( "$start_index" >= 100 && "$start_index" <= 118 && "$end_index" >= 100 && "$end_index" <= 118 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 100 to 118\n"
	else
		echo -e "end of test serie from 100 to 118"
	fi
fi


#run_test_heredoc 120 "<< limiter1 << limiter2" 120 0
#run_test_heredoc 121 "<<limiter1 << limiter2" 120 0
#run_test_heredoc 122 "<< limiter1 <<limiter2" 120 0
#run_test_heredoc 123 "<<limiter1 <<limiter2" 120 0
#run_test_heredoc 124 "<<limiter1<<limiter2" 120 0
#run_test_heredoc 125 "<<limiter1<<limiter2" 120 0
#run_test_heredoc 126 " <<	limiter1 << limiter2" 120 0
#run_test_heredoc 127 " << limiter1	<< limiter2" 120 0
#run_test_heredoc 128 " << limiter1 <<	limiter2" 120 0
#run_test_heredoc 129 " << limiter1 << limiter2	" 120 0
#run_test_heredoc 130 "<< limiter1 << limiter2 << limiter3" 130 0
#run_test_heredoc 131 "<<limiter1 << limiter2 << limiter3" 130 0
#run_test_heredoc 132 "<< limiter1 <<limiter2 << limiter3" 130 0
#run_test_heredoc 133 "<< limiter1 << limiter2 <<limiter3" 130 0
#run_test_heredoc 134 "<< limiter1 << limiter2 << limiter3" 130 0
#run_test_heredoc 135 "<<limiter1 <<limiter2 << limiter3" 130 0
#run_test_heredoc 136 "<<limiter1 <<limiter2 <<limiter3" 130 0
#run_test_heredoc 137 "<<limiter1<<limiter2 <<limiter3" 130 0
#run_test_heredoc 138 "<<limiter1<<limiter2<<limiter3" 130 0

if (( "$start_index" >= 120 && "$start_index" <= 138 && "$end_index" >= 120 && "$end_index" <= 138 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 120 to 138\n"
	else
		echo -e "end of test serie from 120 to 138"
	fi
fi

run_test "simple" 140 ">> temp/outfile1.txt >> temp/outfile2.txt" 140 0
run_test "simple" 141 ">>temp/outfile1.txt >> temp/outfile2.txt" 140 0
run_test "simple" 142 ">> temp/outfile1.txt >>temp/outfile2.txt" 140 0
run_test "simple" 143 ">>temp/outfile1.txt >>temp/outfile2.txt" 140 0
run_test "simple" 144 ">>temp/outfile1.txt>>temp/outfile2.txt" 140 0
run_test "simple" 145 ">>temp/outfile1.txt>>temp/outfile2.txt" 140 0
run_test "simple" 146 " >>	temp/outfile1.txt >> temp/outfile2.txt" 140 0
run_test "simple" 147 " >> temp/outfile1.txt	>> temp/outfile2.txt" 140 0
run_test "simple" 148 " >> temp/outfile1.txt >>	temp/outfile2.txt" 140 0
run_test "simple" 149 " >> temp/outfile1.txt >> temp/outfile2.txt	" 140 0
run_test "simple" 150 ">> temp/outfile1.txt >> temp/outfile2.txt >> temp/outfile3.txt" 150 0
run_test "simple" 151 ">>temp/outfile1.txt >> temp/outfile2.txt >> temp/outfile3.txt" 150 0
run_test "simple" 152 ">> temp/outfile1.txt >>temp/outfile2.txt >> temp/outfile3.txt" 150 0
run_test "simple" 153 ">> temp/outfile1.txt >> temp/outfile2.txt >>temp/outfile3.txt" 150 0
run_test "simple" 154 ">> temp/outfile1.txt >> temp/outfile2.txt >> temp/outfile3.txt" 150 0
run_test "simple" 155 ">>temp/outfile1.txt >>temp/outfile2.txt >> temp/outfile3.txt" 150 0
run_test "simple" 156 ">>temp/outfile1.txt >>temp/outfile2.txt >>temp/outfile3.txt" 150 0
run_test "simple" 157 ">>temp/outfile1.txt>>temp/outfile2.txt >>temp/outfile3.txt" 150 0
run_test "simple" 158 ">>temp/outfile1.txt>>temp/outfile2.txt>>temp/outfile3.txt" 150 0

if (( "$start_index" >= 140 && "$start_index" <= 158 && "$end_index" >= 140 && "$end_index" <= 158 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 140 to 158\n"
	else
		echo -e "end of test serie from 140 to 158"
	fi
fi


run_test "simple" 160 "< 'temp/infile1.txt'" 160 0
run_test "simple" 161 "< \"temp/infile1.txt\"" 161 0
run_test "simple" 162 "< '\"temp/infile1.txt\"'" 162 1 "\"temp/infile1.txt\": No such file or directory"
run_test "simple" 163 "< \"'temp/infile1.txt'\"" 163 1 "'temp/infile1.txt': No such file or directory"
run_test "simple" 164 "< '\"'temp/infile1.txt'\"'" 164 1 "\"temp/infile1.txt\": No such file or directory"
run_test "simple" 165 "< \"'\"temp/infile1.txt\"'\"" 165 1 "'temp/infile1.txt': No such file or directory"
run_test "simple" 166 "> 'temp/outfile1.txt'" 166 0
run_test "simple" 167 "> \"temp/outfile1.txt\"" 167 0
run_test "simple" 168 "> '\"temp/outfile1.txt\"'" 168 1 "\"temp/outfile1.txt\": No such file or directory"
run_test "simple" 169 "> \"'temp/outfile1.txt'\"" 169 1 "'temp/outfile1.txt': No such file or directory"
run_test "simple" 170 "> '\"'temp/outfile1.txt'\"'" 170 1 "\"temp/outfile1.txt\": No such file or directory"
run_test "simple" 171 "> \"'\"temp/outfile1.txt\"'\"" 171 1 "'temp/outfile1.txt': No such file or directory"
#run_test_heredoc 172 "<< 'limiter'" 172 0
#run_test_heredoc 173 "<< \"limiter\"" 172 0
#run_test_heredoc 174 "<< '\"limiter\"'" 174 0
#run_test_heredoc 175 "<< \"'limiter'\"" 175 0
#run_test_heredoc 176 "<< '\"'limiter'\"'" 176 0
#run_test_heredoc 177 "<< \"'\"limiter\"'\"" 177 0
#run_test_heredoc 178 "<< '<limiter'" 178 0
#run_test_heredoc 179 "<< \"<limiter\"" 179 0

run_test "simple" 190 ">> 'temp/outfile1.txt'" 190 0
run_test "simple" 191 ">> \"temp/outfile1.txt\"" 190 0
run_test "simple" 192 ">> '\"temp/outfile1.txt\"'" 192 1 "\"temp/outfile1.txt\": No such file or directory"
run_test "simple" 193 ">> \"'temp/outfile1.txt'\"" 193 1 "'temp/outfile1.txt': No such file or directory"
run_test "simple" 194 ">> '\"'temp/outfile1.txt'\"'" 194 1 "\"temp/outfile1.txt\": No such file or directory"
run_test "simple" 195 ">> \"'\"temp/outfile1.txt\"'\"" 195 1 "'temp/outfile1.txt': No such file or directory"

if (( "$start_index" >= 160 && "$start_index" <= 195 && "$end_index" >= 160 && "$end_index" <= 195 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 160 to 195\n"
	else
		echo -e "end of test serie from 160 to 195"
	fi
fi


run_test "simple" 200 "\"< temp/infile1.txt\"" 200 0
#run_test "simple" 210 "\"<< limiter\"" 210 0
run_test "simple" 220 "\"> temp/outfile1.txt\"" 220 0
run_test "simple" 230 "\">> temp/outfile1.txt\"" 230 0

if (( "$start_index" >= 200 && "$start_index" <= 250 && "$end_index" >= 200 && "$end_index" <= 250 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 200 to 250\n"
	else
		echo -e "end of test serie from 200 to 250"
	fi
fi








run_test "simple" 500 "'ls' -l" 500 0
run_test "simple" 501 "'ls' '-l'" 500 0
run_test "simple" 502 "\"ls\" -l" 500 0
run_test "simple" 503 "\"ls\" \"-l\"" 500 0
run_test "simple" 504 "\"ls\" '-l'" 500 0
run_test "simple" 505 "'ls' \"-l\"" 500 0

run_test "simple" 550 "ls -l | cat -e" 550 0
run_test "simple" 551 "ls '-l' | cat -e" 550 0
run_test "simple" 552 "ls -l | 'cat' -e" 550 0
run_test "simple" 553 "ls -l | cat '-e'" 550 0
run_test "simple" 554 "'ls' '-l' | cat -e" 550 0
run_test "simple" 555 "'ls' '-l' | 'cat' -e" 550 0
run_test "simple" 556 "'ls' '-l' | cat '-e'" 550 0
run_test "simple" 557 "'ls' '-l' | 'cat' '-e'" 550 0
run_test "simple" 558 "ls -l | 'cat' '-e'" 550 0
run_test "simple" 559 "ls -l | cat '-e'" 550 0
run_test "simple" 560 "ls '-l' | 'cat' -e" 550 0
run_test "simple" 561 "ls '-l' | cat '-e'" 550 0
run_test "simple" 562 "ls '-l' | 'cat' '-e'" 550 0
run_test "simple" 563 "ls -l | 'cat' '-e'" 550 0

run_test "simple" 564 "\"ls\" -l | cat -e" 550 0
run_test "simple" 565 "ls \"-l\" | cat -e" 550 0
run_test "simple" 566 "ls -l | \"cat\" -e" 550 0
run_test "simple" 567 "ls -l | cat \"-e\"" 550 0
run_test "simple" 568 "\"ls\" \"-l\" | cat -e" 550 0
run_test "simple" 569 "\"ls\" \"-l\" | \"cat\" -e" 550 0
run_test "simple" 570 "\"ls\" \"-l\" | cat \"-e\"" 550 0
run_test "simple" 571 "\"ls\" \"-l\" | \"cat\" \"-e\"" 550 0
run_test "simple" 572 "\"ls\" -l | \"cat\" \"-e\"" 550 0
run_test "simple" 573 "\"ls\" -l | cat \"-e\"" 550 0
run_test "simple" 574 "ls \"-l\" | \"cat\" -e" 550 0
run_test "simple" 575 "ls \"-l\" | cat \"-e\"" 550 0
run_test "simple" 576 "ls \"-l\" | \"cat\" \"-e\"" 550 0
run_test "simple" 577 "ls -l | \"cat\" \"-e\"" 550 0

run_test "simple" 578 "\"ls\" '-l' | cat -e" 550 0
run_test "simple" 579 "\"ls\" -l | 'cat' -e" 550 0
run_test "simple" 580 "\"ls\" -l | cat '-e'" 550 0
run_test "simple" 581 "\"ls\" '-l' | 'cat' -e" 550 0
run_test "simple" 582 "\"ls\" '-l' | cat '-e'" 550 0
run_test "simple" 583 "\"ls\" '-l' | 'cat' '-e'" 550 0
run_test "simple" 584 "\"ls\" -l | 'cat' '-e'" 550 0

run_test "simple" 585 "'ls' \"-l\" | cat -e" 550 0
run_test "simple" 586 "ls \"-l\" | 'cat' -e" 550 0
run_test "simple" 587 "ls \"-l\" | cat '-e'" 550 0
run_test "simple" 588 "'ls' \"-l\" | 'cat' -e" 550 0
run_test "simple" 589 "'ls' \"-l\" | cat '-e'" 550 0
run_test "simple" 590 "'ls' \"-l\" | 'cat' '-e'" 550 0
run_test "simple" 591 "ls -l | \"cat\" '-e'" 550 0
run_test "simple" 592 "'ls' -l | \"cat\" -e" 550 0
run_test "simple" 593 "ls '-l' | \"cat\" -e" 550 0
run_test "simple" 594 "'ls' '-l' | \"cat\" -e" 550 0
run_test "simple" 595 "'ls' '-l' | \"cat\" '-e'" 550 0
run_test "simple" 596 "ls '-l' | \"cat\" '-e'" 550 0
run_test "simple" 597 "'ls' -l | \"cat\" '-e'" 550 0
run_test "simple" 598 "'ls' -l | cat \"-e\"" 550 0
run_test "simple" 599 "ls '-l' | cat \"-e\"" 550 0
run_test "simple" 600 "ls -l | 'cat' \"-e\"" 550 0
run_test "simple" 601 "'ls' '-l' | cat \"-e\"" 550 0
run_test "simple" 602 "'ls' '-l' | 'cat' \"-e\"" 550 0
run_test "simple" 603 "ls '-l' | 'cat' \"-e\"" 550 0

run_test "simple" 604 "\"ls\" \"-l\" | cat -e" 550 0
run_test "simple" 605 "\"ls\" \"-l\" | 'cat' -e" 550 0
run_test "simple" 606 "\"ls\" \"-l\" | cat '-e'" 550 0
run_test "simple" 607 "\"ls\" \"-l\" | 'cat' '-e'" 550 0

run_test "simple" 608 "\"ls\" -l | \"cat\" -e" 550 0
run_test "simple" 609 "\"ls\" '-l' | \"cat\" -e" 550 0
run_test "simple" 610 "\"ls\" -l | \"cat\" '-e'" 550 0
run_test "simple" 611 "\"ls\" '-l' | \"cat\" '-e'" 550 0

run_test "simple" 612 "\"ls\" -l | cat \"-e\"" 550 0
run_test "simple" 613 "\"ls\" '-l' | cat \"-e\"" 550 0
run_test "simple" 614 "\"ls\" '-l' | 'cat' \"-e\"" 550 0
run_test "simple" 615 "\"ls\" -l | 'cat' \"-e\"" 550 0

run_test "simple" 616 "ls \"-l\" | \"cat\" -e" 550 0
run_test "simple" 617 "'ls' \"-l\" | \"cat\" -e" 550 0
run_test "simple" 618 "ls \"-l\" | \"cat\" '-e'" 550 0
run_test "simple" 619 "'ls' \"-l\" | \"cat\" '-e'" 550 0

run_test "simple" 620 "ls -l | \"cat\" \"-e\"" 550 0
run_test "simple" 621 "'ls' -l | \"cat\" \"-e\"" 550 0
run_test "simple" 622 "ls '-l' | \"cat\" \"-e\"" 550 0
run_test "simple" 623 "'ls' '-l' | \"cat\" \"-e\"" 550 0

run_test "simple" 624 "\"ls\" \"-l\" | \"cat\" -e" 550 0
run_test "simple" 625 "\"ls\" \"-l\" | \"cat\" '-e'" 550 0

run_test "simple" 626 "\"ls\" \"-l\" | cat \"-e\"" 550 0
run_test "simple" 627 "\"ls\" \"-l\" | 'cat' \"-e\"" 550 0

run_test "simple" 628 "\"ls\" -l | \"cat\" \"-e\"" 550 0
run_test "simple" 629 "\"ls\" '-l' | \"cat\" \"-e\"" 550 0

run_test "simple" 630 "ls \"-l\" | \"cat\" \"-e\"" 550 0
run_test "simple" 631 "'ls' \"-l\" | \"cat\" \"-e\"" 550 0

run_test "simple" 632 "\"ls\" \"-l\" | \"cat\" \"-e\"" 550 0

if (( "$start_index" >= 500 && "$start_index" <= 632 && "$end_index" >= 500 && "$end_index" <= 632 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 500 to 632\n"
	else
		echo -e "end of test serie from 500 to 632"
	fi
fi

run_test "simple" 650 "'ls -l'" 650 127 "command not found"
run_test "simple" 651 "\"ls -l\"" 651 127 "command not found"
run_test "simple" 652 "'\"ls -l\"'" 652 127 "command not found"
run_test "simple" 653 "\"'ls -l'\"" 653 127 "command not found"
run_test "simple" 654 "'ls'-l" 654 127 "command not found"
run_test "simple" 655 "ls'-l'" 655 127 "command not found"
run_test "simple" 656 "\"ls\"-l" 656 127 "command not found"
run_test "simple" 657 "ls\"-l\"" 657 127 "command not found"

if (( "$start_index" >= 650 && "$start_index" <= 657 && "$end_index" >= 650 && "$end_index" <= 657 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 650 to 657\n"
	else
		echo -e "end of test serie from 650 to 657"
	fi
fi

run_test "simple" 700 "'ls -l cat -e'" 700 127 "command not found"
run_test "simple" 701 "\"ls -l cat -e\"" 701 0
run_test "simple" 702 "'\"ls -l cat -e\"'" 702 0
run_test "simple" 703 "\"'ls -l cat -e'\"" 703 0

run_test "simple" 704 "'ls'-l cat -e" 704 0
run_test "simple" 705 "ls'-l' cat -e" 705 0
run_test "simple" 706 "\"ls\"-l cat -e" 706 0
run_test "simple" 707 "ls\"-l\" cat -e" 707 0

run_test "simple" 708 "'ls -l' cat -e" 708 0
run_test "simple" 709 "\"ls -l\" cat -e" 709 0
run_test "simple" 710 "'\"ls -l\"' cat -e" 710 0
run_test "simple" 711 "\"'ls -l'\" cat -e" 711 0

run_test "simple" 712 "'ls -l'cat -e" 712 0
run_test "simple" 713 "\"ls -l\"cat -e" 713 0
run_test "simple" 714 "'\"ls -l\"'cat -e" 714 0
run_test "simple" 715 "\"'ls -l'\"cat -e" 715 0

run_test "simple" 716 "'ls -l' 'cat' -e" 716 0
run_test "simple" 717 "\"ls -l\" 'cat' -e" 717 0
run_test "simple" 718 "'\"ls -l\"' 'cat' -e" 718 0
run_test "simple" 719 "\"'ls -l'\" 'cat' -e" 719 0


run_test "simple" 720 "'ls -l' cat '-e'" 720 0
run_test "simple" 721 "\"ls -l\" cat '-e'" 721 0
run_test "simple" 722 "'\"ls -l\"' cat '-e'" 722 0
run_test "simple" 723 "\"'ls -l'\" cat '-e'" 723 0
run_test "simple" 724 "'ls -l' 'cat' '-e'" 724 0
run_test "simple" 725 "\"ls -l\" 'cat' '-e'" 725 0
run_test "simple" 726 "'\"ls -l\"' 'cat' '-e'" 726 0
run_test "simple" 727 "\"'ls -l'\" 'cat' '-e'" 727 0
run_test "simple" 728 "'ls -l' \"cat\" '-e'" 728 0
run_test "simple" 729 "\"ls -l\" \"cat\" '-e'" 729 0
run_test "simple" 730 "'\"ls -l\"' \"cat\" '-e'" 730 0
run_test "simple" 731 "\"'ls -l'\" \"cat\" '-e'" 731 0
run_test "simple" 732 "'ls -l' \"cat\" \"-e\"" 732 0
run_test "simple" 733 "\"ls -l\" \"cat\" \"-e\"" 733 0
run_test "simple" 734 "'\"ls -l\"' \"cat\" \"-e\"" 734 0
run_test "simple" 735 "\"'ls -l'\" \"cat\" \"-e\"" 735 0

if (( "$start_index" >= 700 && "$start_index" <= 735 && "$end_index" >= 700 && "$end_index" <= 735 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 700 to 735\n"
	else
		echo -e "end of test serie from 700 to 735"
	fi
fi

run_test "simple" 736 "'ls -l'cat '-e'" 736 0
run_test "simple" 737 "\"ls -l\"cat '-e'" 737 0
run_test "simple" 738 "'\"ls -l\"'cat '-e'" 738 0
run_test "simple" 739 "\"'ls -l'\"cat '-e'" 739 0
run_test "simple" 740 "'ls -l'cat \"-e\"" 740 0
run_test "simple" 741 "\"ls -l\"cat \"-e\"" 741 0
run_test "simple" 742 "'\"ls -l\"'cat \"-e\"" 742 0
run_test "simple" 743 "\"'ls -l'\"cat \"-e\"" 743 0
run_test "simple" 744 "'ls -l''cat' '-e'" 744 0
run_test "simple" 745 "\"ls -l\"'cat' '-e'" 745 0
run_test "simple" 746 "'\"ls -l\"''cat' '-e'" 746 0
run_test "simple" 747 "\"'ls -l'\"'cat' '-e'" 747 0
run_test "simple" 748 "'ls -l''cat' \"-e\"" 748 0
run_test "simple" 749 "\"ls -l\"'cat' \"-e\"" 749 0
run_test "simple" 750 "'\"ls -l\"''cat' \"-e\"" 750 0
run_test "simple" 751 "\"'ls -l'\"'cat' \"-e\"" 751 0
run_test "simple" 752 "'ls -l'\"cat\" '-e'" 752 0
run_test "simple" 753 "\"ls -l\"\"cat\" '-e'" 753 0
run_test "simple" 754 "'\"ls -l\"'\"cat\" '-e'" 754 0
run_test "simple" 755 "\"'ls -l'\"\"cat\" '-e'" 755 0
run_test "simple" 756 "'ls -l'\"cat\" \"-e\"" 756 0
run_test "simple" 757 "\"ls -l\"\"cat\" \"-e\"" 757 0
run_test "simple" 758 "'\"ls -l\"'\"cat\" \"-e\"" 758 0
run_test "simple" 759 "\"'ls -l'\"\"cat\" \"-e\"" 759 0

if (( "$start_index" >= 735 && "$start_index" <= 759 && "$end_index" >= 735 && "$end_index" <= 759 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 735 to 759\n"
	else
		echo -e "end of test serie from 735 to 759"
	fi
fi

run_test "simple" 760 "'ls -l' cat'-e'" 760 0
run_test "simple" 761 "\"ls -l\" cat'-e'" 761 0
run_test "simple" 762 "'\"ls -l\"' cat'-e'" 762 0
run_test "simple" 763 "\"'ls -l'\" cat'-e'" 763 0
run_test "simple" 764 "'ls -l' 'cat''-e'" 764 0
run_test "simple" 765 "\"ls -l\" 'cat''-e'" 765 0
run_test "simple" 766 "'\"ls -l\"' 'cat''-e'" 766 0
run_test "simple" 767 "\"'ls -l'\" 'cat''-e'" 767 0
run_test "simple" 768 "'ls -l' \"cat\"'-e'" 768 0
run_test "simple" 769 "\"ls -l\" \"cat\"'-e'" 769 0
run_test "simple" 770 "'\"ls -l\"' \"cat\"'-e'" 770 0
run_test "simple" 771 "\"'ls -l'\" \"cat\"'-e'" 771 0
run_test "simple" 772 "'ls -l' \"cat\"\"-e\"" 772 0
run_test "simple" 773 "\"ls -l\" \"cat\"\"-e\"" 773 0
run_test "simple" 774 "'\"ls -l\"' \"cat\"\"-e\"" 774 0
run_test "simple" 775 "\"'ls -l'\" \"cat\"\"-e\"" 775 0
run_test "simple" 776 "\"ls\"'-l'cat\"-e\"" 776 0

if (( "$start_index" >= 760 && "$start_index" <= 776 && "$end_index" >= 760 && "$end_index" <= 776 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 760 to 776\n"
	else
		echo -e "end of test serie from 760 to 776"
	fi
fi

run_test "simple" 1000 "'ls'-l'cat -e'" 1000 0
run_test "simple" 1001 "'ls'-l'cat  -e'" 1001 0

if (( "$start_index" >= 1000 && "$start_index" <= 1001 && "$end_index" >= 1000 && "$end_index" <= 1001 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 1000 to 1001\n"
	else
		echo -e "end of test serie from 1000 to 1001"
	fi
fi


run_test "simple" 1100 "\\" 1100 127 "" "invalid test because bash has a special behaviour"
run_test "simple" 1101 "\"\\\"" 1100 127 "" "invalid test because bash has a special behaviour"
run_test "simple" 1102 "\"\\ls\"" 1102 127 "\ls: command not found"
run_test "simple" 1103 "'\'" 1103 127 "\: command not found"
run_test "simple" 1104 "'\ls'" 1104 127 "\ls: command not found"
run_test "simple" 1105 "(" 1105 127 "" "invalid test because bash has a special behaviour"
run_test "simple" 1106 ")" 1106 127 "" "invalid test because bash has a special behaviour"
run_test "simple" 1107 "()" 1107 127 "" "invalid test because bash has a special behaviour"
run_test "simple" 1108 ";" 1108 127 "" "invalid test because bash has a special behaviour"
run_test "simple" 1109 "\"'\"" 1109 0
run_test "simple" 1110 "@" 1110 0
run_test "simple" 1111 "\"@\"" 1110 0
run_test "simple" 1112 "*" 1112 0
run_test "simple" 1113 "\"*\"" 1112 0

if (( "$start_index" >= 1100 && "$start_index" <= 1200 && "$end_index" >= 1100 && "$end_index" <= 1200 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 1100 to 1200\n"
	else
		echo -e "end of test serie from 1100 to 1200"
	fi
fi


export TEST="test_minishell"

if (( "$start_index" >= 1500 && "$start_index" <= 1570 && "$end_index" >= 1500 && "$end_index" <= 1570 ))
then
	if [ "$display" == "all" ]
	then
		echo ""
		echo -e echo "\$TEST = \"test_minishell\"\n"
	fi
fi

run_test "simple" 1500 "\$TEST" 1500 0
run_test "simple" 1501 "\$DO_NOT_EXIST" 1501 0
run_test "simple" 1502 "'\$TEST'" 1502 0
run_test "simple" 1503 "\"\$TEST\"" 1503 127 ": command not found"
run_test "simple" 1504 "'\"\$TEST\"'" 1504 127
run_test "simple" 1505 "\"'\"\$TEST\"'\"" 1505 0
run_test "simple" 1506 "\"'\$TEST'\"" 1506 0
run_test "simple" 1507 "'\"'\$TEST'\"'" 1507 0
run_test "simple" 1508 "\"\$TEST \$TEST\"" 1508 0
run_test "simple" 1509 "\" \$TEST\"" 1509 0
run_test "simple" 1510 "\"  \$TEST\"" 1510 0
run_test "simple" 1511 "\"\$TEST \"" 1511 0
run_test "simple" 1512 "\"\$TEST  \"" 1512 0
run_test "simple" 1513 "\" \$TEST \"" 1513 0
run_test "simple" 1514 "\"  \$TEST  \"" 1514 0
run_test "simple" 1515 "\"	\$TEST\"" 1515 0
run_test "simple" 1516 "\"\t\t\$TEST\"" 1516 0
run_test "simple" 1517 "\"\$TEST	\"" 1517 127 "test_minishell	: command not found"
run_test "simple" 1518 "\"\$TEST		\"" 1518 127 "test_minishell		: command not found"
run_test "simple" 1519 "\"	\$TEST	\"" 1519 127 "	test_minishell	: command not found"
run_test "simple" 1520 "\"		\$TEST		\"" 1520 127 "		test_minishell		: command not found"
run_test "simple" 1521 "\" \$TEST	\"" 1521 127 " test_minishell	: command not found"
run_test "simple" 1522 "\"	\$TEST \"" 1522 127 "	test_minishell : command not found"

run_test "simple" 1523 "\$\"TEST\"" 1523 127 "TEST: command not found"
run_test "simple" 1524 "\$'TEST'" 1524 0
run_test "simple" 1525 "\"\$ \"TEST\"\"" 1525 0
run_test "simple" 1526 "\"\$ 'TEST'\"" 1526 0

run_test "simple" 1530 "\" \$TEST \$TEST\"" 1530 0
run_test "simple" 1531 "\"  \$TEST \$TEST\"" 1531 0
run_test "simple" 1532 "\"\$TEST  \$TEST\"" 1532 0
run_test "simple" 1533 "\"\$TEST \$TEST \"" 1533 0
run_test "simple" 1534 "\"\$TEST \$TEST  \"" 1534 0
run_test "simple" 1535 "\" \$TEST  \$TEST\"" 1535 0
run_test "simple" 1536 "\" \$TEST  \$TEST \"" 1536 0
run_test "simple" 1537 "\"\t\$TEST\t\$TEST\"" 1537 0
run_test "simple" 1538 "\"\t\$TEST\t\$TEST\t\"" 1538 0
run_test "simple" 1539 "\"\t\t\$TEST\t\t\$TEST\t\t\"" 1539 0
run_test "simple" 1540 "\$TEST\$TEST" 1540 0
run_test "simple" 1541 "\" \$TEST\$TEST\"" 1541 0
run_test "simple" 1542 "\"\$TEST\$TEST \"" 1542 0
run_test "simple" 1543 "\" \$TEST\$TEST \"" 1543 0
run_test "simple" 1544 "\"	\$TEST\$TEST\"" 1544 0
run_test "simple" 1545 "\"\$TEST\$TEST	\"" 1545 0
run_test "simple" 1546 "\"	\$TEST\$TEST	\"" 1546 0

run_test "simple" 1550 "\"text\$TEST\"" 1550 0
run_test "simple" 1551 "\"text \$TEST\"" 1551 0
run_test "simple" 1552 "\" text \$TEST\"" 1552 0
run_test "simple" 1553 "\"text \$TEST \"" 1553 0
run_test "simple" 1554 "\"text \$TEST text\"" 1554 0
run_test "simple" 1555 "'text \$TEST text'" 1555 0
run_test "simple" 1556 "\"'text \$TEST text'\"" 1556 0
run_test "simple" 1557 "'\"text \$TEST text\"'" 1557 0
run_test "simple" 1558 "\"\$TEST text \$TEST\"" 1558 0

run_test "simple" 1559 "\"\$TEST cat\"" 1559 0
run_test "simple" 1560 "\"\$TEST cat \"" 1560 0
run_test "simple" 1561 "\"\$TEST cat	\"" 1561 0

run_test "simple" 1562 "\$" 1562 0
run_test "simple" 1563 "\"\$ TEST\"" 1563 0
run_test "simple" 1564 "\$\"\"" 1564 127 ": command not found"
run_test "simple" 1565 "\$''" 1565 127 ": command not found"
run_test "simple" 1566 "\"\$\"\"\"" 1566 0
run_test "simple" 1567 "\"\$''\"" 1567 0
run_test "simple" 1568 "\"\$\" \"\"" 1568 0
run_test "simple" 1569 "\"\$' '\"" 1569 0
run_test "simple" 1570 "'\$'''" 1570 0
unset TEST

if (( "$start_index" >= 1500 && "$start_index" <= 1570 && "$end_index" >= 1500 && "$end_index" <= 1570 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 1500 to 1570\n"
	else
		echo -e "end of test serie from 1500 to 1570"
	fi
fi




export TEST1="test1"
export TEST2="test2"
export TEST3="salut     les     amis"

#export TEST3="     salut     les     amis     "
#export TEST3="	salut	les	amis	"

export TEST4='echo    "     salut'
#export TEST5='echo    "     salut     les     amis'

if (( "$start_index" >= 1600 && "$start_index" <= 1699 && "$end_index" >= 1600 && "$end_index" <= 1699 ))
then
	if [ "$display" == "all" ]
	then
		echo ""
		echo "\$TEST1 = \"test1\""
		echo "\$TEST2 = \"test2\""
		echo "\$TEST3 = 'salut     les     amis'"
		echo "\$TEST4 = 'echo    \"     salut'"
		echo "\$TEST5 = 'echo    \"     salut     les     amis'\n"
	fi
fi

run_test "simple" 1600 "echo \$TEST1\$TEST2" 1600 0
run_test "simple" 1601 "echo \$TEST1\"\"\$TEST2" 1601 0
run_test "simple" 1602 "echo \$TEST1"text"\$TEST2" 1602 0
run_test "simple" 1603 "echo \$TEST1"text"\$TEST2$" 1603 0
run_test "simple" 1604 "echo \$\"\"\$TEST1"text"\$TEST2$" 1604 0
run_test "simple" 1605 "echo \$DO_NOT_EXIST\$TEST1"text"\$TEST2$" 1605 0
run_test "simple" 1606 "echo    \$TEST1   \$TEST2   " 1610 0

run_test "simple" 1610 "echo \$TEST3" 1610 0
run_test "simple" 1611 "echo \$TEST3'text'" 1611 0
run_test "simple" 1612 "echo '\$TEST3'" 1612 0
run_test "simple" 1613 "echo '\$TEST3''text'" 1613 0
run_test "simple" 1614 "echo \"\$TEST3\"" 1614 0
run_test "simple" 1615 "echo \"\$TEST3\"'text'" 1615 0
run_test "simple" 1616 "\$TEST4" 1616 0
run_test "simple" 1617 "\$TEST4" 1617 0

unset TEST1
unset TEST2
unset TEST3

if (( "$start_index" >= 1600 && "$start_index" <= 1699 && "$end_index" >= 1600 && "$end_index" <= 1699 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 1600 to 1699\n"
	else
		echo -e "end of test serie from 1600 to 1699"
	fi
fi

export INFILE="temp/infile1.txt"

if (( "$start_index" >= 1700 && "$start_index" <= 1900 && "$end_index" >= 1700 && "$end_index" <= 1900 ))
then
	if [ "$display" == "all" ]
	then
		echo ""
		echo "\$INFILE = \"temp/infile.txt\""
		echo ""
	fi
fi

run_test "simple" 1700 "< \$INFILE" 1700 0
run_test "simple" 1701 "< \$DO_NOT_EXIST" 1701 0
run_test "simple" 1702 "< '\$INFILE'" 1702 0
run_test "simple" 1703 "< \"\$INFILE\"" 1703 0
run_test "simple" 1704 "< '\"\$INFILE\"'" 1704 0
run_test "simple" 1705 "< \"'\"\$INFILE\"'\"" 1705 0
run_test "simple" 1706 "< \"\$INFILE \$INFILE\"" 1706 0
run_test "simple" 1707 "< \" \$INFILE\"" 1707 0
run_test "simple" 1708 "< \"  \$INFILE\"" 1708 0
run_test "simple" 1709 "< \"\$INFILE \"" 1709 0
run_test "simple" 1710 "< \"\$INFILE  \"" 1710 0
run_test "simple" 1711 "< \" \$INFILE \"" 1711 0
run_test "simple" 1712 "< \"  \$INFILE  \"" 1712 0
run_test "simple" 1713 "< \"	\$INFILE\"" 1713 0
run_test "simple" 1714 "< \"\$INFILE	\"" 1714 0
run_test "simple" 1715 "< \"		\$INFILE\"" 1715 0
run_test "simple" 1716 "< \"\$INFILE		\"" 1716 0
run_test "simple" 1717 "< \"	\$INFILE	\"" 1717 0
run_test "simple" 1718 "< \"		\$INFILE		\"" 1718 0
run_test "simple" 1719 "< \"INFILE \$INFILE\"" 1719 0
unset INFILE

export OUTFILE="temp/outfile1.txt"

if (( "$start_index" >= 1700 && "$start_index" <= 1900 && "$end_index" >= 1700 && "$end_index" <= 1900 ))
then
	if [ "$display" == "all" ]
	then
		echo ""
		echo "\$OUTFILE = \"temp/outfile.txt\""
		echo ""
	fi
fi

run_test "simple" 1740 "> \$OUTFILE" 1740 0
run_test "simple" 1741 "> \$DO_NOT_EXIST" 1741 0
run_test "simple" 1742 "> '\$OUTFILE'" 1742 0
run_test "simple" 1743 "> \"\$OUTFILE\"" 1743 0
run_test "simple" 1744 "> '\"\$OUTFILE\"'" 1744 0
run_test "simple" 1745 "> \"'\"\$OUTFILE\"'\"" 1745 0
run_test "simple" 1746 "> \"\$OUTFILE \$OUTFILE\"" 1746 0
run_test "simple" 1747 "> \" \$OUTFILE\"" 1747 0
run_test "simple" 1748 "> \"  \$OUTFILE\"" 1748 0
run_test "simple" 1749 "> \"\$OUTFILE \"" 1749 0
run_test "simple" 1750 "> \"\$OUTFILE  \"" 1750 0
run_test "simple" 1751 "> \" \$OUTFILE \"" 1751 0
run_test "simple" 1752 "> \"  \$OUTFILE  \"" 1752 0
run_test "simple" 1753 "> \"	\$OUTFILE\"" 1753 0
run_test "simple" 1754 "> \"\$OUTFILE	\"" 1754 0
run_test "simple" 1755 "> \"		\$OUTFILE\"" 1755 0
run_test "simple" 1756 "> \"\$OUTFILE		\"" 1756 0
run_test "simple" 1757 "> \"	\$OUTFILE	\"" 1757 0
run_test "simple" 1758 "> \"		\$OUTFILE		\"" 1758 0
run_test "simple" 1759 "> \"OUTFILE \$OUTFILE\"" 1759 0
unset OUTFILE

: <<BLOCK_COMMENT

export LIMITER="limiter"

if (( "$start_index" >= 1700 && "$start_index" <= 1900 && "$end_index" >= 1700 && "$end_index" <= 1900 ))
then
	if [ "$display" == "all" ]
	then
		echo ""
		echo "\$LIMITER = \"limiter\""
		echo ""
	fi
fi

run_test "heredoc" 1780 "<< \$LIMITER" 1780 0
run_test "heredoc" 1781 "<< \$DO_NOT_EXIST" 1781 0
run_test "heredoc" 1782 "<< '\$LIMITER'" 1782 0
run_test "heredoc" 1783 "<< \"\$LIMITER\"" 1782 0
run_test "heredoc" 1784 "<< '\"\$LIMITER\"'" 1784 0
run_test "heredoc" 1785 "<< \"'\"\$LIMITER\"'\"" 1785 0
run_test "heredoc" 1786 "<< \"\$LIMITER \$LIMITER\"" 1786 0
run_test "heredoc" 1787 "<< \" \$LIMITER\"" 1787 0
run_test "heredoc" 1788 "<< \"  \$LIMITER\"" 1788 0
run_test "heredoc" 1789 "<< \"\$LIMITER \"" 1789 0
run_test "heredoc" 1790 "<< \"\$LIMITER  \"" 1790 0
run_test "heredoc" 1791 "<< \" \$LIMITER \"" 1791 0
run_test "heredoc" 1792 "<< \"  \$LIMITER  \"" 1792 0
run_test "heredoc" 1793 "<< \"	\$LIMITER\"" 1793 0
run_test "heredoc" 1794 "<< \"\$LIMITER	\"" 1794 0
run_test "heredoc" 1795 "<< \"		\$LIMITER\"" 1795 0
run_test "heredoc" 1796 "<< \"\$LIMITER		\"" 1796 0
run_test "heredoc" 1797 "<< \"	\$LIMITER	\"" 1797 0
run_test "heredoc" 1798 "<< \"		\$LIMITER		\"" 1798 0
run_test "heredoc" 1799 "<< \"LIMITER \$LIMITER\"" 1799 0

tester contenu du heredoc avec :

TEST1="salut"
TEST2="les"
TEST3="amis"
TEST4="     salut     les     amis     "
\$TEST1
\$TEST1 \$TEST2
\$TEST1\$TEST2
\$TEST1 \$TEST2 \$TEST3
\$TEST1\$TEST2\$TEST3
\$TEST4
\$TEST1 \$TEST4
\$TEST1\$TEST4

unset LIMITER

BLOCK_COMMENT

export OUTFILE="temp/outfile1.txt"

if (( "$start_index" >= 1700 && "$start_index" <= 1900 && "$end_index" >= 1700 && "$end_index" <= 1900 ))
then
	if [ "$display" == "all" ]
	then
		echo ""
		echo "\$OUTFILE = \"temp/outfile.txt\""
		echo ""
	fi
fi

run_test "simple" 1820 ">> \$OUTFILE" 1820 0
run_test "simple" 1821 ">> \$DO_NOT_EXIST" 1821 0
run_test "simple" 1822 ">> '\$OUTFILE'" 1822 0
run_test "simple" 1823 ">> \"\$OUTFILE\"" 1823 0
run_test "simple" 1824 ">> '\"\$OUTFILE\"'" 1824 0
run_test "simple" 1825 ">> \"'\"\$OUTFILE\"'\"" 1825 0
run_test "simple" 1826 ">> \"\$OUTFILE \$OUTFILE\"" 1826 0
run_test "simple" 1827 ">> \" \$OUTFILE\"" 1827 0
run_test "simple" 1828 ">> \"  \$OUTFILE\"" 1828 0
run_test "simple" 1829 ">> \"\$OUTFILE \"" 1829 0
run_test "simple" 1830 ">> \"\$OUTFILE  \"" 1830 0
run_test "simple" 1831 ">> \" \$OUTFILE \"" 1831 0
run_test "simple" 1832 ">> \"  \$OUTFILE  \"" 1832 0
run_test "simple" 1833 ">> \"	\$OUTFILE\"" 1833 0
run_test "simple" 1834 ">> \"\$OUTFILE	\"" 1834 0
run_test "simple" 1835 ">> \"		\$OUTFILE\"" 1835 0
run_test "simple" 1836 ">> \"\$OUTFILE		\"" 1836 0
run_test "simple" 1837 ">> \"	\$OUTFILE	\"" 1837 0
run_test "simple" 1838 ">> \"		\$OUTFILE		\"" 1838 0
unset OUTFILE

if (( "$start_index" >= 1700 && "$start_index" <= 1900 && "$end_index" >= 1700 && "$end_index" <= 1900 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 1700 to 1900\n"
	else
		echo -e "end of test serie from 1700 to 1900"
	fi
fi

run_test "simple" 2000 "<" 2000 2 "syntax error"
run_test "simple" 2001 "<<" 2001 2 "syntax error"
run_test "simple" 2002 "<<<" 2002 2 "syntax error"
run_test "simple" 2003 "<<<<" 2003 2 "syntax error"
run_test "simple" 2004 "<" 2004 2 "syntax error"
run_test "simple" 2005 "<<" 2005 2 "syntax error"
run_test "simple" 2006 "<<<" 2006 2 "syntax error"
run_test "simple" 2007 "<<<<" 2007 2 "syntax error"
run_test "simple" 2008 "<>" 2008 2 "syntax error"
run_test "simple" 2009 "><" 2009 2 "syntax error"
run_test "simple" 2010 "<><>" 2010 2 "syntax error"
run_test "simple" 2011 "><><" 2011 2 "syntax error"
run_test "simple" 2012 "<<>" 2012 2 "syntax error"
run_test "simple" 2013 "<<>>" 2013 2 "syntax error"
run_test "simple" 2014 "<<<>>>" 2014 2 "syntax error"
run_test "simple" 2015 "<<<<>>>>" 2015 2 "syntax error"
run_test "simple" 2016 ">><" 2016 2 "syntax error"
run_test "simple" 2017 ">><<" 2017 2 "syntax error"
run_test "simple" 2018 ">>><<<" 2018 2 "syntax error"
run_test "simple" 2019 ">>>><<<<" 2019 2 "syntax error"

run_test "simple" 2020 "ls <" 2020 2 "syntax error"
run_test "simple" 2021 "ls <<" 2021 2 "syntax error"
run_test "simple" 2022 "ls >" 2022 2 "syntax error"
run_test "simple" 2023 "ls >>" 2023 2 "syntax error"
run_test "simple" 2024 "ls<" 2024 2 "syntax error"
run_test "simple" 2025 "ls<<" 2025 2 "syntax error"
run_test "simple" 2026 "ls>" 2026 2 "syntax error"
run_test "simple" 2027 "ls>>" 2027 2 "syntax error"

run_test "simple" 2030 "|" 2030 2 "syntax error"
run_test "simple" 2031 " |" 2031 2 "syntax error"
run_test "simple" 2032 "  |" 2032 2 "syntax error"
run_test "simple" 2033 "| " 2033 2 "syntax error"
run_test "simple" 2034 "|  " 2034 2 "syntax error"
run_test "simple" 2035 " | " 2035 2 "syntax error"
run_test "simple" 2036 "  | " 2036 2 "syntax error"
run_test "simple" 2037 "  |  " 2037 2 "syntax error"
run_test "simple" 2038 "	|" 2038 2 "syntax error"
run_test "simple" 2039 "		|" 2039 2 "syntax error"
run_test "simple" 2040 "|	" 2040 2 "syntax error"
run_test "simple" 2041 "|		" 2041 2 "syntax error"
run_test "simple" 2042 "	|	" 2042 2 "syntax error"
run_test "simple" 2043 "		|		" 2043 2 "syntax error"

run_test "simple" 2050 "| ls" 2050 2 "syntax error"
run_test "simple" 2051 "|ls" 2051 2 "syntax error"
run_test "simple" 2052 " |ls" 2052 2 "syntax error"
run_test "simple" 2053 "ls |" 2053 2 "syntax error"
run_test "simple" 2054 "ls|" 2054 2 "syntax error"
run_test "simple" 2055 "ls| " 2055 2 "syntax error"

run_test "simple" 2060 "||" 2060 2 "syntax error"
run_test "simple" 2061 "| |" 2061 2 "syntax error"
run_test "simple" 2062 "|	|" 2062 2 "syntax error"
run_test "simple" 2063 "|||" 2063 2 "syntax error"
run_test "simple" 2064 "| | |" 2064 2 "syntax error"
run_test "simple" 2065 "|	|	|" 2065 2 "syntax error"
run_test "simple" 2066 "||||" 2066 2 "syntax error"
run_test "simple" 2067 "| | | |" 2067 2 "syntax error"
run_test "simple" 2068 "|	|	|	|" 2068 2 "syntax error"

run_test "simple" 2070 ">|" 2070 2 "syntax error"
run_test "simple" 2071 "<|" 2071 2 "syntax error"
run_test "simple" 2072 "|>" 2072 2 "syntax error"
run_test "simple" 2073 "|<" 2073 2 "syntax error"
run_test "simple" 2074 ">>|" 2074 2 "syntax error"
run_test "simple" 2075 "<<|" 2075 2 "syntax error"
run_test "simple" 2076 "|>>" 2076 2 "syntax error"
run_test "simple" 2077 "|<<" 2077 2 "syntax error"

run_test "simple" 2090 ">|>" 2090 2 "syntax error"
run_test "simple" 2091 "<|<" 2091 2 "syntax error"
run_test "simple" 2092 "<|>" 2092 2 "syntax error"
run_test "simple" 2093 ">|<" 2093 2 "syntax error"
run_test "simple" 2094 ">>|<<" 2094 2 "syntax error"
run_test "simple" 2095 "<<|>>" 2095 2 "syntax error"
run_test "simple" 2096 "<<|>>" 2096 2 "syntax error"
run_test "simple" 2097 ">>|<<" 2097 2 "syntax error"

run_test "simple" 2100 "|| ls" 2100 2 "syntax error"
run_test "simple" 2101 "||ls" 2101 2 "syntax error"
run_test "simple" 2102 "ls ||" 2102 2 "syntax error"
run_test "simple" 2103 "ls||" 2103 2 "syntax error"
run_test "simple" 2104 "||| ls" 2104 2 "syntax error"
run_test "simple" 2105 "|||ls" 2105 2 "syntax error"
run_test "simple" 2106 "ls |||" 2106 2 "syntax error"
run_test "simple" 2107 "ls|||" 2107 2 "syntax error"

#run_test "simple" 2110 "ls || cat" 2110 2 "syntax error"//invalid test because bash has a special behaviour
run_test "simple" 2111 "ls | | cat" 2111 2 "syntax error"
run_test "simple" 2112 "ls | cat |" 2112 2 "syntax error"
run_test "simple" 2113 "ls || cat |" 2113 2 "syntax error"


if (( "$start_index" >= 2000 && "$start_index" <= 2150 && "$end_index" >= 2000 && "$end_index" <= 2150 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 2000 to 2150\n"
	else
		echo -e "end of test serie from 2000 to 2150"
	fi
fi


run_test "simple" 3000 "<<< infile.txt" 3000 2 "syntax error" "invalid test because bash has a special behaviour"
run_test "simple" 3001 "<<<< infile.txt" 3001 2 "syntax error"
run_test "simple" 3002 "<<<<< infile.txt" 3002 2 "syntax error"
run_test "simple" 3003 "<<> infile.txt" 3003 2 "syntax error"
run_test "simple" 3004 "<<>> infile.txt" 3004 2 "syntax error"
run_test "simple" 3005 "<<>>> infile.txt" 3005 2 "syntax error"
run_test "simple" 3006 "<<>>>> infile.txt" 3006 2 "syntax error"
run_test "simple" 3007 "<<>< infile.txt" 3007 2 "syntax error"
run_test "simple" 3008 "<<><< infile.txt" 3008 2 "syntax error"
run_test "simple" 3009 "<<><<< infile.txt" 3009 2 "syntax error"
run_test "simple" 3010 "<<><<<< infile.txt" 3010 2 "syntax error"
run_test "simple" 3011 "<<><> infile.txt" 3011 2 "syntax error"
run_test "simple" 3012 "<<><>> infile.txt" 3012 2 "syntax error"
run_test "simple" 3013 "<<><>>> infile.txt" 3013 2 "syntax error"
run_test "simple" 3014 "<<><>>>> infile.txt" 3014 2 "syntax error"
run_test "simple" 3015 "<> infile.txt" 3015 2 "syntax error" "invalid test because bash has a special behaviour"
run_test "simple" 3016 "<>> infile.txt" 3016 2 "syntax error"
run_test "simple" 3017 "<>>> infile.txt" 3017 2 "syntax error"
run_test "simple" 3018 "<>>>> infile.txt" 3018 2 "syntax error"
run_test "simple" 3019 "<>>>>> infile.txt" 3019 2 "syntax error"
run_test "simple" 3020 "<>< infile.txt" 3020 2 "syntax error"
run_test "simple" 3021 "<><< infile.txt" 3021 2 "syntax error"
run_test "simple" 3022 "<><<< infile.txt" 3022 2 "syntax error"
run_test "simple" 3023 "<><<<< infile.txt" 3023 2 "syntax error"
run_test "simple" 3024 "<><> infile.txt" 3024 2 "syntax error"
run_test "simple" 3025 "<><>> infile.txt" 3025 2 "syntax error"
run_test "simple" 3026 "<><>>> infile.txt" 3026 2 "syntax error"
run_test "simple" 3027 "<><>>>> infile.txt" 3027 2 "syntax error"
run_test "simple" 3028 "<><>>>>> infile.txt" 3028 2 "syntax error"
run_test "simple" 3029 ">>> outfile.txt" 3029 2 "syntax error"
run_test "simple" 3030 ">>>> outfile.txt" 3030 2 "syntax error"
run_test "simple" 3031 ">>>>> outfile.txt" 3031 2 "syntax error"
run_test "simple" 3032 ">>>>>> outfile.txt" 3032 2 "syntax error"
run_test "simple" 3033 ">>< outfile.txt" 3033 2 "syntax error"
run_test "simple" 3034 ">><< outfile.txt" 3034 2 "syntax error"
run_test "simple" 3035 ">><<< outfile.txt" 3035 2 "syntax error"
run_test "simple" 3036 ">><<<< outfile.txt" 3036 2 "syntax error"
run_test "simple" 3037 ">><<<<< outfile.txt" 3037 2 "syntax error"
run_test "simple" 3038 ">><> outfile.txt" 3038 2 "syntax error"
run_test "simple" 3039 ">><>> outfile.txt" 3039 2 "syntax error"
run_test "simple" 3040 ">><>>> outfile.txt" 3040 2 "syntax error"
run_test "simple" 3041 ">><>>>> outfile.txt" 3041 2 "syntax error"
run_test "simple" 3042 ">><>>>>> outfile.txt" 3042 2 "syntax error"

if (( "$start_index" >= 3000 && "$start_index" <= 3050 && "$end_index" >= 3000 && "$end_index" <= 3050 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 3000 to 3050\n"
	else
		echo -e "end of test serie from 3000 to 3050"
	fi
fi

run_test "simple" 3300 "< 'infile.txt" 3300 2  "syntax error"
run_test "simple" 3301 "< infile.txt'" 3301 2 "syntax error"
run_test "simple" 3302 "< \"infile.txt" 3302 2 "syntax error"
run_test "simple" 3303 "< infile.txt\"" 3303 2 "syntax error"
run_test "simple" 3304 "< 'infile.txt\"" 3304 2 "syntax error"
run_test "simple" 3305 "< 'infile.txt'\"" 3305 2 "syntax error"
#run_test "simple" 3306 "< \"infile.txt'\"" 3306 2 "syntax error"
run_test "simple" 3307 "< \"infile.txt\"'" 3307 2 "syntax error"
run_test "simple" 3308 "<< 'infile.txt" 3308 2 "syntax error"
run_test "simple" 3309 "<< infile.txt'" 3309 2 "syntax error"
run_test "simple" 3310 "<< \"infile.txt" 3310 2 "syntax error"
run_test "simple" 3311 "<< infile.txt\"" 3311 2 "syntax error"
run_test "simple" 3312 "<< 'infile.txt\"" 3312 2 "syntax error"
run_test "simple" 3313 "<< 'infile.txt'\"" 3313 2 "syntax error"
#run_test "simple" 3314 "<< \"infile.txt'\"" 3314 2 "syntax error"
run_test "simple" 3315 "<< \"infile.txt\"'" 3315 2 "syntax error"

run_test "simple" 3400 "> 'outfile.txt" 3400 2 "syntax error"
run_test "simple" 3401 "> outfile.txt'" 3401 2 "syntax error"
run_test "simple" 3402 "> \"outfile.txt" 3402 2 "syntax error"
run_test "simple" 3403 "> outfile.txt\"" 3403 2 "syntax error"
run_test "simple" 3404 "> 'outfile.txt\"" 3404 2 "syntax error"
run_test "simple" 3405 "> 'outfile.txt'\"" 3405 2 "syntax error"
#run_test "simple" 3406 "> \"outfile.txt'\"" 3406 2 "syntax error"
run_test "simple" 3407 "> \"outfile.txt\"'" 3407 2 "syntax error"
run_test "simple" 3408 ">> 'outfile.txt" 3408 2 "syntax error"
run_test "simple" 3409 ">> outfile.txt'" 3409 2 "syntax error"
run_test "simple" 3410 ">> \"outfile.txt" 3410 2 "syntax error"
run_test "simple" 3411 ">> outfile.txt\"" 3411 2 "syntax error"
run_test "simple" 3412 ">> 'outfile.txt\"" 3412 2 "syntax error"
run_test "simple" 3413 ">> 'outfile.txt'\"" 3413 2 "syntax error"
#run_test "simple" 3414 ">> \"outfile.txt'\"" 3414 2 "syntax error"
run_test "simple" 3415 ">> \"outfile.txt\"'" 3415 2 "syntax error"

if (( "$start_index" >= 3300 && "$start_index" <= 3415 && "$end_index" >= 3300 && "$end_index" <= 3415 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 3300 to 3415\n"
	else
		echo -e "end of test serie from 3300 to 3415"
	fi
fi

run_test "simple" 4000 "'ls" 4000 2 "syntax error"
run_test "simple" 4001 "ls'" 4001 2 "syntax error"
run_test "simple" 4002 "\"ls" 4002 2 "syntax error"
run_test "simple" 4003 "ls\"" 4003 2 "syntax error"
run_test "simple" 4004 "'ls\"" 4004 2 "syntax error"
run_test "simple" 4005 "'ls'\"" 4005 2 "syntax error"
run_test "simple" 4006 "\"ls'" 4006 2 "syntax error"
run_test "simple" 4007 "\"ls\"'" 4007 2 "syntax error"
#run_test "simple" 4008 "''ls" 4008 2 "syntax error"
run_test "simple" 4009 "''ls'" 4009 2 "syntax error"
run_test "simple" 4010 "'''ls" 4010 2 "syntax error"
#run_test "simple" 4011 "'''ls'" 4011 2 "syntax error"
run_test "simple" 4012 "'''ls''" 4012 2 "syntax error"
#run_test "simple" 4013 "\"\"ls" 4013 2 "syntax error"
run_test "simple" 4014 "\"\"ls\"" 4014 2 "syntax error"
run_test "simple" 4015 "\"\"\"ls" 4015 2 "syntax error"
#run_test "simple" 4016 "\"\"\"ls\"" 4016 2 "syntax error"
run_test "simple" 4017 "\"\"\"ls\"\"" 4017 2 "syntax error"
#to continue


if (( "$start_index" >= 4000 && "$start_index" <= 4020 && "$end_index" >= 4000 && "$end_index" <= 4020 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 4000 to 4020\n"
	else
		echo -e "end of test serie from 4000 to 4020"
	fi
fi



run_test "simple" 4100 "cat 'ls" 4100 2 "syntax error"
run_test "simple" 4101 "cat ls'" 4101 2 "syntax error"
run_test "simple" 4102 "cat \"ls" 4102 2 "syntax error"
run_test "simple" 4103 "cat ls\"" 4103 2 "syntax error"
run_test "simple" 4104 "'cat' 'ls" 4104 2 "syntax error"
run_test "simple" 4105 "'cat' ls'" 4105 2 "syntax error"
run_test "simple" 4106 "'cat' ls'" 4106 2 "syntax error"
run_test "simple" 4107 "'cat' \"ls" 4107 2 "syntax error"
run_test "simple" 4108 "'cat' ls\"" 4108 2 "syntax error"
run_test "simple" 4109 ""cat" 'ls" 4109 2 "syntax error"
run_test "simple" 4110 ""cat" ls'" 4110 2 "syntax error"
run_test "simple" 4111 ""cat" ls'" 4111 2 "syntax error"
run_test "simple" 4112 ""cat" \"ls" 4112 2 "syntax error"
run_test "simple" 4113 ""cat" ls\"" 4113 2 "syntax error"
run_test "simple" 4114 "cat 'ls " 4114 2 "syntax error"
run_test "simple" 4115 "cat ls' " 4115 2 "syntax error"
run_test "simple" 4116 "cat \"ls " 4116 2 "syntax error"
run_test "simple" 4117 "cat ls\" " 4117 2 "syntax error"
run_test "simple" 4118 "cat 'ls  " 4118 2 "syntax error"
run_test "simple" 4119 "cat ls'  " 4119 2 "syntax error"
run_test "simple" 4120 "cat \"ls  " 4120 2 "syntax error"
run_test "simple" 4121 "cat ls\"  " 4121 2 "syntax error"
run_test "simple" 4122 "cat ' ls" 4122 2 "syntax error"
run_test "simple" 4123 "cat  ls'" 4123 2 "syntax error"
run_test "simple" 4124 "cat \" ls" 4124 2 "syntax error"
run_test "simple" 4125 "cat ls \"" 4125 2 "syntax error"

if (( "$start_index" >= 4100 && "$start_index" <= 4125 && "$end_index" >= 4100 && "$end_index" <= 4125 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 4100 to 4125\n"
	else
		echo -e "end of test serie from 4100 to 4125"
	fi
fi

run_test "simple" 4300 "'" 4300 2 #exit_status to confirm
run_test "simple" 4301 "\"" 4301 2 #exit_status to confirm
run_test "simple" 4302 "\"\"\"" 4302 2 #exit_status to confirm

if (( "$start_index" >= 4300 && "$start_index" <= 4350 && "$end_index" >= 4300 && "$end_index" <= 4350 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 4300 to 4350\n"
	else
		echo -e "end of test serie from 4300 to 4350"
	fi
fi


run_test "simple" 4400 "'ls -l cat -e'" 4400 127
run_test "simple" 4401 "\"ls -l cat -e\"" 4401 127
run_test "simple" 4402 "'\"ls -l cat -e\"'" 4402 127
run_test "simple" 4403 "\"'ls -l cat -e'\"" 4403 127

run_test "simple" 4404 "'ls'-l cat -e" 4404 127
run_test "simple" 4405 "ls'-l' cat -e" 4405 127
run_test "simple" 4406 "\"ls\"-l cat -e" 4406 127
run_test "simple" 4407 "ls\"-l\" cat -e" 4407 127

run_test "simple" 4408 "'ls -l' cat -e" 4408 127
run_test "simple" 4409 "\"ls -l\" cat -e" 4409 127
run_test "simple" 4410 "'\"ls -l\"' cat -e" 4410 127
run_test "simple" 4411 "\"'ls -l'\" cat -e" 4411 127

run_test "simple" 4412 "'ls -l'cat -e" 4412 127
run_test "simple" 4413 "\"ls -l\"cat -e" 4413 127
run_test "simple" 4414 "'\"ls -l\"'cat -e" 4414 127
run_test "simple" 4415 "\"'ls -l'\"cat -e" 4415 127

run_test "simple" 4416 "'ls -l' 'cat' -e" 4416 127
run_test "simple" 4417 "\"ls -l\" 'cat' -e" 4417 127
run_test "simple" 4418 "'\"ls -l\"' 'cat' -e" 4418 127
run_test "simple" 4419 "\"'ls -l'\" 'cat' -e" 4419 127


run_test "simple" 4420 "'ls -l' cat '-e'" 4420 127
run_test "simple" 4421 "\"ls -l\" cat '-e'" 4421 127
run_test "simple" 4422 "'\"ls -l\"' cat '-e'" 4422 127
run_test "simple" 4423 "\"'ls -l'\" cat '-e'" 4423 127
run_test "simple" 4424 "'ls -l' 'cat' '-e'" 4424 127
run_test "simple" 4425 "\"ls -l\" 'cat' '-e'" 4425 127
run_test "simple" 4426 "'\"ls -l\"' 'cat' '-e'" 4426 127
run_test "simple" 4427 "\"'ls -l'\" 'cat' '-e'" 4427 127
run_test "simple" 4428 "'ls -l' \"cat\" '-e'" 4428 127
run_test "simple" 4429 "\"ls -l\" \"cat\" '-e'" 4429 127
run_test "simple" 4430 "'\"ls -l\"' \"cat\" '-e'" 4430 127
run_test "simple" 4431 "\"'ls -l'\" \"cat\" '-e'" 4431 127
run_test "simple" 4432 "'ls -l' \"cat\" \"-e\"" 4432 127
run_test "simple" 4433 "\"ls -l\" \"cat\" \"-e\"" 4433 127
run_test "simple" 4434 "'\"ls -l\"' \"cat\" \"-e\"" 4434 127
run_test "simple" 4435 "\"'ls -l'\" \"cat\" \"-e\"" 4435 127

run_test "simple" 4436 "'ls -l'cat '-e'" 4436 127
run_test "simple" 4437 "\"ls -l\"cat '-e'" 4437 127
run_test "simple" 4438 "'\"ls -l\"'cat '-e'" 4438 127
run_test "simple" 4439 "\"'ls -l'\"cat '-e'" 4439 127
run_test "simple" 4440 "'ls -l'cat \"-e\"" 4470 127
run_test "simple" 4441 "\"ls -l\"cat \"-e\"" 4441 127
run_test "simple" 4442 "'\"ls -l\"'cat \"-e\"" 4472 127
run_test "simple" 4443 "\"'ls -l'\"cat \"-e\"" 4443 127
run_test "simple" 4444 "'ls -l''cat' '-e'" 4444 127
run_test "simple" 4445 "\"ls -l\"'cat' '-e'" 4445 127
run_test "simple" 4446 "'\"ls -l\"''cat' '-e'" 4446 127
run_test "simple" 4447 "\"'ls -l'\"'cat' '-e'" 4447 127
run_test "simple" 4448 "'ls -l''cat' \"-e\"" 4448 127
run_test "simple" 4449 "\"ls -l\"'cat' \"-e\"" 4449 127
run_test "simple" 4450 "'\"ls -l\"''cat' \"-e\"" 4450 127
run_test "simple" 4451 "\"'ls -l'\"'cat' \"-e\"" 4451 127
run_test "simple" 4452 "'ls -l'\"cat\" '-e'" 4452 127
run_test "simple" 4453 "\"ls -l\"\"cat\" '-e'" 4453 127
run_test "simple" 4454 "'\"ls -l\"'\"cat\" '-e'" 4454 127
run_test "simple" 4455 "\"'ls -l'\"\"cat\" '-e'" 4455 127
run_test "simple" 4456 "'ls -l'\"cat\" \"-e\"" 4456 127
run_test "simple" 4457 "\"ls -l\"\"cat\" \"-e\"" 4457 127
run_test "simple" 4458 "'\"ls -l\"'\"cat\" \"-e\"" 4458 127
run_test "simple" 4459 "\"'ls -l'\"\"cat\" \"-e\"" 4459 127

run_test "simple" 4460 "'ls -l' cat'-e'" 4460 127
run_test "simple" 4461 "\"ls -l\" cat'-e'" 4461 127
run_test "simple" 4462 "'\"ls -l\"' cat'-e'" 4462 127
run_test "simple" 4463 "\"'ls -l'\" cat'-e'" 4463 127
run_test "simple" 4464 "'ls -l' 'cat''-e'" 4464 127
run_test "simple" 4465 "\"ls -l\" 'cat''-e'" 4465 127
run_test "simple" 4466 "'\"ls -l\"' 'cat''-e'" 4466 127
run_test "simple" 4467 "\"'ls -l'\" 'cat''-e'" 4467 127
run_test "simple" 4468 "'ls -l' \"cat\"'-e'" 4468 127
run_test "simple" 4469 "\"ls -l\" \"cat\"'-e'" 4469 127
run_test "simple" 4470 "'\"ls -l\"' \"cat\"'-e'" 4470 127
run_test "simple" 4471 "\"'ls -l'\" \"cat\"'-e'" 4471 127
run_test "simple" 4472 "'ls -l' \"cat\"\"-e\"" 4472 127
run_test "simple" 4473 "\"ls -l\" \"cat\"\"-e\"" 4473 127
run_test "simple" 4474 "'\"ls -l\"' \"cat\"\"-e\"" 4474 127
run_test "simple" 4475 "\"'ls -l'\" \"cat\"\"-e\"" 4475 127

if (( "$start_index" >= 4400 && "$start_index" <= 4475 && "$end_index" >= 4400 && "$end_index" <= 4475 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 4400 to 4475\n"
	else
		echo -e "end of test serie from 4400 to 4475"
	fi
fi

if (( "$start_index" >= 4800 && "$start_index" <= 4999 && "$end_index" >= 4800 && "$end_index" <= 4999 ))
then
	echo -e "lucas tests implementation, and more\n"
fi


run_test "simple" 4801 "echo hello world" 4801 0
run_test "simple" 4802 "echo \"hello world\"" 4802 0
run_test "simple" 4803 "echo 'hello world'" 4803 0
run_test "simple" 4804 "echo hello'world'" 4804 0
run_test "simple" 4805 "echo hello\"\"world" 4805 0
run_test "simple" 4806 "echo ''" 4806 0
run_test "simple" 4807 "echo \"\$PWD\"" 4807 0
run_test "simple" 4808 "echo '\$PWD'" 4808 0
run_test "simple" 4809 "echo \"aspas ->'\"" 4809 0
run_test "simple" 4810 "echo \"aspas -> ' \"" 4810 0
run_test "simple" 4811 "echo 'aspas ->\"'" 4811 0
run_test "simple" 4812 "echo 'aspas -> \" '" 4812 0
run_test "simple" 4813 "echo \"> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<\"" 4813 0


run_test "simple" 4857 "grep est <./temp/infile1.txt" 4857 0 "" "grep leak"
run_test "simple" 4858 "grep est \"<infile1.txt\" <         ./temp/infile1.txt" 4858 0 "" "grep leak"


run_test "simple" 4873 "cat <\"./temp/infile1.txt\" | echo hi" 4873 0
run_test "simple" 4874 "cat <\"./test_files/infile1\" | grep hello\" | echo hi" 4874 0
run_test "simple" 4875 "cat <\"./temp/infile_big.txt\" | echo hi" 4875 0



run_test "simple" 4933 "\$PWD" 4933 126 ": Is a directory"

mkdir ./temp/no_permission_dir
chmod 000 ./temp/no_permission_dir
run_test "simple" 4935 "./temp/no_permission_dir" 4935 126 "./temp/no_permission_dir: Is a directory"
run_test "simple" 4936 "cd ./temp/no_permission_dir" 4936 1 "cd: ./temp/no_permission_dir: Permission denied"

chmod 744 ./temp/no_permission_dir
rmdir ./temp/no_permission_dir

run_test "simple" 4937 "./missing.out" 4937 127 "./missing.out: No such file or directory"
#run_test "simple" 4938 "./minishell" 4938 0

run_test "simple" 4941 "./temp" 4941 126 "./temp: Is a directory"
run_test "simple" 4942 "temp/" 4942 126 "temp/: Is a directory"
run_test "simple" 4943 "/temp" 4943 127 "/temp: No such file or directory"
run_test "simple" 4944 "./missing" 4944 127 "./missing: No such file or directory"
run_test "simple" 4945 "/missing" 4945 127 "/missing: No such file or directory"
run_test "simple" 4946 "missing/" 4946 127 "missing/: No such file or directory"
run_test "simple" 4947 "/missing/" 4947 127 "/missing/: No such file or directory"
run_test "simple" 4948 "./missing/" 4948 127 "./missing/: No such file or directory"
run_test "simple" 4949 "./missing/missing" 4949 127 "./missing/missing: No such file or directory"
run_test "simple" 4950 "/missing/missing" 4950 127 "/missing/missing: No such file or directory"
run_test "simple" 4951 "missing/missing" 4951 127 "missing/missing: No such file or directory"
run_test "simple" 4952 "missing/missing/" 4952 127 "missing/missing/: No such file or directory"
run_test "simple" 4953 "/missing/missing/" 4953 127 "/missing/missing/: No such file or directory"
run_test "simple" 4954 "./missing/missing/" 4954 127 "./missing/missing/: No such file or directory"

run_test "simple" 4960 "/nfs" 4960 126 "/nfs: Is a directory"
run_test "simple" 4961 "/nfs/homes" 4961 126 "/nfs/homes: Is a directory"
run_test "simple" 4962 "/nix" 4962 126 "/nix: Is a directory"

run_test "simple" 4970 "temp" 4970 127 "temp: command not found"



if (( "$start_index" >= 4800 && "$start_index" <= 4999 && "$end_index" >= 4800 && "$end_index" <= 4999 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 4800 to 4999\n"
	else
		echo -e "end of test serie from 4800 to 4999"
	fi
fi





run_test "simple" 5000 "< temp/infile1.txt cat" 5000 0
run_test "simple" 5001 "cat < temp/infile1.txt" 5000 0
run_test "simple" 5002 "< temp/infile1.txt cat -e" 5002 0
run_test "simple" 5003 "cat -e < temp/infile1.txt" 5002 0
run_test "simple" 5004 "cat temp/infile1.txt" 5004 0

run_test "simple" 5010 "< temp/infile1.txt wc" 5010 0
run_test "simple" 5011 "wc < temp/infile1.txt" 5010 0
run_test "simple" 5012 "< temp/infile1.txt wc -l" 5012 0
run_test "simple" 5013 "wc -l < temp/infile1.txt" 5012 0
run_test "simple" 5014 "wc -l temp/infile1.txt" 5014 0

run_test "simple" 5020 "ls > temp/outfile1.txt" 5020 0
run_test "simple" 5021 "> temp/outfile1.txt ls" 5020 0

run_test "simple" 5030 "< temp/infile1.txt cat > temp/outfile1.txt" 5030 0
run_test "simple" 5031 "< temp/infile1.txt > temp/outfile1.txt cat" 5030 0
run_test "simple" 5032 "> temp/outfile1.txt < temp/infile1.txt cat" 5030 0

run_test "simple" 5035 "< temp/infile1.txt wc -l > temp/outfile1.txt" 5035 0
run_test "simple" 5036 "< temp/infile1.txt > temp/outfile1.txt wc -l" 5035 0
run_test "simple" 5037 "> temp/outfile1.txt < temp/infile1.txt wc -l" 5035 0

run_test "simple" 5040 "< temp/infile1.txt ls > temp/outfile1.txt" 5040 0
run_test "simple" 5041 "< temp/infile1.txt > temp/outfile1.txt ls" 5040 0
run_test "simple" 5042 "> temp/outfile1.txt < temp/infile1.txt ls" 5040 0

run_test "simple" 5045 "< temp/infile1.txt < temp/infile2.txt cat" 5045 0
run_test "simple" 5046 "< temp/infile1.txt cat < temp/infile2.txt" 5045 0
run_test "simple" 5047 "cat < temp/infile1.txt < temp/infile2.txt" 5045 0

run_test "simple" 5050 "< temp/infile1.txt < temp/infile2.txt wc -l" 5050 0
run_test "simple" 5051 "< temp/infile1.txt wc -l < temp/infile2.txt" 5050 0
run_test "simple" 5052 "wc -l < temp/infile1.txt < temp/infile2.txt" 5050 0

run_test "simple" 5055 "< temp/infile1.txt < temp/infile2.txt ls" 5055 0
run_test "simple" 5056 "< temp/infile1.txt ls < temp/infile2.txt" 5055 0
run_test "simple" 5057 "ls < temp/infile1.txt < temp/infile2.txt" 5055 0

#run_test "simple" 5060 "> temp/outfile1.txt > temp/outfile2.txt cat" 5060 0
#run_test "simple" 5061 "> temp/outfile1.txt cat > temp/outfile2.txt" 5060 0
#run_test "simple" 5062 "cat > temp/outfile1.txt > temp/outfile2.txt" 5060 0

#run_test "simple" 5065 "> temp/outfile1.txt > temp/outfile2.txt wc -l" 5065 0
#run_test "simple" 5066 "> temp/outfile1.txt wc -l > temp/outfile2.txt" 5065 0
#run_test "simple" 5067 "wc -l > temp/outfile1.txt > temp/outfile2.txt" 5065 0

run_test "simple" 5070 "> temp/outfile1.txt > temp/outfile2.txt ls" 5070 0
run_test "simple" 5071 "> temp/outfile1.txt ls > temp/outfile2.txt" 5070 0
run_test "simple" 5072 "ls > temp/outfile1.txt > temp/outfile2.txt" 5070 0

run_test "simple" 5080 "cat < temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt" 5080 0
run_test "simple" 5081 "< temp/infile1.txt cat < temp/infile2.txt > temp/outfile1.txt" 5080 0
run_test "simple" 5082 "< temp/infile1.txt < temp/infile2.txt cat > temp/outfile1.txt" 5080 0
run_test "simple" 5083 "< temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt cat" 5080 0
run_test "simple" 5084 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt cat" 5080 0
run_test "simple" 5085 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt cat" 5080 0

run_test "simple" 5090 "wc -l < temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt" 5090 0
run_test "simple" 5091 "< temp/infile1.txt wc -l < temp/infile2.txt > temp/outfile1.txt" 5090 0
run_test "simple" 5092 "< temp/infile1.txt < temp/infile2.txt wc -l > temp/outfile1.txt" 5090 0
run_test "simple" 5093 "< temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt wc -l" 5090 0
run_test "simple" 5094 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt wc -l" 5090 0
run_test "simple" 5095 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt wc -l" 5090 0

run_test "simple" 5100 "ls < temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt" 5100 0
run_test "simple" 5101 "< temp/infile1.txt ls < temp/infile2.txt > temp/outfile1.txt" 5100 0
run_test "simple" 5102 "< temp/infile1.txt < temp/infile2.txt ls > temp/outfile1.txt" 5100 0
run_test "simple" 5103 "< temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt ls" 5100 0
run_test "simple" 5104 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt ls" 5100 0
run_test "simple" 5105 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt ls" 5100 0

run_test "simple" 5110 "cat < temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt" 5110 0
run_test "simple" 5111 "< temp/infile1.txt cat > temp/outfile1.txt > temp/outfile2.txt" 5110 0
run_test "simple" 5112 "< temp/infile1.txt > temp/outfile1.txt cat > temp/outfile2.txt" 5110 0
run_test "simple" 5113 "< temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt cat" 5110 0
run_test "simple" 5114 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt cat" 5110 0
run_test "simple" 5115 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt cat" 5110 0

run_test "simple" 5120 "wc -l < temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt" 5120 0
run_test "simple" 5121 "< temp/infile1.txt wc -l > temp/outfile1.txt > temp/outfile2.txt" 5120 0
run_test "simple" 5122 "< temp/infile1.txt > temp/outfile1.txt wc -l > temp/outfile2.txt" 5120 0
run_test "simple" 5123 "< temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt wc -l" 5120 0
run_test "simple" 5124 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt wc -l" 5120 0
run_test "simple" 5125 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt wc -l" 5120 0

run_test "simple" 5130 "ls < temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt" 5130 0
run_test "simple" 5131 "< temp/infile1.txt ls > temp/outfile1.txt > temp/outfile2.txt" 5130 0
run_test "simple" 5132 "< temp/infile1.txt > temp/outfile1.txt ls > temp/outfile2.txt" 5130 0
run_test "simple" 5133 "< temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt ls" 5130 0
run_test "simple" 5134 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt ls" 5130 0
run_test "simple" 5135 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt ls" 5130 0

run_test "simple" 5150 "< temp/infile1.txt < temp/infile2.txt cat > temp/outfile1.txt > temp/outfile2.txt" 5150 0
run_test "simple" 5151 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt > temp/outfile2.txt cat" 5150 0
run_test "simple" 5152 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt > temp/outfile2.txt cat" 5150 0
run_test "simple" 5153 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt < temp/infile2.txt cat" 5150 0
run_test "simple" 5154 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt < temp/infile2.txt cat" 5150 0

run_test "simple" 5155 "< temp/infile1.txt < temp/infile2.txt wc -l > temp/outfile1.txt > temp/outfile2.txt" 5155 0
run_test "simple" 5156 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt > temp/outfile2.txt wc -l" 5155 0
run_test "simple" 5157 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt > temp/outfile2.txt wc -l" 5155 0
run_test "simple" 5158 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt < temp/infile2.txt wc -l" 5155 0
run_test "simple" 5159 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt < temp/infile2.txt wc -l" 5155 0

run_test "simple" 5165 "< temp/infile1.txt < temp/infile2.txt ls > temp/outfile1.txt > temp/outfile2.txt" 5165 0
run_test "simple" 5166 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt > temp/outfile2.txt ls" 5165 0
run_test "simple" 5167 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt > temp/outfile2.txt ls" 5165 0
run_test "simple" 5168 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt < temp/infile2.txt ls" 5165 0
run_test "simple" 5169 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt < temp/infile2.txt ls" 5165 0

if (( "$start_index" >= 5000 && "$start_index" <= 5170 && "$end_index" >= 5000 && "$end_index" <= 5170 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 5000 to 5170\n"
	else
		echo -e "end of test serie from 5000 to 5170"
	fi
fi

run_test "simple" 5200 "grep un < temp/infile1.txt" 5200 0 "" "grep leak"
run_test "simple" 5201 "echo < temp/infile1.txt added_word" 5201 0
run_test "simple" 5202 "echo < temp/infile1.txt added_word" 5202 0
run_test "simple" 5203 "echo added_word1 < temp/infile1.txt added_word2" 5203 0


#run_test "simple" 5250 "cat | cat | ls" 5250 0 "" "needs 2 entries"


if (( "$start_index" >= 5200 && "$start_index" <= 5300 && "$end_index" >= 5200 && "$end_index" <= 5300 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 5200 to 5300\n"
	else
		echo -e "end of test serie from 5200 to 5300"
	fi
fi


run_test "simple" 7000 "temp/infile1.txt cat" 7000 126 "temp/infile1.txt: Permission denied"
run_test "simple" 7001 "temp/infile1.txt wc" 7001 126 "temp/infile1.txt: Permission denied"
run_test "simple" 7002 "./temp/infile1.txt cat" 7002 126 "temp/infile1.txt: Permission denied"
run_test "simple" 7003 "./temp/infile1.txt wc" 7003 126 "temp/infile1.txt: Permission denied"
run_test "simple" 7004 "Makefile cat" 7004 127 "Makefile: command not found"
run_test "simple" 7005 "Makefile wc" 7005 127 "Makefile: command not found"

echo "ceci est un test" > temp/full_permission_file.txt
chmod 777 temp/full_permission_file.txt
run_test "simple" 7010 "./temp/full_permission_file.txt" 7010 127 "./temp/full_permission_file.txt: line 1: ceci: command not found"
run_test "simple" 7011 "./temp/full_permission_file.txt cat" 7011 127 "./temp/full_permission_file.txt: line 1: ceci: command not found"

echo "ls" > temp/full_permission_file.txt
run_test "simple" 7015 "./temp/full_permission_file.txt" 7015 0


run_test "simple" 7020 "< temp/infile1.txt cat wc" 7020 1 "cat: wc: No such file or directory"

run_test "simple" 7100 "< missing_file cat -e" 7100 1 "missing_file: No such file or directory"
run_test "simple" 7101 "< missing_file invalid_command" 7101 1 "missing_file: No such file or directory"

run_test "simple" 7200 "< missing_file cat > outfile1.txt" 7200 1 "missing_file: No such file or directory"
run_test "simple" 7201 "> temp/outfile1.txt < missing_file cat" 7201 1 "missing_file: No such file or directory"

echo > temp/outfile_without_permission
chmod 000 temp/outfile_without_permission
run_test "simple" 7300 "> temp/outfile_without_permission < missing_file cat -e" 7300 1 "temp/outfile_without_permission: Permission denied"
run_test "simple" 7301 "< missing_file > temp/outfile_without_permission cat -e" 7301 1 "missing_file: No such file or directory"
run_test "simple" 7302 "> temp/outfile_without_permission < temp/infile1.txt cat -e" 7302 1 "temp/outfile_without_permission: Permission denied"
run_test "simple" 7303 "< temp/infile1.txt > temp/outfile_without_permission cat -e" 7303 1 "temp/outfile_without_permission: Permission denied"
run_test "simple" 7304 "> temp/outfile_without_permission < missing_file invalid_command" 7304 1 "temp/outfile_without_permission: Permission denied"
run_test "simple" 7305 " invalid_command > temp/outfile_without_permission < missing_file" 7305 1 "temp/outfile_without_permission: Permission denied"

echo > temp/infile_without_permission
chmod 000 temp/infile_without_permission
run_test "simple" 7306 "temp/infile_without_permission" 7300 1 "temp/infile_without_permission: Permission denied"
run_test "simple" 7307 "./temp/infile_without_permission" 7300 1 "temp/infile_without_permission: Permission denied"


run_test "simple" 7310 "< temp/infile_without_permission > temp/outfile1.txt cat -e" 7310 1 "temp/infile_without_permission: Permission denied"
run_test "simple" 7311 "> temp/outfile_without_permission < temp/infile_without_permission cat -e" 7311 1 "temp/outfile_without_permission: Permission denied"
run_test "simple" 7312 "< temp/infile_without_permission > temp/outfile_without_permission cat -e" 7312 1 "temp/infile_without_permission: Permission denied"
run_test "simple" 7313 "< temp/infile_without_permission > temp/outfile1.txt cat -e" 7313 1 "temp/infile_without_permission: Permission denied"
run_test "simple" 7314 "> temp/outfile1.txt < temp/infile_without_permission cat -e" 7314 1 "temp/infile_without_permission: Permission denied"
run_test "simple" 7315 "< temp/infile_without_permission > temp/outfile1.txt invalid_command" 7315 1 "temp/infile_without_permission: Permission denied"
run_test "simple" 7316 "invalid_command < temp/infile_without_permission > temp/outfile1.txt" 7316 1 "temp/infile_without_permission: Permission denied"

chmod 644 temp/outfile_without_permission
delete_file temp/outfile_without_permission
chmod 644 temp/infile_without_permission
delete_file temp/infile_without_permission


# -g for greater than and -ge for greater than or equal to
if [ $flag -gt 0 ]
then
	echo -e "${RED}$flag errors were detected${NC}"
else
	echo -e "${GREEN}no error detected${NC}"
fi
#delete_files

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

BLOCK_COMMENT


exit
