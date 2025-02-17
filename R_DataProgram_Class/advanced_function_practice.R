# 高阶函数编程练习

**1. 函数工厂：**
  
  ```R
function_factory <- function(n) {
  return(function(x) x^n)
}

# 示例
power_of_2 <- function_factory(2)
power_of_2(4)  # 输出 16
```

**2. 递归函数：**
  
  ```R
factorial <- function(n) {
  if (n == 0) {
    return(1)
  } else {
    return(n * factorial(n - 1))
  }
}

# 示例
factorial(5)  # 输出 120
```

**3. 函数组合：**
  
  ```R
compose <- function(f, g) {
  return(function(x) f(g(x)))
}

# 示例
add_one <- function(x) x + 1
square <- function(x) x^2
composed_function <- compose(add_one, square)
composed_function(4)  # 输出 17
```

**4. 高阶函数 - 映射：**
  
  ```R
my_map <- function(func, vec) {
  result <- vector("numeric", length(vec))
  for (i in 1:length(vec)) {
    result[i] <- func(vec[i])
  }
  return(result)
}

# 示例
double <- function(x) x * 2
my_vector <- c(1, 2, 3, 4)
mapped_vector <- my_map(double, my_vector)
mapped_vector  # 输出 2 4 6 8
```

**5. 高阶函数 - 过滤：**
  
  ```R
my_filter <- function(predicate, vec) {
  result <- c()
  for (element in vec) {
    if (predicate(element)) {
      result <- c(result, element)
    }
  }
  return(result)
}

# 示例
is_even <- function(x) x %% 2 == 0
my_vector <- c(1, 2, 3, 4, 5, 6)
filtered_vector <- my_filter(is_even, my_vector)
filtered_vector  # 输出 2 4 6
```

**6. 高阶函数 - 折叠：**
  
  ```R
my_reduce <- function(func, init, vec) {
  result <- init
  for (element in vec) {
    result <- func(result, element)
  }
  return(result)
}

# 示例
add <- function(x, y) x + y
my_vector <- c(1, 2, 3, 4, 5)
sum_of_vector <- my_reduce(add, 0, my_vector)
sum_of_vector  # 输出 15
```

**7. 闭包：**
  
  ```R
counter <- function() {
  count <- 0
  return(function() {
    count <<- count + 1
    return(count)
  })
}

# 示例
my_counter <- counter()
my_counter()  # 输出 1
my_counter()  # 输出 2
```

**8. 匿名函数：**
  
  ```R
squared_vector <- function(vec) {
  return(sapply(vec, function(x) x^2))
}

# 示例
my_vector <- c(1, 2, 3, 4, 5)
squared_values <- squared_vector(my_vector)
squared_values  # 输出 1 4 9 16 25
```

**9. 函数作为参数：**
  
  ```R
apply_function <- function(func, mat) {
  return(sapply(mat, func))
}

# 示例
my_matrix <- matrix(1:9, nrow = 3)
sqrt_matrix <- apply_function(sqrt, my_matrix)
sqrt_matrix  # 输出 1.000000 1.414214 1.732051 2.000000 2.236068 2.449490 2.645751 2.828427 3.000000
```

**10. 自定义迭代器：**
  
  ```R
my_iterator <- function(func, n) {
  for (i in 1:n) {
    func()
  }
}

# 示例
print_hello <- function() {
  print("Hello, World!")
}
my_iterator(print_hello, 3)
# 输出:
# [1] "Hello, World!"
# [1] "Hello, World!"
# [1] "Hello, World!"
```

