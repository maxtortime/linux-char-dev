struct Node {
	int data;
	struct Node* next;
};

void Enqueue(int x);
void Dequeue(void);
int Front(void);
void Print(void); // prints whole queue entry