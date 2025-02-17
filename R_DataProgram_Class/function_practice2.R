**1. 参数传递和返回值：**
  
  编写一个函数 `add_numbers`，接受两个数字作为参数，并返回它们的和。

```R
add_numbers <- function(a, b) {
  result <- a + b
  return(result)
}

# 示例
sum_result <- add_numbers(5, 3)
sum_result  # 输出 8
```
问题1：参数传递和返回值

1.1 什么是函数的参数，为什么我们需要它们？

1.2 如果一个函数没有返回语句，它会返回什么值？




**2. 参数的多样性：**
  
  创建一个函数 `calculate_area`，接受参数 `length` 和 `width`，并根据不同参数的组合计算面积。如果只提供一个参数，则计算正方形的面积；如果提供两个参数，则计算矩形的面积。

```R
calculate_area <- function(length, width = NULL) {
  if (is.null(width)) {
    area <- length^2
  } else {
    area <- length * width
  }
  return(area)
}

# 示例
square_area <- calculate_area(4)
rectangle_area <- calculate_area(5, 3)
square_area  # 输出 16
rectangle_area  # 输出 15
```

问题2：参数的多样性

2.1 有了默认参数的函数，如何调用它来计算正方形的面积？

2.2 如果你不提供宽度参数，会发生什么情况？



**3. 参数的计算：**
  
  编写一个函数 `calculate_power`，接受一个数字 `x` 和一个指数 `n` 作为参数，并返回 `x` 的 `n` 次幂。

```R
calculate_power <- function(x, n) {
  result <- x^n
  return(result)
}

# 示例
power_result <- calculate_power(2, 3)
power_result  # 输出 8
```
问题3：参数的计算

3.1 函数 calculate_power 的目的是什么？如何使用它来计算 3 的 4 次幂？

3.2 如果将负数传递给 calculate_power 函数会怎样？




**4. 参数的默认值：**
  
  创建一个函数 `greet_person`，接受一个字符串参数 `name`，并根据是否提供了 `name` 参数来打印不同的问候语。

```R
greet_person <- function(name = NULL) {
  if (is.null(name)) {
    message("Hello, there!")
  } else {
    message("Hello, ", name, "!")
  }
}

# 示例
greet_person()  # 输出 "Hello, there!"
greet_person("Alice")  # 输出 "Hello, Alice!"
```
问题4：参数的默认值

4.1 在 greet_person 函数中，当不提供 name 参数时，会发生什么？

4.2 如何调用 greet_person 函数以向名字为 "Alice" 的人打招呼？



**5. 参数的累积：**
  
  编写一个函数 `calculate_sum`，接受任意数量的数字参数，并返回它们的总和。

```R
calculate_sum <- function(...) {
  nums <- c(...)
  result <- sum(nums)
  return(result)
}

# 示例
sum_result <- calculate_sum(1, 2, 3, 4, 5)
sum_result  # 输出 15
```
问题5：参数的累积

5.1 函数 calculate_sum 接受哪种类型的参数？如何传递多个数字给它？

5.2 如何使用 calculate_sum 函数来计算 1、3 和 5 的总和？



**6. 参数的平均值：**
  
  创建一个函数 `calculate_average`，接受一个数字列表作为参数，并返回列表中所有元素的平均值。

```R
calculate_average <- function(nums) {
  result <- mean(nums)
  return(result)
}

# 示例
my_numbers <- c(10, 20, 30, 40, 50)
average_result <- calculate_average(my_numbers)
average_result  # 输出 30
```
问题6：参数的平均值

6.1 什么类型的参数传递给函数 calculate_average？

6.2 如果你有一个包含 10、20 和 30 的数字列表，如何计算它们的平均值？




**7. 参数的字符拼接：**
  
  编写一个函数 `concatenate_strings`，接受两个字符串参数 `str1` 和 `str2`，并返回它们的连接字符串。

```R
concatenate_strings <- function(str1, str2) {
  result <- paste(str1, str2, sep = " ")
  return(result)
}

# 示例
greeting <- concatenate_strings("Hello", "World")
greeting  # 输出 "Hello World"
```

问题7：参数的字符拼接

7.1 在函数 concatenate_strings 中，为什么我们使用 sep = " "？

7.2 如何使用 concatenate_strings 函数将 "Hello" 和 "World" 连接成 "Hello World"？



**8. 参数的字符串反转：**
  
  创建一个函数 `reverse_string`，接受一个字符串作为参数，并返回该字符串的反转版本。

```R
reverse_string <- function(str) {
  result <- paste(rev(unlist(strsplit(str, ""))), collapse = "")
  return(result)
}

# 示例
input_string <- "R Programming"
reversed_string <- reverse_string(input_string)
reversed_string  # 输出 "gnimmargorP R"
```
问题8：参数的字符串反转

8.1 描述函数 reverse_string 的目的。

8.2 如果你将 "abcdef" 作为输入传递给 reverse_string 函数，会得到什么结果？



**9. 参数的条件判断：**
  
  编写一个函数 `is_positive`，接受一个数字参数 `x`，并返回一个逻辑值，表示 `x` 是否为正数。

```R
is_positive <- function(x) {
  result <- x > 0
  return(result)
}

# 示例
check1 <- is_positive(5)
check2 <- is_positive(-3)
check1  # 输出 TRUE
check2  # 输出 FALSE
```

问题9：参数的条件判断

9.1 在 is_positive 函数中，如何检查一个数字是否为正数？

9.2 如果你将 0 传递给 is_positive 函数，它会返回什么值？


**10. 参数的元素筛选：**
  
  创建一个函数 `filter_even_numbers`，接受一个数字列表作为参数，并返回只包含偶数的新列表。

```R
filter_even_numbers <- function(nums) {
  result <- nums[nums %% 2 == 0]
  return(result)
}

# 示例


my_numbers <- c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
even_numbers <- filter_even_numbers(my_numbers)
even_numbers  # 输出 2 4 6 8 10
```

问题10：参数的元素筛选

10.1 函数 filter_even_numbers 返回哪种类型的结果？

10.2 如果你有一个包含 2、4、6 和 7 的数字列表，如何使用 filter_even_numbers 函数来筛选出偶数？




**11. 参数的累积求积：**
  
  编写一个函数 `calculate_product`，接受任意数量的数字参数，并返回它们的乘积。

```R
calculate_product <- function(...) {
  nums <- c(...)
  result <- prod(nums)
  return(result)
}

# 示例
product_result <- calculate_product(2, 3, 4)
product_result  # 输出 24
```
问题11：参数的累积求积

11.1 函数 calculate_product 的目的是什么？

11.2 如何使用 calculate_product 函数来计算 2、3 和 4 的乘积？




**12. 参数的最大值和最小值：**
  
  创建一个函数 `find_min_max`，接受一个数字列表作为参数，并返回列表中的最小值和最大值。

```R
find_min_max <- function(nums) {
  min_value <- min(nums)
  max_value <- max(nums)
  result <- list(min = min_value, max = max_value)
  return(result)
}

# 示例
my_numbers <- c(12, 7, 25, 3, 18)
min_max_values <- find_min_max(my_numbers)
min_max_values  # 输出 min = 3, max = 25
```

问题12：参数的最大值和最小值

12.1 函数 find_min_max 返回一个什么样的结果？

12.2 如果你有一个包含 12、7、25、3 和 18 的数字列表，如何使用 find_min_max 函数来找到最小值和最大值？



**13. 参数的字符长度：**
  
  编写一个函数 `calculate_string_length`，接受一个字符串参数 `str`，并返回字符串的长度。

```R
calculate_string_length <- function(str) {
  result <- nchar(str)
  return(result)
}

# 示例
my_string <- "Data Analysis"
length_result <- calculate_string_length(my_string)
length_result  # 输出 13
```
问题13：参数的字符长度

13.1 函数 calculate_string_length 用于计算什么？

13.2 如果你有一个包含 "Data Analysis" 的字符串，如何使用 calculate_string_length 函数来找到其长度？


**14. 参数的平方根：**
  
  创建一个函数 `calculate_square_root`，接受一个非负数参数 `x`，并返回它的平方根。

```R
calculate_square_root <- function(x) {
  if (x >= 0) {
    result <- sqrt(x)
  } else {
    result <- NaN
  }
  return(result)
}

# 示例
root1 <- calculate_square_root(25)
root2 <- calculate_square_root(-9)
root1  # 输出 5
root2  # 输出 NaN
```
问题14：参数的平方根

14.1 函数 calculate_square_root 的目的是什么？

14.2 如果你将 -16 传递给 calculate_square_root 函数，它会返回什么值？



**15. 参数的字符分割：**
  
  编写一个函数 `split_string`，接受一个字符串参数 `str` 和一个字符参数 `delimiter`，并将字符串分割成子字符串列表。

```R
split_string <- function(str, delimiter) {
  result <- unlist(strsplit(str, delimiter))
  return(result)
}

# 示例
my_text <- "apple,banana,cherry"
delimiter <- ","
split_result <- split_string(my_text, delimiter)
split_result  # 输出 "apple" "banana" "cherry"
```
问题15：参数的字符分割

15.1 函数 split_string 如何将一个字符串分割成多个子字符串？

15.2 如果你有一个包含 "apple,banana,cherry" 的字符串和一个逗号作为分隔符，如何使用 split_string 函数来分割字符串？


