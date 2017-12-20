#include "listlist.h"


ListElement::ListElement (void *itemPtr, long long sortKey)
{
    item = itemPtr;
    key = sortKey;
    next = NULL
}

List::List ()
{
    first = last = NULL;
}

List::~List ()
{
    while (Remove () != NULL)
	;			// delete all the list elements
}


void
List::Append (void *item)
{
    ListElement *element = new ListElement (item, 0);

    if (IsEmpty ())
      {				// list is empty
	  first = element;
	  last = element;
      }
    else
      {				// else put it after last
	  last->next = element;
	  last = element;
      }
}


void
List::Prepend (void *item)
{
    ListElement *element = new ListElement (item, 0);

    if (IsEmpty ())
      {				// list is empty
	  first = element;
	  last = element;
      }
    else
      {				// else put it before first
	  element->next = first;
	  first = element;
      }
}

void *
List::Remove ()
{
    return SortedRemove (NULL);	// Same as SortedRemove, but ignore the key
}

void
List::Mapcar (VoidFunctionPtr func)
{
    for (ListElement * ptr = first; ptr != NULL; ptr = ptr->next)
      {
	  DEBUG ('l', "In mapcar, about to invoke %x(%x)\n", func, ptr->item);
	  (*func) ((int) ptr->item);
      }
}

bool
List::IsEmpty ()
{
    if (first == NULL)
	return TRUE;
    else
	return FALSE;
}

void
List::SortedInsert (void *item, long long sortKey)
{
    ListElement *element = new ListElement (item, sortKey);
    ListElement *ptr;		// keep track

    if (IsEmpty ())
      {				// if list is empty, put
	  first = element;
	  last = element;
      }
    else if (sortKey < first->key)
      {
	  // item goes on front of list
	  element->next = first;
	  first = element;
      }
    else
      {				// look for first elt in list bigger than item
	  for (ptr = first; ptr->next != NULL; ptr = ptr->next)
	    {
		if (sortKey < ptr->next->key)
		  {
		      element->next = ptr->next;
		      ptr->next = element;
		      return;
		  }
	    }
	  last->next = element;	// item goes at end of list
	  last = element;
      }
}

//----------------------------------------------------------------------
// List::SortedRemove
//      Remove the first "item" from the front of a sorted list.
// 
// Returns:
//      Pointer to removed item, NULL if nothing on the list.
//      Sets *keyPtr to the priority value of the removed item
//      (this is needed by interrupt.cc, for instance).
//
//      "keyPtr" is a pointer to the location in which to store the 
//              priority of the removed item.
//----------------------------------------------------------------------

void *
List::SortedRemove (long long *keyPtr)
{
    ListElement *element = first;
    void *thing;

    if (IsEmpty ())
	return NULL;

    thing = first->item;
    if (first == last)
      {				// list had one item, now has none 
	  first = NULL;
	  last = NULL;
      }
    else
      {
	  first = element->next;
      }
    if (keyPtr != NULL)
	*keyPtr = element->key;
    delete element;
    return thing;
}
