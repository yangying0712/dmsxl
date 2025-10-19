class MyLinkedList {
private:
    ListNode* head; //哨兵节点
    int size;
public:
    //定义链表节点
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    MyLinkedList() {
        head = new ListNode(0);
        size = 0;
    }
    
    int get(int index) {
        //边界检查
        if(index < 0 || index >= size) return -1;
        
        ListNode* current = head->next; //跳过哨兵节点       
        
        //遍历链表
        while(index--){
            if(current->next == NULL) return -1; //索引越界
            current = current->next;
        }

        //返回值
        return current->val;
    }
    
    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head->next;
        head->next = newNode;
        size++;
    }
    
    void addAtTail(int val) {
        ListNode* newNode = new ListNode(val);
        ListNode* current = head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
        size++;
    }
    
    void addAtIndex(int index, int val) {
        ListNode* newNode = new ListNode(val);
        if(index < 0 || index > size) return;
        if(index == 0) {
            addAtHead(val);
            return;
        }
        if(index == size){
            addAtTail(val);
            return;
        }

        ListNode* current = head;
        while(index--){
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if(index < 0 || index >= size) return;
        ListNode* current = head;
        while(index--){
            current = current->next;
        }
        LinkedNode* tmp = cur->next;
        current->next = current->next->next;
        size--; 
        delete tmp;
        tmp = NULL;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */