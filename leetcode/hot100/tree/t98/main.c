#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}treeNode = {0 , NULL, NULL};;
typedef struct lineStack
{
    struct TreeNode node;
    struct lineStack * next;
}lineStack;

lineStack* push(lineStack * stack, struct TreeNode t)
{
    lineStack * line = (lineStack*)malloc(sizeof(lineStack));
    line->node = t;
    printf("push: %d\n", t.val);
    line->next = stack;
    stack=line;
    return stack;
}
struct TreeNode* pop2(lineStack * stack)
{
    struct TreeNode * result = NULL;
    if(stack)
    {
        result = &(stack->node);
        stack = stack->next;
        printf("pop up %d.\n",result->val);
        if(stack){
            printf("%d is in the Top.\n", stack->node.val);
        }
    }
    return result;
}
lineStack* _pop(lineStack * stack, struct TreeNode ** pp)
{
    if(stack)
    {
        *pp = &(stack->node);
        stack = stack->next;
        printf("pop up %d.\n",(*pp)->val);
        if(stack){
            printf("%d is in the Top.\n", stack->node.val);
        }
    }
    return stack;
}
lineStack* pop(lineStack * stack)
{
    if(stack)
    {
        struct TreeNode * p = &(stack->node);
        stack = stack->next;
        printf("pop up %d.\n",p->val);
        if(stack){
            printf("%d is in the Top.\n", stack->node.val);
        }
    }
    return stack;
}

_Bool isEmpty(lineStack * stack)
{
    return stack == NULL;
}
int main()
{
    double mini = -pow(2,32)-1;
    struct TreeNode node1 = {1, NULL, NULL};
    struct TreeNode root = {2, NULL, NULL};
    struct TreeNode node3 = {3, NULL, NULL};
    root.left = &node1;
    root.right = &node3;

    lineStack * stack = NULL;
    struct TreeNode * p = &root;

    while(!isEmpty(stack) || p != NULL){
        if(p != NULL){
            stack = push(stack, *p);
            p = p->left;
        }else{
            p = &(stack->node);
            stack = pop(stack);
            if(p == NULL){
                printf("p == NULL");
                return -1;
            }
            if (mini < p->val){
                mini = (double)p->val;
            }else{
                return 0;
            }
            p = p->right;
        }
    }
    printf("you are ok\n");
    return 1;
}
