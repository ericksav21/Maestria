setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Optimizacion/Proyecto/Test_R/")

library(quantreg)

#################
# read in data  #
#################
X <- data.frame(as.matrix(read.table("toyPCA.txt",skip=2)))
#################

n <- nrow(X)
m <- ncol(X)

# matrix to hold principal components: the main output
Alphas <- matrix(nrow=m, ncol=m)

# keep track of product of Vk matrices
prodVk <- diag(m)

k <- m

# main loop: iterate over dimensions of the data
for (k in m:2) {
  #print(sprintf("Iteración %d.\n", k))
  minobjective <- 10000000.0
  # Step 3: Identify best-fit L1 hyperplane using result from Theorem 1
  for (j in 1:k) {
    names(X)[j] <- "depvar" 
    # constrain intercept to 0
    Rmatrix <- matrix(c(1,-1,rep(0,2*(k-1))),nrow=2)
    rvector <- c(0,0)
    #L1 regression 
    l1regress <- rq(depvar ~ ., data=X, R=Rmatrix, r=rvector, method="fnc") 
    Rj <- sum(abs(l1regress$residuals))
    if (Rj < minobjective) {
      jstar <- j
      minobjective <- Rj
      if (j == 1) {
        betak <- c(0,l1regress$coefficients[2:k])
      } else if (j < k) {
        betak <- c(l1regress$coefficients[2:j], 0, l1regress$coefficients[(j+1):k])
      } else {
        betak <- c(l1regress$coefficients[2:j], 0)
      }
    }
    names(X)[j] <- paste("indepvar",j, sep="")
  }
  # Step 4: Calculate projected points in terms of the k-dimensional subspace
  Ijstark <- diag(k)
  Ijstark[jstar,] <- betak
  Z <- as.matrix(X) %*% t(Ijstark)
  # Step 5: Caculcate SVD of Z
  Zsvd <- svd(Z)
  Vk <- Zsvd$v[,1:(k-1)]
  
  # Step 6: Calculate the k^th principal component
  betak[jstar] <- -1.0
  Alphas[,k] <- prodVk %*% (betak/sqrt(sum(betak*betak)))
  
  # Step 7: Calculate the scores
  X <- data.frame(Z %*% Vk)
  
  prodVk <- prodVk %*% Vk  
}   

Alphas[,1] <- prodVk