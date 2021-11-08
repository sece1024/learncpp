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

# 101对称二叉树

[101. 对称二叉树 - 力扣（LeetCode） (leetcode-cn.com)](https://leetcode-cn.com/problems/symmetric-tree/)

给定一个二叉树，检查它是否是镜像对称的。

 

例如，二叉树 `[1,2,2,3,4,4,3] `是对称的。

    	1
       / \
      2   2
     / \ / \
    3  4 4  3



但是下面这个 `[1,2,2,null,3,null,3]` 则不是镜像对称的:

    	1
       / \
      2   2
       \   \
       3    3

## 递归

- The Tree is symmetry when root is NULL
- Otherwise it's `leftchild.val == rightchild.val` and left child tree are symmetric with right child tree
- And root's left child tree's left child symmetric with root's right child tree's right child, root's left child tree's right child symmetric with root's right child tree's left child.

### Python

执行用时: **32 ms**

内存消耗: **15 MB**

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isSymmetric(self, root: TreeNode) -> bool:
        if root == None:
            return True
        return self.symmetric(root.left, root.right)
        
    
    def symmetric(self, t1: TreeNode, t2: TreeNode)->bool:
        if t1 == None and t2 == None:
            return True
        if t1 == None or t2 == None:
            return False
        if t1.val != t2.val:
            return False
        return self.symmetric(t1.left, t2.right) and self.symmetric(t1.right, t2.left)
```

### C

执行用时：**0 ms**

内存消耗：**6.6 MB**

```c
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isSymmetric(self, root: TreeNode) -> bool:
        if root == None:
            return True
        return self.symmetric(root.left, root.right)
        
    
    def symmetric(self, t1: TreeNode, t2: TreeNode)->bool:
        if t1 == None and t2 == None:
            return True
        if t1 == None or t2 == None:
            return False
        if t1.val != t2.val:
            return False
        return self.symmetric(t1.left, t2.right) and self.symmetric(t1.right, t2.left)
```

# 102二叉树的层序遍历

[102. 二叉树的层序遍历](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)

给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。

示例：
二叉树：[3,9,20,null,null,15,7],

    	3
       / \
      9  20
        /  \
       15   7

返回其层序遍历结果：

```
[
  [3],
  [9,20],
  [15,7]
]
```

## 迭代

### 使用队列

Queue q1 save nodes had been visited.

Queue q2 save childs of nodes in q1's node.

#### Python

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        if root is None:
            return []
        q = [root]
        q2 = []
        temp = []
        result = [[root.val]]
        while q:
            item = q.pop(0)
            if item.left:
                q2.append(item.left)
                temp += [item.left.val]
            if item.right:
                q2.append(item.right)
                temp += [item.right.val]
            if not q:
                q = q2
                q2 = []
                if temp:
                    result.append(temp)
                    temp = []
        return result

```

C

```c

```

# 104.二叉树的最大深度

给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。

示例：
给定二叉树 [3,9,20,null,null,15,7]，

    	3
       / \
      9  20
        /  \
       15   7

返回它的最大深度 3 。

## 错误解法

由于之前学了利用栈遍历二叉树，所以首先想到了使用遍历的方法：

`stack` 保存节点

`deep` 保存当前深度

`m = deep if deep>m else m` 保存最大深度

-  在将左子树入栈的时候，该方法似乎没有问题

  但是在遍历右子树，将栈顶元素出栈，`deep -= 1`后就不行了。

- 比如，对于只有右子树的一个单链表结构的树，`deep`始终在0和1之间循环。

## 正确解法

### 递归

**递归出口：**

单个节点深度为1，空节点深度为0

**所以**

最大深度 `deep = max(maxDeepth(root.left), maxDeepth(root.right)) + 1`

### BFS广度优先搜索

使用列表保存每一层节点，每遍历一层就将深度`deep`加一。

###  **代码**

#### 递归

##### **Python**

执行用时: **52 ms**

内存消耗: **16.6 MB**

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        if root is None:
            return 0
        if  not (root.left or root.right):
            return 1
        
        return max(self.maxDepth(root.left), self.maxDepth(root.right)) + 1
```

##### C

执行用时: **4 ms**

内存消耗: **8 MB**

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int max(int a, int b){
    return a>b? a : b;
}
int maxDepth(struct TreeNode* root){
    if(root == NULL){
        return 0;
    }
    if(root->left == NULL && root->right == NULL){
        return 1;
    }
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
```

#### BFS

##### Python

执行用时: **36 ms**

内存消耗: **16 MB**

```python
class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        if root is None:
            return 0
        if  not (root.left or root.right):
            return 1
        stack = [root]
        deep = 0
        while stack:
            deep += 1
            tempStack = []
            for i in range(len(stack)):
                if stack[i].left:
                    tempStack.append(stack[i].left)
                if stack[i].right:
                    tempStack.append(stack[i].right)
            stack = tempStack

        return deep
```

#### 

# 105从前序与中序遍历序列构造二叉树

[105 ](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

给定一棵树的前序遍历 preorder 与中序遍历  inorder。请构造二叉树并返回其根节点。

 ![](https://assets.leetcode.com/uploads/2021/02/19/tree.jpg)

示例 1:

```
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
```

## 递归

- 从preorder获取根节点root
- 从inorder获取root边的序列left和right
- 使用新的序列递归生成root的左右子树

### Python

执行用时：332 ms, 在所有 Python3 提交中击败了5.15%的用户

内存消耗：87.3 MB, 在所有 Python3 提交中击败了13.29%的用户

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        root = TreeNode()
        if not preorder:
            return None

        if len(preorder) == 1:
            root.val = preorder[0]
            return root
        
        root.val = preorder[0]
        left = []
        right = []
        index = 0
        for i in range(len(inorder)):
            if inorder[i] == root.val:
                index = i
                left = inorder[:i]
                right = inorder[i+1:] if i != len(inorder) - 1 else []
                break
        root.left = self.buildTree(preorder[1:1+len(left)], left)
        root.right = self.buildTree(preorder[1+len(left):] , right)

        return root;


```



# 114二叉树展开为链表

[114. ](https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/)

给你二叉树的根结点 root ，请你将它展开为一个单链表：

展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
展开后的单链表应该与二叉树 先序遍历 顺序相同。


示例 1：

```
输入：root = [1,2,5,3,4,null,6]
输出：[1,null,2,null,3,null,4,null,5,null,6]
```

示例 2：

```
输入：root = []
输出：[]
```

示例 3：

```
输入：root = [0]
输出：[0]
```


提示：

树中结点数在范围 [0, 2000] 内
-100 <= Node.val <= 100


进阶：你可以使用原地算法（O(1) 额外空间）展开这棵树吗？

## 普通的先序遍历

先序遍历一遍，将所有节点保存在列表中，在遍历一便列表将root变成线性结构。

### Python

执行用时：20 ms, 在所有 Python3 提交中击败了99.88%的用户

内存消耗：14.7 MB, 在所有 Python3 提交中击败了99.03%的用户

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def flatten(self, root: TreeNode) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        if not root:
            return
        if root.left is None and root.right is None:
            return
        else:
            p = root
            stack = []
            stack2 = []
            while stack or p:
                if p:
                    stack.append(p)
                    stack2.append(p)
                    p = p.left
                else:
                    p = stack.pop()
                    p = p.right
            p = stack2[0]
            for item in stack2:
                if item == root:
                    p.left = None
                else:
                    p.left = None
                    p.right = item
                    p = p.right
                
                    
```

# 226翻转二叉树

#### [226](https://leetcode-cn.com/problems/invert-binary-tree/)

翻转一棵二叉树。

示例：

输入：

          4
        /   \
      2     7
     / \   / \
    1   3 6   9

输出：

          4
        /   \
      7     2
     / \   / \
    9   6 3   1

备注:
这个问题是受到 Max Howell 的 原问题 启发的 ：

>  谷歌：我们90％的工程师使用您编写的软件(Homebrew)，但是您却无法在面试时在白板上写出翻转二叉树这道题，这太糟糕了。



## 普通递归

### python

执行用时：36 ms, 在所有 Python3 提交中击败了34.53%的用户

内存消耗：14.8 MB, 在所有 Python3 提交中击败了93.84%的用户

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        if root is None or (root.left is None and root.right is None):
            return root
        temp = self.invertTree(root.right) 
        root.right = self.invertTree(root.left)
        root.left = temp
        return root

```

