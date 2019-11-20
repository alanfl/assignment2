TEST_DATETIME=$(date +%Y%m%d_%H%M%S)
RESULTS_DIR='results/'

echo "Generating results in dir: ${RESULTS_DIR}"
echo "Generating directory for results..."
mkdir -pv "${RESULTS_DIR}/${TEST_DATETIME}"

echo "Building searchtest_proc..."
make searchtest_proc
make searchtest_thread

if [ ! -f searchtest_proc ]; then
	echo "searchtest_proc failed to build, removing result dir and exiting"
	find "${RESULTS_DIR}/${TEST_DATETIME}" -type r -delete
	exit 1
fi

if [ ! -f searchtest_thread ]; then
	echo "searchtest_thread failed to build, removing result dir and exiting"
	find "${RESULTS_DIR/${TEST_DATETIME}" -type r -delete
	exit 1
fi

for i in {1..5}
do
