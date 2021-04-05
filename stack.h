struct Node{
	int data;
	Node *next;
};
struct Stack{
	Node *top;
	Stack(){
		top = NULL;
	}
};
