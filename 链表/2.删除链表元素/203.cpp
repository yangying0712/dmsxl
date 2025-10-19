/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
    //设置哨兵 
    ListNode* sentinel = new ListNode(0); 
    sentinel->next = head;
    ListNode* cur = sentinel;
    while(cur->next != nullptr){
        if(cur->next->val == val){
            ListNode* temp = cur->next;
            cur->next = cur->next->next;
            delete temp;
        }else{
            cur = cur->next;
        }
    }
    return sentinel->next;
    //设置哨兵 
    //遍历链表，删除指定值节点
    //返回新的头节点
};