
#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the BST
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {  // If the tree is empty, create a new node
        return createNode(value);
    }

    if (value < root->data) {  // If value is smaller, insert in the left subtree
        root->left = insert(root->left, value);
    } else if (value > root->data) {  // If value is greater, insert in the right subtree
        root->right = insert(root->right, value);
    }

    return root;  // Return the unchanged root pointer
}

// Function to search for a node in the BST
struct Node* search(struct Node* root, int value) {
    if (root == NULL || root->data == value) {  // Base case: root is null or value is found
        return root;
    }

    if (value < root->data) {  // Search in the left subtree
        return search(root->left, value);
    }

    return search(root->right, value);  // Search in the right subtree
}

// Function to find the minimum value node in the BST
struct Node* findMin(struct Node* root) {
    struct Node* current = root;
    while (current && current->left != NULL) {  // Traverse to the leftmost node
        current = current->left;
    }
    return current;
}

// Function to delete a node in the BST
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL) {  // Base case: tree is empty
        return root;
    }

    if (value < root->data) {  // If value is smaller, move to the left subtree
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {  // If value is greater, move to the right subtree
        root->right = deleteNode(root->right, value);
    } else {  // Node to be deleted found
        // Case 1: Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Node with two children
        struct Node* temp = findMin(root->right);  // Find the minimum value in the right subtree
        root->data = temp->data;  // Replace node's data with the successor's data
        root->right = deleteNode(root->right, temp->data);  // Delete the successor
    }

    return root;
}

// Function for in-order traversal (Left, Root, Right)
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Function for pre-order traversal (Root, Left, Right)
void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Function for post-order traversal (Left, Right, Root)
void postOrder(struct Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n*** Binary Search Tree Menu ***\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Search Node\n");
        printf("4. In-Order Traversal\n");
        printf("5. Pre-Order Traversal\n");
        printf("6. Post-Order Traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("%d inserted into the tree.\n", value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("%d deleted from the tree.\n", value);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                struct Node* result = search(root, value);
                if (result != NULL) {
                    printf("%d found in the tree.\n", value);
                } else {
                    printf("%d not found in the tree.\n", value);
                }
                break;
            case 4:
                printf("In-Order Traversal: ");
                inOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Pre-Order Traversal: ");
                preOrder(root);
                printf("\n");
                break;
            case 6:
                printf("Post-Order Traversal: ");
                postOrder(root);
                printf("\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
