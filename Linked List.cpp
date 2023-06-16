/* 
 * ==================================================================
 * Ed Morrow
 * Southern New Hampshire University
 * CS-499: Computer Science Capstone
 * Professor Brooke Goggin
 * Enhanced code for a linear singly-linked list
 * 30th May 2023
 * ==================================================================
 */

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

// STRUCT DECLARATIONS
/* struct to hold list data */
struct ListData {
  int elementId;
  string name;
};

/* struct to hold nodes in list */
struct Node {
  ListData data;
  Node* next;
  Node() {
    next = NULL;
  }
};

// FUNCTION PROTOTYPES
/* 
 * Function to create and return a new Node
 * @params newData: the data to be held by the Node
 * @return: the new Node
 */
Node* createNode(ListData newData);

/*
 * Singly-linked linear list
 */
class LinkedList {

  private:
    // internal structure for List entries, housekeeping variables
    Node* head;
    int size;
    int nextId;
    Node* TortoiseAndHare(Node* start);
    Node* Merge(Node* a, Node* b);


public:
    // List methods
    LinkedList();
    virtual ~LinkedList();
    void Postpend(ListData data);
    void Prepend(ListData data);
    void Insert(ListData data, int index);
    void Remove(string removeName);
    void Delete(int index);
    void Reverse();
    LinkedList Mirror();
    Node* Sort(Node* first); // FIXME
    void MergeSort();        // 
    vector<string> MakeVector();
    void Clear();
    void PrintList();
    ListData Get(int index);
    int Find(string searchName);
    int Size();
};

/*
 * Default constructor
 */
LinkedList::LinkedList() {
  head = new Node;
  int size = 0;
  int nextId = 1;
}

/*
 * Default destructor
 */
LinkedList::~LinkedList() {
  Clear();
  delete head;

}

/*
 * Method to append a new node to the end of the List
 * @params newData: the data that is to be held by the new node
 */
void LinkedList::Postpend(ListData newData) {
  /* create the new node and initialize its attributes */
  Node* newNode = createNode(newData);
  newNode -> data.elementId = nextId++;

  /* direct the new Node to point at the head-node, then redirect
   * it to each successive node in turn until the node it is pointing
   * to points to NULL */
  newNode -> next = head;
  while (newNode -> next -> next) {
    newNode -> next = newNode -> next -> next;
  }

  /* redirect the node point to Null to point to the new Node, then
   * redirect the new Node to point to NULL */
  newNode -> next -> next = newNode;
  newNode -> next = NULL;

  ++size;
}

/*
 * Method to append a new node to the beginning of the List
 * @params newData: the data that is to be held by the new node
 */
void LinkedList::Prepend(ListData newData) {
  /* create the new node and initialize its attributes */
  Node* newNode = createNode(newData);
  newNode -> data.elementId = nextId++;

  /* direct the new Node to point to where the head-node points,
   * then redirect head to point ti the new Node */
  newNode -> next = head -> next;
  head -> next = newNode;

  ++size;
}

/*
 * Method to insert a new node into the List at the given index,
 * or to the end of the list if the List is too short
 * @params newData: the data that is to be held by the new node
 */
void LinkedList::Insert(ListData newData, int index) {
  /* create the new node and initialize its attributes */
  Node* newNode = createNode(newData);
  newNode -> data.elementId = nextId++;

  Node* temp = head;

  /* iterate over the list and transfer the existing target
   * of the node that needs to be redirected to the new
   * Node's target, then redirect it to the new Node */
  while (temp -> next && index > 0) {
    temp = temp -> next;
    --index;
  }

  /* transfer the existing target of the Node that needs 
   * to be redirected to become the new Node's target, 
   * then redirect its own target to be the new Node */
  newNode -> next = temp -> next;
  temp -> next = newNode;

  ++size;
}


/*
 * Method to remove a Node from the List based on its contents
 * @params removeName: the data that is to be removed
 */
void LinkedList::Remove(string removeName) {
  Node* seeker = head;
  while (seeker -> next && seeker -> next -> data.name != removeName) {
    seeker = seeker -> next;
  }

  /* point temp at node to be deleted, bypass it then delete */
  Node* temp = seeker -> next;
  seeker -> next = seeker -> next -> next;
  delete temp;

  --size;
}

/*
 *  Method to delete a Node from the List given its index
 *  @params index: the index of the Node to be deleted
 */
void LinkedList::Delete(int index) {
  Node* seeker = head;
  /* decrement (relative) index with each step through List */
  while (seeker -> next && index > 0) {
    seeker = seeker -> next;
    --index;
  }

  /* point temp at node to be deleted, bypass it then delete */
  Node* temp = seeker -> next;
  seeker -> next = seeker -> next -> next;
  delete temp;

  --size;
}

/*
 * Method to reverse the List in-place
 */
void LinkedList::Reverse() {
  Node* temp1 = head;
  Node* temp2 = temp1 -> next;
  Node* temp3;

  /* take Nodes three at a time, redirect the second to point
   * at the first, then shift the group of three on one */
  while (temp1) {
    if (!temp2) {
      head -> next -> next = NULL;
      head -> next = temp1;
      break;
    }
    else {
      temp3 = temp2 -> next;
    }

    temp2 -> next = temp1;
    temp1 = temp2;
    temp2 = temp3;
  }
}

/* 
 * Method to return a new List which is the mirror-image of the current one
 */
LinkedList LinkedList::Mirror() {

  LinkedList mirror;
  mirror.size = Size();
  Node* nextElement = head -> next;

  /* access each Node in turn and prepend it to the new List to return 
   * the mirror */
  while (nextElement) {
    mirror.Prepend(nextElement -> data);
    nextElement = nextElement -> next;
  }
  return mirror;
}

/*
 * Method returns midpoint of a list
 */
Node* LinkedList::TortoiseAndHare(Node* first) {
  Node* tortoise = first;
  Node* hare = first -> next;

  /* hare moves twice as quickly through the list as tortoise,
   * leaving tortoise at the midpoint when hare reaches the end */
  while (hare != NULL & hare -> next != NULL) {
    tortoise = hare -> next;
    hare = hare -> next -> next; 
  }

  return tortoise;
}

/*
 * Method merges two sorted Lists to form a single
 * sorted List
 * @params left: 
 * @ params right:
 * @ return: the sorted List
 */
Node* LinkedList::Merge(Node* a, Node* b) {
  /* Nodes for the head of the new list and to track progress */
  Node* mergedListHead;
  Node* current = mergedListHead;

  while (a != NULL & b != NULL) {

    int comp = (a -> data.name).compare(b -> data.name);
    
    /* add next element from a if less than next element of b */
    if (comp < 0) {
      current -> next = a;
      a = a -> next;
      current = current -> next;
    }

    /* add next element from b if less than next element of a */
    else if (comp > 0)  {
      current -> next = b;
      b = b -> next;
      current = current -> next;
    }
  }

  /* add elements from a in turn if b is exhausted */
  while (a != NULL) {
    current -> next = a;
    a = a -> next;
    current = current -> next;
  }

  /* add elements from b in turn if a is exhausted */
  while (b != NULL) {
    current -> next = b;
    b = b -> next;
    current = current -> next;
  }

  return mergedListHead -> next;
}

/*
 * Method performs a merge-sort using the private TortoiseAndHare() and
 * Merge() functions and returns the first element of the sorted List
 */
Node* LinkedList::Sort(Node* first) {
  
  /* nothing to sort if fewer than two elements */
  if (first -> next == NULL) {
    return first;
  }

  /* break the list into two at the midpoint */
  Node* mid = TortoiseAndHare(first);
  Node* b_first = mid -> next;
  mid -> next = NULL;

  /* sort each of the two sublists */
  Node* a = Sort(first);
  Node* b = Sort(b_first);

  /* merge the two sorted sublists to form a sorted list */
  Node* new_first = Merge(a, b);

  return new_first;

}

/*
 * Performs a merge-sort in-place
 */
void LinkedList::MergeSort() {
  head -> next = Sort(head -> next);
}

/*
 * Method converts List to a Vector
 * @ return v: The vectorized List
 */
vector<string> LinkedList::MakeVector() {
  /* initialize new Vector and Node to scan List */
  vector<string> v;
  Node* nextNode = head -> next;

  /* visit each Node in turn and add its data to the Vector */
  while (nextNode) {
    v.push_back(nextNode -> data.name);
    nextNode = nextNode -> next;
  }

  return v;
}

/*
 * Method to clear the entire List but have the head-node persist, so that
 * the list remains but is empty
 */
void LinkedList::Clear() {
  while (head -> next) {
    Node* temp;
    temp = head -> next;
    head -> next = head -> next -> next;
    delete temp;
  }

  size = 0;
}

 /*
 * Method to print the List with the format
 * "Element ID: %d; Element: %s\n""
 */
void LinkedList::PrintList() {
  Node* current = head -> next;

  while (current) {
    cout << "Element ID: " << current -> data.elementId << "; Element: " << current -> data.name << endl;
    current = current -> next;
  }
}

/*
 * Method returns element of List at given index:
 * this should be used in conjunction with Find()
 * @ params index: the index of the List
 * @return item: the item to be returned
 */
ListData LinkedList::Get(int index) {
  Node* seeker = head -> next;

  /* decrement (relative) index with each step through List */
  while (seeker && index > 0) {
    seeker = seeker -> next;
    --index;
  }

  return seeker -> data;
}

/*
 * Method to return the index of the given name, if present,
 * and -1 if not
 * @params searchName: the name whose index is to be searched for
 * @return index: the index, defaulting to -1 if searchNAme not found
 */
int LinkedList::Find(string searchName) {
  int index = -1;
  Node* seeker = head -> next;

  while (seeker && seeker -> data.name != searchName) {
    ++index;
    seeker = seeker -> next;
  }

  return index;
}

/*
 * Method to return the size of a Linked List (excluding the head)
 * @return szie: the size of the List
 */
int LinkedList::Size() {
  return size;
}

/*
 * Function to create a new Node given the ListData to be contained
 * @params data: the data to be held by the new Node
 */
Node* createNode(ListData data) {
  Node* newNode = new Node;
  newNode -> data = data;

  return newNode;
}

/* driver code */
int main() {
  
  /* initialize a list and a vector of names to form the data */
  LinkedList myList;
  vector<string> names = {"Anglea", "Bill", "Cathy", "Dave", "Ella", "Fred", "Gladys", "Harry", "Ivy", "James", "Kate", "Luke", "Melody", "Neil", "Olivia", "Peter", "Qiteria", "Richard", "Samantha", "Thomas", "Ursula", "Victor", "Wendy", "Xavier", "Yvette", "Zoltan"}; 

  /* postpend the last five names to the list */
  for (int i = 0; i < 5; ++i) {
    ListData newElement;
    newElement.name = names.at(21 + i);
    myList.Postpend(newElement);
  }

  /* prepend the first five names to the List */
  for (int i = 0; i < 5; ++i) {
    ListData newElement;
    newElement.name = names.at(4 - i);
    myList.Prepend(newElement);
  }

  /* insert the middle two elements into the middle of the List */
  for (int i = 0; i < 2; ++i) {
    ListData newElement;
    newElement.name = names.at(12 + i);
    myList.Insert(newElement, 5 + i);
  }

  /* print the List, reverse it, then print it again */
  myList.PrintList();
  myList.Reverse();
  myList.PrintList();
  
  /* create a mirror of the (reversed) list and print it */
  LinkedList mirrorList = myList.Mirror();
  mirrorList.PrintList();

  /* convert the mirror list to a vector and print the
   * third, sixth and tenth elements */
  vector<string> myVector = mirrorList.MakeVector();
  cout << "Third element is " << myVector.at(2) << endl;
  cout << "Sixth element is " << myVector.at(5) << endl;
  cout << "Tenth element is " << myVector.at(9) << endl;

  /* clear the list then print its size */
  myList.Clear();
  cout << "Size of list is " << myList.Size() << endl;

  return 0;
}
