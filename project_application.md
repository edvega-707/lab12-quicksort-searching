# Lab 12 - Project Application

## E1 - Filter and ownership

The program selects four active DELIVERY orders with IDs 420, 180, 310, and 205.

Order 650 is excluded because it is a DINE_IN order. Order 900 is excluded because its status is COMPLETED.

The original orders are stored in the orders array. The view only stores pointers to the selected orders and does not own them. This allows the program to organize the report without changing the original records.

## E2 - Report order and algorithm

The sorted report shows the following order IDs:

205, 310, 420, 180.

The program first sorts the orders by building in ascending order.

When two orders have the same building, it sorts them by priority in descending order.

If both building and priority are the same, it sorts by order ID in ascending order.

For example, orders 205 and 310 have the same building and priority, so order 205 appears first.

The program uses Quicksort to organize the pointers.

With balanced partitions, Quicksort takes O(n log n) time and O(log n) extra space for recursive calls.

In the worst case, Quicksort takes O(n²) time and O(n) extra space for recursive calls.

The pointer view also uses O(n) storage.

## E3 - Lookup choice and tests

The program uses Linear Search because the report is sorted by building and priority, not by order ID.

Binary Search would not work correctly because the order IDs are not sorted from smallest to largest.

Test 1: Searching for order 205 finds the order in Biblioteca with priority 3 and status PENDING.

Test 2: Searching for order 650 returns "Order not found in the delivery report." because it is a DINE_IN order.

Test 3: Searching for order 111 returns the same message because that order does not exist.

Creating another view sorted by order ID would require O(n) additional storage. Sorting it with Quicksort would take O(n log n) time with balanced partitions, or O(n²) in the worst case.

After sorting the second view, Binary Search could find orders in O(log n) time.

## E4 - Evidence and project connection

Source: delivery_report_practice.cpp

Output: delivery_report_output.txt

The original orders were displayed before and after creating the delivery report.

Both lists kept the same order IDs, order types, statuses, buildings, and priorities.

The program only exchanges pointers inside the temporary view, so the original orders are not moved or modified.

This is important for the cafeteria project because the original FIFO order must be preserved.

The delivery report can organize active orders for the staff without changing the order in which the cafeteria received them.