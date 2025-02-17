# 中阶函数编程练习

**1. 阶乘计算函数：**
  
  编写一个函数 `calculate_factorial`，接受一个正整数 `n` 作为参数，并返回 `n!` 的值。

```R
calculate_factorial <- function(n) {
  if (n == 0) {
    return(1)
  } else {
    return(n * calculate_factorial(n - 1))
  }
}

# 示例
calculate_factorial(5)  # 输出 120
```

**2. 求平均值函数：**
  
  创建一个函数 `calculate_average`，接受一个数字向量作为参数，并返回向量中所有元素的平均值。

```R
calculate_average <- function(nums) {
  return(mean(nums))
}

# 示例
my_vector <- c(2, 4, 6, 8, 10)
calculate_average(my_vector)  # 输出 6
```

**3. 列表连接函数：**
  
  编写一个函数 `concatenate_lists`，接受两个字符列表作为参数，并将它们连接成一个新的字符列表。

```R
concatenate_lists <- function(list1, list2) {
  return(c(list1, list2))
}

# 示例
fruits <- c("apple", "banana")
colors <- c("red", "yellow")
concatenated <- concatenate_lists(fruits, colors)
concatenated  # 输出 "apple" "banana" "red" "yellow"
```

**4. 字符串反转函数：**
  
  创建一个函数 `reverse_string`，接受一个字符串作为参数，并返回该字符串的反转版本。

```R
reverse_string <- function(str) {
  return(paste(rev(unlist(strsplit(str, ""))), collapse = ""))
}

# 示例
my_string <- "hello"
reversed <- reverse_string(my_string)
reversed  # 输出 "olleh"
```

**5. 乘法表生成函数：**
  
  编写一个函数 `generate_multiplication_table`，接受一个正整数 `n` 作为参数，并生成它的乘法表。

```R
generate_multiplication_table <- function(n) {
  table <- matrix(NA, n, n)
  for (i in 1:n) {
    for (j in 1:n) {
      table[i, j] <- i * j
    }
  }
  rownames(table) <- colnames(table) <- 1:n
  return(table)
}

# 示例
multiplication_table <- generate_multiplication_table(5)
multiplication_table
# 输出:
#      [,1] [,2] [,3] [,4] [,5]
# [1,]    1    2    3    4    5
# [2,]    2    4    6    8   10
# [3,]    3    6    9   12   15
# [4,]    4    8   12   16   20
# [5,]    5   10   15   20   25
```

**6. 斐波那契数列生成函数：**
  
  创建一个函数 `generate_fibonacci_sequence`，接受一个正整数 `n` 作为参数，并生成前 `n` 个斐波那契数列的值。

```R
generate_fibonacci_sequence <- function(n) {
  if (n == 1) {
    return(0)
  } else if (n == 2) {
    return(c(0, 1))
  } else {
    fibonacci <- c(0, 1)
    for (i in 3:n) {
      next_value <- fibonacci[i - 1] + fibonacci[i - 2]
      fibonacci <- c(fibonacci, next_value)
    }
    return(fibonacci)
  }
}

# 示例
fibonacci_sequence <- generate_fibonacci_sequence(10)
fibonacci_sequence  # 输出 0 1 1 2 3 5 8 13 21 34
```

**7. 列表元素求和函数：**
  
  编写一个函数 `sum_list_elements`，接受一个数字列表作为参数，并返回列表中所有元素的和。

```R
sum_list_elements <- function(nums) {
  return(sum(nums))
}

# 示例
my_list <- c(10, 20, 30, 40, 50)
total_sum <- sum_list_elements(my_list)
total_sum  # 输出 150
```

**8. 奇数和偶数分割函数：**
  
  创建一个函数 `split_odd_even`，接受一个数字列表作为参数，并返回一个列表，其中包含两个子列表，一个包含所有奇数，另一个包含所有偶数。

```R
split_odd_even <- function(nums) {
  odd_numbers <- nums[nums %% 2 != 0]
  even_numbers <- nums[nums %% 2 == 0]
  return(list(odd = odd_numbers, even = even_numbers))
}

# 示例
my_numbers <- c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
result <- split_odd_even(my_numbers)
result$odd  # 输出 1 3 5 7 9
result$even  # 输出 2 4 6 8 10
```

**9. 元素平方和函数：**
  
  编写一个函数 `sum_of_squares`，接受一个数字向量作为参数，并返回向量中所有元素的平方和。

```R
sum_of_squares <- function(nums) {
  return(sum(nums^2))
}

# 示例
my_vector <- c(1, 2, 3, 4, 5)
sum_of_squares_result <- sum_of_squares(my_vector)
sum_of_squares_result  # 输出 55
```

**10. 随机整数列表生成函数：**
  
  创建

一个函数 `generate_random_integers`，接受一个正整数 `n` 和两个整数 `min` 和 `max` 作为参数，并生成一个包含 `n` 个在 `[min, max]` 范围内的随机整数的列表。

```R
generate_random_integers <- function(n, min, max) {
  random_integers <- sample(min:max, n, replace = TRUE)
  return(random_integers)
}

# 示例
random_numbers <- generate_random_integers(5, 1, 10)
random_numbers  # 可能的输出: 3 7 2 5 8
```

**11. 字符串拼接函数：**
  
  编写一个函数 `concatenate_strings`，接受两个字符串作为参数，并返回它们的连接字符串。

```R
concatenate_strings <- function(str1, str2) {
  return(paste(str1, str2, sep = ""))
}

# 示例
first_name <- "John"
last_name <- "Doe"
full_name <- concatenate_strings(first_name, last_name)
full_name  # 输出 "JohnDoe"
```

**12. 温度转换函数：**
  
  创建一个函数 `convert_temperature`，接受一个温度值（摄氏度）作为参数，并将其转换为华氏度。转换公式为 `Fahrenheit = (Celsius * 9/5) + 32`。

```R
convert_temperature <- function(celsius) {
  fahrenheit <- (celsius * 9/5) + 32
  return(fahrenheit)
}

# 示例
celsius_temp <- 25
fahrenheit_temp <- convert_temperature(celsius_temp)
fahrenheit_temp  # 输出 77
```

**13. 长度检查函数：**
  
  编写一个函数 `check_length`，接受一个字符串和一个整数作为参数，并检查字符串的长度是否大于等于指定的整数。如果是，返回 `TRUE`，否则返回 `FALSE`。

```R
check_length <- function(str, length_threshold) {
  return(nchar(str) >= length_threshold)
}

# 示例
my_string <- "Hello, World!"
result <- check_length(my_string, 10)
result  # 输出 TRUE
```

**14. 列表反转函数：**
  
  创建一个函数 `reverse_list`，接受一个列表作为参数，并返回列表中元素的逆序版本。

```R
reverse_list <- function(lst) {
  return(rev(lst))
}

# 示例
my_list <- list(1, 2, 3, 4, 5)
reversed_list <- reverse_list(my_list)
reversed_list  # 输出 5 4 3 2 1
```

**15. 列表元素去重函数：**
  
  编写一个函数 `remove_duplicates`，接受一个数字列表作为参数，并返回一个新的列表，其中去除了重复的元素。

```R
remove_duplicates <- function(nums) {
  return(unique(nums))
}

# 示例
my_numbers <- c(1, 2, 2, 3, 4, 4, 5)
unique_numbers <- remove_duplicates(my_numbers)
unique_numbers  # 输出 1 2 3 4 5
```

