# 1. 创建一个函数，接受两个整数作为参数，并返回它们的和。
add_numbers <- function(a, b) {
  return(a + b)
}

# 2. 编写一个函数，接受一个数字作为参数，然后返回它的平方。
square <- function(x) {
  return(x^2)
}

# 3. 创建一个函数，接受一个字符向量和一个分隔符作为参数，并将向量中的元素连接在一起，使用分隔符分隔。
concatenate <- function(vec, separator) {
  return(paste(vec, collapse = separator))
}

# 4. 编写一个函数，接受一个数字向量作为参数，然后返回向量中所有元素的平均值。
calculate_mean <- function(nums) {
  return(mean(nums))
}

# 5. 创建一个函数，接受一个字符向量作为参数，并返回向量中包含的唯一元素。
unique_elements <- function(vec) {
  return(unique(vec))
}

# 6. 编写一个函数，接受一个数字向量和一个阈值作为参数，然后返回大于阈值的所有元素。
above_threshold <- function(nums, threshold) {
  return(nums[nums > threshold])
}

# 7. 创建一个函数，接受一个字符串作为参数，然后返回字符串中的字母数。
count_letters <- function(str) {
  return(nchar(str))
}

# 8. 编写一个函数，接受一个整数向量作为参数，然后返回向量中的最大值。
find_max <- function(nums) {
  return(max(nums))
}

# 9. 创建一个函数，接受一个数字向量和一个百分位数（例如，0.25表示第一四分位数）作为参数，并返回向量中对应百分位的值。
calculate_percentile <- function(nums, percentile) {
  return(quantile(nums, probs = percentile))
}

# 10. 编写一个函数，接受一个字符向量和一个字符作为参数，然后返回向量中包含指定字符的元素数量。
count_character <- function(vec, char) {
  return(sum(vec == char))
}

# 11. 创建一个函数，接受一个数字向量和一个逻辑条件作为参数，然后返回满足条件的所有元素。
filter_by_condition <- function(nums, condition) {
  return(nums[condition])
}

# 12. 编写一个函数，接受一个字符向量作为参数，然后返回向量中每个元素的长度。
calculate_lengths <- function(vec) {
  return(nchar(vec))
}

# 13. 创建一个函数，接受一个整数和一个次方数作为参数，然后返回整数的指定次方。
power <- function(base, exponent) {
  return(base^exponent)
}

# 14. 编写一个函数，接受一个数字向量作为参数，然后返回向量中的中位数。
calculate_median <- function(nums) {
  return(median(nums))
}

# 15. 创建一个函数，接受一个字符向量和一个字符作为参数，然后返回包含指定字符的元素索引。
find_indices <- function(vec, char) {
  return(which(vec == char))
}

# 16. 编写一个函数，接受一个数字向量和一个阈值作为参数，然后返回小于阈值的所有元素的索引。
find_below_threshold_indices <- function(nums, threshold) {
  return(which(nums < threshold))
}

# 17. 创建一个函数，接受一个字符串和一个字符作为参数，然后返回字符串中包含指定字符的次数。
count_character_occurrences <- function(str, char) {
  return(sum(strsplit(str, NULL)[[1]] == char))
}

# 18. 编写一个函数，接受一个整数向量作为参数，然后返回向量中的最小值。
find_min <- function(nums) {
  return(min(nums))
}

# 19. 创建一个函数，接受一个数字向量和一个百分位数作为参数，并返回向量中对应百分位的值，要求函数使用自定义算法而不使用内置函数。
calculate_percentile_custom <- function(nums, percentile) {
  sorted_nums <- sort(nums)
  n <- length(sorted_nums)
  index <- ceiling(percentile * n)
  return(sorted_nums[index])
}

# 20. 编写一个函数，接受一个字符向量和一个字符作为参数，然后返回包含指定字符的元素的百分比。
calculate_character_percentage <- function(vec, char) {
  total_chars <- sum(nchar(vec))
  char_count <- sum(strsplit(vec, NULL)[[1]] == char)
  return((char_count / total_chars) * 100)
}
