# Basics
## array
### declare 

```c++
// type arrayName [arraySize]
int numbers[5];
int numbers[5] = {3, 4, 5, 1, 2};
int numbers[] = {3, 4, 5, 1, 2};
```

# Error

## stdexcept

| 异常               | 描述                                 |
| :----------------- | :----------------------------------- |
| `std::exception`   | 所有标准C++异常类的父类              |
| `std::logic_error` | 理论上可以通过读取代码来检查到的异常 |

