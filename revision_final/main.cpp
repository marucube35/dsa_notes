#include "header.h"

int main()
{
	int a[] = {8, 5, 10, 3, 7, 9};
	int n = sizeof(a) / sizeof(a[0]);

	NODE *root = createAVLTree(a, n);

	levelOrder(root);
    NODE* prev = nullptr;
	cout << isBST(root,prev) << endl;

	system("pause");
	return 0;
}