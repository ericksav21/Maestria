x <- runif(1000, -1, 1)
y <- runif(1000, -1, 1)
d <- sqrt(x^2 + y^2)
print((length(d[d < 1]) / 1000) * 100)