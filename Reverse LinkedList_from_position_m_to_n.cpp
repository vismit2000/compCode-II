// https://www.interviewbit.com/problems/reverse-link-list-ii/
/*
Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
ListNode* Solution::reverseBetween(ListNode* A, int B, int C) 
{
    int m = B, n = C;
    if(m == n || A == NULL)
        return A;
        
    ListNode *prev, *temp, *third, *atM = NULL, *atN = NULL, *beforeM = NULL, *afterN = NULL;
    ListNode *head = A;
    
    //change head if m == 1
    
    int cnt = 1;
    
    temp = A;
    while(temp)
    {
        if(cnt == m-1)
            beforeM = temp;
        if(cnt == m)
            atM = temp;
        if(cnt == n)
        {
            atN = temp;
            break;
        }
        cnt++;
        temp = temp->next;
    }
    afterN = atN->next;
    
    prev = atM;
    temp = atM->next;
    third = temp->next;
    
    prev->next = afterN;
    
    while(temp != afterN)
    {
        temp->next = prev;
        prev = temp;
        temp = third;
        if(third != afterN)
            third = third->next;
    }
    if(beforeM == NULL)
        return atN;
    else
        beforeM->next = atN;
        
    return head;
}
