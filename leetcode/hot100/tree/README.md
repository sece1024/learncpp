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

[226](https://leetcode-cn.com/problems/invert-binary-tree/)

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

# 236二叉树的最近公共祖先

[236. ](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

>  [百度百科](https://baike.baidu.com/item/最近公共祖先/8918834?fr=aladdin)中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
```

**示例 3：**

```
输入：root = [1,2], p = 1, q = 2
输出：1
```

 

**提示：**

- 树中节点数目在范围 `[2, 105]` 内。
- `-109 <= Node.val <= 109`
- 所有 `Node.val` `互不相同` 。
- `p != q`
- `p` 和 `q` 均存在于给定的二叉树中。

## DFS递归

遍历整棵树，返回子树中是否存在目标节点p、q。

当左右子树同时返回true，或者t为p或q且有一个子树是p或q，则表示当前节点就是最近公共祖先。



### Python

执行用时：44 ms, 在所有 Python3 提交中击败了99.86%的用户

内存消耗：28.1 MB, 在所有 Python3 提交中击败了12.82%的用户

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:

    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        self.ancestor = root
        # 判断孩子中是否有p或q
        def dfs(r: 'TreeNode', p: 'TreeNode', q: 'TreeNode')->bool:
            lChild = False
            rChild = False
            if r is None:
                return False
            if r.left:
                lChild = dfs(r.left, p, q)
            if r.right:
                rChild = dfs(r.right, p, q)
            if (lChild and rChild) or ((r == p or r == q) and (lChild or rChild)):
                self.ancestor = r
            return r == p or r == q or lChild or rChild
        dfs(root, p, q)
        return self.ancestor
```

### C

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct TreeNode *ancestor = root;
    bool dfs(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q){
        bool lChild = false;
        bool rChild = false;
        if(root == NULL)    return false;
        if(root->left)  lChild = dfs(root->left, p, q);
        if(root->right) rChild = dfs(root->right, p, q);
        if(lChild&&rChild || (root == p || root == q ) && (lChild || rChild))   ancestor = root;
        return root == p || root == q || lChild || rChild;
    }
    dfs(root, p, q);
    return ancestor;
}
```

# 297二叉树的序列化与反序列化

[297. ](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/)

难度困难676

序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

**提示:** 输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 [LeetCode 序列化二叉树的格式](https://leetcode-cn.com/faq/#binary-tree)。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/09/15/serdeser.jpg)

```
输入：root = [1,2,3,null,null,4,5]
输出：[1,2,3,null,null,4,5]
```

**示例 2：**

```
输入：root = []
输出：[]
```

**示例 3：**

```
输入：root = [1]
输出：[1]
```

**示例 4：**

```
输入：root = [1,2]
输出：[1,2]
```

 

**提示：**

- 树中结点数在范围 `[0, 104]` 内
- `-1000 <= Node.val <= 1000`

## 层序遍历

看了别人的代码才意识到之前用两个栈进行层序遍历比较蠢。

关键点：序列化出来的不一定是完全二叉树，反序列画的时候不能简单的`i*2 + 1`或者 `i*2+2`,而是用`index += 2`的方式来获取数组中的值。

### Python

```python
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        if root is None:    return ''
        if not (root.left or root.right):  return str(root.val)

        self.result = ''
        def bfs(root):
            p = root
            stack1 = [root]
            while stack1:
                tempStack = stack1
                stack1 = []
                while tempStack:

                    p = tempStack.pop(0)
                    if not p:
                        self.result += '-1999'
                        self.result += '#'
                    else:
                        self.result += str(p.val)
                        self.result += '#'
                        stack1.append(p.left if p.left else False) 
                        stack1.append(p.right if p.right else False)
                    # print(self.result)
                
        bfs(root)
        return self.result

        

    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        data.strip()
        if data == '':  return None
        li = data.split('#')
        inp = []
        for i in li:
            if i.strip() != '':
                inp.append(int(i))
        self.root = TreeNode(inp[0])

        if len(inp) == 1:
            return self.root
        

        def buildTree(arr:[int]):
            length = len(arr)
            # print(arr,end='\n')
            index = 0
            self.root = TreeNode(arr[0])
            queue = [self.root]
            index = 1
            while queue:
                p = queue.pop(0)
                if p:
                    p.left = TreeNode(int(arr[index])) if arr[index]>= -1000 and arr[index] <= 1000 else None
                    p.right = TreeNode(int(arr[index + 1])) if arr[index+1]>= -1000 and arr[index+1] <= 1000 else None
                    queue.append(p.left)
                    queue.append(p.right)
                    index += 2
            # nodeList = []

            # for i in range(length):
            #     if arr[i] < -1000 or arr[i] > 1000:
            #         nodeList.append(None)
            #     else:
            #         nodeList.append(TreeNode(arr[i]))
                
            # for j in range(length):
            #     if nodeList[j]:
            #         if j*2+1 < length:
            #             nodeList[j].left = nodeList[j*2 + 1]
            #         else:
            #             nodeList[j].left = None
            #         if j*2 + 2 < length:
            #             nodeList[j].right = nodeList[j*2 + 2]
            #         else:
            #             nodeList[j].right = None
                    
            #         # print(nodeList[j])
            # self.root = nodeList[0]
        buildTree(inp)
        return self.root

                

        

        

# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# ans = deser.deserialize(ser.serialize(root))
```

# 337打家劫舍 III

[337. ](https://leetcode-cn.com/problems/house-robber-iii/)

难度中等1033

在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

**示例 1:**

```
输入: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \ 
     3   1

输出: 7 
解释: 小偷一晚能够盗取的最高金额 = 3 + 3 + 1 = 7.
```

**示例 2:**

```
输入: [3,4,5,1,3,null,1]

     3
    / \
   4   5
  / \   \ 
 1   3   1

输出: 9
解释: 小偷一晚能够盗取的最高金额 = 4 + 5 = 9.
```

## 错误解法

层序遍历，分别求奇数层和偶数层的节点和。

错误代码

**64 / 124** 个通过测试用例

```python
class Solution:
    def rob(self, root: TreeNode) -> int:
        if not root:
            return 0
        if root.left == None and root.right == None:
            return root.val
        # 不偷当前节点,最大值
        self.f = {}
        # 偷当前节点，最大值
        self.g = {}
        def dfs(root: TreeNode):
            if not root:
                return None
            dfs(root.left)
            dfs(root.right)
            lFChild = self.f[root.left] if self.f.get(root.left) else 0
            rFChild = self.f[root.right] if self.f.get(root.right) else 0
            lGChild = self.g[root.left] if self.g.get(root.left) else 0
            rGChild = self.g[root.right] if self.g.get(root.right) else 0
            
            self.f[root] = max(lFChild+rFChild, lGChild+rGChild)
            self.g[root] = root.val + lFChild + rFChild
        dfs(root)
        return max(self.f[root], self.g[root])
```



## DFS

自底向上使用字典保存每一个节点偷或不偷的最大价值。

**注意，需要考虑两个子树一个偷一个不偷的情况**

### Python

执行用时：48 ms, 在所有 Python3 提交中击败了59.27%的用户

内存消耗：18 MB, 在所有 Python3 提交中击败了9.54%的用户

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rob(self, root: TreeNode) -> int:
        if not root:
            return 0
        if root.left == None and root.right == None:
            return root.val
        # 不偷当前节点,最大值
        self.f = {}
        # 偷当前节点，最大值
        self.g = {}
        def dfs(root: TreeNode):
            if not root:
                return None
            dfs(root.left)
            dfs(root.right)
            lFChild = self.f[root.left] if self.f.get(root.left) else 0
            rFChild = self.f[root.right] if self.f.get(root.right) else 0

            lGChild = self.g[root.left] if self.g.get(root.left) else 0
            rGChild = self.g[root.right] if self.g.get(root.right) else 0
            # 需要考虑左子树和右子树一个偷一个不偷的情况
            self.f[root] = max(max(lFChild+rFChild, lGChild+rGChild), max(lFChild+rGChild, lGChild+rFChild))
            # print(root,end='\t')
            # print(self.f[root])
            self.g[root] = root.val + lFChild + rFChild
        dfs(root)
        return max(self.f[root], self.g[root])
```

# 543二叉树的直径

## DFS

自底向上保存当前节点为端点、当前节点不为端点时的直径字典，同时更新最大直径。

### Python

执行用时：52 ms, 在所有 Python3 提交中击败了16.80%的用户

内存消耗：17.4 MB, 在所有 Python3 提交中击败了5.21%的用户

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def diameterOfBinaryTree(self, root: TreeNode) -> int:
        if not root:
            return 0
        if root.left is None and root.right is None:
            return 0
        # 当前节点为端点
        self.isEnd = {}
        # 当前节点不是端点
        self.notEnd = {}
        self.Max = -999
        def dfs(root:TreeNode):
            if not root:
                self.isEnd[root] = 0
                self.notEnd[root] = 0
                return
            dfs(root.left)
            dfs(root.right)
            lChildIsEnd= self.isEnd[root.left] 
            rChildIsEnd = self.isEnd[root.right] 

            # lChildNot = notEnd[root.left] if notEnd.get(root.left) else 0
            # rChildNot = notEnd[root.right] if notEnd.get(root.right) else 0

            if root.left or root.right:
                self.isEnd[root] = 1
            else:
                self.isEnd[root] = 0

            self.isEnd[root] += max(lChildIsEnd, rChildIsEnd)
            self.notEnd[root] = 0
            if root.left:
                self.notEnd[root] += 1
            if root.right:
                self.notEnd[root] += 1
            self.notEnd[root] += lChildIsEnd + rChildIsEnd

            self.Max = max(self.isEnd[root], self.notEnd[root]) if max(self.isEnd[root], self.notEnd[root]) > self.Max else self.Max

        dfs(root)
        return self.Max

            
```



# 437路径总和 III

[437. ](https://leetcode-cn.com/problems/path-sum-iii/)

难度中等1140

给定一个二叉树的根节点 `root` ，和一个整数 `targetSum` ，求该二叉树里节点值之和等于 `targetSum` 的 **路径** 的数目。

**路径** 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/04/09/pathsum3-1-tree.jpg)

```
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条，如图所示。
```

**示例 2：**

```
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3
```

 

**提示:**

- 二叉树的节点个数的范围是 `[0,1000]`
- `-109 <= Node.val <= 109` 
- `-1000 <= targetSum <= 1000` 

## 双递归

看了别人的解法，比较考验逻辑。

- `calculateSum(TreeNode, int)`
  - 计算以输入节点为起点的路径是否满足要求，是则`count += 1`
  - 对子结点调用`calculateSum`，将返回值与`count`相加
- `pathSum(TreeNode, int)`
  - 计算以当输入节点为根节点的树，是否有和为target的路径

### Python

执行用时：588 ms, 在所有 Python3 提交中击败了37.43%的用户

内存消耗：16.3 MB, 在所有 Python3 提交中击败了50.25%的用户

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def pathSum(self, root: TreeNode, targetSum: int) -> int:
        if not root:
            return 0

        def calculateSum(r: TreeNode, tar: int)->int:
            if not r:
                return 0
            count = 0
            tar -= r.val
            if tar == 0:
                count += 1
            return count + calculateSum(r.left, tar) + calculateSum(r.right, tar)

        return calculateSum(root, targetSum) + self.pathSum(root.left, targetSum) + self.pathSum(root.right, targetSum)

```

### C

执行用时：28 ms, 在所有 C 提交中击败了37.00%的用户

内存消耗：8.2 MB, 在所有 C 提交中击败了26.98%的用户

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int calculateSum(struct TreeNode* root, int target){
    if(root == NULL)    return 0;
    int count = 0;
    target -= root->val;
    if(!target) count = 1;

    return count + calculateSum(root->left, target) + calculateSum(root->right, target);
}
int pathSum(struct TreeNode* root, int targetSum){
    if(root == NULL)    return 0;

    return calculateSum(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
}
```

# 538把二叉搜索树转换为累加树

[538. ](https://leetcode-cn.com/problems/convert-bst-to-greater-tree/)

难度中等608

给出二叉 **搜索** 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），使每个节点 `node` 的新值等于原树中大于或等于 `node.val` 的值之和。

提醒一下，二叉搜索树满足下列约束条件：

- 节点的左子树仅包含键 **小于** 节点键的节点。
- 节点的右子树仅包含键 **大于** 节点键的节点。
- 左右子树也必须是二叉搜索树。

**注意：**本题和 1038: https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/ 相同

 

**示例 1：**

**![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/05/03/tree.png)**

```
输入：[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
输出：[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
```

**示例 2：**

```
输入：root = [0,null,1]
输出：[1,null,1]
```

**示例 3：**

```
输入：root = [1,0,2]
输出：[3,3,2]
```

**示例 4：**

```
输入：root = [3,2,4,1]
输出：[7,9,4,10]
```

 

**提示：**

- 树中的节点数介于 `0` 和 `104` 之间。
- 每个节点的值介于 `-104` 和 `104` 之间。
- 树中的所有值 **互不相同** 。
- 给定的树为二叉搜索树。

## 右子树DFS

使用一个变量保存当前节点和即可。

### Python

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None
        # 大于等于该节点的节点和
        self.nowMax = 0
        def test(r:Optional[TreeNode]):
            if not r:
                return
            test(r.right)
            r.val += self.nowMax
            self.nowMax = r.val
            test(r.left)

        # 向右深度优先遍历
        # def dfsRight(r:Optional[TreeNode])->int:
        #     if not r:
        #         return 0
        #     maxValueInRight = dfsRight(r.right)
        #     r.val += maxValueInRight
        #     maxValueInLeft = max(dfsRight(r.left), r.val)
        #     if r.left:
        #         r.left.val += r.val

        #     return maxValueInLeft + maxValueInRight 

        test(root)
        return root
            
```

### C

执行用时：20 ms, 在所有 C 提交中击败了76.89%的用户

内存消耗：13.6 MB, 在所有 C 提交中击败了36.13%的用户

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int* NowMax = NULL;
void dfsRF(struct TreeNode* root){
    if(root==NULL)  return NULL;
    dfsRF(root->right);
    root->val += *NowMax;
    *NowMax = root->val;
    dfsRF(root->left);
}
struct TreeNode* convertBST(struct TreeNode* root){
    if(root == NULL)    return NULL;
    int zero = 0;
    NowMax = &zero;
    dfsRF(root);
    return root;
}
```

# 617合并二叉树

[617. ](https://leetcode-cn.com/problems/merge-two-binary-trees/)

难度简单807

给定两个二叉树，想象当你将它们中的一个覆盖到另一个上时，两个二叉树的一些节点便会重叠。

你需要将他们合并为一个新的二叉树。合并的规则是如果两个节点重叠，那么将他们的值相加作为节点合并后的新值，否则**不为** NULL 的节点将直接作为新二叉树的节点。

**示例 1:**

```
输入: 
	Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
输出: 
合并后的树:
	     3
	    / \
	   4   5
	  / \   \ 
	 5   4   7
```

**注意:** 合并必须从两个树的根节点开始。



## 层序遍历

重点是保证层序遍历时每一层节点数相同，对于左树中没有，右树中有，或者左树中有，右数中没有的情况，用值为0的节点填充。

### Python

执行用时：88 ms, 在所有 Python3 提交中击败了6.18%的用户

内存消耗：15.5 MB, 在所有 Python3 提交中击败了23.24%的用户

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def mergeTrees(self, root1: TreeNode, root2: TreeNode) -> TreeNode:
        if not(root1 or root2):
            return None
        if not root1 and root2:
            temp = root1
            root1 = root2
            root2 = temp
        
        queue1 = [root1]
        queue2 = [root2]

        while queue1 or queue2:
            p1 = queue1.pop(0)
            p2 = queue2.pop(0)

            if p1 and p2:
                p1.val += p2.val
            if p1:
                if not p1.left and (p2 and p2.left):
                    p1.left = TreeNode(0)
                if not p1.right and (p2 and p2.right):
                    p1.right = TreeNode(0)
            if p2:
                if not p2.left and (p1 and p1.left):
                    p2.left = TreeNode(0)
                if not p2.right and (p1 and p1.right):
                    p2.right = TreeNode(0)
            if p1 and p2:
                queue1.append(p1.left)
                queue1.append(p1.right)
                queue2.append(p2.left)
                queue2.append(p2.right)
        return root1




        
```

# 124二叉树中的最大路径和

[124.](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)

难度困难1286

**路径** 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 **至多出现一次** 。该路径 **至少包含一个** 节点，且不一定经过根节点。

**路径和** 是路径中各节点值的总和。

给你一个二叉树的根节点 `root` ，返回其 **最大路径和** 。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/13/exx1.jpg)

```
输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2020/10/13/exx2.jpg)

```
输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
```

 

**提示：**

- 树中节点数目范围是 `[1, 3 * 104]`
- `-1000 <= Node.val <= 1000`

## 递归

维护一个静态变量保存最大路径，自底向上计算已当节点为端点或者中间节点的最大值

### Python

执行用时：72 ms, 在所有 Python3 提交中击败了84.11%的用户

内存消耗：22.5 MB, 在所有 Python3 提交中击败了25.41%的用户

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        if not root:
            return -sys.maxsize
        if not(root.left or root.right):
            return root.val

        self.m = -999
        def dfs(r: TreeNode)->int:
            if not r:   return 0
            left = dfs(r.left)
            right = dfs(r.right)
            self.m = max(self.m, r.val, r.val + left, r.val + right, r.val + left + right)
            return max(r.val, r.val + left, r.val + right)
        dfs(root)
        return self.m
```

### C

```c
int f(struct TreeNode* r, int* p){
    if(r == NULL)   return 0;
    int left = f(r->left, p);
    int right = f(r->right, p);
    int result = left>right? left>0? r->val + left: r->val : right>0? r->val + right: r->val;
    *p = left>0 && right>0?left+right+r->val > *p? left+right+r->val: *p: result>*p? result: *p;

    return result;
}
int maxPathSum(struct TreeNode* root){
    if(root == NULL)    return NULL;
    int *m = malloc(sizeof(int));
    *m = -999;
    f(root, m);
    return *m;
}
```

