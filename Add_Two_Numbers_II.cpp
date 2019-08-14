// https://leetcode.com/problems/add-two-numbers-ii/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Node {
public:
    unordered_map < ListNode *, ListNode * > mp;
    ListNode *tail;
    
    Node(ListNode *head)
    {
        ListNode *prev = NULL;
        while(head != NULL)
        {
            tail = head;
            mp[head] = prev;
            prev = head;
            head = head->next;
        }
    }
    
    ListNode *getPrev(ListNode *curr)
    {
        return mp[curr];
    }
    ListNode *getTail()
    {
        return tail;
    }
};


class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        Node *A = new Node(l1);
        Node *B = new Node(l2);
        
        ListNode *f = A->getTail();
        ListNode *s = B->getTail();
        
        ListNode *res = NULL;
        
        int carry = 0;
        
        while(f != NULL && s != NULL)
        {
            int sum = f->val + s->val + carry;
            if(res == NULL)
                res = new ListNode(sum % 10);
            else
            {
                ListNode *ptr = new ListNode(sum % 10);
                ptr->next = res;
                res = ptr;
            }
            
            carry = sum/10;
            f = A->getPrev(f);
            s = B->getPrev(s);
        }
        
        while(f != NULL)
        {
            int sum = carry + f->val;
            ListNode *ptr = new ListNode(sum % 10);
            ptr->next = res;
            res = ptr;
            carry = sum/10;
            f = A->getPrev(f);
        }
        
        while(s != NULL)
        {
            int sum = carry + s->val;
            ListNode *ptr = new ListNode(sum % 10);
            ptr->next = res;
            res = ptr;
            carry = sum/10;
            s = B->getPrev(s);
        }
        
        if(carry)
        {
            ListNode *ptr = new ListNode(1);
            ptr->next = res;
            res = ptr;
        }
        
        return res;
    }
};
