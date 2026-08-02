#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 1009

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *table[TABLE_SIZE] = {NULL};

int hash(int key)
{
    if (key < 0)
        key = -key;

    return key % TABLE_SIZE;
}

int hasDuplicate(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int index = hash(arr[i]);

        Node *temp = table[index];

        while (temp != NULL)
        {
            if (temp->data == arr[i])
                return 1;

            temp = temp->next;
        }

        Node *newNode = (Node *)malloc(sizeof(Node));

        newNode->data = arr[i];
        newNode->next = table[index];
        table[index] = newNode;
    }

    return 0;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    if (hasDuplicate(arr, n))
        printf("\nDuplicate elements found.\n");
    else
        printf("\nAll elements are unique.\n");

    return 0;
}