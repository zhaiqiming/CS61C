#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* TODO: Implement ll_has_cycle */
    const int max_length = 100000;
    node* one = head;
    node* two = head;
    while(two != NULL && one != NULL){
        if(one->next != NULL) one = one->next;
        else return 0;
        if(two->next != NULL && two->next->next != NULL) two = two->next->next;
        else return 0;
        if(one == two) return 1;
    }
    return 0;
}
