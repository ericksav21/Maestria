library("mvtnorm")
library("mixtools")

#Distancia euclideana
euc <- function(x1, y1, x2, y2) {
  return(sqrt((x2 - x1)^2 + (y2 - y1)^2))
}

#log-verosimilitud
loglikelihood <- function(x, y, alpha_s, mu_x, mu_y, sigma, N, K) {
  res <- 0
  for(i in 1:N) {
    ll <- 0
    for(k in 1:K) {
      ll <- ll + (dmvnorm(c(x[i], y[i]), c(mu_x[k], mu_y[k]), sigma[[k]]) * alpha_s[k])
    }
    res <- res + log(ll)
  }
  return(res)
}

#Plotear los contornos de las Gaussianas generadas por EM
plot_EM_res <- function(x, y, mu_x, mu_y, sigma, K) {
  plot(x, y, xlim = c(0, 1), ylim = c(0, 1), title("Conjunto de puntos y sus mezclas obtenidas con K = 15"))
  for(k in 1:K) {
    mmu <- c(mu_x[k], mu_y[k])
    ellipse(mu = mmu, sigma = sigma[[k]], alpha = 0.5, col = "blue")
  }
}

#Función principal. Algoritmo EM
EM <- function(x, y, N, K, it, use_km) {
  alpha_s <- rep(1 / K, K)
  mu_x <- rep(runif(1, 0, 1), K)
  mu_y <- rep(runif(1, 0, 1), K)
  sigma <- list()
  #Anteriores
  lalpha_s <- vector()
  lmu_x <- vector()
  lmu_y <- vector()
  lsigma <- list()
  
  #Inicializar los centros usando K-Means
  if(use_km) {
    m_aux <- array(0, dim = c(length(x), 2))
    m_aux[, 1] <- x
    m_aux[, 2] <- y
    k_clust <- kmeans(m_aux, K, nstart = 20)
    for(k in 1:K) {
      mu_x[k] <- k_clust$centers[k, 1]
      mu_y[k] <- k_clust$centers[k, 2]
    }
  }
  
  for(i in 1:K) {
    sigma[[i]] <- array(0, dim = c(2, 2))
    sigma[[i]][1, 1] <- sigma[[i]][2, 2] <- runif(1, 0, 1)
  }
  W <- matrix(0, nrow = N, ncol = K)
  tol <- 0.0001
  loglike <- 0
  
  flag <- TRUE
  #Paro por iteraciones
  for(t in 1:it) {
    if(!flag) {
      break
    }
    #Expectation
    for(i in 1:N) {
      for(j in 1:K) {
        W[i, j] <- (dmvnorm(c(x[i], y[i]), c(mu_x[j], mu_y[j]), sigma[[j]]) * alpha_s[j])
      }
    }
    W <- sweep(W, 1, rowSums(W), '/')
    
    #Maximization
    for(k in 1:K) {
      Nk <- 0
      Nxk <- c(0, 0)
      S_aux <- array(0, dim = c(2, 2))
      for(i in 1:N) {
        Nk <- Nk + W[i, k]
        Nxk <- Nxk + (W[i, k] * c(x[i], y[i]))
      }
      alpha_s[k] <- Nk / N
      mu_x[k] <- Nxk[1] / Nk
      mu_y[k] <- Nxk[2] / Nk
      for(i in 1:N) {
        v_aux <- c(x[i] - mu_x[k], y[i] - mu_y[k])
        S_aux <- S_aux + (W[i, k] * (v_aux %*% t(v_aux)))
      }
      sigma[[k]] <- S_aux / Nk
    }
    if(t > 1) {
      #Paro porque la log-verosimilud del theta actual es muy parecida a la de la iteración anterior.
      loglike <- abs(loglikelihood(x, y, alpha_s, mu_x, mu_y, sigma, N, K) - loglikelihood(x, y, lalpha_s, lmu_x, lmu_y, lsigma, N, K))
      print(loglike)
      if(loglike < tol) {
        flag <- FALSE
      }
    }
    lalpha_s = alpha_s
    lmu_x = mu_x
    lmu_y = mu_y
    lsigma = sigma
  }
  
  #Generar la gráfica
  cat("Diferencia de la Log-verosimilitud final:", loglike, sep = " ")
  plot_EM_res(x, y, mu_x, mu_y, sigma, K)
}

cnt <- 0
n <- 200
x <- vector()
y <- vector()

cx1 <- 1
cy1 <- 0.5
r1 <- 0.5

cx2 <- 0.5
cy2 <- 0.5
r2 <- 0.5

while(cnt < n) {
  xi <- runif(1, 0, 1)
  yi <- runif(1, 0, 1)
  if(((xi - cx1)^2 / 0.28) + ((yi - cy1)^2 / 0.1) > 1 && euc(xi, yi, cx2, cy2) <= r2) {
    x <- c(x, xi)
    y <- c(y, yi)
    cnt <- cnt + 1
  }
}

EM(x, y, n, 10, 100, FALSE)