/*
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};
*/
// Should reverse list and return new head.


Node* reverseList(Node *head)
{
    Node *prev = NULL, *curr = head, *NEXT = NULL;
    if(head == NULL || head->next == NULL)
        return head;
    while(curr != NULL)
    {
        NEXT = curr->next;
        curr->next = prev;
        prev = curr;
        curr = NEXT;
    }
    return prev;
}
