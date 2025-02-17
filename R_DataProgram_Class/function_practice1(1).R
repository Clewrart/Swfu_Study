
# 1. 创建一个函数，接受两个整数作为参数，并返回它们的和。

add_numbers <- function(a, b) {
  
  
  return(c(a + b, a * b))
  
}

add_numbers(5,10)

mean(5, 10)

mean(add_numbers(5, 10))


mean


?mean
help(mean)  

# 2. 编写一个函数，接受一个数字作为参数，然后返回它的平方。


z <- 56.789

square <- function(x) {

  z  
  y <- x^2

  return(x^2)

  }

square(10)



aba <- function(b, m = 2){
  r <- ( b ^ m ) + 1
  return(r)
  
}

aba(10, 3)



# 3. 创建一个函数，接受一个字符向量和一个分隔符作为参数，并将向量中的元素连接在一起，使用分隔符分隔。

vv <- c("aaaa",'bbb','cccd','wzysds')

paste(vv, collapse = " &&&& ")


abc <- c(1,2,3,4)

concatenate <- function(vec, separator) {
  
  ss <- paste(vec,  collapse = separator)
  
  return(ss)
}

concatenate(vv, "+=====")



# 4. 编写一个函数，接受一个数字向量作为参数，然后返回向量中所有元素的平均值。


vv <- c(2,4,6,8,10,12,18)

mean(vv)


calculate_mean <- function(nums) {
  
  y <- mean(nums)
  
  return( y )
  
}

calculate_mean(vv)

sum()

calculate_sum <- function(nums) {
  
  return(sum(nums))
  
}

calculate_sum(vv)


max(vv)
min(vv)

calculate_len <- function(nums) {
  
  z <- max(nums) - min(nums)
  
  return(z)
  
}

calculate_len(nums = vv)

max(vv)^min(vv)

calculate_vip <- function(nums) {
  
  z <- max(nums)^min(nums)
  
  return(z)
  
}

calculate_vip(nums = vv)



# 5. 创建一个函数，接受一个字符向量作为参数，并返回向量中包含的唯一元素。

unique_elements <- function(vec) {
  
  return( )
}

# 6. 编写一个函数，接受一个数字向量和一个阈值作为参数，然后返回大于阈值的所有元素。

above_threshold <- function(nums, threshold) {
  
  z <- nums[nums > threshold]

  return(z)
  
}

above_threshold(vv, 8)



# 7. 创建一个函数，接受一个字符串作为参数，然后返回字符串中的字母数。

count_letters <- function(str) {
  
  return( )
}

# 8. 编写一个函数，接受一个整数向量作为参数，然后返回向量中的最大值。


find_max <- function(nums) {

    
  return( max(nums) )
}



# 9. 创建一个函数，接受一个数字向量和一个百分位数（例如，0.25表示第一四分位数）作为参数，并返回向量中对应百分位的值。

calculate_percentile <- function(nums, percentile) {
  
  return( )
}

# 10. 编写一个函数，接受一个字符向量和一个字符作为参数，然后返回向量中包含指定字符的元素数量。

count_character <- function(vec, char) { 
  
  return( )
}

# 11. 创建一个函数，接受一个数字向量和一个逻辑条件作为参数，然后返回满足条件的所有元素。

filter_by_condition <- function(nums, condition) {
  
  return( )
}

# 12. 编写一个函数，接受一个字符向量作为参数，然后返回向量中每个元素的长度。

calculate_lengths <- function(vec) {
  
  return( )
}

# 13. 创建一个函数，接受一个整数和一个次方数作为参数，然后返回整数的指定次方。

power <- function(base, exponent) {
  
  return( )
}

# 14. 编写一个函数，接受一个数字向量作为参数，然后返回向量中的中位数。

calculate_median <- function(nums) {
  
  return( )
}

# 15. 创建一个函数，接受一个字符向量和一个字符作为参数，然后返回包含指定字符的元素索引。

find_indices <- function(vec, char) {
  
  return( )
}

# 16. 编写一个函数，接受一个数字向量和一个阈值作为参数，然后返回小于阈值的所有元素的索引。

find_below_threshold_indices <- function(nums, threshold) {
  
  return( )
}

# 17. 编写一个函数，接受一个整数向量作为参数，然后返回向量中的最小值。

find_min <- function(nums) {
  
  return( )
}
