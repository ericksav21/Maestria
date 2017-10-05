library(png)
library(plot3Drgl)

a <- as.matrix(readPNG("pipila.png")[,,1])
len <- dim(a)[1] * dim(a)[2]
noise <- matrix(rnorm(len, -0.1, 0.1), dim(a)[1])
b <- a + noise
#image(a, col=gray((0:256)/256))
image(b, col=gray((0:256)/256))