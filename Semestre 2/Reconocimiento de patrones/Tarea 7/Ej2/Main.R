reg <- function(x) {
  return(log(1.0 + exp(-x)))
}

boosting <- function(x) {
  return(exp(-x))
}

svm <- function(x) {
  y <- rep(0, length(x))
  for(i in 1:length(x)) {
    if(x[i] < 1) {
      y[i] <- 1.0 - x[i]
    }
    else {
      y[i] <- 0.0
    }
  }
  return(y)
}

n <- 200
x <- rep(0, n)
a <- -5.0
b <- 5.0
dx <- (b - a) / (n - 1)
for(i in 1:n) {
  x[i] <- a + (i - 1) * dx
}
y1 <- reg(x)
y2 <- boosting(x)
y3 <- svm(x)
plot_colors <- c("blue", "black", "orange")
plot(x, y1, type = "l", col = "blue", xlab = "x", ylab = "f(x)")
lines(x, y2, type = "l", col = "black")
lines(x, y3, type = "l", col = "orange")
legend("topright", c("Regresión", "Boosting", "SVM"), cex = 0.8, col = plot_colors, lwd = 2)