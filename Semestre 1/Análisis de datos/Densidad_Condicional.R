C <- rep(100)
for(i in 1:100) {
  U1 <- runif(100, 0, 1)
  U2 <- runif(100, 0, 1)
  X <- 2 * sqrt(U1)
  Y <- (U2 * X) / 2
  C[i] <- cov(X, Y)
}

#Se proyecta la densidad de las covarianzas
#plot(density(C))

#Hacer un QQPlot
qm <- sort(C)
qt <- rnorm(100)
qqplot(qt, qm, xlab="Cuantil teórico", ylab="Cuantil muestral")
qqline(qm, col = 2)