vec1 <- vector(, 0)
vec2 <- vector(, 0)
for(i in 1:50) {
  x <- runif(10000000, 0, 50)
  t1 <- system.time(x1 <- sort(x, method = "shell"), gcFirst = TRUE)
  t2 <- system.time(x2 <- sort(x, method = "quick"), gcFirst = TRUE)
  vec1 <- c(vec1, t1[3])
  vec2 <- c(vec2, t2[3])
}

print(vec1)
print(vec2)

print(mean(vec1))
print(mean(vec2))

print(sd(vec1))
print(sd(vec2))

#Generar un QQPlot
qm <- sort(vec1) #Shell
qqplot(vec2, qm, xlab="Cuantil teórico (Quick)", ylab="Cuantil muestral (Shell)")
lines(seq(min(qm), max(qm), .01), seq(min(qm), max(qm), .01))
