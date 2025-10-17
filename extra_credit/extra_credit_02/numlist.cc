#include "numlist.h"

// Partitioning functions
// Serial partition
unsigned int NumList::partition(vector<int>& keys, unsigned int low, 
                                unsigned int high)
    // TODO: Implement the serial partitioning method
{
    // Use the last element as the pivot
    int pivot = keys[high];
    int i = low - 1;

    for (unsigned int j = low; j < high; j++) {
	    if (keys[j] < pivot) {
		    ++i;
		    std::swap(keys[i], keys[j]);
	    }
    }
    std::swap(keys[i+1], keys[high]);
    return i+1;
}



// Parallel partition
unsigned int NumList:: partition_par(vector<int>& keys, unsigned int low,
                                     unsigned int high)
{
    // Use the last element as the pivot

	int pivot = keys[high];
	int n = high - low + 1;

	// Assign 0 or 1 for comparison against pivot
	std::vector<int> lt(n, 0);	// 1 if element < pivot
	std::vector<int> gt(n, 0);	// 1 if element >= pivot
	std::vector<int> output(n);


    // TODO: Implement the parallel partitioning method
    // There should be two #pragmas to parallelize the loop
    // First loop is calculating the lt and gt arrays
    // Second is when the integers are copied to the correct position (i.e.,
    // left or right side of the pivot

	// Loop 1: compute lt and gt arrays
	#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		if (keys[low+i] < pivot) {
			lt[i] = 1;
		} else if (i != n-1) {		// exclude pivot (final position)
			gt[i] = 1;
		}
	}

	// prefix sums
	std::vector<int> lt_prefix(n,0);
	std::vector<int> gt_prefix(n, 0);

	for (int i = 1; i<n; ++i) {
		lt_prefix[i] = lt_prefix[i-1] + lt[i-1];
		gt_prefix[i] = gt_prefix[i-1] + gt[i-1];
	}

	int num_lt = lt_prefix[n-1] + lt[n-1];

	// Loop 2: copy integers to correct position
	#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		if (lt[i] == 1) {
			output[lt_prefix[i]] = keys[low + i];
		} else if (gt[i] == 1) {
			output[num_lt + gt_prefix[i]] = keys[low + i];
		}
	}

	output[num_lt] = pivot;

	// Copy back original keys
	for (int i = 0; i < n; ++i) {
		keys[low+1] = output[i];
	}

	return low + num_lt;


}

// Actual qsort that recursively calls itself with particular partitioning
// strategy to sort the list
void NumList::qsort(vector<int>& keys, int low, int high, ImplType opt)
{
    if(low < high) {
        unsigned int pi;
        if(opt == serial) {
            pi = partition(keys, low, high);
        } else {
            pi = partition_par(keys, low, high);
        }
        qsort(keys, low, pi - 1, opt);
        qsort(keys, pi + 1, high, opt);
    }
}

// wrapper for calling qsort
void NumList::my_qsort(ImplType opt)
{
    /* Initiate the quick sort from this function */
    qsort(list, 0, list.size() - 1, opt);
}
// Default constructor
// This should "create" an empty list
NumList::NumList() {
    /* do nothing */
    /* you will have an empty vector */
}
// Contructor
// Pass in a vector and the partitioning strategy to use
NumList::NumList(vector<int> in, ImplType opt) {
    list = in;
    my_qsort(opt);
}
// Destructor
NumList::~NumList() {
    /* do nothing */
    /* vector will be cleaned up automatically by its destructor */
}
// Get the element at index
int NumList::get_elem(unsigned int index)
{
    return list[index];
}
// Print the list
void NumList::print(ostream& os)
{
    for(unsigned int i = 0; i < list.size(); i++) {
        os << i << ":\t" << list[i] << endl;
    }
}
