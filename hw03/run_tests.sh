export CPP_FILE="${1:-homework_3.cpp}"
export EXEC_NAME="${2:-homework_3_exec_file}"
export TEST_FILE="${3:-input1.txt}"
export TEST_OUTPUT_FILE="${4:-out1.txt}"
export TEST_SOLUTION_FILE="${4:-solution1.txt}"
export TEST_OUTPUT_SUMMARY_FILE="${5:-out1_formatted_summary.txt}"
export TEST_SOLUTION_SUMMARY_FILE="${5:-solution1_formatted_summary.txt}"

# compile
g++ "${CPP_FILE}" -o "${EXEC_NAME}" -std=c++11

# run
"./${EXEC_NAME}" < "${TEST_FILE}" > "${TEST_OUTPUT_FILE}"

# setup tmp dir
export TEST_CASE_DELIMITER='---- Start Test Output ----'
export TMP_DIR=_tmp_test_artifacts
export TMP_OUTPUT_BASE="${TMP_DIR}/test_output"
export TMP_SOLUTION_BASE="${TMP_DIR}/test_solution"

# clean up any preexisting tmp artifacts
rm -rf "${TMP_DIR}"
mkdir "${TMP_DIR}"

# process test output
awk '{f=ENVIRON["TMP_OUTPUT_BASE"] NR; print $0 " -|"> f}' RS="${TEST_CASE_DELIMITER}" "${TEST_OUTPUT_FILE}"

# process solution output
awk '{f=ENVIRON["TMP_SOLUTION_BASE"] NR; print $0 " -|"> f}' RS='---- Start Test Output ----' "${TEST_SOLUTION_FILE}"

# get test output files
export solutionfiles=$(ls _tmp_test_artifacts/test_solution*)

# run the comparisons on each section of the file
n=1
for file in $solutionfiles
do
    output_file="${TMP_OUTPUT_BASE}${n}"
    test_result=$(diff "${file}" "${output_file}" --strip-trailing-cr)

    echo -e "\n"
    if [ "${test_result}" ]
    then
      echo "******** Failed test ${n} ********"
      echo "${test_result}"
    else
      echo "******** Passed test ${n} ********"
    fi
    echo -e "\n"

    n=$(($n+1))
done

# compare formatted file with expected output file
touch "${TEST_OUTPUT_SUMMARY_FILE}"
summary_test_result=$(diff "${TEST_SOLUTION_SUMMARY_FILE}" "${TEST_OUTPUT_SUMMARY_FILE}" --strip-trailing-cr)

echo -e "\n"
if [ "${summary_test_result}" ]
then
  echo "******** Failed Test: File Format ********"
  echo "${summary_test_result}"
else
  echo "******** Passed Test: File Format ********"
fi

# cleanup
rm -rf "${TMP_DIR}"
