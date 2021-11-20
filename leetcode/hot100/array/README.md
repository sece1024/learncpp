# 31下一个排列

[31. ](https://leetcode-cn.com/problems/next-permutation/)

难度中等1410

实现获取 **下一个排列** 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列（即，组合出下一个更大的整数）。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须**[ 原地 ](https://baike.baidu.com/item/原地算法)**修改，只允许使用额外常数空间。

 

**示例 1：**

```
输入：nums = [1,2,3]
输出：[1,3,2]
```

**示例 2：**

```
输入：nums = [3,2,1]
输出：[1,2,3]
```

**示例 3：**

```
输入：nums = [1,1,5]
输出：[1,5,1]
```

**示例 4：**

```
输入：nums = [1]
输出：[1]
```

 

**提示：**

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 100`

通过次数230,488

提交次数618,386

## 反向遍历

1. 反向遍历获取所有可交换使得排列增大的数中（`j<index and nums[j] < nums[index]`），使得增大的程度最小的下标。
2. 交换使得排列增大，并对j后的排列进行递增排序





### Python

执行用时：56 ms, 在所有 Python3 提交中击败了5.31%的用户

内存消耗：14.9 MB, 在所有 Python3 提交中击败了57.98%的用户

```python
class Solution:
    def nextPermutation(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        length = len(nums)
        arr = []
        # 反向遍历，找到位数最小的j
        for i in range(length):
            index = length - 1 - i
            j = index - 1
            while j >= 0 :
                if nums[j] < nums[index]:
                    arr.append((j,index))
                j -= 1
        if not arr:
            nums.sort()
            return
        arr.sort()
        t = arr.pop()
        if t:
            j = t[0]
            index = t[1]
            temp = nums[j]
            nums[j] = nums[index]
            nums[index] = temp
            for ii in range(j+1,length):
                for jj in range(j+1, length + j - ii):
                    if nums[jj] > nums[jj + 1]:
                        temp = nums[jj]
                        nums[jj] = nums[jj + 1]
                        nums[jj + 1] = temp
           
            
```

### C

执行用时：8 ms, 在所有 C 提交中击败了59.65%的用户

内存消耗：6 MB, 在所有 C 提交中击败了94.46%的用户

```c
void sort(int* nums, int mSize){
    int i,j, temp;
    for(i=0; i<mSize; i++){
        for(j=0; j<mSize - 1 - i; j++){
            if(nums[j]>nums[j+1]){
                temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }
}
void nextPermutation(int* nums, int numsSize){
    if (nums == NULL || numsSize == 0) return;
    int i,j;
    int max = -9999;
    int m,n;
    int temp;
    for(i = numsSize - 1; i >=0; i--)
        for(j = i - 1; j >= 0; j--)
            if(nums[j] < nums[i])
                if(j > max){
                    max = m = j;
                    n = i;
                }
    if (max == -9999){
        sort(nums, numsSize);
        return;
    }
    temp = nums[m];
    nums[m] = nums[n];
    nums[n] = temp; 
    sort(nums+m+1, numsSize - m - 1);
    return;
}
```

