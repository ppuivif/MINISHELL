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
#	if [ $status_output_minishell -eq $status ] &&
	if [ $status_output_minishell -ne 0 ] &&
		grep "$substring" temp/stderr2_minishell$test_index.txt >/dev/null &&
		[ $(wc -c < "temp/minishell_test$test_index.txt") -eq 0 ]
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

run_test 21 "<< infile.txt cat | cat > outfile.txt" 21 0
run_test 22 "<<infile.txt cat | cat > outfile.txt" 21 0
run_test 23 "<< infile.txt cat| cat > outfile.txt" 21 0
run_test 24 "<< infile.txt cat |cat > outfile.txt" 21 0
run_test 25 "<< infile.txt cat | cat> outfile.txt" 21 0
run_test 26 "<< infile.txt cat | cat >outfile.txt" 21 0
run_test 27 "<<infile.txt cat|cat >outfile.txt" 21 0
run_test 28 "<< infile.txt cat | cat > outfile.txt" 21 0
run_test 29 "<<	infile.txt cat | cat > outfile.txt" 21 0
run_test 30 "<<		infile.txt cat | cat > outfile.txt" 21 0
run_test 31 "<< infile.txt cat	| cat > outfile.txt" 21 0
run_test 32 "<< infile.txt cat		| cat > outfile.txt" 21 0
run_test 33 "<< infile.txt cat |	cat > outfile.txt" 21 0
run_test 34 "<< infile.txt cat |		cat > outfile.txt" 21 0
run_test 35 "<< infile.txt cat | cat	> outfile.txt" 21 0
run_test 36 "<< infile.txt cat | cat		> outfile.txt" 21 0
run_test 37 "<< infile.txt cat | cat >	outfile.txt" 21 0
run_test 38 "<< infile.txt cat | cat >		outfile.txt" 21 0
run_test 39 "<< infile.txt cat | cat > outfile.txt	" 21 0
run_test 40 "<< infile.txt cat | cat > outfile.txt		" 21 0

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

run_test 61 "<< infile.txt cat | cat >> outfile.txt" 61 0
run_test 62 "<<infile.txt cat | cat >> outfile.txt" 61 0
run_test 63 "<< infile.txt cat| cat >> outfile.txt" 61 0
run_test 64 "<< infile.txt cat |cat >> outfile.txt" 61 0
run_test 65 "<< infile.txt cat | cat>> outfile.txt" 61 0
run_test 66 "<< infile.txt cat | cat >>outfile.txt" 61 0
run_test 67 "<<infile.txt cat|cat >>outfile.txt" 61 0
run_test 68 "<< infile.txt cat | cat >> outfile.txt" 61 0
run_test 69 "<<	infile.txt cat | cat >> outfile.txt" 61 0
run_test 70 "<<		infile.txt cat | cat >> outfile.txt" 61 0
run_test 71 "<< infile.txt cat	| cat >> outfile.txt" 61 0
run_test 72 "<< infile.txt cat		| cat >> outfile.txt" 61 0
run_test 73 "<< infile.txt cat |	cat >> outfile.txt" 61 0
run_test 74 "<< infile.txt cat |		cat >> outfile.txt" 61 0
run_test 75 "<< infile.txt cat | cat	>> outfile.txt" 61 0
run_test 76 "<< infile.txt cat | cat		>> outfile.txt" 61 0
run_test 77 "<< infile.txt cat | cat >>	outfile.txt" 61 0
run_test 78 "<< infile.txt cat | cat >>		outfile.txt" 61 0
run_test 79 "<< infile.txt cat | cat >> outfile.txt	" 61 0
run_test 80 "<< infile.txt cat | cat >> outfile.txt		" 61 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 1 to 80\n"
else
	echo -e "end of test serie from 1 to 80"
fi

run_test 500 "'ls' -l" 500 0
run_test 501 "'ls' '-l'" 501 0
run_test 502 "\"ls\" -l" 502 0
run_test 503 "\"ls\" \"-l\"" 503 0
run_test 504 "\"ls\" '-l'" 504 0
run_test 505 "'ls' \"-l\"" 505 0

run_test 550 "ls -l | cat -e" 550 0
run_test 551 "ls '-l' | cat -e" 551 0
run_test 552 "ls -l | 'cat' -e" 552 0
run_test 553 "ls -l | cat '-e'" 553 0
run_test 554 "'ls' '-l' | cat -e" 554 0
run_test 555 "'ls' '-l' | 'cat' -e" 555 0
run_test 556 "'ls' '-l' | cat '-e'" 556 0
run_test 557 "'ls' '-l' | 'cat' '-e'" 557 0
run_test 558 "ls -l | 'cat' '-e'" 558 0
run_test 559 "ls -l | cat '-e'" 559 0
run_test 560 "ls '-l' | 'cat' -e" 560 0
run_test 561 "ls '-l' | cat '-e'" 561 0
run_test 562 "ls '-l' | 'cat' '-e'" 562 0
run_test 563 "ls -l | 'cat' '-e'" 563 0

run_test 564 "\"ls\" -l | cat -e" 564 0
run_test 565 "ls \"-l\" | cat -e" 565 0
run_test 566 "ls -l | \"cat\" -e" 566 0
run_test 567 "ls -l | cat \"-e\"" 567 0
run_test 568 "\"ls\" \"-l\" | cat -e" 568 0
run_test 569 "\"ls\" \"-l\" | \"cat\" -e" 569 0
run_test 570 "\"ls\" \"-l\" | cat \"-e\"" 570 0
run_test 571 "\"ls\" \"-l\" | \"cat\" \"-e\"" 571 0
run_test 572 "\"ls\" -l | \"cat\" \"-e\"" 572 0
run_test 573 "\"ls\" -l | cat \"-e\"" 573 0
run_test 574 "ls \"-l\" | \"cat\" -e" 574 0
run_test 575 "ls \"-l\" | cat \"-e\"" 575 0
run_test 576 "ls \"-l\" | \"cat\" \"-e\"" 576 0
run_test 577 "ls -l | \"cat\" \"-e\"" 577 0

run_test 578 "\"ls\" '-l' | cat -e" 578 0
run_test 579 "\"ls\" -l | 'cat' -e" 579 0
run_test 580 "\"ls\" -l | cat '-e'" 580 0
run_test 581 "\"ls\" '-l' | 'cat' -e" 581 0
run_test 582 "\"ls\" '-l' | cat '-e'" 582 0
run_test 583 "\"ls\" '-l' | 'cat' '-e'" 583 0
run_test 584 "\"ls\" -l | 'cat' '-e'" 584 0

run_test 585 "'ls' \"-l\" | cat -e" 585 0
run_test 586 "ls \"-l\" | 'cat' -e" 586 0
run_test 587 "ls \"-l\" | cat '-e'" 587 0
run_test 588 "'ls' \"-l\" | 'cat' -e" 588 0
run_test 589 "'ls' \"-l\" | cat '-e'" 589 0
run_test 590 "'ls' \"-l\" | 'cat' '-e'" 590 0
run_test 591 "ls -l | \"cat\" '-e'" 591 0
run_test 592 "'ls' -l | \"cat\" -e" 592 0
run_test 593 "ls '-l' | \"cat\" -e" 593 0
run_test 594 "'ls' '-l' | \"cat\" -e" 594 0
run_test 595 "'ls' '-l' | \"cat\" '-e'" 595 0
run_test 596 "ls '-l' | \"cat\" '-e'" 596 0
run_test 597 "'ls' -l | \"cat\" '-e'" 597 0
run_test 598 "'ls' -l | cat \"-e\"" 598 0
run_test 599 "ls '-l' | cat \"-e\"" 599 0
run_test 600 "ls -l | 'cat' \"-e\"" 600 0
run_test 601 "'ls' '-l' | cat \"-e\"" 601 0
run_test 602 "'ls' '-l' | 'cat' \"-e\"" 602 0
run_test 603 "ls '-l' | 'cat' \"-e\"" 603 0

run_test 604 "\"ls\" \"-l\" | cat -e" 604 0
run_test 605 "\"ls\" \"-l\" | 'cat' -e" 605 0
run_test 606 "\"ls\" \"-l\" | cat '-e'" 606 0
run_test 607 "\"ls\" \"-l\" | 'cat' '-e'" 607 0

run_test 608 "\"ls\" -l | \"cat\" -e" 608 0
run_test 609 "\"ls\" '-l' | \"cat\" -e" 609 0
run_test 610 "\"ls\" -l | \"cat\" '-e'" 610 0
run_test 611 "\"ls\" '-l' | \"cat\" '-e'" 611 0

run_test 612 "\"ls\" -l | cat \"-e\"" 612 0
run_test 613 "\"ls\" '-l' | cat \"-e\"" 613 0
run_test 614 "\"ls\" '-l' | 'cat' \"-e\"" 614 0
run_test 615 "\"ls\" -l | 'cat' \"-e\"" 615 0

run_test 616 "ls \"-l\" | \"cat\" -e" 616 0
run_test 617 "'ls' \"-l\" | \"cat\" -e" 617 0
run_test 618 "ls \"-l\" | \"cat\" '-e'" 618 0
run_test 619 "'ls' \"-l\" | \"cat\" '-e'" 619 0

run_test 620 "ls -l | \"cat\" \"-e\"" 620 0
run_test 621 "'ls' -l | \"cat\" \"-e\"" 621 0
run_test 622 "ls '-l' | \"cat\" \"-e\"" 622 0
run_test 623 "'ls' '-l' | \"cat\" \"-e\"" 623 0

run_test 624 "\"ls\" \"-l\" | \"cat\" -e" 624 0
run_test 625 "\"ls\" \"-l\" | \"cat\" '-e'" 625 0

run_test 626 "\"ls\" \"-l\" | cat \"-e\"" 626 0
run_test 627 "\"ls\" \"-l\" | 'cat' \"-e\"" 627 0

run_test 628 "\"ls\" -l | \"cat\" \"-e\"" 628 0
run_test 629 "\"ls\" '-l' | \"cat\" \"-e\"" 629 0

run_test 630 "ls \"-l\" | \"cat\" \"-e\"" 630 0
run_test 631 "'ls' \"-l\" | \"cat\" \"-e\"" 631 0

run_test 632 "\"ls\" \"-l\" | \"cat\" \"-e\"" 632 0
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
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 760 to 775\n"
else
	echo -e "end of test serie from 760 to 775"
fi

run_test 1000 "'ls'-l'cat -e'" 1000 0
run_test 1001 "'ls'-l'cat  -e'" 1001 0
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 1000 to 1100\n"
else
	echo -e "end of test serie from 1000 to 1100"
fi


run_test_syntax_error 2000 "<<< infile.txt" 2 #exit_status to confirm
run_test_syntax_error 2001 "<<<< infile.txt" 2
run_test_syntax_error 2002 "<<<<< infile.txt" 2
run_test_syntax_error 2003 "<<> infile.txt" 2
run_test_syntax_error 2004 "<<>> infile.txt" 2
run_test_syntax_error 2005 "<<>>> infile.txt" 2
run_test_syntax_error 2006 "<<>>>> infile.txt" 2
run_test_syntax_error 2007 "<<>< infile.txt" 2
run_test_syntax_error 2008 "<<><< infile.txt" 2
run_test_syntax_error 2009 "<<><<< infile.txt" 2
run_test_syntax_error 2010 "<<><<<< infile.txt" 2
run_test_syntax_error 2011 "<<><> infile.txt" 2
run_test_syntax_error 2012 "<<><>> infile.txt" 2
run_test_syntax_error 2013 "<<><>>> infile.txt" 2
run_test_syntax_error 2014 "<<><>>>> infile.txt" 2
run_test_syntax_error 2014 "<> infile.txt" 2
run_test_syntax_error 2015 "<>> infile.txt" 2
run_test_syntax_error 2016 "<>>> infile.txt" 2
run_test_syntax_error 2017 "<>>>> infile.txt" 2
run_test_syntax_error 2018 "<>>>>> infile.txt" 2
run_test_syntax_error 2019 "<>< infile.txt" 2
run_test_syntax_error 2020 "<><< infile.txt" 2
run_test_syntax_error 2021 "<><<< infile.txt" 2
run_test_syntax_error 2022 "<><<<< infile.txt" 2
run_test_syntax_error 2023 "<><> infile.txt" 2
run_test_syntax_error 2024 "<><>> infile.txt" 2
run_test_syntax_error 2025 "<><>>> infile.txt" 2
run_test_syntax_error 2026 "<><>>>> infile.txt" 2
run_test_syntax_error 2027 "<><>>>>> infile.txt" 2
run_test_syntax_error 2028 ">>> outfile.txt" 2
run_test_syntax_error 2029 ">>>> outfile.txt" 2
run_test_syntax_error 2030 ">>>>> outfile.txt" 2
run_test_syntax_error 2031 ">>>>>> outfile.txt" 2
run_test_syntax_error 2032 ">>< outfile.txt" 2
run_test_syntax_error 2033 ">><< outfile.txt" 2
run_test_syntax_error 2034 ">><<< outfile.txt" 2
run_test_syntax_error 2035 ">><<<< outfile.txt" 2
run_test_syntax_error 2036 ">><<<<< outfile.txt" 2
run_test_syntax_error 2037 ">><> outfile.txt" 2
run_test_syntax_error 2038 ">><>> outfile.txt" 2
run_test_syntax_error 2039 ">><>>> outfile.txt" 2
run_test_syntax_error 2040 ">><>>>> outfile.txt" 2
run_test_syntax_error 2041 ">><>>>>> outfile.txt" 2
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 2000 to 2499\n"
else
	echo -e "end of test serie from 2000 to 2499"
fi

run_test_syntax_error 2300 "< 'infile.txt" 2 #exit_status to confirm
run_test_syntax_error 2301 "< infile.txt'" 2
run_test_syntax_error 2302 "< \"infile.txt" 2
run_test_syntax_error 2303 "< infile.txt\"" 2
run_test_syntax_error 2304 "< 'infile.txt\"" 2
run_test_syntax_error 2305 "< 'infile.txt'\"" 2
run_test_syntax_error 2306 "< \"infile.txt'\"" 2
run_test_syntax_error 2307 "< \"infile.txt\"'" 2
run_test_syntax_error 2308 "<< 'infile.txt" 2
run_test_syntax_error 2309 "<< infile.txt'" 2
run_test_syntax_error 2310 "<< \"infile.txt" 2
run_test_syntax_error 2311 "<< infile.txt\"" 2
run_test_syntax_error 2312 "<< 'infile.txt\"" 2
run_test_syntax_error 2313 "<< 'infile.txt'\"" 2
run_test_syntax_error 2314 "<< \"infile.txt'\"" 2
run_test_syntax_error 2315 "<< \"infile.txt\"'" 2

run_test_syntax_error 2400 "> 'outfile.txt" 2
run_test_syntax_error 2401 "> outfile.txt'" 2
run_test_syntax_error 2402 "> \"outfile.txt" 2
run_test_syntax_error 2403 "> outfile.txt\"" 2
run_test_syntax_error 2404 "> 'outfile.txt\"" 2
run_test_syntax_error 2405 "> 'outfile.txt'\"" 2
run_test_syntax_error 2406 "> \"outfile.txt'\"" 2
run_test_syntax_error 2407 "> \"outfile.txt\"'" 2
run_test_syntax_error 2408 ">> 'outfile.txt" 2
run_test_syntax_error 2409 ">> outfile.txt'" 2
run_test_syntax_error 2410 ">> \"outfile.txt" 2
run_test_syntax_error 2411 ">> outfile.txt\"" 2
run_test_syntax_error 2412 ">> 'outfile.txt\"" 2
run_test_syntax_error 2413 ">> 'outfile.txt'\"" 2
run_test_syntax_error 2414 ">> \"outfile.txt'\"" 2
run_test_syntax_error 2415 ">> \"outfile.txt\"'" 2
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 2300 to 2999\n"
else
	echo -e "end of test serie from 2300 to 2999"
fi

run_test_syntax_error 3000 "'ls" 2 #exit_status to confirm
run_test_syntax_error 3001 "ls'" 2
run_test_syntax_error 3002 "\"ls" 2
run_test_syntax_error 3003 "ls\"" 2
run_test_syntax_error 3004 "'ls\"" 2
run_test_syntax_error 3005 "'ls'\"" 2
run_test_syntax_error 3006 "\"ls'" 2
run_test_syntax_error 3007 "\"ls\"'" 2
#run_test_syntax_error 3008 "''ls" 2
run_test_syntax_error 3009 "''ls'" 2
run_test_syntax_error 3010 "'''ls" 2
#run_test_syntax_error 3011 "'''ls'" 2
run_test_syntax_error 3012 "'''ls''" 2
#run_test_syntax_error 3013 "\"\"ls" 2
run_test_syntax_error 3014 "\"\"ls\"" 2
run_test_syntax_error 3015 "\"\"\"ls" 2
#run_test_syntax_error 3016 "\"\"\"ls\"" 2
run_test_syntax_error 3017 "\"\"\"ls\"\"" 2
#to continue

run_test_syntax_error 3100 "cat 'ls" 2
run_test_syntax_error 3101 "cat ls'" 2
run_test_syntax_error 3102 "cat \"ls" 2
run_test_syntax_error 3103 "cat ls\"" 2
run_test_syntax_error 3104 "'cat' 'ls" 2
run_test_syntax_error 3105 "'cat' ls'" 2
run_test_syntax_error 3106 "'cat' ls'" 2
run_test_syntax_error 3107 "'cat' \"ls" 2
run_test_syntax_error 3108 "'cat' ls\"" 2
run_test_syntax_error 3109 ""cat" 'ls" 2
run_test_syntax_error 3110 ""cat" ls'" 2
run_test_syntax_error 3111 ""cat" ls'" 2
run_test_syntax_error 3112 ""cat" \"ls" 2
run_test_syntax_error 3113 ""cat" ls\"" 2
run_test_syntax_error 3114 "cat 'ls " 2
run_test_syntax_error 3115 "cat ls' " 2
run_test_syntax_error 3116 "cat \"ls " 2
run_test_syntax_error 3117 "cat ls\" " 2
run_test_syntax_error 3118 "cat 'ls  " 2
run_test_syntax_error 3119 "cat ls'  " 2
run_test_syntax_error 3120 "cat \"ls  " 2
run_test_syntax_error 3121 "cat ls\"  " 2
run_test_syntax_error 3122 "cat ' ls" 2
run_test_syntax_error 3123 "cat  ls'" 2
run_test_syntax_error 3124 "cat \" ls" 2
run_test_syntax_error 3125 "cat ls \"" 2
if [ "$display" == "all" ]
then
	echo -e "end of test serie from 3000 to 3999\n"
else
	echo -e "end of test serie from 3000 to 3999"
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
delete_test_files

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