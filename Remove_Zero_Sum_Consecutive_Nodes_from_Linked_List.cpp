// https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/

/*
Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such 
sequences.
After doing so, return the head of the final linked list.  You may return any such answer.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    unordered_map <int, ListNode *> mp;
    ListNode* removeZeroSumSublists(ListNode* head) 
    {
        ListNode *temp = head;
        int sum = 0;
        mp[0] = head;
        while(temp)
        {
            sum += temp->val;
            if(mp.count(sum))
            {
                if(sum != 0)
                    mp[sum]->next = temp->next;
                else
                    head = temp->next;
            }
            else
                mp[sum] = temp;
            temp = temp->next;
        }
        return head;
    }
};
