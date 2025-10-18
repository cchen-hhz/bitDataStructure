void change( int n, int m, NODE * head )
{
    if (m <= 0) return;
    NODE ** rem_node = (NODE **) calloc(m, sizeof(NODE *));
    if (rem_node == NULL) {
        head->next = NULL;
        return;
    }

    int rem = n % m;
    NODE * cur = head;
    while (rem != 0 && rem_node[rem] == NULL) {
        int r = rem;
        int d = (r * 10) / m;
        NODE * newnode = (NODE *) malloc(sizeof(NODE));
        newnode->data = d;
        newnode->next = NULL;
        cur->next = newnode;
        cur = newnode;
        rem_node[r] = newnode;
        rem = (r * 10) % m;
    }

    if (rem == 0) {
        cur->next = NULL;
    } else {
        cur->next = rem_node[rem];
    }

    free(rem_node);
}

NODE * find( NODE * head, int * n )
{
    if (head == NULL || head->next == NULL) {
        *n = 0;
        return NULL;
    }

    NODE * slow = head->next;
    NODE * fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    if (fast == NULL || fast->next == NULL) {
        *n = 0;
        return NULL;
    }

    int len = 1;
    NODE * p = slow->next;
    while (p != slow) {
        len++;
        p = p->next;
    }

    NODE * p1 = head->next;
    NODE * p2 = head->next;
    for (int i = 0; i < len; ++i) p2 = p2->next;
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }

    *n = len;
    return p1;
}