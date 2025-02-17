
st = read.csv("20230925stdscr.csv")

head(st)
nm <- c("陈洁","王强","李磊","赵敏","张三","李四","王五","赵六","郑七","周八","吴九","蒋十","杨博","张峰","刘涛","陈明","李华","周伟","郑强","王刚","张磊","杨涛","陈丽","赵强","刘博","孙峰","周涛","吴明","李华","蒋刚","沈磊","杨丽","王强","陈明","周伟","张刚","郑磊","刘涛","孙丽","李强","赵明","钱伟","吴刚","杨磊","沈丽","宋强","马明","王伟","冯刚","陈磊","黄涛","梁丽","高强","夏明","董伟","范刚","郭磊","林涛","何丽","钱强","严明","苏伟","张刚","赵磊","石涛","武丽","贾强","唐明","韩伟","傅刚")

rr = nm[-c(68,70)]
st$name <- rr
head(st)


xiugai <- function(x){
  if(x > 1000){
    x <- x / 100
  }
  
  else if(x > 200){
    x <- x / 10
  }
  
  else if(x > 100){
    x <- x - 10
  }
  
  else{
    x <- x
  }
  
  
  return(x)
}

sapply(st$math, xiugai)

xiugai(st$math[31])

st$math[1] <- xiugai(st$math[1])
st$math[2] <- xiugai(st$math[2])
st$math[3] <- xiugai(st$math[3])
st$math[4] <- xiugai(st$math[4])
st$math[5] <- xiugai(st$math[5])
...elt
st$math[68] <- xiugai(st$math[68])

for(i in 1:68){
  st$math[i] <- xiugai(st$math[i])
  st$engl[i] <- xiugai(st$engl[i])
  st$lite[i] <- xiugai(st$lite[i])
  st$biol[i] <- xiugai(st$biol[i])
  st$poli[i] <- xiugai(st$poli[i])
}


mean(st$math)

sum(st$math >= 90) / length(st$math)

sum(st$math < 60) / length(st$math)


ss <- function(x){
  s1 <- mean(x)
  s2 <- sum(x >= 90) / length(x)
  s3 <- sum(x < 60) / length(x)
  return(c(s1, s2, s3))
}

scl <- list(
  math = round(ss(st$math),3),
  engl = round(ss(st$engl),3),
  lite = round(ss(st$lite),3),
  biol = round(ss(st$biol),3),
  poli = round(ss(st$poli),3))

scr_ss <- as.data.frame(scl)
scr_ss <- as.data.frame(t(scr_ss))
names(scr_ss) <- c("平均值","优秀率","不及格率")
scr_ss

head(st)

for(i in 1:68){

  st$total[有东西] <- sum(st[有东西 , 有其他东西])

  }

for(i in 1:68){
  
  st$total[i] <- sum(st[i,2:6])
  
}

sort(st$math)

sort_st <- st[order(-st$total),]

head(sort_st, round(length(st$total) * 0.05),0)
tail(sort_st, round(length(st$total) * 0.05),0)

