/* TODO: Add necessary header files here */
#include <stdio.h>

int main(){

    /* TODO: Allocate the memory manager. */


    /*
     * TODO: Test functions in the doubly linkded implementation,
     * according to section 2.5 of the writeup.
     * If you want to build new helper functions that is ok.
     * remember to print each list after creation or modifications.
     */

    /* TODO: Print final larger list. */

    /* TODO: Free all list items and then lists to the memory manager. */

    /* TODO: Deallocate the memory manager. */
    dl_list list1;
    dl_list list2;
    dl-list list3;
    mm_t MM;
    mm_init(&MM, 1500, 32);
    int i;

    for (i = 0; i < 500; i++)
    {
        intert_item(list1, i, MM);
    }

    for (i = 0; i < 500; i++)
    {
        intert_item(list2, random(500), MM);
    }

    while (list2->cursor->next == NULL)
    {
        <`0:insert_item(list3, list2->cursor->value + list1->cursor->value, MM)`>
    }


    return 0;
}
