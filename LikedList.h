struct Node{
	int data;
	Node *next;
};
struct LinkedList{
	Node *pHead;
	Node *pTail;
	LinkedList(){
		pHead = NULL;
		pTail = NULL;
	}
	bool Empty(){
		return (pHead == NULL);
	}
	int Length(){
		int count=0;
		Node *node = pHead;
		while(node != NULL){
			count++;
			node = node->next;
		}
		return count;
	}
	Node* CreateNode(int value){
		Node *node = new Node;
		Node->data = value;
		node->next = NULL;
		return node;
	}
	void AddHead(Node *node){
		if (pHead == NULL){
			pHead = node;
			pTail = node;
		}
		else{
			node->next = pHead;
			pHead = node;
		}
	}
	void AddTail(Node *node){
		if(pHead == NULL){
			pHead = node;
			pTail = node;
		}
		else{
			pTail->next = node;
			pTail = node;
		}
	}
	void DelTail(){
		
	}
	~LinkedList(){
		while(node != NULL){
			Node *node = pHead;
			pHead = pHead->next;
			delete node;
		}
	}
};