/*
 * Course: COEN 2220 - Programming 2
 * Name: Eduardo D. Vega Rodriguez
 * Lab: Lab 12 - Quicksort and Searching
 * Description: Practice - sort delivery orders and search by ID
 * Due date: 11/10/2026
 */

#include <iostream>
#include <string>
using namespace std;

// Store the information for one cafeteria order.
struct OrderPreview
{
    int orderId;       // Store the order identification number.
    string orderType;  // Store DELIVERY or DINE_IN.
    string status;     // Store the current order status.
    string building;   // Store the delivery building.
    int priority;      // Store the priority of the order.
};

// Declare the functions used to sort and search the view.
void swapOrderPointers(OrderPreview *&left, OrderPreview *&right);
bool comesBefore(OrderPreview *left, OrderPreview *right);
int partitionOrders(OrderPreview *view[], int first, int last);
void quickSortOrders(OrderPreview *view[], int first, int last);
int findOrderInView(OrderPreview *view[], int count, int target);

int main()
{
    const int ORDER_COUNT = 6;

    // Create six orders in their original arrival order.
    OrderPreview orders[ORDER_COUNT] =
    {
        {420, "DELIVERY", "PENDING", "Biblioteca", 1},
        {180, "DELIVERY", "IN_PROGRESS", "Ingenieria", 3},
        {650, "DINE_IN", "PENDING", "Cafeteria-Lunch", 1},
        {310, "DELIVERY", "PENDING", "Biblioteca", 3},
        {205, "DELIVERY", "PENDING", "Biblioteca", 3},
        {900, "DELIVERY", "COMPLETED", "Ingenieria", 2}
    };

    // Create an array to store pointers to selected orders.
    OrderPreview *view[ORDER_COUNT];

    // Count how many valid orders are stored in the view.
    int viewCount = 0;

    // Display the original orders before creating the view.
    cout << "Original orders before creating the view:" << endl;

    for (int index = 0; index < ORDER_COUNT; index++)
    {
        cout << "Order ID: " << orders[index].orderId
             << " | Type: " << orders[index].orderType
             << " | Status: " << orders[index].status
             << " | Building: " << orders[index].building
             << " | Priority: " << orders[index].priority
             << endl;
    }

    // Check each order without removing it from the original array.
    for (int index = 0; index < ORDER_COUNT; index++)
    {
        // Select only active DELIVERY orders.
        if (orders[index].orderType == "DELIVERY" &&
            (orders[index].status == "PENDING" ||
             orders[index].status == "IN_PROGRESS"))
        {
            // Store the address of the selected order.
            view[viewCount] = &orders[index];

            // Increase the number of selected orders.
            viewCount++;
        }
    }

    // Sort only the selected delivery orders.
    quickSortOrders(view, 0, viewCount - 1);

    // Display the selected delivery orders.
    cout << "\nTemporary delivery view:" << endl;

    for (int index = 0; index < viewCount; index++)
    {
        cout << "Order ID: " << view[index]->orderId
             << " | Building: " << view[index]->building
             << " | Priority: " << view[index]->priority
             << " | Status: " << view[index]->status
             << endl;
    }

    // Display how many orders were selected.
    cout << "\nTotal selected delivery orders: " << viewCount << endl;

    // Display the original orders again to verify their order.
    cout << "\nOriginal orders after creating the view:" << endl;

    for (int index = 0; index < ORDER_COUNT; index++)
    {
        cout << "Order ID: " << orders[index].orderId
             << " | Type: " << orders[index].orderType
             << " | Status: " << orders[index].status
             << " | Building: " << orders[index].building
             << " | Priority: " << orders[index].priority
             << endl;
    }

    // Ask the user for an order ID.
    int target;

    cout << "\nEnter an order ID: ";

    if (!(cin >> target))
    {
        cout << "Invalid order ID." << endl;
        return 1;
    }

    // Search for the order in the sorted view.
    int position = findOrderInView(view, viewCount, target);

    // Check if the order was found.
    if (position == -1)
    {
        cout << "Order not found in the delivery report." << endl;
    }
    else
    {
        // Display the information of the selected order.
        cout << "Order ID: " << view[position]->orderId
             << " | Building: " << view[position]->building
             << " | Status: " << view[position]->status
             << " | Priority: " << view[position]->priority
             << endl;
    }

    return 0;
}

// Exchange two pointer addresses without changing the original orders.
void swapOrderPointers(OrderPreview *&left, OrderPreview *&right)
{
    OrderPreview *saved = left;
    left = right;
    right = saved;
}

// Compare two orders using the report sorting rules.
bool comesBefore(OrderPreview *left, OrderPreview *right)
{
    // Sort buildings in ascending order.
    if (left->building != right->building)
    {
        return left->building < right->building;
    }

    // Sort priorities in descending order.
    if (left->priority != right->priority)
    {
        return left->priority > right->priority;
    }

    // Sort order IDs in ascending order.
    return left->orderId < right->orderId;
}

// Divide the view using the middle order as the pivot.
int partitionOrders(OrderPreview *view[], int first, int last)
{
    int middle = first + (last - first) / 2;

    // Move the middle pointer to the first position.
    swapOrderPointers(view[first], view[middle]);

    // Save the pivot pointer before moving other pointers.
    OrderPreview *pivot = view[first];

    int boundary = first;

    // Compare each order with the pivot.
    for (int scan = first + 1; scan <= last; scan++)
    {
        if (comesBefore(view[scan], pivot))
        {
            boundary++;

            // Move the smaller order pointer to the left side.
            swapOrderPointers(view[boundary], view[scan]);
        }
    }

    // Place the pivot pointer in its final position.
    swapOrderPointers(view[first], view[boundary]);

    return boundary;
}

// Sort the delivery view using quicksort.
void quickSortOrders(OrderPreview *view[], int first, int last)
{
    // Stop when the range has zero or one order.
    if (first >= last)
    {
        return;
    }

    // Divide the view into two smaller ranges.
    int pivotIndex = partitionOrders(view, first, last);

    // Sort the left side.
    quickSortOrders(view, first, pivotIndex - 1);

    // Sort the right side.
    quickSortOrders(view, pivotIndex + 1, last);
}

// Search for an order ID using linear search.
int findOrderInView(OrderPreview *view[], int count, int target)
{
    // Check each selected order.
    for (int index = 0; index < count; index++)
    {
        if (view[index]->orderId == target)
        {
            return index; // Return the position in the view.
        }
    }

    return -1; // Return -1 if the order was not found.
}