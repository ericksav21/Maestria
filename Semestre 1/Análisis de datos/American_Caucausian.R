AN <- c(8.50, 9.48, 8.65, 8.16, 8.83, 7.76, 8.63)
Cau <- c(8.27, 8.20, 8.25, 8.14, 9.00, 8.10, 7.20, 8.32, 7.70)
U <- c(AN, Cau)
m <- rep(0, 500)
mOrg <- abs(median(AN) - median(Cau))
for(i in 1:1000) {
  Perm <- sample(U, length(U))
  m[i] <- abs(median(Perm[1:length(AN)]) - median(Perm[(length(AN) + 1) : (length(U))]))
  #m[i] <- abs(median(Perm[1:length(AN)]) - median(Perm[(length(AN) + 1) : (length(U))]))
}

hist(m)
p <- sum(m[m > mOrg])
print(p)