#old.par <- par(mfrow=c(1, 2))
x <- runif(1000)
h <- 0.1
#plot(density(x, adjust=0.1, kernel="triangular"))
#plot(density(x, adjust=0.1, kernel="gaussian"))
#plot(density(x, adjust=0.1, kernel="epanechnikov"))
plot(density(x, adjust=0.1, kernel="biweight"))
#par(old.par)