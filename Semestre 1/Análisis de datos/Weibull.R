alpha <- 5
k <- 3
X <- runif(100, 0, 1)
Y <- alpha * (-log(X))^(1 / k)

qm <- sort(Y)
qt <- rweibull(100, k, alpha)
qqplot(qt, qm, xlab="Cuantil teórico", ylab="Cuantil muestral")
lines(seq(min(qm), max(qm), .01), seq(min(qm), max(qm), .01))