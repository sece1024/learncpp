# 98. 验证二叉搜索树

[98. 验证二叉搜索树](https://leetcode-cn.com/problems/validate-binary-search-tree/)

给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

有效 二叉搜索树定义如下：

节点的左子树只包含 小于 当前节点的数。
节点的右子树只包含 大于 当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。

![](https://assets.leetcode.com/uploads/2020/12/01/tree1.jpg)

```
输入：root = [2,1,3]
输出：true
```

## 211101——解题失败



### 递归

遍历整个树，看是否违反二叉搜索树的规则——左小右大。

递归的遍历？

**二叉树的数组表示法**

对于数组`a`的某节点`a[i]`它的左右子树分别为`a[2*i + 1]` 和 `a[2*i + 2]`

**二叉搜索树**

左子树小，右子树大。
比较的不仅仅是子树这一个节点，而是所有子树。

**递归判断**

* 没有子树 -> True
* 有子树
	* 符合规则 -> True
	* 不符合 -> return False

### 中序遍历

因为二叉搜索树的特性，中序遍历得到的序列一定是有序的。



### 错误解法

#### Python-递归

没有考虑到类似于`[5,4,6,null,null,3,7]`的情况，3是6的左子树，它却小于根节点5

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isValidBST(self, root: TreeNode) -> bool:
        if root.left == None and root.right == None:
            return True
        return self.validLeft(root) and self.validRight(root)
    
    def validLeft(self, root: TreeNode， v: int)->bool:
        if root.left == None:
            return True
        
        if root.left.val >= root.val:
            return False
        return self.isValidBST(root.left)
    def validRight(self, root: TreeNode)->bool:
        if root.right == None:
            return True
        
        if root.right.val <= root.val:
            return False
        return self.isValidBST(root.right)
```

#### Python-中序遍历

leetcode上对于[0,-1]，调试时输出是true，提交时输出却是false？

```python
class Solution:
    MIN = -2**31 - 1
    l = []
    def isValidBST(self, root: TreeNode) -> bool:
        if root.left == None and root.right == None:
            return True
        self.visitLeft(root)
        length = len(self.l)
        for i in range(length):
            if self.MIN < self.l[i]:
                self.MIN = self.l[i]
            else:
                return False
        
        return True

    def visitLeft(self, root: TreeNode)->int:
        if root.left == None and root.right == None:
            return root.val

        if root.left != None:
            self.l.append(self.visitLeft(root.left))
        self.l.append(root.val)
        if root.right != None:
            self.l.append(self.visitLeft(root.right))
        return 0
```

## 211103——成功

### 非递归

参考《数据结构》遍历二叉树章节，使用栈非递归地遍历整棵树。

对于栈stack，用到的基本操作有：

1. 判断栈是否为空
2. 入栈
3. 出栈

**主要步骤**:

1. 循环地将节点的左子节点入栈
2. 没有左子树时，栈顶节点出栈
3. 将该节点右子节点入栈，回到步骤1
4. 没有子节点时，栈顶节点出栈

### 注意

C语言中没有引用传递，当使用`stack = pop(stack)`时可以得到新的栈，而使用`pop(stack)`不会改边`pop`外面的`stack`值。

### 代码

#### Python

```python
def isValidBST(self, root: TreeNode) -> bool:
    mini = -(2**32+1)
    result = True
    stack = []
    p = root

    while len(stack) > 0 or p != None:
        if p != None:
            stack.append(p)
            p = p.left
        else:
            p = stack.pop()
            if p == None:
                return
            if mini < p.val:
                mini = p.val
            else:
                result = False
                break
            p = p.right
    return result
```

#### C

##### 自定义栈

执行用时：4 ms, 在所有 C 提交中击败了94.07%的用户

内存消耗：9.2 MB, 在所有 C 提交中击败了8.96%的用户

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct lineStack
{
    struct TreeNode node;
    struct lineStack * next;
}lineStack;

lineStack* push(lineStack * stack, struct TreeNode t)
{
    lineStack * line = (lineStack*)malloc(sizeof(lineStack));
    line->node = t;
    line->next = stack;
    stack=line;
    return stack;
}
lineStack* pop(lineStack * stack)
{
    if(stack)
    {
        stack = stack->next;
    }
    return stack;
}
bool isEmpty(lineStack * stack)
{
    return stack == NULL;
}
bool isValidBST(struct TreeNode* root){
    double mini = -pow(2,32)-1;
    lineStack * stack = NULL;
    struct TreeNode * p = root;
    while(stack != NULL || p != NULL){
        if(p != NULL){
            stack = push(stack, *p);
            p = p->left;
        }else{
            p = &(stack->node);
            stack = pop(stack);
            if (mini < p->val){
                //printf("p-val = %d",p->val);
                mini = (double)p->val;
            }else{
                return 0;
            }
            p = p->right;
        }
    }
    return 1;
}
```

