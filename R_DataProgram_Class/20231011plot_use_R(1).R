
使用R语言进行作图

例题1: 绘制散点图
问题:使用ggplot2包绘制身高和体重的散点图
代码:
  ```r
在线安装ggplot2 package

install.packages("ggplot2")

library(ggplot2) 



height <- c(168, 174, 160, 180, 176, 182, 175, 166)
weight <- c(62, 68, 55, 74, 62, 80, 64, 58)

plot(height, weight, type = "l",
     log = "xy",
     main = "身高肯体总胡关系")

plot(height, weight, xlab="身高", ylab="体重", main="身高体重散点图",
    col = "red")
?plot

a <- rnorm(100)
b <- a * 1.5 + rnorm(1)
c <- a * 3.5 + rnorm(1)
d <- a * 9.0 + rnorm(1)


plot(a, b, type = "b",
     col = "blue", pch = 5.5)
points(a, c, col = "red", pch = 5.5)
lines(a, d, col = "brown")

library(ggplot2)

abcd <- data.frame(a = a,
           b = b,
           c = c,
           d = d)

ggplot(data = abcd) +
  geom_point(aes(x = a, y = b, col = d)) +
  scale_color_gradient(low = "red",
                      high = "blue") +
  theme_bw() +
  labs(title = "a和b的关系",
       subtitle =  "这里还有c和d",
       x = "a其实不是b",
       y = "b其实不是c") +
  annotate("text", 
           x = -2, 
           y = 3, 
           col="red",
           label = "这里是a和b的红线")
?scale_color_continuous




ggplot(data=data.frame(height, weight), aes(x=height, y=weight)) +
  geom_point()
```

例题2: 绘制条形图  
问题:使用ggplot2包绘制不同城市的平均气温条形图
代码:
  ```r  
city <- c("北京","上海","广州","深圳")
temp <- c(18, 21, 25, 22) 

barplot(temp, names.arg=city, xlab="City", ylab="Temperature", main="Bar Plot")

ggplot(data=data.frame(city, temp), aes(x=city, y=temp)) +
  geom_bar(stat="identity")
```

例题3: 绘制折线图
问题:使用ggplot2包绘制2010年至2020年我国GDP变化趋势的折线图
代码:
  ```r
year <- 2011:2020
gdp <- c(600000, 650000, 700000, 750000, 800000, 850000, 900000, 950000, 1000000, 1050000)

plot(year, gdp, type="l", xlab="Year", ylab="GDP", main="Line Plot")

ggplot(data=data.frame(year, gdp), aes(x=year, y=gdp)) +
  geom_line()
```

例题4: 绘制箱线图
问题:使用ggplot2包绘制不同品牌手机价格的箱线图
代码:
  ```r
brand <- c(rep("A",50), rep("B",50), rep("C",50)) 
price <- c(sample(4000:8000, 50), sample(2000:5000, 50), sample(500:1500, 50))

boxplot(price~brand, xlab="Brand", ylab="Price", main="Boxplot")

ggplot(data=data.frame(brand, price), aes(x=brand, y=price)) +
  geom_boxplot()
```

例题5: 绘制饼图  
问题:使用ggplot2包绘制某公司各部门员工人数饼图
代码:
  ```r
dept <- c("技术部","市场部","财务部","行政部")
num <- c(35, 42, 15, 28)

pie(num, labels=dept, main="Pie Chart")

ggplot(data=data.frame(dept,num), aes(x="", y=num, fill=dept)) +
  geom_bar(stat="identity", width=1) +
  coord_polar("y", start=0)
```

例题6: 绘制散点图并加趋势线
问题:绘制年龄和收入的散点图,并加上趋势线
代码:
  ```r
age <- c(30,40,20,35,60,45,25,50) 
income <- c(20000,40000,15000,30000,50000,35000,18000,45000)

plot(age, income, xlab="Age", ylab="Income", main="Scatter Plot")
abline(lm(income~age), col="red")

ggplot(data=data.frame(age, income), aes(x=age, y=income)) +
  geom_point() +
  geom_smooth(method=lm, se=F)
```

例题7: 绘制层叠柱状图
问题:绘制不同年份不同品类销售额层叠柱状图
代码:  
  ```r
year <- c(rep(2015,3),rep(2016,3),rep(2017,3))
type <- rep(c("服装","食品","电子产品"),3)  
sales <- c(2000,3000,5000,2200,3200,5500,2400,3300,5800)

barplot(sales, names.arg=year, beside=T, legend=type, main="Stacked Bar Plot")

ggplot(data=data.frame(year,type,sales), aes(x=year, y=sales, fill=type)) +
  geom_bar(stat="identity", position="stack")
```

例题8: 绘制分面图
问题:按性别绘制身高和体重的分面散点图
代码:
  ```r
gender <- c(rep("male",50),rep("female",50))
height <- c(rnorm(50, mean=175, sd=7),rnorm(50, mean=165, sd=6))  
weight <- c(rnorm(50, mean=70, sd=10),rnorm(50, mean=55, sd=8))

par(mfrow=c(1,2))
plot(height[gender=="male"], weight[gender=="male"], main="Male", xlab="Height", ylab="Weight")
plot(height[gender=="female"], weight[gender=="female"], main="Female", xlab="Height", ylab="Weight")

ggplot(data=data.frame(gender,height,weight), aes(x=height, y=weight)) +
  geom_point() +
  facet_wrap(~gender) 
```

例题9: 设置坐标轴范围
问题:绘制1-20的正态分布密度图,x轴范围设置为0-30
代码:  
  ```r
x <- rnorm(1000, mean=10, sd=3)

hist(x, breaks=seq(0,30,by=3), main="Histogram", xlab="X", xlim=c(0,30))

ggplot(data.frame(x), aes(x=x)) +
  geom_density() +
  xlim(0,30)
```

例题10: 设置图注释
问题:在条形图上添加标题、副标题、注释
代码:
  ```r
score <- c(80,75,90,85,60,95) 

barplot(1:6, score, 
        names.arg = score, 
        main="Bar Plot", 
        sub="Score", 
        ylim=c(0,10))

text(85, 5, "Average=85")

ggplot(data.frame(x = 1:6, score), aes(x=x, y=score)) +
  geom_bar(stat = "identity") +
  ggtitle("考试成绩条形图") + 
  labs(subtitle="R语言编程") +
  annotate("text", x=3.5, y=100, label="平均分=85",size=4)
```