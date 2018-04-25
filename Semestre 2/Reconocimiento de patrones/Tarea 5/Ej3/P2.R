library("class")
library("nnet")
library("GGally")
library("ggplot2")

#Funciones
exp_fn <- function(data_in_act, mu_act, sigma_act) {
  res <- exp(-((data_in_act - mu_act) ^ 2) / sigma_act)
  return(res)
}

gauss_fn <- function(data_in_act, betas, mus, sigmas) {
  res <- 0.0
  for(i in 1 : length(betas)) {
    res <- res + (betas[i] * exp_fn(data_in_act, mus[i], sigmas[i]))
  }
  return(res)
}

cost_fn <- function(data_in, data_out, betas, mus, sigmas) {
  res <- 0.0
  for(i in 1 : length(data_in)) {
    res <- res + (data_out[i] - gauss_fn(data_in[i], betas, mus, sigmas)) ^ 2
  }
  
  return(res)
}

#Gradientes
grad_beta <- function(data_in, data_out, betas, mus, sigmas) {
  grad <- vector()
  for(i in 1 : length(mus)) {
    aux <- 0.0
    for(j in 1 : length(data_in)) {
      aux <- aux + ((data_out[j] - gauss_fn(data_in[j], betas, mus, sigmas)) * exp_fn(data_in[j], mus[i], sigmas[i]))
    }
    grad <- c(grad, -2.0 * aux)
  }
  return(grad)
}

grad_sigma <- function(data_in, data_out, betas, mus, sigmas) {
  grad <- vector()
  for(i in 1 : length(mus)) {
    aux <- 0.0
    for(j in 1 : length(data_in)) {
      aux <- aux + ((data_out[j] - gauss_fn(data_in[j], betas, mus, sigmas)) * exp_fn(data_in[j], mus[i], sigmas[i]) * (data_in[j] - mus[i]) ^ 2)
    }
    grad <- c(grad, -2.0 * (betas[i] / (sigmas[i] ^ 2)) * aux)
  }
  return(grad)
}

grad_mu <- function(data_in, data_out, betas, mus, sigmas) {
  grad <- vector()
  for(i in 1 : length(mus)) {
    aux <- 0.0
    for(j in 1 : length(data_in)) {
      aux <- aux + ((data_out[j] - gauss_fn(data_in[j], betas, mus, sigmas)) * exp_fn(data_in[j], mus[i], sigmas[i]) * (data_in[j] - mus[i]))
    }
    grad <- c(grad, -4.0 * (betas[i] / sigmas[i]) * aux)
  }
  return(grad)
}
#Fin Gradientes

#Descenso por gradiente
gradient_descent <- function(data_in, data_out, betas, mus, sigmas, alpha, par_to_opt) {
  iter <- 1
  iter_max <- 15000
  tol <- 0.01
  while(T) {
    if(par_to_opt == 1) {
      g <- grad_beta(data_in, data_out, betas, mus, sigmas)
      betas <- betas - alpha * g
    }
    else if(par_to_opt == 2) {
      g <- grad_sigma(data_in, data_out, betas, mus, sigmas)
      sigmas <- sigmas - alpha * g
    }
    else {
      g <- grad_mu(data_in, data_out, betas, mus, sigmas)
      mus <- mus - alpha * g
    }
    g_n <- norm(g, type = "2")
    print(sprintf("Iteración: %d\n", iter))
    print(sprintf("Norma del gradiente: %f\n", g_n))
    if(g_n < tol) {
      break
    }
    if(iter == iter_max) {
      break
    }
    iter <- iter + 1
  }
  
  if(par_to_opt == 1) {
    return(betas)
  }
  else if(par_to_opt == 2) {
    return(sigmas)
  }
  else {
    return(mus)
  }
}

#Validación
validation <- function(betas1, mus1, sigmas1, betas2, mus2, sigmas2, test_in, test_out) {
  f1 <- gauss_fn(test_in, betas1, mus1, sigmas1)
  f2 <- gauss_fn(test_in, betas2, mus2, sigmas2)
  eps <- 0.01
  
  F1 <- (f1 + eps) / (f1 + f2 + 2.0 * eps)
  F2 <- (f2 + eps) / (f1 + f2 + 2.0 * eps)
  
  res <- 0
  if(F2 < F1) {
    print("Predicción: 0")
  }
  else {
    res <- 1
    print("Predicción: 1")
  }
  print(sprintf("Real: %d\n\n", test_out))
  return(res)
}

no_gauss <- 7

#Declaración de los conjuntos de prueba y entrenamiento
n <- 200
m <- 100
train_set1 <- rnorm(n, 5, 1)
train_labels1 <- rep(0, n)
train_set2 <- rnorm(n, 20, 1)
train_labels2 <- rep(1, n)

test_set1 <- rnorm(m, 5, 1)
test_labels1 <- rep(0, m)
s1 <- cbind(test_set1, test_labels1)
test_set2 <- rnorm(m, 20, 1)
test_labels2 <- rep(1, m)
s2 <- cbind(test_set2, test_labels2)
test_f <- rbind(s1, s2)
test_f <- test_f[sample(nrow(test_f)), ]
test_data <- test_f[, 1]
test_labels <- test_f[, 2]

#Declaración de los parámetros
km1 <- kmeans(train_set1, no_gauss, nstart = 20)
mu1 <- km1$centers
beta1 <- rnorm(no_gauss, 0, 1)
sigma1 <- rnorm(no_gauss, 2, 2)

km2 <- kmeans(train_set2, no_gauss, nstart = 20)
mu2 <- km2$centers
beta2 <- beta1
sigma2 <- sigma1

#Algoritmo de optimización
alpha <- 0.002
#Optimizar para el primer conjunto
m <- mu1
b <- beta1
s <- sigma1
beta1 <- gradient_descent(train_set1, train_labels1, beta1, mu1, sigma1, alpha, 1)
print("Optimización para el primer conjunto terminada.")

#Optimizar para el segundo conjunto
beta2 <- gradient_descent(train_set2, train_labels2, beta2, mu2, sigma2, alpha, 1)
print("Optimización para el segundo conjunto terminada.")

#Realizar la validación
tp <- 0
fp <- 0
for(i in 1 : length(test_data)) {
  p <- validation(beta1, mu1, sigma1, beta2, mu2, sigma2, test_data[i], test_labels[i])
  if(p == test_labels[i] && p == 1) {
    tp <- tp + 1
  }
  else if(p != test_labels[i] && p == 1) {
    fp <- fp + 1
  }
}
print(sprintf("Precision: %f\n", tp / (tp + fp)))