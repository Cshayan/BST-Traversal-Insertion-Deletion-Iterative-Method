#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int top1=-1;
int top2=-1;
int top=-1;
struct node
{
   struct node *left;
   int data;
   struct node *right;
};
struct node * insert(struct node *root, int item)
{
    struct node *x=root;
    struct node *par=NULL; //only for the first node it is set to null

    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    temp->data=item;
    temp->left=NULL;
    temp->right=NULL;

    while(x!=NULL)
    {
        par=x;
        if(item < x->data)
        {
            x=x->left;
        }
        else
        {
            x=x->right;
        }
    }

    if(par==NULL)
    {
        par=temp;
    }
    else if(item < par->data)
    {
        par->left=temp;
    }
    else
    {
        par->right=temp;
    }
    return par;
}
void preorder(struct node *root)
{
    struct node *stack[MAX],*temp;
    stack[++top]=root;    // push root into stack

    while(top!=-1)    //till the stack is not empty
    {
        temp=stack[top--];    // pop from stack
        if(temp!=NULL)
        {
            printf("%d\t",temp->data);   //display its value
            stack[++top]=temp->right;  //push right child into stack
            stack[++top]=temp->left;   //push left child into stack
        }
    }
}
void Inorder(struct node *root)
{
    struct node *stack[MAX];
    top=-1;
    while(top!=-1 || root!=NULL)
    {
        if(root!=NULL)
        {
            stack[++top]=root;
            root=root->left;
        }
        else
        {
            root=stack[top--];
            printf("%d\t",root->data);
            root=root->right;
        }
    }
}
int search(struct node *root,int item)
{
    while(root!=NULL)
    {
        if(item < root->data)
            root= root->left;
        else if(item > root->data)
            root= root->right;
        else
            return 1;
    }
    return 0;
}
void postOrderIterative(struct node *curr)
{
    struct node *stack1[MAX];
    struct node *stack2[MAX];
    struct node *ptr1, *ptr2;
    top1=-1; top2=-1;

    stack1[++top1]=curr;  //push root node to 1st stack
        while(top1!=-1)   //till the first stack is not empty
        {
            ptr1=stack1[top1--];   //pop from first stack
            stack2[++top2]=ptr1;   //push it to second stack
            if(ptr1->left!=NULL)   //if that node has both left  child
            {
                stack1[++top1]=ptr1->left;      //push them
                                                //in the 1st stack
            }
            if(ptr1->right!=NULL)         //has right child
            {
                stack1[++top1]=ptr1->right;
            }
        }

        //print the contents of second stack
        while(top2!=-1)
        {
            ptr2=stack2[top2--];  // pop from stack2
            printf("%d\t",ptr2->data);  //print the values
        }
}
void delete_leaf(struct node *ptr, struct node *par,int isLeft, struct node *root)
{
    if(par==NULL)    // if root node is to be deleted
       {
           free(ptr);
           root=NULL;
       }
       else
       {
           free(ptr);
           if(isLeft)
              par->left=NULL;
           else
              par->right=NULL;
       }
}
void delete_oneChild(struct node *ptr, struct node *par, int isLeft, struct node *root)
{
    struct node *childptr;

    if(ptr->left!=NULL)
        childptr=ptr->left;      // find the child of deleted value that is to be added with its grandfather
       else
         childptr=ptr->right;   // find the child of deleted value that is to be added with its grandfather

       if(par==NULL)        // node to be deleted is root
       {
           free(ptr);
           root=childptr;
       }
       else
       {
           if(isLeft)
            par->left=childptr;        // attach child to its grandfather
           else
            par->right=childptr;

            free(ptr);
       }
}
struct node *deleteNode(struct node *root,int item)
{
   struct node *par=NULL;
   struct node *ptr=root;
   int isLeft=0;
   while(ptr!=NULL)
   {
       //if less search in left subtree
       if(item < ptr->data)
       {
           par=ptr;
           isLeft=1;
           ptr=ptr->left;
       }
       // if more find it in right subtree
       else if(item > ptr->data)
       {
           par=ptr;
           isLeft=0;
           ptr=ptr->right;
       }
       else
        break;   // value found
   }

   if(ptr==NULL)     // if value to be deleted does not exists
   {
       printf("Value does not exits in the tree\n");
       return root;
   }

   //case 1:node having no child
   if(ptr->left==NULL && ptr->right==NULL)
   {
       delete_leaf(ptr,par,isLeft,root);
   }
   //case 2:node having only one child
   else if(ptr->left==NULL || ptr->right==NULL)
   {
       delete_oneChild(ptr,par,isLeft,root);
   }
   //case 3:node having two children
   else
   {
       struct node *parReplacement, *replacement;
       isLeft=1; //replacement is in the left subtree
       parReplacement= ptr;
       replacement= ptr->left;
       while(replacement->right != NULL)
       {
           parReplacement=replacement;
           replacement=replacement->right;
           isLeft=0;   // replacement is in the right subtree
       }
       ptr->data=replacement->data;

       if(replacement->left==NULL && replacement->right==NULL)
       {
           delete_leaf(replacement,parReplacement,isLeft,root);
       }
       else
       {
           delete_oneChild(replacement,parReplacement,isLeft,root);
       }
    }
    return root;
}


int main()
{
    // Let us construct the tree shown in above figure
    int tot;
    struct node *root=NULL;
    printf("\nEnter the total no of nodes to be inserted in BST:- ");
    scanf("%d",&tot);
    int i,item;
    printf("\nEnter the elements:-\n");
    scanf("%d",&item);
    root=insert(root,item);
    for(i=0;i<tot-1;i++)
    {
        scanf("%d",&item);
        insert(root,item);
    }
   printf("\nPre-order:- \n");
    preorder(root);
    printf("\n");
    printf("\nPost-order:- \n");
    postOrderIterative(root);
    printf("\n");
    printf("\nIn-order:- \n");
    Inorder(root);
      printf("\nEnter a value to be searched in the tree:- ");
    scanf("%d",&item);
    if(search(root, item))
    {
        printf("\nValue found in the tree\n");
    }
    else
    {
        printf("\nValue is not present in the tree\n");
    }
    printf("\nEnter the number of nodes to delete:- ");
    scanf("%d",&tot);

    for(i=0;i<tot;i++)
    {
        printf("\nEnter the element:- \n");
        printf("\n");
        scanf("%d",&item);
        root=deleteNode(root,item);
        printf("\nAfter deletion in-order traversal:-\n");
        Inorder(root);
    }



    return 0;
}
