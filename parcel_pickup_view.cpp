/*
 * Course: COEN 2220 - Programming 2
 * Name: Eduardo D. Vega Rodriguez
 * Lab: Lab 12 - Quicksort and Searching
 * Description: Preserve parcel arrival records and search a ready-only view
 * Due date: 11/10/2026
 */

#include <iostream>
#include <string>
using namespace std;

struct Parcel
{
    int pickupCode; // Unique lookup key supplied by the recipient.
    string locker; // Physical location, not a sorting key.
    bool ready;    // Only ready parcels belong in the lookup view.
};

void displayParcels(const Parcel parcels[], int count);
void displayReady(Parcel *view[], int count);
void swapParcelPointers(Parcel *&left, Parcel *&right);
int partitionReady(Parcel *view[], int first, int last);
void quickSortReady(Parcel *view[], int first, int last);
int binaryFindReady(Parcel *view[], int count, int target);

int main()
{
    const int CAPACITY = 8;

    Parcel parcels[CAPACITY] = {
        {640, "L-4", true},  {215, "L-8", false},
        {580, "L-2", true},  {325, "L-6", true},
        {710, "L-1", true},  {460, "L-5", false},
        {190, "L-3", true},  {505, "L-7", true}
    };

    Parcel *readyView[CAPACITY]; // Borrow addresses; do not delete these objects.
    int readyCount = 0;

    cout << boolalpha << "Original arrival records:" << endl;
    displayParcels(parcels, CAPACITY);

    for (int index = 0; index < CAPACITY; index++)
    {
        if (parcels[index].ready)
        {
            readyView[readyCount] = &parcels[index];
            readyCount++; // Count initialized view positions only.
        }
    }

    quickSortReady(readyView, 0, readyCount - 1);

    cout << "Ready parcels by pickup code:" << endl;
    displayReady(readyView, readyCount);

    cout << "Original arrival records after sorting:" << endl;
    displayParcels(parcels, CAPACITY);

    // --- STEP D1: Activate after completing the search function ---

    int target;

    cout << "Enter a pickup code: ";

    if (!(cin >> target))
    {
        cout << "Invalid code input." << endl;
        return 1;
    }

    int position = binaryFindReady(readyView, readyCount, target);

    if (position == -1)
    {
        cout << "No ready parcel with that code." << endl;
    }
    else
    {
        cout << "Pickup code " << readyView[position]->pickupCode
             << " | Locker: " << readyView[position]->locker << endl;
    }

    return 0;
}

// ===== Resolve only these TODOs now (Part C) =====

void swapParcelPointers(Parcel *&left, Parcel *&right)
{
    // TODO (Part C): Exchange the two borrowed addresses without changing objects.

    Parcel *saved = left; // Save the address of the first parcel.
    left = right;         // Move the second address to the first position.
    right = saved;        // Move the saved address to the second position.
}

int partitionReady(Parcel *view[], int first, int last)
{
    // TODO (Part C): Select the central record and partition by ascending pickupCode.

    int middle = first + (last - first) / 2;

    // Move the middle pointer to the first position.
    swapParcelPointers(view[first], view[middle]);

    // Save the pivot code before moving other pointers.
    int pivotCode = view[first]->pickupCode;

    // Start the smaller group at the first position.
    int boundary = first;

    // TODO (Part C): Follow the lecture's pivot-at-first scheme and return its final index.

    for (int scan = first + 1; scan <= last; scan++)
    {
        // Check if the current parcel code is smaller than the pivot.
        if (view[scan]->pickupCode < pivotCode)
        {
            boundary++; // Make space for the smaller code.

            // Move the smaller pointer to the left side.
            swapParcelPointers(view[boundary], view[scan]);
        }
    }

    // Place the pivot pointer in its final position.
    swapParcelPointers(view[first], view[boundary]);

    return boundary; // Return the final index of the pivot.
}

void quickSortReady(Parcel *view[], int first, int last)
{
    // TODO (Part C): Handle base cases and request partitioning and recursive sorting.

    // Stop when the range has zero or one pointer.
    if (first >= last)
    {
        return;
    }

    // Divide the range using the pivot.
    int pivotIndex = partitionReady(view, first, last);

    // Sort the pointers on the left side.
    quickSortReady(view, first, pivotIndex - 1);

    // Sort the pointers on the right side.
    quickSortReady(view, pivotIndex + 1, last);
}

// ===== Resolve this TODO later (Part D) =====

int binaryFindReady(Parcel *view[], int count, int target)
{
    // TODO (Part D): Implement iterative binary search by pickupCode on the sorted view.

    // Start searching from the first valid position.
    int first = 0;

    // Use count to find the last valid position.
    int last = count - 1;

    // Continue searching while the range is not empty.
    while (first <= last)
    {
        // Find the middle position of the current range.
        int middle = first + (last - first) / 2;

        // Check if the middle parcel matches the target.
        if (view[middle]->pickupCode == target)
        {
            return middle; // Return the position in readyView.
        }

        // If the middle code is smaller, search the right side.
        if (view[middle]->pickupCode < target)
        {
            first = middle + 1;
        }
        else
        {
            // If the middle code is greater, search the left side.
            last = middle - 1;
        }
    }

    return -1; // Return -1 when the code is not found.
}

void displayParcels(const Parcel parcels[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Code: " << parcels[index].pickupCode
             << " | Locker: " << parcels[index].locker
             << " | Ready: " << parcels[index].ready << endl;
    }
}

void displayReady(Parcel *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "View index: " << index
             << " | Code: " << view[index]->pickupCode
             << " | Locker: " << view[index]->locker << endl;
    }
}

/*
 * Analysis Answers
 *
 * C3 - Partition decisions
 * Trace the first partition of the six-pointer ready view. Record first, last,
 * middle, pivotCode, boundary, scan, and codes before and after each comparison.
 * Include the loop's final false test and the final pivot exchange.
 *
 * Answer:
 * The first partition starts with six ready parcels.
 * The initial codes are 640, 580, 325, 710, 190, and 505.
 *
 * first = 0, last = 5, middle = 2.
 * The middle code is 325, so pivotCode = 325.
 * The pivot is moved to index 0.
 *
 * The codes are now 325, 580, 640, 710, 190, 505.
 * boundary starts at 0.
 *
 * Step 1:
 * scan = 1, boundary = 0.
 * Code 580 is compared with 325.
 * Since 580 < 325 is false, nothing changes.
 * Codes: 325, 580, 640, 710, 190, 505.
 *
 * Step 2:
 * scan = 2, boundary = 0.
 * Code 640 is compared with 325.
 * Since 640 < 325 is false, nothing changes.
 * Codes: 325, 580, 640, 710, 190, 505.
 *
 * Step 3:
 * scan = 3, boundary = 0.
 * Code 710 is compared with 325.
 * Since 710 < 325 is false, nothing changes.
 * Codes: 325, 580, 640, 710, 190, 505.
 *
 * Step 4:
 * scan = 4, boundary = 0.
 * Code 190 is compared with 325.
 * Since 190 < 325 is true, boundary becomes 1.
 * The pointers at indexes 1 and 4 are swapped.
 * Codes: 325, 190, 640, 710, 580, 505.
 *
 * Step 5:
 * scan = 5, boundary = 1.
 * Code 505 is compared with 325.
 * Since 505 < 325 is false, nothing changes.
 * Codes: 325, 190, 640, 710, 580, 505.
 *
 * After the last comparison, scan becomes 6.
 * The condition 6 <= 5 is false, so the loop stops.
 *
 * Finally, the pivot at index 0 is swapped with
 * the pointer at boundary = 1.
 *
 * The codes become 190, 325, 640, 710, 580, 505.
 * The final pivot index is 1.
 *
 * The left range is 0 to 0 and the right range is 2 to 5.
 * Quicksort continues sorting the right side because
 * the complete view is not sorted yet.
 *
 * C4 - Data and memory
 * Explain what changes when swapping two Parcel pointers by reference.
 * Identify who owns the objects and why the view must not delete them.
 *
 * Answer:
 * When two Parcel pointers are swapped by reference,
 * only their addresses change positions in readyView.
 * The original Parcel objects are not modified or moved.
 *
 * The parcels array owns the original objects and keeps
 * them in the same arrival order.
 *
 * readyView only stores addresses that point to ready
 * parcels, so it does not own those objects.
 *
 * We should not use delete on these pointers because
 * the objects were created inside the parcels array
 * and were not created using new.
 *
 * This allows the program to sort the ready parcels
 * without changing the original records.
 *
 * D3 - Search positions and absence
 * Trace code 505 and the absent ready-view code 460. Give the checked ranges
 * and explain why a view index cannot be used as an index into parcels.
 *
 * Answer:
 * The sorted readyView contains these codes:
 * 190, 325, 505, 580, 640, 710.
 *
 * Searching for code 505:
 *
 * First step:
 * first = 0, last = 5, middle = 2.
 * The inspected code is 505.
 * Since the code matches, the function returns index 2.
 * The program displays locker L-7.
 *
 * Searching for code 460:
 *
 * First step:
 * first = 0, last = 5, middle = 2.
 * The inspected code is 505.
 * Since 460 is smaller than 505, the next range is 0 to 1.
 *
 * Second step:
 * first = 0, last = 1, middle = 0.
 * The inspected code is 190.
 * Since 460 is greater than 190, the next range is 1 to 1.
 *
 * Third step:
 * first = 1, last = 1, middle = 1.
 * The inspected code is 325.
 * Since 460 is greater than 325, the next range is 2 to 1.
 *
 * Now first = 2 and last = 1.
 * Since first is greater than last, the loop stops.
 * The function returns -1 because code 460 is not
 * available in the ready view.
 *
 * The program displays "No ready parcel with that code."
 *
 * A readyView index cannot be used directly as an index
 * into parcels because both arrays have different orders.
 * readyView only contains pointers to ready parcels,
 * while parcels keeps all records in their arrival order.
 *
 * For example, code 505 is at index 2 in readyView,
 * but its original position in parcels is index 7.
 * We must use readyView[position] to access the correct parcel.
 *
 * D4 - Time and auxiliary space
 * For n ready parcels and q queries, compare sorting once then using binary
 * search with scanning the unsorted ready view for every query. Give worst-case
 * bounds for this quicksort, balanced-partition bounds, and iterative-search
 * auxiliary space. Distinguish the view storage from recursive-call storage.
 *
 * Answer:
 * Sorting the ready view once allows the program to
 * search for parcel codes faster when there are many queries.
 *
 * With balanced partitions, quicksort takes O(n log n)
 * time to sort the ready parcels.
 * After sorting, each binary search takes O(log n) time.
 *
 * For q queries, the total time with balanced partitions
 * is O(n log n + q log n).
 *
 * If we use linear search without sorting, each search
 * can take O(n) time. For q queries, the total is O(qn).
 *
 * However, quicksort does not always divide the data evenly.
 * In the worst case, this quicksort takes O(n^2) time.
 * Choosing the middle position does not guarantee
 * balanced partitions.
 *
 * The readyView array uses O(n) space to store the
 * pointers to the ready parcels.
 *
 * Quicksort also uses extra memory for recursive calls.
 * With balanced partitions, it uses O(log n) stack space.
 * In the worst case, it can use O(n) stack space.
 *
 * Iterative binary search only uses a few variables,
 * so its auxiliary space is O(1).
 *
 * The view storage is separate from the memory used
 * by recursive calls during sorting.
 */