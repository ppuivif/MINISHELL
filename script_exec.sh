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

function delete_file() {
	file="$1"

	if [ -f $file ]
	then
		chmod 644 $file
		rm $file
	fi
}


execute_test() {
    test_index=$1
    command=$2
	file_test=$3
    exit_code_expected=$4
 	substring=$5
	test="test$test_index\t$command\t"
    message=$test
    
	create_files_and_set_permissions $test_index
	
	eval "$command" 1>"temp/$test_index-bash_stdout.txt" 2>"temp/$test_index-bash_stderr.txt"
	exit_code_bash=$?
#	echo "exit_code_bash"
#	echo "$exit_code_bash"
	cat "temp/outfile1.txt" >"temp/$test_index-bash_outfile1.txt"
	cat "temp/outfile2.txt" >"temp/$test_index-bash_outfile2.txt"
	
	echo > temp/outfile1.txt
	echo > temp/outfile2.txt	
    
#	echo "$command" >&100
	echo "$command" >"temp/tmp_to_read_command.txt"

#	ls -l /proc/$$/fd

#    echo "$command" | ./minishell 1>"temp/$test_index-minishell_stdout.txt" 2>"temp/$test_index-minishell_stderr.txt"
    ./minishell 100 1>"temp/$test_index-minishell_stdout.txt" 2>"temp/$test_index-minishell_stderr.txt"
	exit_code_minishell=$?
#	echo "exit_code_minishell"
#	echo "$exit_code_minishell"
	cat "temp/outfile1.txt" >"temp/$test_index-minishell_outfile1.txt"
	cat "temp/outfile2.txt" >"temp/$test_index-minishell_outfile2.txt"
 	
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
		if [ "$status1" == "KO" ] || [ "$status2" == "KO" ] || [ "$status3" == "KO" ] || [ "$status4" == "KO" ] || [ "$status5" == "KO" ]
#		if [ "$status1" == "KO" ] || [ "$status2" == "KO" ] || [ "$status3" == "KO" ] || [ "$status4" == "KO" ]
		then
			status_message="${RED} KO : ${NC}"
			echo -e "${message}${spaces}${test_index}${status_message}${error_detail1}${error_detail2}${error_detail3}${error_detail4}${error_detail5}"
		fi
	else
		if [ "$status1" == "KO" ] || [ "$status2" == "KO" ] || [ "$status3" == "KO" ] || [ "$status4" == "KO" ] || [ "$status5" == "KO" ]
#		if [ "$status1" == "KO" ] || [ "$status2" == "KO" ] || [ "$status3" == "KO" ] || [ "$status4" == "KO" ]
		then
			status_message="${RED} KO : ${NC}"
			echo -e "${message}${spaces}${test_index}${status_message}${error_detail1}${error_detail2}${error_detail3}${error_detail4}${error_detail5}"
		else
			status_message="${GREEN} OK${NC}"
			echo -e "${message}${spaces}${status_message}"
		fi
	fi
	substring=""
	delete_infiles
	delete_outfiles
	delete_file "temp/tmp_to_read_command.txt"
	exec 100>&-
}

run_test_heredoc() {
    test_index=$1
    command=$2
	file_test=$3
    exit_code_expected=$4
 	substring=$5
	test="test$test_index\t$command\t"
    message=$test
    create_files_and_set_permissions $test_index
#	heredoc_input=$(cat << 'EOF'
#	first_line
#	limiter
#	EOF
#	)
	eval "$command" <<< "$heredoc_input" 1>"temp/bash_stdout$test_index.txt" 2>temp/bash_stderr$test_index.txt
	exit_code_bash=$?
	cat "outfile1.txt" >"temp/$test_index\_bash_outfile_1.txt"
	cat "outfile2.txt" >"temp/$test_index\_bash_outfile_2.txt"
	echo > outfile1.txt
	echo > outfile2.txt	
    echo "$command" | ./minishell 100 | echo -e "first line" | echo -e "limiter" 1>"temp/minishell_stdout$test_index.txt" 2>temp/minishell_stderr$test_index.txt
	exit_code_minishell=$?
#	echo "$exit_code_minishell"
	cat "outfile1.txt" >"temp/$test_index\_minishell_outfile_1.txt"
	cat "outfile2.txt" >"temp/$test_index\_minishell_outfile_2.txt"
 	diff_outfile1=$(diff "temp/$test_index\_minishell_outfile_1.txt" "temp/$test_index\_bash_outfile_1.txt" > /dev/null)
	diff_exit_outfile1=$?
	diff_outfile1=$(diff "temp/$test_index\_minishell_outfile_2.txt" "temp/$test_index\_bash_outfile_2.txt" > /dev/null)
	diff_exit_outfile2=$?
	diff_stdout=$(diff "temp/minishell_stdout$test_index.txt" "temp/bash_stdout$test_index.txt" > /dev/null)
	diff_exit_stdout=$?
	empty_substring=""
	if [ "$substring" = "$empty_substring" ] && [ ! -s "temp/minishell_stderr$test_index.txt" ]
	then
		diff_empty_substring=0
	else
		diff_empty_substring=1
	fi
 	diff_stderr=$(grep "$substring" temp/minishell_stderr$test_index.txt >/dev/null)
	diff_exit_stderr=$?
	if [ $diff_exit_outfile1 -eq 1 ]
	then
		error_detail1="${RED}outfile1.txt ${NC}"
		status_message="${RED}KO : ${NC}"
		flag=$((flag + 1))
	else
		status_message="${GREEN} OK${NC}"
		delete_file "temp/$test_index\_minishell_outfile_1.txt"
		delete_file "temp/$test_index\_bash_outfile_1.txt"
	fi
	if [ $diff_exit_outfile2 -eq 1 ]
	then
		error_detail2="${RED}outfile2.txt ${NC}"
		status_message="${RED}KO : ${NC}"
		flag=$((flag + 1))
	else
		status_message="${GREEN} OK${NC}"
		delete_file "temp/$test_index\_minishell_outfile_2.txt"
		delete_file "temp/$test_index\_bash_outfile_2.txt"
	fi
	if [ $diff_exit_stdout -eq 1 ]
	then
		error_detail3="${RED}std_output ${NC}"
		status_message="${RED}KO : ${NC}"
		flag=$((flag + 1))
	else
		status_message="${GREEN} OK${NC}"
		delete_file "temp/minishell_stdout$test_index.txt"
		delete_file "temp/bash_stdout$test_index.txt"
	fi
	if [ $diff_exit_stderr -eq 0 ] || [ $diff_empty_substring -eq 0 ]
#	if	grep "$substring" temp/minishell_stderr$test_index.txt >/dev/null
	then
    	status_message="${GREEN} OK${NC}"
		delete_file "temp/minishell_stderr$test_index.txt"
		delete_file "temp/bash_stderr$test_index.txt"
	else	
		error_detail4="${RED}stderr_output ${NC}"
		status_message="${RED}KO : ${NC}"
		flag=$((flag + 1))
    fi
#	if [ $exit_code_minishell -ne $exit_code_bash ]
#   then
#		error_detail5="${RED}exit_code ${NC}"
#	    status_message="${RED}KO : ${NC}"
#		flag=$((flag + 1))
#	else
#       status_message="${GREEN} OK${NC}"
#    fi
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
		if [ "$status_message" == "${RED}KO : ${NC}" ]
		then
			echo -e "${message}${spaces}${status_message}${error_detail1}${error_detail2}${error_detail3}${error_detail4}${error_detail5}"
		fi
	else
			echo -e "${message}${spaces}${status_message}"
	fi
	delete_infiles
	delete_outfiles
}

: <<BLOCK_COMMENT

run_test_heredoc() {
    test_index=$1
    command=$2
	file_test=$3
    status=$4
    test="test$test_index\t$command\t"
    message=$test
    echo > "temp/minishell_test$test_index.txt"
    chmod 644 "temp/minishell_test$test_index.txt"
	exec 100> "temp/minishell_test$test_index.txt"
    echo -e "$command" | ./minishell 100 2>&1 >/dev/null | echo -e "second line" | echo -e "limiter" 2>&1 >/dev/null

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

BLOCK_COMMENT

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
		[ $(wc -c < "temp/minishell_test$test_index.txt") -eq 0 ] &&
		grep "$substring" temp/stderr2_minishell$test_index.txt >/dev/null
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

#see bash -c for valgrind (avec -c autorise argc argv)

run_test_error() {
    test_index=$1
    command=$2
	file_test=$3
    status=$4
	substring=$5
    test="test$test_index\t$command\t"
    message=$test
	echo > "temp/minishell_test$test_index.txt"
    chmod 644 "temp/minishell_test$test_index.txt"
    echo > "temp/stderr2_minishell$test_index.txt"
    chmod 644 "temp/stderr2_minishell$test_index.txt"
	exec 3> "temp/minishell_test$test_index.txt"
	echo "$command" | ./minishell 3 1>/dev/null 2>"temp/stderr2_minishell$test_index.txt"
    status_output_minishell=$?
	diff_output=$(diff "temp/minishell_test$test_index.txt" "Tests/test$file_test.txt" > /dev/null)
	diff_exit_status=$?
	if [ $diff_exit_status -eq 1 ]
#	if	[ -s "temp/minishell_test$test_index.txt" ]
	then
		error_detail1="${RED}std_output ${NC}"
		status_message="${RED}KO : ${NC}"
		flag=$((flag + 1))
	else
		status_message="${GREEN} OK${NC}"
		delete_test_file "temp/minishell_test$test_index.txt"
	fi
	if	grep "$substring" temp/stderr2_minishell$test_index.txt >/dev/null
	then
		error_detail2="${RED}stderr_output ${NC}"
        status_message="${RED}KO : ${NC}"
		flag=$((flag + 1))
	else
        status_message="${GREEN} OK${NC}"
		delete_stderr_file "temp/stderr2_minishell$test_index.txt"
    fi
	if [ $status_output_minishell -ne $status ]
    then
		error_detail3="${RED}status_output ${NC}"
	    status_message="${RED}KO : ${NC}"
		flag=$((flag + 1))
	else
        status_message="${GREEN} OK${NC}"
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
		if [ "$status_message" == "${RED}KO : ${NC}" ]
		then
			echo -e "${message}${spaces}${status_message}${error_detail1}${error_detail2}${error_detail3}"
		fi
	else
			echo -e "${message}${spaces}${status_message}"
	fi
	#echo -e "$message"
}

create_temp_directory

run_test() {
	index=$1
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



run_test 1 "< temp/infile1.txt cat | cat > temp/outfile1.txt" 1 0
run_test 2 "<temp/infile1.txt cat | cat > temp/outfile1.txt" 1 0
run_test 3 "< temp/infile1.txt cat| cat > temp/outfile1.txt" 1 0
run_test 4 "< temp/infile1.txt cat |cat > temp/outfile1.txt" 1 0
run_test 5 "< temp/infile1.txt cat | cat >temp/outfile1.txt" 1 0
run_test 6 "<temp/infile1.txt cat|cat >temp/outfile1.txt" 1 0
run_test 7 "<	temp/infile1.txt cat | cat > temp/outfile1.txt" 1 0
run_test 8 "<		temp/infile1.txt cat | cat > temp/outfile1.txt" 1 0
run_test 9 "< temp/infile1.txt cat	| cat > temp/outfile1.txt" 1 0
run_test 10 "< temp/infile1.txt cat		| cat > temp/outfile1.txt" 1 0
run_test 11 "< temp/infile1.txt cat |	cat > temp/outfile1.txt" 1 0
run_test 12 "< temp/infile1.txt cat |		cat > temp/outfile1.txt" 1 0
run_test 13 "< temp/infile1.txt cat |	cat > temp/outfile1.txt" 1 0
run_test 14 "< temp/infile1.txt cat |		cat > temp/outfile1.txt" 1 0
run_test 15 "< temp/infile1.txt cat | cat	> temp/outfile1.txt" 1 0
run_test 16 "< temp/infile1.txt cat | cat		> temp/outfile1.txt" 1 0
run_test 17 "< temp/infile1.txt cat | cat >	temp/outfile1.txt" 1 0
run_test 18 "< temp/infile1.txt cat | cat >		temp/outfile1.txt" 1 0
run_test 19 "< temp/infile1.txt cat | cat > temp/outfile1.txt	" 1 0
run_test 20 "< temp/infile1.txt cat | cat > temp/outfile1.txt		" 1 0


#run_test_heredoc 21 "<< limiter cat | cat > outfile1.txt" 21 0
#run_test_heredoc 22 "<<limiter cat | cat > outfile1.txt" 21 0
#run_test_heredoc 36 "<< limiter cat | cat		> outfile1.txt" 21 0
#run_test_heredoc 37 "<< limiter cat | cat >	outfile1.txt" 21 0
#run_test_heredoc 38 "<< limiter cat | cat >		outfile1.txt" 21 0
#run_test_heredoc 39 "<< limiter cat | cat > outfile1.txt	" 21 0
#run_test_heredoc 40 "<< limiter cat | cat > outfile1.txt		" 21 0

run_test 41 "< temp/infile1.txt cat | cat >> temp/outfile1.txt" 41 0
run_test 42 "<temp/infile1.txt cat | cat >> temp/outfile1.txt" 41 0
run_test 43 "< temp/infile1.txt cat| cat >> temp/outfile1.txt" 41 0
run_test 44 "< temp/infile1.txt cat |cat >> temp/outfile1.txt" 41 0
run_test 45 "< temp/infile1.txt cat | cat>> temp/outfile1.txt" 41 0
run_test 46 "< temp/infile1.txt cat | cat >>temp/outfile1.txt" 41 0
run_test 47 "<temp/infile1.txt cat|cat >>temp/outfile1.txt" 41 0
run_test 48 "< temp/infile1.txt cat | cat >> temp/outfile1.txt" 41 0
run_test 49 "<	temp/infile1.txt cat | cat >> temp/outfile1.txt" 41 0
run_test 50 "<		temp/infile1.txt cat | cat >> temp/outfile1.txt" 41 0
run_test 51 "< temp/infile1.txt cat	| cat >> temp/outfile1.txt" 41 0
run_test 52 "< temp/infile1.txt cat		| cat >> temp/outfile1.txt" 41 0
run_test 53 "< temp/infile1.txt cat |	cat >> temp/outfile1.txt" 41 0
run_test 54 "< temp/infile1.txt cat |		cat >> temp/outfile1.txt" 41 0
run_test 55 "< temp/infile1.txt cat | cat	>> temp/outfile1.txt" 41 0
run_test 56 "< temp/infile1.txt cat | cat		>> temp/outfile1.txt" 41 0
run_test 57 "< temp/infile1.txt cat | cat >>	temp/outfile1.txt" 41 0
run_test 58 "< temp/infile1.txt cat | cat >>		temp/outfile1.txt" 41 0
run_test 59 "< temp/infile1.txt cat | cat >> temp/outfile1.txt	" 41 0
run_test 60 "< temp/infile1.txt cat | cat >> temp/outfile1.txt		" 41 0

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


#run_test_heredoc 61 "<< limiter cat | cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 62 "<<limiter cat | cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 63 "<< limiter cat| cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 64 "<< limiter cat |cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 65 "<< limiter cat | cat>> temp/outfile1.txt" 61 0
#run_test_heredoc 66 "<< limiter cat | cat >>temp/outfile1.txt" 61 0
#run_test_heredoc 67 "<<limiter cat|cat >>temp/outfile1.txt" 61 0
#run_test_heredoc 68 "<< limiter cat | cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 69 "<<	limiter cat | cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 70 "<<		limiter cat | cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 71 "<< limiter cat	| cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 72 "<< limiter cat		| cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 73 "<< limiter cat |	cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 74 "<< limiter cat |		cat >> temp/outfile1.txt" 61 0
#run_test_heredoc 75 "<< limiter cat | cat	>> temp/outfile1.txt" 61 0
#run_test_heredoc 76 "<< limiter cat | cat		>> temp/outfile1.txt" 61 0
#run_test_heredoc 77 "<< limiter cat | cat >>	temp/outfile1.txt" 61 0
#run_test_heredoc 78 "<< limiter cat | cat >>		temp/outfile1.txt" 61 0
#run_test_heredoc 79 "<< limiter cat | cat >> temp/outfile1.txt	" 61 0
#run_test_heredoc 80 "<< limiter cat | cat >> temp/outfile1.txt		" 61 0

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

run_test 81 "< temp/infile1.txt < temp/infile2.txt" 81 0
run_test 82 "<temp/infile1.txt < temp/infile2.txt" 81 0
run_test 83 "< temp/infile1.txt <temp/infile2.txt" 81 0
run_test 84 "<temp/infile1.txt <temp/infile2.txt" 81 0
run_test 85 "<temp/infile1.txt<temp/infile2.txt" 81 0
run_test 86 "<temp/infile1.txt<temp/infile2.txt" 81 0
run_test 87 " <	temp/infile1.txt < temp/infile2.txt" 81 0
run_test 88 " < temp/infile1.txt	< temp/infile2.txt" 81 0
run_test 89 " < temp/infile1.txt <	temp/infile2.txt" 81 0
run_test 90 " < temp/infile1.txt < temp/infile2.txt	" 81 0
run_test 91 "< temp/infile1.txt < temp/infile2.txt < temp/infile3.txt" 91 0
run_test 92 "<temp/infile1.txt < temp/infile2.txt < temp/infile3.txt" 91 0
run_test 93 "< temp/infile1.txt <temp/infile2.txt < temp/infile3.txt" 91 0
run_test 94 "< temp/infile1.txt < temp/infile2.txt <temp/infile3.txt" 91 0
run_test 95 "< temp/infile1.txt < temp/infile2.txt < temp/infile3.txt" 91 0
run_test 96 "<temp/infile1.txt <temp/infile2.txt < temp/infile3.txt" 91 0
run_test 97 "<temp/infile1.txt <temp/infile2.txt <temp/infile3.txt" 91 0
run_test 98 "<temp/infile1.txt<temp/infile2.txt <temp/infile3.txt" 91 0
run_test 99 "<temp/infile1.txt<temp/infile2.txt<temp/infile3.txt" 91 0

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

run_test 100 "> temp/outfile1.txt > temp/outfile2.txt" 100 0
run_test 101 ">temp/outfile1.txt > temp/outfile2.txt" 100 0
run_test 102 "> temp/outfile1.txt >temp/outfile2.txt" 100 0
run_test 103 ">temp/outfile1.txt >temp/outfile2.txt" 100 0
run_test 104 ">temp/outfile1.txt>temp/outfile2.txt" 100 0
run_test 105 ">temp/outfile1.txt>temp/outfile2.txt" 100 0
run_test 106 " >	temp/outfile1.txt > temp/outfile2.txt" 100 0
run_test 107 " > temp/outfile1.txt	> temp/outfile2.txt" 100 0
run_test 108 " > temp/outfile1.txt >	temp/outfile2.txt" 100 0
run_test 109 " > temp/outfile1.txt > temp/outfile2.txt	" 100 0
run_test 110 "> temp/outfile1.txt > temp/outfile2.txt > temp/outfile3.txt" 110 0
run_test 111 ">temp/outfile1.txt > temp/outfile2.txt > temp/outfile3.txt" 110 0
run_test 112 "> temp/outfile1.txt >temp/outfile2.txt > temp/outfile3.txt" 110 0
run_test 113 "> temp/outfile1.txt > temp/outfile2.txt >temp/outfile3.txt" 110 0
run_test 114 "> temp/outfile1.txt > temp/outfile2.txt > temp/outfile3.txt" 110 0
run_test 115 ">temp/outfile1.txt >temp/outfile2.txt > temp/outfile3.txt" 110 0
run_test 116 ">temp/outfile1.txt >temp/outfile2.txt >temp/outfile3.txt" 110 0
run_test 117 ">temp/outfile1.txt>temp/outfile2.txt >temp/outfile3.txt" 110 0
run_test 118 ">temp/outfile1.txt>temp/outfile2.txt>temp/outfile3.txt" 110 0

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

run_test 140 ">> temp/outfile1.txt >> temp/outfile2.txt" 140 0
run_test 141 ">>temp/outfile1.txt >> temp/outfile2.txt" 140 0
run_test 142 ">> temp/outfile1.txt >>temp/outfile2.txt" 140 0
run_test 143 ">>temp/outfile1.txt >>temp/outfile2.txt" 140 0
run_test 144 ">>temp/outfile1.txt>>temp/outfile2.txt" 140 0
run_test 145 ">>temp/outfile1.txt>>temp/outfile2.txt" 140 0
run_test 146 " >>	temp/outfile1.txt >> temp/outfile2.txt" 140 0
run_test 147 " >> temp/outfile1.txt	>> temp/outfile2.txt" 140 0
run_test 148 " >> temp/outfile1.txt >>	temp/outfile2.txt" 140 0
run_test 149 " >> temp/outfile1.txt >> temp/outfile2.txt	" 140 0
run_test 150 ">> temp/outfile1.txt >> temp/outfile2.txt >> temp/outfile3.txt" 150 0
run_test 151 ">>temp/outfile1.txt >> temp/outfile2.txt >> temp/outfile3.txt" 150 0
run_test 152 ">> temp/outfile1.txt >>temp/outfile2.txt >> temp/outfile3.txt" 150 0
run_test 153 ">> temp/outfile1.txt >> temp/outfile2.txt >>temp/outfile3.txt" 150 0
run_test 154 ">> temp/outfile1.txt >> temp/outfile2.txt >> temp/outfile3.txt" 150 0
run_test 155 ">>temp/outfile1.txt >>temp/outfile2.txt >> temp/outfile3.txt" 150 0
run_test 156 ">>temp/outfile1.txt >>temp/outfile2.txt >>temp/outfile3.txt" 150 0
run_test 157 ">>temp/outfile1.txt>>temp/outfile2.txt >>temp/outfile3.txt" 150 0
run_test 158 ">>temp/outfile1.txt>>temp/outfile2.txt>>temp/outfile3.txt" 150 0

if (( "$start_index" >= 140 && "$start_index" <= 158 && "$end_index" >= 140 && "$end_index" <= 158 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 140 to 158\n"
	else
		echo -e "end of test serie from 140 to 158"
	fi
fi


run_test 160 "< 'temp/infile1.txt'" 160 0
run_test 161 "< \"temp/infile1.txt\"" 160 0
run_test 162 "< '\"temp/infile1.txt\"'" 162 0
run_test 163 "< \"'temp/infile1.txt'\"" 163 0
run_test 164 "< '\"'temp/infile1.txt'\"'" 164 0
run_test 165 "< \"'\"temp/infile1.txt\"'\"" 165 0
run_test 166 "> 'temp/outfile1.txt'" 166 0
run_test 167 "> \"temp/outfile1.txt\"" 166 0
run_test 168 "> '\"temp/outfile1.txt\"'" 168 0
run_test 169 "> \"'temp/outfile1.txt'\"" 169 0
run_test 170 "> '\"'temp/outfile1.txt'\"'" 170 0
run_test 171 "> \"'\"temp/outfile1.txt\"'\"" 171 0
#run_test_heredoc 172 "<< 'limiter'" 172 0
#run_test_heredoc 173 "<< \"limiter\"" 172 0
#run_test_heredoc 174 "<< '\"limiter\"'" 174 0
#run_test_heredoc 175 "<< \"'limiter'\"" 175 0
#run_test_heredoc 176 "<< '\"'limiter'\"'" 176 0
#run_test_heredoc 177 "<< \"'\"limiter\"'\"" 177 0
#run_test_heredoc 178 "<< '<limiter'" 178 0
#run_test_heredoc 179 "<< \"<limiter\"" 179 0

run_test 190 ">> 'temp/outfile1.txt'" 190 0
run_test 191 ">> \"temp/outfile1.txt\"" 190 0
run_test 192 ">> '\"temp/outfile1.txt\"'" 192 0
run_test 193 ">> \"'temp/outfile1.txt'\"" 193 0
run_test 194 ">> '\"'temp/outfile1.txt'\"'" 194 0
run_test 195 ">> \"'\"temp/outfile1.txt\"'\"" 195 0

if (( "$start_index" >= 160 && "$start_index" <= 195 && "$end_index" >= 160 && "$end_index" <= 195 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 160 to 195\n"
	else
		echo -e "end of test serie from 160 to 195"
	fi
fi


run_test 200 "\"< temp/infile1.txt\"" 200 0
#run_test 210 "\"<< limiter\"" 210 0
run_test 220 "\"> temp/output1.txt\"" 220 0
run_test 230 "\">> temp/output1.txt\"" 230 0

if (( "$start_index" >= 200 && "$start_index" <= 250 && "$end_index" >= 200 && "$end_index" <= 250 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 200 to 250\n"
	else
		echo -e "end of test serie from 200 to 250"
	fi
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

if (( "$start_index" >= 500 && "$start_index" <= 632 && "$end_index" >= 500 && "$end_index" <= 632 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 500 to 632\n"
	else
		echo -e "end of test serie from 500 to 632"
	fi
fi

run_test 650 "'ls -l'" 650 127 "command not found"
run_test 651 "\"ls -l\"" 651 127 "command not found"
run_test 652 "'\"ls -l\"'" 652 127 "command not found"
run_test 653 "\"'ls -l'\"" 653 127 "command not found"
run_test 654 "'ls'-l" 654 127 "command not found"
run_test 655 "ls'-l'" 655 127 "command not found"
run_test 656 "\"ls\"-l" 656 127 "command not found"
run_test 657 "ls\"-l\"" 657 127 "command not found"

if (( "$start_index" >= 650 && "$start_index" <= 657 && "$end_index" >= 650 && "$end_index" <= 657 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 650 to 657\n"
	else
		echo -e "end of test serie from 650 to 657"
	fi
fi

run_test 700 "'ls -l cat -e'" 700 127 "command not found"
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

if (( "$start_index" >= 700 && "$start_index" <= 735 && "$end_index" >= 700 && "$end_index" <= 735 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 700 to 735\n"
	else
		echo -e "end of test serie from 700 to 735"
	fi
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

if (( "$start_index" >= 735 && "$start_index" <= 759 && "$end_index" >= 735 && "$end_index" <= 759 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 735 to 759\n"
	else
		echo -e "end of test serie from 735 to 759"
	fi
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

if (( "$start_index" >= 760 && "$start_index" <= 776 && "$end_index" >= 760 && "$end_index" <= 776 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 760 to 776\n"
	else
		echo -e "end of test serie from 760 to 776"
	fi
fi

run_test 1000 "'ls'-l'cat -e'" 1000 0
run_test 1001 "'ls'-l'cat  -e'" 1001 0

if (( "$start_index" >= 1000 && "$start_index" <= 1001 && "$end_index" >= 1000 && "$end_index" <= 1001 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 1000 to 1001\n"
	else
		echo -e "end of test serie from 1000 to 1001"
	fi
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
run_test 1500 "\$TEST" 1500 0
run_test 1501 "\$DO_NOT_EXIST" 1501 0
run_test 1502 "'\$TEST'" 1502 0
run_test 1503 "\"\$TEST\"" 1503 127 "test_minishell	: command not found"
run_test 1504 "'\"\$TEST\"'" 1504 127
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
run_test 1515 "\"	\$TEST\"" 1515 0
run_test 1516 "\"\t\t\$TEST\"" 1516 0
run_test 1517 "\"\$TEST	\"" 1517 127 "test_minishell	: command not found"
run_test 1518 "\"\$TEST		\"" 1518 127 "test_minishell		: command not found"
run_test 1519 "\"	\$TEST	\"" 1519 127 "	test_minishell	: command not found"
run_test 1520 "\"		\$TEST		\"" 1520 127 "		test_minishell		: command not found"
run_test 1521 "\" \$TEST	\"" 1521 127 " test_minishell	: command not found"
run_test 1522 "\"	\$TEST \"" 1522 127 "	test_minishell : command not found"

run_test 1523 "\$\"TEST\"" 1523 127 "TEST: command not found"
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
run_test 1537 "\"\t\$TEST\t\$TEST\"" 1537 0
run_test 1538 "\"\t\$TEST\t\$TEST\t\"" 1538 0
run_test 1539 "\"\t\t\$TEST\t\t\$TEST\t\t\"" 1539 0
run_test 1540 "\$TEST\$TEST" 1540 0
run_test 1541 "\" \$TEST\$TEST\"" 1541 0
run_test 1542 "\"\$TEST\$TEST \"" 1542 0
run_test 1543 "\" \$TEST\$TEST \"" 1543 0
run_test 1544 "\"	\$TEST\$TEST\"" 1544 0
run_test 1545 "\"\$TEST\$TEST	\"" 1545 0
run_test 1546 "\"	\$TEST\$TEST	\"" 1546 0

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
run_test 1561 "\"\$TEST cat	\"" 1561 0

run_test 1562 "\$" 1562 0
run_test 1563 "\"\$ TEST\"" 1563 0
run_test 1564 "\$\"\"" 1564 127 ": command not found"
run_test 1565 "\$''" 1565 127 ": command not found"
run_test 1566 "\"\$\"\"\"" 1566 0
run_test 1567 "\"\$''\"" 1567 0
run_test 1568 "\"\$\" \"\"" 1568 0
run_test 1569 "\"\$' '\"" 1569 0
run_test 1570 "'\$'''" 1570 0
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

echo ""
echo "\$TEST1 = \"test1\""
echo "\$TEST2 = \"test2\""
echo "\$TEST3 = 'salut     les     amis'"
echo "\$TEST4 = 'echo    \"     salut'"
echo "\$TEST5 = 'echo    \"     salut     les     amis'"
echo ""

run_test 1600 "echo \$TEST1\$TEST2" 1600 0
run_test 1601 "echo \$TEST1\"\"\$TEST2" 1601 0
run_test 1602 "echo \$TEST1"text"\$TEST2" 1602 0
run_test 1603 "echo \$TEST1"text"\$TEST2$" 1603 0
run_test 1604 "echo \$\"\"\$TEST1"text"\$TEST2$" 1604 0
run_test 1605 "echo \$DO_NOT_EXIST\$TEST1"text"\$TEST2$" 1605 0
run_test 1606 "echo    \$TEST1   \$TEST2   " 1610 0

run_test 1610 "echo \$TEST3" 1610 0
run_test 1611 "echo \$TEST3'text'" 1611 0
run_test 1612 "echo '\$TEST3'" 1612 0
run_test 1613 "echo '\$TEST3''text'" 1613 0
run_test 1614 "echo \"\$TEST3\"" 1614 0
run_test 1615 "echo \"\$TEST3\"'text'" 1615 0
run_test 1616 "$TEST4" 1616 0
run_test 1617 "$TEST4" 1617 0

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

echo ""
echo "\$INFILE = \"temp/infile.txt\""
echo ""

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
run_test 1713 "< \"	\$INFILE\"" 1713 0
run_test 1714 "< \"\$INFILE	\"" 1714 0
run_test 1715 "< \"		\$INFILE\"" 1715 0
run_test 1716 "< \"\$INFILE		\"" 1716 0
run_test 1717 "< \"	\$INFILE	\"" 1717 0
run_test 1718 "< \"		\$INFILE		\"" 1718 0
run_test 1719 "< \"INFILE \$INFILE\"" 1719 0
unset INFILE

export OUTFILE="temp/outfile1.txt"

echo ""
echo "\$OUTFILE = \"temp/outfile.txt\""
echo ""

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
run_test 1753 "> \"	\$OUTFILE\"" 1753 0
run_test 1754 "> \"\$OUTFILE	\"" 1754 0
run_test 1755 "> \"		\$OUTFILE\"" 1755 0
run_test 1756 "> \"\$OUTFILE		\"" 1756 0
run_test 1757 "> \"	\$OUTFILE	\"" 1757 0
run_test 1758 "> \"		\$OUTFILE		\"" 1758 0
run_test 1759 "> \"OUTFILE \$OUTFILE\"" 1759 0
unset OUTFILE

: <<BLOCK_COMMENT

export LIMITER="limiter"

echo ""
echo "\$LIMITER = \"limiter\""
echo ""

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
run_test 1793 "<< \"	\$LIMITER\"" 1793 0
run_test 1794 "<< \"\$LIMITER	\"" 1794 0
run_test 1795 "<< \"		\$LIMITER\"" 1795 0
run_test 1796 "<< \"\$LIMITER		\"" 1796 0
run_test 1797 "<< \"	\$LIMITER	\"" 1797 0
run_test 1798 "<< \"		\$LIMITER		\"" 1798 0
run_test 1799 "<< \"LIMITER \$LIMITER\"" 1799 0

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

echo ""
echo "\$OUTFILE = \"temp/outfile.txt\""
echo ""

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
run_test 1833 ">> \"	\$OUTFILE\"" 1833 0
run_test 1834 ">> \"\$OUTFILE	\"" 1834 0
run_test 1835 ">> \"		\$OUTFILE\"" 1835 0
run_test 1836 ">> \"\$OUTFILE		\"" 1836 0
run_test 1837 ">> \"	\$OUTFILE	\"" 1837 0
run_test 1838 ">> \"		\$OUTFILE		\"" 1838 0
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

run_test 2000 "<" 2000 2 "syntax error"
run_test 2001 "<<" 2001 2 "syntax error"
run_test 2002 "<<<" 2002 2 "syntax error"
run_test 2003 "<<<<" 2003 2 "syntax error"
run_test 2004 "<" 2004 2 "syntax error"
run_test 2005 "<<" 2005 2 "syntax error"
run_test 2006 "<<<" 2006 2 "syntax error"
run_test 2007 "<<<<" 2007 2 "syntax error"
run_test 2008 "<>" 2008 2 "syntax error"
run_test 2009 "><" 2009 2 "syntax error"
run_test 2010 "<><>" 2010 2 "syntax error"
run_test 2011 "><><" 2011 2 "syntax error"
run_test 2012 "<<>" 2012 2 "syntax error"
run_test 2013 "<<>>" 2013 2 "syntax error"
run_test 2014 "<<<>>>" 2014 2 "syntax error"
run_test 2015 "<<<<>>>>" 2015 2 "syntax error"
run_test 2016 ">><" 2016 2 "syntax error"
run_test 2017 ">><<" 2017 2 "syntax error"
run_test 2018 ">>><<<" 2018 2 "syntax error"
run_test 2019 ">>>><<<<" 2019 2 "syntax error"

run_test 2020 "ls <" 2020 2 "syntax error"
run_test 2021 "ls <<" 2021 2 "syntax error"
run_test 2022 "ls >" 2022 2 "syntax error"
run_test 2023 "ls >>" 2023 2 "syntax error"
run_test 2024 "ls<" 2024 2 "syntax error"
run_test 2025 "ls<<" 2025 2 "syntax error"
run_test 2026 "ls>" 2026 2 "syntax error"
run_test 2027 "ls>>" 2027 2 "syntax error"

run_test 2030 "|" 2030 2 "syntax error"
run_test 2031 " |" 2031 2 "syntax error"
run_test 2032 "  |" 2032 2 "syntax error"
run_test 2033 "| " 2033 2 "syntax error"
run_test 2034 "|  " 2034 2 "syntax error"
run_test 2035 " | " 2035 2 "syntax error"
run_test 2036 "  | " 2036 2 "syntax error"
run_test 2037 "  |  " 2037 2 "syntax error"
run_test 2038 "	|" 2038 2 "syntax error"
run_test 2039 "		|" 2039 2 "syntax error"
run_test 2040 "|	" 2040 2 "syntax error"
run_test 2041 "|		" 2041 2 "syntax error"
run_test 2042 "	|	" 2042 2 "syntax error"
run_test 2043 "		|		" 2043 2 "syntax error"

run_test 2050 "| ls" 2050 2 "syntax error"
run_test 2051 "|ls" 2051 2 "syntax error"
run_test 2052 " |ls" 2052 2 "syntax error"
run_test 2053 "ls |" 2053 2 "syntax error"
run_test 2054 "ls|" 2054 2 "syntax error"
run_test 2055 "ls| " 2055 2 "syntax error"

run_test 2060 "||" 2060 2 "syntax error"
run_test 2061 "| |" 2061 2 "syntax error"
run_test 2062 "|	|" 2062 2 "syntax error"
run_test 2063 "|||" 2063 2 "syntax error"
run_test 2064 "| | |" 2064 2 "syntax error"
run_test 2065 "|	|	|" 2065 2 "syntax error"
run_test 2066 "||||" 2066 2 "syntax error"
run_test 2067 "| | | |" 2067 2 "syntax error"
run_test 2068 "|	|	|	|" 2068 2 "syntax error"

run_test 2070 ">|" 2070 2 "syntax error"
run_test 2071 "<|" 2071 2 "syntax error"
run_test 2072 "|>" 2072 2 "syntax error"
run_test 2073 "|<" 2073 2 "syntax error"
run_test 2074 ">>|" 2074 2 "syntax error"
run_test 2075 "<<|" 2075 2 "syntax error"
run_test 2076 "|>>" 2076 2 "syntax error"
run_test 2077 "|<<" 2077 2 "syntax error"

run_test 2090 ">|>" 2090 2 "syntax error"
run_test 2091 "<|<" 2091 2 "syntax error"
run_test 2092 "<|>" 2092 2 "syntax error"
run_test 2093 ">|<" 2093 2 "syntax error"
run_test 2094 ">>|<<" 2094 2 "syntax error"
run_test 2095 "<<|>>" 2095 2 "syntax error"
run_test 2096 "<<|>>" 2096 2 "syntax error"
run_test 2097 ">>|<<" 2097 2 "syntax error"

run_test 2100 "|| ls" 2100 2 "syntax error"
run_test 2101 "||ls" 2101 2 "syntax error"
run_test 2102 "ls ||" 2102 2 "syntax error"
run_test 2103 "ls||" 2103 2 "syntax error"
run_test 2104 "||| ls" 2104 2 "syntax error"
run_test 2105 "|||ls" 2105 2 "syntax error"
run_test 2106 "ls |||" 2106 2 "syntax error"
run_test 2107 "ls|||" 2107 2 "syntax error"

#run_test 2110 "ls || cat" 2110 2 "syntax error"//invalid test because bash has a special behaviour
run_test 2111 "ls | | cat" 2111 2 "syntax error"
run_test 2112 "ls | cat |" 2112 2 "syntax error"
run_test 2113 "ls || cat |" 2113 2 "syntax error"


if (( "$start_index" >= 2000 && "$start_index" <= 2150 && "$end_index" >= 2000 && "$end_index" <= 2150 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 2000 to 2150\n"
	else
		echo -e "end of test serie from 2000 to 2150"
	fi
fi


#run_test 3000 "<<< infile.txt" 3000 2 "syntax error"//invalid test because bash has a special behaviour
run_test 3001 "<<<< infile.txt" 3001 2 "syntax error"
run_test 3002 "<<<<< infile.txt" 3002 2 "syntax error"
run_test 3003 "<<> infile.txt" 3003 2 "syntax error"
run_test 3004 "<<>> infile.txt" 3004 2 "syntax error"
run_test 3005 "<<>>> infile.txt" 3005 2 "syntax error"
run_test 3006 "<<>>>> infile.txt" 3006 2 "syntax error"
run_test 3007 "<<>< infile.txt" 3007 2 "syntax error"
run_test 3008 "<<><< infile.txt" 3008 2 "syntax error"
run_test 3009 "<<><<< infile.txt" 3009 2 "syntax error"
run_test 3010 "<<><<<< infile.txt" 3010 2 "syntax error"
run_test 3011 "<<><> infile.txt" 3011 2 "syntax error"
run_test 3012 "<<><>> infile.txt" 3012 2 "syntax error"
run_test 3013 "<<><>>> infile.txt" 3013 2 "syntax error"
run_test 3014 "<<><>>>> infile.txt" 3014 2 "syntax error"
#run_test 3015 "<> infile.txt" 3015 2 "syntax error"//invalid test because bash has a special behaviour
run_test 3016 "<>> infile.txt" 3016 2 "syntax error"
run_test 3017 "<>>> infile.txt" 3017 2 "syntax error"
run_test 3018 "<>>>> infile.txt" 3018 2 "syntax error"
run_test 3019 "<>>>>> infile.txt" 3019 2 "syntax error"
run_test 3020 "<>< infile.txt" 3020 2 "syntax error"
run_test 3021 "<><< infile.txt" 3021 2 "syntax error"
run_test 3022 "<><<< infile.txt" 3022 2 "syntax error"
run_test 3023 "<><<<< infile.txt" 3023 2 "syntax error"
run_test 3024 "<><> infile.txt" 3024 2 "syntax error"
run_test 3025 "<><>> infile.txt" 3025 2 "syntax error"
run_test 3026 "<><>>> infile.txt" 3026 2 "syntax error"
run_test 3027 "<><>>>> infile.txt" 3027 2 "syntax error"
run_test 3028 "<><>>>>> infile.txt" 3028 2 "syntax error"
run_test 3029 ">>> outfile.txt" 3029 2 "syntax error"
run_test 3030 ">>>> outfile.txt" 3030 2 "syntax error"
run_test 3031 ">>>>> outfile.txt" 3031 2 "syntax error"
run_test 3032 ">>>>>> outfile.txt" 3032 2 "syntax error"
run_test 3033 ">>< outfile.txt" 3033 2 "syntax error"
run_test 3034 ">><< outfile.txt" 3034 2 "syntax error"
run_test 3035 ">><<< outfile.txt" 3035 2 "syntax error"
run_test 3036 ">><<<< outfile.txt" 3036 2 "syntax error"
run_test 3037 ">><<<<< outfile.txt" 3037 2 "syntax error"
run_test 3038 ">><> outfile.txt" 3038 2 "syntax error"
run_test 3039 ">><>> outfile.txt" 3039 2 "syntax error"
run_test 3040 ">><>>> outfile.txt" 3040 2 "syntax error"
run_test 3041 ">><>>>> outfile.txt" 3041 2 "syntax error"
run_test 3042 ">><>>>>> outfile.txt" 3042 2 "syntax error"

if (( "$start_index" >= 3000 && "$start_index" <= 3050 && "$end_index" >= 3000 && "$end_index" <= 3050 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 3000 to 3050\n"
	else
		echo -e "end of test serie from 3000 to 3050"
	fi
fi

run_test 3300 "< 'infile.txt" 3300 2  "syntax error"
run_test 3301 "< infile.txt'" 3301 2 "syntax error"
run_test 3302 "< \"infile.txt" 3302 2 "syntax error"
run_test 3303 "< infile.txt\"" 3303 2 "syntax error"
run_test 3304 "< 'infile.txt\"" 3304 2 "syntax error"
run_test 3305 "< 'infile.txt'\"" 3305 2 "syntax error"
#run_test 3306 "< \"infile.txt'\"" 3306 2 "syntax error"
run_test 3307 "< \"infile.txt\"'" 3307 2 "syntax error"
run_test 3308 "<< 'infile.txt" 3308 2 "syntax error"
run_test 3309 "<< infile.txt'" 3309 2 "syntax error"
run_test 3310 "<< \"infile.txt" 3310 2 "syntax error"
run_test 3311 "<< infile.txt\"" 3311 2 "syntax error"
run_test 3312 "<< 'infile.txt\"" 3312 2 "syntax error"
run_test 3313 "<< 'infile.txt'\"" 3313 2 "syntax error"
#run_test 3314 "<< \"infile.txt'\"" 3314 2 "syntax error"
run_test 3315 "<< \"infile.txt\"'" 3315 2 "syntax error"

run_test 3400 "> 'outfile.txt" 3400 2 "syntax error"
run_test 3401 "> outfile.txt'" 3401 2 "syntax error"
run_test 3402 "> \"outfile.txt" 3402 2 "syntax error"
run_test 3403 "> outfile.txt\"" 3403 2 "syntax error"
run_test 3404 "> 'outfile.txt\"" 3404 2 "syntax error"
run_test 3405 "> 'outfile.txt'\"" 3405 2 "syntax error"
#run_test 3406 "> \"outfile.txt'\"" 3406 2 "syntax error"
run_test 3407 "> \"outfile.txt\"'" 3407 2 "syntax error"
run_test 3408 ">> 'outfile.txt" 3408 2 "syntax error"
run_test 3409 ">> outfile.txt'" 3409 2 "syntax error"
run_test 3410 ">> \"outfile.txt" 3410 2 "syntax error"
run_test 3411 ">> outfile.txt\"" 3411 2 "syntax error"
run_test 3412 ">> 'outfile.txt\"" 3412 2 "syntax error"
run_test 3413 ">> 'outfile.txt'\"" 3413 2 "syntax error"
#run_test 3414 ">> \"outfile.txt'\"" 3414 2 "syntax error"
run_test 3415 ">> \"outfile.txt\"'" 3415 2 "syntax error"

if (( "$start_index" >= 3300 && "$start_index" <= 3415 && "$end_index" >= 3300 && "$end_index" <= 3415 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 3300 to 3415\n"
	else
		echo -e "end of test serie from 3300 to 3415"
	fi
fi

run_test 4000 "'ls" 4000 2 "syntax error"
run_test 4001 "ls'" 4001 2 "syntax error"
run_test 4002 "\"ls" 4002 2 "syntax error"
run_test 4003 "ls\"" 4003 2 "syntax error"
run_test 4004 "'ls\"" 4004 2 "syntax error"
run_test 4005 "'ls'\"" 4005 2 "syntax error"
run_test 4006 "\"ls'" 4006 2 "syntax error"
run_test 4007 "\"ls\"'" 4007 2 "syntax error"
#run_test 4008 "''ls" 4008 2 "syntax error"
run_test 4009 "''ls'" 4009 2 "syntax error"
run_test 4010 "'''ls" 4010 2 "syntax error"
#run_test 4011 "'''ls'" 4011 2 "syntax error"
run_test 4012 "'''ls''" 4012 2 "syntax error"
#run_test 4013 "\"\"ls" 4013 2 "syntax error"
run_test 4014 "\"\"ls\"" 4014 2 "syntax error"
run_test 4015 "\"\"\"ls" 4015 2 "syntax error"
#run_test 4016 "\"\"\"ls\"" 4016 2 "syntax error"
run_test 4017 "\"\"\"ls\"\"" 4017 2 "syntax error"
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



run_test 4100 "cat 'ls" 4100 2 "syntax error"
run_test 4101 "cat ls'" 4101 2 "syntax error"
run_test 4102 "cat \"ls" 4102 2 "syntax error"
run_test 4103 "cat ls\"" 4103 2 "syntax error"
run_test 4104 "'cat' 'ls" 4104 2 "syntax error"
run_test 4105 "'cat' ls'" 4105 2 "syntax error"
run_test 4106 "'cat' ls'" 4106 2 "syntax error"
run_test 4107 "'cat' \"ls" 4107 2 "syntax error"
run_test 4108 "'cat' ls\"" 4108 2 "syntax error"
run_test 4109 ""cat" 'ls" 4109 2 "syntax error"
run_test 4110 ""cat" ls'" 4110 2 "syntax error"
run_test 4111 ""cat" ls'" 4111 2 "syntax error"
run_test 4112 ""cat" \"ls" 4112 2 "syntax error"
run_test 4113 ""cat" ls\"" 4113 2 "syntax error"
run_test 4114 "cat 'ls " 4114 2 "syntax error"
run_test 4115 "cat ls' " 4115 2 "syntax error"
run_test 4116 "cat \"ls " 4116 2 "syntax error"
run_test 4117 "cat ls\" " 4117 2 "syntax error"
run_test 4118 "cat 'ls  " 4118 2 "syntax error"
run_test 4119 "cat ls'  " 4119 2 "syntax error"
run_test 4120 "cat \"ls  " 4120 2 "syntax error"
run_test 4121 "cat ls\"  " 4121 2 "syntax error"
run_test 4122 "cat ' ls" 4122 2 "syntax error"
run_test 4123 "cat  ls'" 4123 2 "syntax error"
run_test 4124 "cat \" ls" 4124 2 "syntax error"
run_test 4125 "cat ls \"" 4125 2 "syntax error"

if (( "$start_index" >= 4100 && "$start_index" <= 4125 && "$end_index" >= 4100 && "$end_index" <= 4125 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 4100 to 4125\n"
	else
		echo -e "end of test serie from 4100 to 4125"
	fi
fi

run_test 4300 "'" 4300 2 #exit_status to confirm
run_test 4301 "\"" 4301 2 #exit_status to confirm
run_test 4302 "\"\"\"" 4302 2 #exit_status to confirm

if (( "$start_index" >= 4300 && "$start_index" <= 4350 && "$end_index" >= 4300 && "$end_index" <= 4350 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 4300 to 4350\n"
	else
		echo -e "end of test serie from 4300 to 4350"
	fi
fi


run_test 4400 "'ls -l cat -e'" 4400 127
run_test 4401 "\"ls -l cat -e\"" 4401 127
run_test 4402 "'\"ls -l cat -e\"'" 4402 127
run_test 4403 "\"'ls -l cat -e'\"" 4403 127

run_test 4404 "'ls'-l cat -e" 4404 127
run_test 4405 "ls'-l' cat -e" 4405 127
run_test 4406 "\"ls\"-l cat -e" 4406 127
run_test 4407 "ls\"-l\" cat -e" 4407 127

run_test 4408 "'ls -l' cat -e" 4408 127
run_test 4409 "\"ls -l\" cat -e" 4409 127
run_test 4410 "'\"ls -l\"' cat -e" 4410 127
run_test 4411 "\"'ls -l'\" cat -e" 4411 127

run_test 4412 "'ls -l'cat -e" 4412 127
run_test 4413 "\"ls -l\"cat -e" 4413 127
run_test 4414 "'\"ls -l\"'cat -e" 4414 127
run_test 4415 "\"'ls -l'\"cat -e" 4415 127

run_test 4416 "'ls -l' 'cat' -e" 4416 127
run_test 4417 "\"ls -l\" 'cat' -e" 4417 127
run_test 4418 "'\"ls -l\"' 'cat' -e" 4418 127
run_test 4419 "\"'ls -l'\" 'cat' -e" 4419 127


run_test 4420 "'ls -l' cat '-e'" 4420 127
run_test 4421 "\"ls -l\" cat '-e'" 4421 127
run_test 4422 "'\"ls -l\"' cat '-e'" 4422 127
run_test 4423 "\"'ls -l'\" cat '-e'" 4423 127
run_test 4424 "'ls -l' 'cat' '-e'" 4424 127
run_test 4425 "\"ls -l\" 'cat' '-e'" 4425 127
run_test 4426 "'\"ls -l\"' 'cat' '-e'" 4426 127
run_test 4427 "\"'ls -l'\" 'cat' '-e'" 4427 127
run_test 4428 "'ls -l' \"cat\" '-e'" 4428 127
run_test 4429 "\"ls -l\" \"cat\" '-e'" 4429 127
run_test 4430 "'\"ls -l\"' \"cat\" '-e'" 4430 127
run_test 4431 "\"'ls -l'\" \"cat\" '-e'" 4431 127
run_test 4432 "'ls -l' \"cat\" \"-e\"" 4432 127
run_test 4433 "\"ls -l\" \"cat\" \"-e\"" 4433 127
run_test 4434 "'\"ls -l\"' \"cat\" \"-e\"" 4434 127
run_test 4435 "\"'ls -l'\" \"cat\" \"-e\"" 4435 127

run_test 4436 "'ls -l'cat '-e'" 4436 127
run_test 4437 "\"ls -l\"cat '-e'" 4437 127
run_test 4438 "'\"ls -l\"'cat '-e'" 4438 127
run_test 4439 "\"'ls -l'\"cat '-e'" 4439 127
run_test 4440 "'ls -l'cat \"-e\"" 4470 127
run_test 4441 "\"ls -l\"cat \"-e\"" 4441 127
run_test 4442 "'\"ls -l\"'cat \"-e\"" 4472 127
run_test 4443 "\"'ls -l'\"cat \"-e\"" 4443 127
run_test 4444 "'ls -l''cat' '-e'" 4444 127
run_test 4445 "\"ls -l\"'cat' '-e'" 4445 127
run_test 4446 "'\"ls -l\"''cat' '-e'" 4446 127
run_test 4447 "\"'ls -l'\"'cat' '-e'" 4447 127
run_test 4448 "'ls -l''cat' \"-e\"" 4448 127
run_test 4449 "\"ls -l\"'cat' \"-e\"" 4449 127
run_test 4450 "'\"ls -l\"''cat' \"-e\"" 4450 127
run_test 4451 "\"'ls -l'\"'cat' \"-e\"" 4451 127
run_test 4452 "'ls -l'\"cat\" '-e'" 4452 127
run_test 4453 "\"ls -l\"\"cat\" '-e'" 4453 127
run_test 4454 "'\"ls -l\"'\"cat\" '-e'" 4454 127
run_test 4455 "\"'ls -l'\"\"cat\" '-e'" 4455 127
run_test 4456 "'ls -l'\"cat\" \"-e\"" 4456 127
run_test 4457 "\"ls -l\"\"cat\" \"-e\"" 4457 127
run_test 4458 "'\"ls -l\"'\"cat\" \"-e\"" 4458 127
run_test 4459 "\"'ls -l'\"\"cat\" \"-e\"" 4459 127

run_test 4460 "'ls -l' cat'-e'" 4460 127
run_test 4461 "\"ls -l\" cat'-e'" 4461 127
run_test 4462 "'\"ls -l\"' cat'-e'" 4462 127
run_test 4463 "\"'ls -l'\" cat'-e'" 4463 127
run_test 4464 "'ls -l' 'cat''-e'" 4464 127
run_test 4465 "\"ls -l\" 'cat''-e'" 4465 127
run_test 4466 "'\"ls -l\"' 'cat''-e'" 4466 127
run_test 4467 "\"'ls -l'\" 'cat''-e'" 4467 127
run_test 4468 "'ls -l' \"cat\"'-e'" 4468 127
run_test 4469 "\"ls -l\" \"cat\"'-e'" 4469 127
run_test 4470 "'\"ls -l\"' \"cat\"'-e'" 4470 127
run_test 4471 "\"'ls -l'\" \"cat\"'-e'" 4471 127
run_test 4472 "'ls -l' \"cat\"\"-e\"" 4472 127
run_test 4473 "\"ls -l\" \"cat\"\"-e\"" 4473 127
run_test 4474 "'\"ls -l\"' \"cat\"\"-e\"" 4474 127
run_test 4475 "\"'ls -l'\" \"cat\"\"-e\"" 4475 127

if (( "$start_index" >= 4400 && "$start_index" <= 4475 && "$end_index" >= 4400 && "$end_index" <= 4475 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 4400 to 4475\n"
	else
		echo -e "end of test serie from 4400 to 4475"
	fi
fi

run_test 5000 "< temp/infile1.txt cat" 5000 0
run_test 5001 "cat < temp/infile1.txt" 5000 0
run_test 5002 "< temp/infile1.txt cat -e" 5002 0
run_test 5003 "cat -e < temp/infile1.txt" 5002 0
run_test 5004 "cat temp/infile1.txt" 5004 0

run_test 5010 "< temp/infile1.txt wc" 5010 0
run_test 5011 "wc < temp/infile1.txt" 5010 0
run_test 5012 "< temp/infile1.txt wc -l" 5012 0
run_test 5013 "wc -l < temp/infile1.txt" 5012 0
run_test 5014 "wc -l temp/infile1.txt" 5014 0

run_test 5020 "ls > temp/outfile1.txt" 5020 0
run_test 5021 "> temp/outfile1.txt ls" 5020 0

run_test 5030 "< temp/infile1.txt cat > temp/outfile1.txt" 5030 0
run_test 5031 "< temp/infile1.txt > temp/outfile1.txt cat" 5030 0
run_test 5032 "> temp/outfile1.txt < temp/infile1.txt cat" 5030 0

run_test 5035 "< temp/infile1.txt wc -l > temp/outfile1.txt" 5035 0
run_test 5036 "< temp/infile1.txt > temp/outfile1.txt wc -l" 5035 0
run_test 5037 "> temp/outfile1.txt < temp/infile1.txt wc -l" 5035 0

run_test 5040 "< temp/infile1.txt ls > temp/outfile1.txt" 5040 0
run_test 5041 "< temp/infile1.txt > temp/outfile1.txt ls" 5040 0
run_test 5042 "> temp/outfile1.txt < temp/infile1.txt ls" 5040 0

run_test 5045 "< temp/infile1.txt < temp/infile2.txt cat" 5045 0
run_test 5046 "< temp/infile1.txt cat < temp/infile2.txt" 5045 0
run_test 5047 "cat < temp/infile1.txt < temp/infile2.txt" 5045 0

run_test 5050 "< temp/infile1.txt < temp/infile2.txt wc -l" 5050 0
run_test 5051 "< temp/infile1.txt wc -l < temp/infile2.txt" 5050 0
run_test 5052 "wc -l < temp/infile1.txt < temp/infile2.txt" 5050 0

run_test 5055 "< temp/infile1.txt < temp/infile2.txt ls" 5055 0
run_test 5056 "< temp/infile1.txt ls < temp/infile2.txt" 5055 0
run_test 5057 "ls < temp/infile1.txt < temp/infile2.txt" 5055 0

#run_test 5060 "> temp/outfile1.txt > temp/outfile2.txt cat" 5060 0
#run_test 5061 "> temp/outfile1.txt cat > temp/outfile2.txt" 5060 0
#run_test 5062 "cat > temp/outfile1.txt > temp/outfile2.txt" 5060 0

#run_test 5065 "> temp/outfile1.txt > temp/outfile2.txt wc -l" 5065 0
#run_test 5066 "> temp/outfile1.txt wc -l > temp/outfile2.txt" 5065 0
#run_test 5067 "wc -l > temp/outfile1.txt > temp/outfile2.txt" 5065 0

run_test 5070 "> temp/outfile1.txt > temp/outfile2.txt ls" 5070 0
run_test 5071 "> temp/outfile1.txt ls > temp/outfile2.txt" 5070 0
run_test 5072 "ls > temp/outfile1.txt > temp/outfile2.txt" 5070 0

run_test 5080 "cat < temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt" 5080 0
run_test 5081 "< temp/infile1.txt cat < temp/infile2.txt > temp/outfile1.txt" 5080 0
run_test 5082 "< temp/infile1.txt < temp/infile2.txt cat > temp/outfile1.txt" 5080 0
run_test 5083 "< temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt cat" 5080 0
run_test 5084 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt cat" 5080 0
run_test 5085 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt cat" 5080 0

run_test 5090 "wc -l < temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt" 5090 0
run_test 5091 "< temp/infile1.txt wc -l < temp/infile2.txt > temp/outfile1.txt" 5090 0
run_test 5092 "< temp/infile1.txt < temp/infile2.txt wc -l > temp/outfile1.txt" 5090 0
run_test 5093 "< temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt wc -l" 5090 0
run_test 5094 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt wc -l" 5090 0
run_test 5095 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt wc -l" 5090 0

run_test 5100 "ls < temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt" 5100 0
run_test 5101 "< temp/infile1.txt ls < temp/infile2.txt > temp/outfile1.txt" 5100 0
run_test 5102 "< temp/infile1.txt < temp/infile2.txt ls > temp/outfile1.txt" 5100 0
run_test 5103 "< temp/infile1.txt < temp/infile2.txt > temp/outfile1.txt ls" 5100 0
run_test 5104 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt ls" 5100 0
run_test 5105 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt ls" 5100 0

run_test 5110 "cat < temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt" 5110 0
run_test 5111 "< temp/infile1.txt cat > temp/outfile1.txt > temp/outfile2.txt" 5110 0
run_test 5112 "< temp/infile1.txt > temp/outfile1.txt cat > temp/outfile2.txt" 5110 0
run_test 5113 "< temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt cat" 5110 0
run_test 5114 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt cat" 5110 0
run_test 5115 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt cat" 5110 0

run_test 5120 "wc -l < temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt" 5120 0
run_test 5121 "< temp/infile1.txt wc -l > temp/outfile1.txt > temp/outfile2.txt" 5120 0
run_test 5122 "< temp/infile1.txt > temp/outfile1.txt wc -l > temp/outfile2.txt" 5120 0
run_test 5123 "< temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt wc -l" 5120 0
run_test 5124 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt wc -l" 5120 0
run_test 5125 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt wc -l" 5120 0

run_test 5130 "ls < temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt" 5130 0
run_test 5131 "< temp/infile1.txt ls > temp/outfile1.txt > temp/outfile2.txt" 5130 0
run_test 5132 "< temp/infile1.txt > temp/outfile1.txt ls > temp/outfile2.txt" 5130 0
run_test 5133 "< temp/infile1.txt > temp/outfile1.txt > temp/outfile2.txt ls" 5130 0
run_test 5134 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt ls" 5130 0
run_test 5135 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt ls" 5130 0

run_test 5150 "< temp/infile1.txt < temp/infile2.txt cat > temp/outfile1.txt > temp/outfile2.txt" 5150 0
run_test 5151 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt > temp/outfile2.txt cat" 5150 0
run_test 5152 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt > temp/outfile2.txt cat" 5150 0
run_test 5153 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt < temp/infile2.txt cat" 5150 0
run_test 5154 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt < temp/infile2.txt cat" 5150 0

run_test 5155 "< temp/infile1.txt < temp/infile2.txt wc -l > temp/outfile1.txt > temp/outfile2.txt" 5155 0
run_test 5156 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt > temp/outfile2.txt wc -l" 5155 0
run_test 5157 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt > temp/outfile2.txt wc -l" 5155 0
run_test 5158 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt < temp/infile2.txt wc -l" 5155 0
run_test 5159 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt < temp/infile2.txt wc -l" 5155 0

run_test 5165 "< temp/infile1.txt < temp/infile2.txt ls > temp/outfile1.txt > temp/outfile2.txt" 5165 0
run_test 5166 "< temp/infile1.txt > temp/outfile1.txt < temp/infile2.txt > temp/outfile2.txt ls" 5165 0
run_test 5167 "> temp/outfile1.txt < temp/infile1.txt < temp/infile2.txt > temp/outfile2.txt ls" 5165 0
run_test 5168 "> temp/outfile1.txt < temp/infile1.txt > temp/outfile2.txt < temp/infile2.txt ls" 5165 0
run_test 5169 "> temp/outfile1.txt > temp/outfile2.txt < temp/infile1.txt < temp/infile2.txt ls" 5165 0

if (( "$start_index" >= 5000 && "$start_index" <= 5170 && "$end_index" >= 5000 && "$end_index" <= 5170 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 5000 to 5170\n"
	else
		echo -e "end of test serie from 5000 to 5170"
	fi
fi

run_test 5200 "grep un < temp/infile1.txt" 5200 0
run_test 5201 "echo < temp/infile1.txt added_word" 5201 0
run_test 5202 "echo < temp/infile1.txt added_word" 5202 0
run_test 5203 "echo added_word1 < temp/infile1.txt added_word2" 5203 0

if (( "$start_index" >= 5200 && "$start_index" <= 5300 && "$end_index" >= 5200 && "$end_index" <= 5300 ))
then
	if [ "$display" == "all" ]
	then
		echo -e "end of test serie from 5200 to 5300\n"
	else
		echo -e "end of test serie from 5200 to 5300"
	fi
fi


run_test 7000 "temp/infile1.txt cat" 7000 127 "temp/infile1.txt: No such file or directory"
run_test 7001 "temp/infile1.txt wc" 7001 127 "temp/infile1.txt: No such file or directory"
run_test 7002 "Makefile cat" 7002 127 "Makefile: command not found"
run_test 7003 "Makefile wc" 7003 127 "Makefile: command not found"

run_test 7002 "< temp/infile1.txt cat wc" 7002 1 "cat: wc: No such file or directory"

run_test 7100 "< missing_file cat -e" 7100 1 "missing_file: No such file or directory"
run_test 7101 "< missing_file invalid_command" 7101 1 "missing_file: No such file or directory"

run_test 7200 "< missing_file cat > outfile1.txt" 7200 1 "missing_file: No such file or directory"
run_test 7201 "> temp/outfile1.txt < missing_file cat" 7201 1 "missing_file: No such file or directory"

echo > temp/outfile_without_permission
chmod 000 temp/outfile_without_permission
run_test 7300 "> temp/outfile_without_permission < missing_file cat -e" 7300 1 "temp/outfile_without_permission: Permission denied"
run_test 7301 "< missing_file > temp/outfile_without_permission cat -e" 7301 1 "missing_file: No such file or directory"
run_test 7302 "> temp/outfile_without_permission < temp/infile1.txt cat -e" 7302 1 "temp/outfile_without_permission: Permission denied"
run_test 7303 "< temp/infile1.txt > temp/outfile_without_permission cat -e" 7303 1 "temp/outfile_without_permission: Permission denied"
run_test 7304 "> temp/outfile_without_permission < missing_file invalid_command" 7304 1 "temp/outfile_without_permission: Permission denied"
run_test 7305 " invalid_command > temp/outfile_without_permission < missing_file" 7305 1 "temp/outfile_without_permission: Permission denied"

echo > temp/infile_without_permission
chmod 000 temp/infile_without_permission
run_test 7300 "< temp/infile_without_permission > temp/outfile1.txt cat -e" 7300 1 "temp/infile_without_permission: Permission denied"
run_test 7301 "> temp/outfile_without_permission < temp/infile_without_permission cat -e" 7301 1 "temp/outfile_without_permission: Permission denied"
run_test 7302 "< temp/infile_without_permission > temp/outfile_without_permission cat -e" 7302 1 "temp/infile_without_permission: Permission denied"
run_test 7303 "< temp/infile_without_permission > temp/outfile1.txt cat -e" 7303 1 "temp/infile_without_permission: Permission denied"
run_test 7304 "> temp/outfile1.txt < temp/infile_without_permission cat -e" 7304 1 "temp/infile_without_permission: Permission denied"
run_test 7305 "< temp/infile_without_permission > temp/outfile1.txt invalid_command" 7305 1 "temp/infile_without_permission: Permission denied"
run_test 7306 "invalid_command < temp/infile_without_permission > temp/outfile1.txt" 7306 1 "temp/infile_without_permission: Permission denied"

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
