## Category Two: Data Structures and Algorithms 
#### Linked List

This is an enhancement of code I submitted as a milestone in the *CS-260: Data Structures and Algorithms* class. The linked list contained *bids*, that is, structs containing several data items, the most notable being an ID number. The linked list class included methods to prepend and postpend elements, to search for or delete and element by its ID number, and to print the list.

For the enhancements for my *CS-499: Computer Science Capstone* class, I implemented several additional methods that were not included originally:.

1. a method to insert an item into the list at a given index;
2. a method to clear the list and leave it empty;
3. a method to delete the list entirely;
4. a method to delete an item at a given index;
5. methods to find an item and return its index and to get an item at a particular index;
7. methods to reverse the list in-place or to return the reversed list as a new list;
8. a method to convert the list to a C++ vector;
9. a method to sort the list in-place.

I removed the code from its original context (which included a *.csv* file and a parser which were provided to me for the project) because the purpose of the enhancements was to make the code more reusable.

For the last method mentioned, I opted for a merge sort because its worst-case runtime is $\mathcal{O}\(n\log n\)$, it not being subject to pathological cases of the sort that reduce quicksort to $\mathcal{O}\(n^2\)$ time; and the sequential-access nature of linked lists means it is better suited to those applications than quicksort anyway. The enhancements resulted in code which is more modular and reusable and has removed the possibility of memory leaks which had not been addressed in the original.
{% include mathjax.html %}
