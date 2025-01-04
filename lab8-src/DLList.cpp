#include "DLList.h"

/**
 * @brief      Constructor for the DLList.
 */
DLList::DLList()
{
	head = new DLNode();
	this->nElements = 0;
	head->next = head;
	head->prev = head;
}

/**
 * @brief      Destructor for the DLList.
 */
DLList::~DLList()
{
	delete[] head;
}

/**
 * @brief      Print the DLList line by line.
 */
void DLList::print()
{
	/** @todo Print this list line by line **/
	DLNode *n = this->head;
	if (n == NULL)
	{
		std::cout << "NULL" << std::endl;
		return;
	}
	n = n->next;

	while (n != head)
	{
		std::cout << n->data << std::endl;
		n = n->next;
	}
}

/**
 * @brief      Sort and print the list.
 *
 * This function should sort and print the list.
 * Note: the actual list is NOT to be modified.
 * In other words, it should only *print* in a
 * sorted order, not actually sort the list.
 */
void DLList::printSorted()
{
	DLList * sorted = new DLList();
	DLNode * n3 = head->prev;
	while (n3 != head) {
		int data = n3->data;
		sorted->insertFront(data);
		n3 = n3->prev;
	}
	int length = sorted->nElements;
	for (int i = 0; i < length-1; i++) {
		for (int j = 0; j < length - 1 - i; j++) {
			DLNode * node1 = sorted->head->next;
			for (int s = 0; s < j; s++) {
				node1 = node1->next;
			}
			DLNode * node2 = sorted->head->next;
			for (int s = 0; s < j+1; s++) {
				node2 = node2->next;
			}
			if (node1->data > node2->data) {
				int temp = node1->data;
				node1->data = node2->data;
				node2->data = temp;
			}
		}
	}
	sorted->print();
	/** @todo Print a sorted copy of this list **/

}

/**
 * @brief      Add to the front of the list.
 *
 * @param[in]  data  Item to add to front.
 */
void DLList::insertFront(int value)
{
	/** @todo Insert to the front of the list **/
	DLNode *e = new DLNode();
	e->data = value;

	if (nElements == 0) {
		e->next = head->next;
		e->prev = head;
		head->next = e;
		head->prev = e;
		nElements++;
		return;
	}
	e->data = value;
	e->next = head->next;
	e->prev = head;
	e->next->prev = e;
	head->next = e;
	nElements++;
}

/**
 * @brief      Removes & stores the last element.
 *
 * The last element is removed and stored in the
 * referenced variable data.
 *
 * @param      data  Thing in which we are storing the data.
 *
 * @return     True upon successful removal.
 */
bool DLList::removeLast(int &data)
{
	if (nElements == 0) {
		return false;
	}
	DLNode * e = head->next;
	while (e->next!=head) {
		e = e->next;
	}
	e->prev->next = head;
	head->next->prev = e->prev;
	data = e->data;
	delete e;
	return true;
}

/**
 * @brief      Difference of two lists.
 *
 * @param      list  Subtrahend.
 *
 * @return     Returns a pointer to the difference.
 */
DLList *DLList::difference(DLList &list)
{
	DLList *diff = new DLList();
	DLNode * n1 = head->next;
	bool isFound = false;
	while (n1 != head) {
		isFound = false;
		DLNode * n2 = list.head->next;
		while (n2 != list.head) {
			if (n1->data == n2->data) {
				isFound = true;
				break;
			}
			n2 = n2->next;
		}
		if (!isFound) {
			diff->insertFront(n1->data);
		}
		n1 = n1->next;
	}
	/** @todo Implement this function **/
	return diff;
}

/**
 * @brief      Returns a sublist of items in a range.
 *
 * @param[in]  start  First index.
 * @param[in]  end    Second index.
 *
 * @return     Elements between first and second index.
 */
DLList *DLList::getRange(int start, int end)
{
	DLList *range = new DLList();
	/** @todo getRange **/
	DLNode * n1 = head->next;
	for (int i = 0; i < start; i++) {
		n1 = n1->next;
	}
	for (int i = 0; i < end-start; i++) {
		range->insertFront(n1->data);
		n1 = n1->next;
	}
	return range;
}

/**
 * @brief      Intersection of this list and another list.
 *
 * @param      list  The other list.
 *
 * @return     Elements list shares with this one.
 */
DLList *DLList::intersection(DLList &list)
{
	DLList *inter = new DLList();
	DLNode * n1 = head->prev;
	bool isFound = false;
	while (n1 != head) {
		isFound = false;
		DLNode * n2 = list.head->next;
		while (n2 != list.head) {
			if (n1->data == n2->data) {
				isFound = true;
				break;
			}
			n2 = n2->next;
		}
		if (isFound) {
			inter->insertFront(n1->data);
		}
		n1 = n1->prev;
	}
	return inter;
}

/**
 * @brief      Removes nodes in the start-end range.
 *
 * @param[in]  start  First node.
 * @param[in]  end    Second node.
 */
void DLList::removeRange(int start, int end)
{
	DLNode * n1 = head->next;
	for (int i = 0; i < start; i++) {
		n1 = n1->next;
	}
	DLNode * n2 = n1;
	for (int i = 0; i < end-start; i++) {
		DLNode * n3 = n2;
		n2 = n2->next;
		delete n3;
	}
	n1->next = n2;
	n2->prev = n1;
}
