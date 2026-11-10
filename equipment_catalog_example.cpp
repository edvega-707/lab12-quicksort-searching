/*
 * Course: COEN 2220 - Programming 2
 * Name: Eduardo D. Vega Rodriguez 
 * Lab: Lab 12 - Quicksort and Searching
 * Description: Guided equipment catalog and code lookup
 * Due date: 11/10/2026
 */

#include <iostream>
#include <string>
using namespace std;

struct Equipment
{
    int assetCode;   // Identify one physical device; codes are unique.
    string cabinet; // Keep its storage location attached to the code.
};

void displayEquipment(const Equipment equipment[], int count);
void swapEquipment(Equipment& left, Equipment& right);
int partitionEquipment(Equipment equipment[], int first, int last);
void quickSortEquipment(Equipment equipment[], int first, int last);
int binaryFindEquipment(const Equipment equipment[], int first, int last, int target);

int main()
{
    const int COUNT = 8;
    Equipment equipment[COUNT] = {
        {48, "C-4"}, {21, "A-2"}, {63, "D-1"}, {35, "B-3"},
        {57, "C-2"}, {14, "A-1"}, {72, "D-4"}, {29, "B-1"}
    };

    cout << "Inspection order:" << endl;
    displayEquipment(equipment, COUNT);

    // --- STEP B2: Prepare the catalog for repeated code searches ---
    
    quickSortEquipment(equipment, 0, COUNT - 1);
    cout << "Sorted by asset code:" << endl;
    displayEquipment(equipment, COUNT);
    

    // --- STEP B3: Read a code and retrieve its cabinet safely ---
    
    int target;
    cout << "Enter an asset code: ";
    if (!(cin >> target))
    {
        cout << "Invalid code input." << endl;
        return 1; // Stop before searching with an unread value.
    }

    int position = binaryFindEquipment(equipment, 0, COUNT - 1, target);
    if (position == -1)
    {
        cout << "Equipment not found." << endl;
    }
    else
    {
        cout << "Found code " << equipment[position].assetCode
             << " in cabinet " << equipment[position].cabinet << endl;
    }
    
    return 0;
}

void displayEquipment(const Equipment equipment[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Code: " << equipment[index].assetCode
             << " | Cabinet: " << equipment[index].cabinet << endl;
    }
}

// --- STEP B2: Define the sorting operations ---

void swapEquipment(Equipment& left, Equipment& right)
{
    Equipment saved = left; // Preserve both fields during the exchange.
    left = right;
    right = saved;
}

int partitionEquipment(Equipment equipment[], int first, int last)
{
    int middle = first + (last - first) / 2;
    swapEquipment(equipment[first], equipment[middle]);
    int pivotCode = equipment[first].assetCode; // Keep this value fixed during the scan.
    int boundary = first; // The smaller group initially has no elements.

    for (int scan = first + 1; scan <= last; scan++)
    {
        if (equipment[scan].assetCode < pivotCode)
        {
            boundary++; // Reserve the next position in the smaller group.
            swapEquipment(equipment[boundary], equipment[scan]);
        }
    }
    swapEquipment(equipment[first], equipment[boundary]); // Complete the partition.
    return boundary; // This final position divides the next recursive ranges.
}

void quickSortEquipment(Equipment equipment[], int first, int last)
{
    if (first >= last)
    {
        return; // Empty and one-record ranges need no partition.
    }
    int pivotIndex = partitionEquipment(equipment, first, last);
    quickSortEquipment(equipment, first, pivotIndex - 1);
    quickSortEquipment(equipment, pivotIndex + 1, last);
}


// --- STEP B3: Define recursive lookup on the sorted catalog ---

int binaryFindEquipment(const Equipment equipment[], int first, int last, int target)
{
    if (first > last)
    {
        return -1; // An empty search range proves that the code is absent.
    }
    int middle = first + (last - first) / 2;
    if (equipment[middle].assetCode == target)
    {
        return middle; // A one-record range must still be checked for a match.
    }
    if (equipment[middle].assetCode < target)
    {
        return binaryFindEquipment(equipment, middle + 1, last, target);
    }
    return binaryFindEquipment(equipment, first, middle - 1, target);
}


/*
 * Analysis Answers
 *
 * B4 - Partition and recursive control
 * After the first partition, identify the pivot code, its returned index, and
 * the two next ranges. Is the whole catalog already sorted? Explain using data.
 *
 * Answer:
 * 
 * The first pivot is code 35, and its final index is 3.
 * After the first partition, quickSortEquipment works on
 * the left range from 0 to 2 and then the right range from 4 to 7.
 *
 * The catalog is not completely sorted yet because some codes
 * are still out of order. For example, the left side contains
 * 29, 21, and 14, which are not in ascending order.
 * Quicksort needs to continue sorting both sides until
 * all the equipment codes are in the correct order.
 *
 * B5 - A search that fails
 * Trace the recursive search for code 36. List each first, last, middle,
 * inspected code, and next range. At the empty range, explain which calls resume
 * and how -1 reaches main without an invalid array access.
 *
 * Answer:
 * 
 * When searching for code 36, binaryFindEquipment starts
 * checking the sorted catalog.
 *
 * First call:
 * first = 0, last = 7, middle = 3.
 * The inspected code is 35.
 * Since 36 is greater than 35, it searches the range 4 to 7.
 *
 * Second call:
 * first = 4, last = 7, middle = 5.
 * The inspected code is 57.
 * Since 36 is smaller than 57, it searches the range 4 to 4.
 *
 * Third call:
 * first = 4, last = 4, middle = 4.
 * The inspected code is 48.
 * Since 36 is smaller than 48, it searches the range 4 to 3.
 *
 * Fourth call:
 * first = 4, last = 3.
 * Since first is greater than last, the function returns -1.
 * No middle value is calculated and no code is checked.
 *
 * The -1 returns to the third call, then the second call,
 * and finally the first call until it reaches main.
 *
 * The program avoids accessing an invalid array position
 * because it checks if first is greater than last before
 * reading the array. Main also checks if position is -1
 * before trying to display the equipment information.
 *
 * Finally, the program displays "Equipment not found."
 * because code 36 does not exist in the catalog.
 */