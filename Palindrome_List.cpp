// https://www.interviewbit.com/problems/palindrome-list/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
int Solution::lPalin(ListNode* A) 
{
    if(A == NULL || A->next == NULL)
        return 1;
        
    int isEven;
        
    ListNode *slow = A, *fast = A;
    
    while(1)
    {
        if(fast->next == NULL)
        {
            isEven = 0;
            break;
        }
        fast = fast->next;
        
        if(fast->next == NULL)
        {
            isEven = 1;
            break;
        }
        fast = fast->next;
        
        slow = slow->next;
    }
    
    //handle case: when list has only two elements
    if(slow == A)
    {
        if(slow->val == slow->next->val)
            return 1;
        else
            return 0;
    }
        
    ListNode *mid1 = slow, *mid2 = slow->next;
    mid1->next = NULL;
    
    //Reverse first half
        
    ListNode *prev, *temp, *third;
        
    prev = A;
    temp = prev->next;
    third = temp->next;
    
    while(temp)
    {
        if(prev == A)
            prev->next == NULL;
        
        temp->next = prev;
        prev = temp;
        temp = third;
        if(third)
            third = third->next;
    }
    
    if(isEven == 0)
        mid1 = prev->next;
    
    while(mid2)
    {
        if(mid1->val != mid2->val)
            return 0;
        mid1 = mid1->next;
        mid2 = mid2->next;
    }
    return 1;
}
