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



# 39.组合总和

[39. 组合总和](https://leetcode-cn.com/problems/combination-sum/)

难度中等1641

给定一个**无重复元素**的正整数数组 `candidates` 和一个正整数 `target` ，找出 `candidates` 中所有可以使数字和为目标数 `target` 的唯一组合。

`candidates` 中的数字可以无限制重复被选取。如果至少一个所选数字数量不同，则两种组合是唯一的。 

对于给定的输入，保证和为 `target` 的唯一组合数少于 `150` 个。

 

**示例 1：**

```
输入: candidates = [2,3,6,7], target = 7
输出: [[7],[2,2,3]]
```

**示例 2：**

```
输入: candidates = [2,3,5], target = 8
输出: [[2,2,2,2],[2,3,3],[3,5]]
```

**示例 3：**

```
输入: candidates = [2], target = 1
输出: []
```

**示例 4：**

```
输入: candidates = [1], target = 1
输出: [[1]]
```

**示例 5：**

```
输入: candidates = [1], target = 2
输出: [[1,1]]
```

 

**提示：**

- `1 <= candidates.length <= 30`
- `1 <= candidates[i] <= 200`
- `candidate` 中的每个元素都是独一无二的。
- `1 <= target <= 500`



## 回溯法

- 难点在于去除重复

### Python

执行用时：64 ms, 在所有 Python3 提交中击败了52.95%的用户

内存消耗：15.1 MB, 在所有 Python3 提交中击败了22.64%的用户

```python
class Solution:
    def f(self, arr: [int], t: int)->bool:
        if t == 0:
            self.result.append(arr)
            return True
        for index in range(len(self.a)):
            item = self.a[index]
            copy = self.a
            if item == t:
                self.result.append(arr + [item])
                return True
            elif item < t:
                self.a = self.a[index:]
                self.f(arr+[item], t - item)
            self.a = copy
        return False
                    
   

    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        self.a = candidates
        self.result = []

        for index in range(len(candidates)):
            self.a = candidates
            item = self.a[index]
            if item <= target:
                arr = [item]
                self.a = candidates[index:]
                self.f(arr, target - item)

        return self.result
```

