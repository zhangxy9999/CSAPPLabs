#include "dl_list.h"
#include "mm_public.h"
/*
 * TODO: Implement the following functions
 * DL_LIST_INIT: Initialize list
 * INSERT_ITEM: Insert item at the end of the list
 * DELETE_ITEM: Delete all items with a specified value
 * COUNT_ITEMS: Count all items with a specified value
 * PRINT_LIST: Print the list from head to tail
 * JOIN_LISTS: Join two lists
 * DELETE_LIST: Delete all items in the list + the list itself
 */



/*
 * TODO: Initiate the list
 * Takes as argument a newly created dl_list
 * Initialize all members with appropriate values.
 */
void dl_list_init(dl_list* list)
{
    mm_t MM;
    mm_init(&MM, 1500, 32)
}


/*
 * TODO: Insert an item with value "val" at the end of "list"
 */
void insert_item(dl_list* list, long int val, mm_t* mm)
{
    dl_list_node *node;
    node = mm_get(mm);
    node->value = val;
    node->prev = list->tail;
    node->next = NULL;

    if (list->tail != NULL)
    {
        list->tail->next = node;
    }
    if (list->head == NULL)
    {
        list->head = node;
        list->cursor = item;
    }
    list->tail = node;

    printf("")
}


/*
 * TODO: Delete all items with value "val" from "list"
 * Return the number of items deleted.
 */
int delete_item(dl_list* list, long int val, mm_t* mm)
{
    if (list->cursor->value == val) list->cursor =
    return 0;
}


/*
 * TODO: Count the number of items with value "val"
 */
int count_items(dl_list* list, long int val) {
    return 0;
}


/*
 * TODO: Print out the value of all items in "list" in order
 * In order means: From head to tail; NOT sorted values.
 * Value are separated by spaces
 */
void print_list(dl_list* list)
{

}


/*
 * TODO: Joins two lists
 * Attach list_b to list_a, and Leave list_b empty
 */
void join_lists(dl_list* list_a, dl_list* list_b) {

}


/*
 * TODO: Delete all items in the list.
 * Return the number of all items delete.
 */
int empty_list(dl_list* list, mm_t* mm) {
    return 0;
}
