X <- runif(100, 0, 1)
Y <- -2 * log(X)

print(mean(Y))
Z <- rexp(100, 0.5)

T <- dexp(seq(.01, 8, .01), 0.5)
plot(seq(.01, 8, .01), T)

par(mfrow=c(1, 2))
#hist(Y)
#hist(Z)

#Cuantiles
qm <- sort(Y)
qt <- -2 * log(1 - seq(1 / 100, 1, 1/100))

plot(qt, qm, main="QQ Plot", xlab="Cuantiles teóricos", ylab="Cuantiles muestrales")
lines(seq(min(qm), max(qm), .01), seq(min(qm), max(qm), .01))