setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 5/Ej2")
library("class")
library("nnet")
library("GGally")
library("ggplot2")

data <- as.data.frame(read.table("data.txt", sep = ",", header = FALSE))
colnames(data) <- c("Variance", "Skewness", "Kurtosis", "Entropy", "Label")

no_tests <- 30
train_data_per <- 0.75
avg_acc_knn <- 0.0
avg_acc_nn <- 0.0

#Funciones
exp_fn <- function(data_in_act, mu_act, sigma_act) {
  res <- exp(-(data_in_act - mu_act) ^ 2 / sigma_act)
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
    grad <- c(grad, -2.0 * (betas[i] / sigmas[i] ^ 2) * aux)
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
#Gradientes

