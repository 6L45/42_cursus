#!/bin/bash

VECTOR_DIR="./ft_vector/"
MAP_DIR="./ft_map/"
STACK_DIR="./ft_stack/"
SET_DIR="./ft_set/"

STD_VECTOR_DIR="./std_vector/"
STD_MAP_DIR="./std_map/"
STD_STACK_DIR="./std_stack/"
STD_SET_DIR="./std_set/"

VECTOR_PROGS=($(ls $VECTOR_DIR))
MAP_PROGS=($(ls $MAP_DIR))
STACK_PROGS=($(ls $STACK_DIR))
SET_PROGS=($(ls $SET_DIR))

CONTAINERS=(
	VECTOR_PROGS[@]
	MAP_PROGS[@]
	STACK_PROGS[@]
	SET_PROGS[@]
)

for container in "${CONTAINERS[@]}"; do

	programs=( "${container}" )
	programs=( "${!programs}" )

	if [[ $container == "VECTOR"* ]]; then
		FTLOC=$VECTOR_DIR
		STDLOC=$STD_VECTOR_DIR
	elif [[ $container == "MAP"* ]]; then
		FTLOC=$MAP_DIR
		STDLOC=$STD_MAP_DIR
	elif [[ $container == "SET"* ]]; then
		FTLOC=$SET_DIR
		STDLOC=$STD_SET_DIR
	elif [[ $container == "STACK"* ]]; then
		FTLOC=$STACK_DIR
		STDLOC=$STD_STACK_DIR
	fi

	echo
	echo
	echo "CONTAINER : ${container%_*}"

	for program in "${programs[@]}"; do
		
		ft_time=$( { time $FTLOC$program 1>/dev/null 2>&1; } 2>&1 )
		std_time=$( { time $STDLOC$program 1>/dev/null 2>&1; } 2>&1 )
		
		# extract the time values from the output of `time`
		ft_real=$(echo $ft_time | awk '{print $2}')
		ft_user=$(echo $ft_time | awk '{print $4}')
		ft_sys=$(echo $ft_time | awk '{print $6}')
		
		std_real=$(echo $std_time | awk '{print $2}')
		std_user=$(echo $std_time | awk '{print $4}')
		std_sys=$(echo $std_time | awk '{print $6}')
		
		echo "-------"
		echo " file $FTLOC / $STDLOC - [$program]" 
		echo "---"
		echo "real   $ft_real / $std_real" "|"
		echo "user   $ft_user / $std_user" "|"
		echo "sys    $ft_sys / $std_sys" "|"
		echo ""
	done
	echo "_________________________________________"
done
