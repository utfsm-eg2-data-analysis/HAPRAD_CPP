#!/bin/bash

#####################################################
#                                                   #
#  Script made to execute the chain of programs     #
#        to calculate hadron radiative corrections  #
#                                                   #
#####################################################

function print_help() {
    echo "SCRIPT: exec_rad-corr_chain.sh"
    echo "======================="
    echo "./exec_rad-corr_chain.sh --part <part>"
    echo "Where:"
    echo "  <part>  = selects particle (eta, omega)"
    echo "Example:"
    echo "  ./exec_rad-corr_chain.sh --part omega"
    exit
}

function process_args() {
    arr=("$@")
    ic=0
    while [[ $ic -le $((${#arr[@]}-1)) ]]; do
        if [[ "${arr[$ic]}" == "--part" ]]; then
            part=${arr[$((ic+1))]}
        else
            echo "ERROR: unrecognized argument: ${arr[$((ic))]}.";
            print_help;
        fi
        ((ic+=2))
    done
}

function print_args() {
    echo "SCRIPT: exec_rad-corr_chain.sh"
    echo "=============================="
    echo "part = ${part}"
}

################
###   Main   ###
################

if [[ -z "${HAPRAD_CPP}" ]]; then
    echo "ERROR: variable HAPRAD_CPP is unset."
    exit 1
fi

if [[ -z "${PRODIR}" ]]; then
    echo "ERROR: variable PRODIR is unset."
    exit 1
fi

if [[ ${#} -ne 2 ]]; then
    echo "ERROR: ${#} arguments were provided, they should be 2."
    print_help
fi

argArray=("$@")
process_args "${argArray[@]}"
print_args

targets=("D" "A")

# move to main dir
cd ${HAPRAD_CPP}/Utilities

# loop over targets
for tar in "${targets[@]}"; do

    # (related to structure functions)
    # replace the following lines with the previously obtained values
    source ${PRODIR}/gfx/rad-corr_${part}/fit-results_${part}_${tar}.sh
    cd ${HAPRAD_CPP}
    sed -i "s|Double_t A;|Double_t A = ${PARAM_A};|g" TStructFunctionArray.cxx
    sed -i "s|Double_t Ac;|Double_t Ac = ${PARAM_AC};|g" TStructFunctionArray.cxx
    sed -i "s|Double_t Acc;|Double_t Acc = ${PARAM_ACC};|g" TStructFunctionArray.cxx

    # recompile HAPRAD_CPP
    make

    # recompile Utilities
    cd ${HAPRAD_CPP}/Utilities
    make clean; make

    # (final step)
    # get radiative correction factors
    ./bin/GetRC -p${part} -t${tar}

    mv -v RCFactor_${part}_${tar}.txt ${PRODIR}/gfx/rad-corr_${part}/

    # (related to structure functions)
    # restore TStructFunctionArray.cxx
    cd ${HAPRAD_CPP}
    sed -i "s|Double_t A = ${PARAM_A};|Double_t A;|g" TStructFunctionArray.cxx
    sed -i "s|Double_t Ac = ${PARAM_AC};|Double_t Ac;|g" TStructFunctionArray.cxx
    sed -i "s|Double_t Acc = ${PARAM_ACC};|Double_t Acc;|g" TStructFunctionArray.cxx
    make

    # return to Utilities
    cd ${HAPRAD_CPP}/Utilities
done
