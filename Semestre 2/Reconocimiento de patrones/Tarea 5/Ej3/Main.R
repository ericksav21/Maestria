setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 5/Ej2")
#setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 5/Ej2")

cat_to_int <- function(x) {
  if(x == "setosa") {
    return(0)
  }
  else if(x == "versicolor") {
    return(1)
  }
  else {
    return(2)
  }
}

normalize <- function(x) {
  return ((x - min(x)) / (max(x) - min(x)))
}

radial_basis_fn <- function(x, mu, sigma_a) {
  res <- exp(-(norm(x - mu, type = "2") * norm(x - mu, type = "2")) / sigma_a)
  return(res)
}

weighted_rbf <- function(x, betas, mus, sigmas) {
  res <- 0.0
  for(i in 1 : length(betas)) {
    res <- res + (betas[i] * radial_basis_fn(x, mu[i, ], sigmas[i]))
  }
  return(res)
}

cost_fn <- function(in_d, out_d, betas, mus, sigmas) {
  res <- 0.0
  for(i in 1 : nrow(in_d)) {
    aux <- out_d[i] - weighted_rbf(in_d[i, ], betas, mus, sigmas)
    res <- res + (aux * aux)
  }
  return(res)
}

data(iris)
print(iris)
train_data_per <- 0.75
shuffled_data <- iris[sample(nrow(iris)),]
smp_size <- floor(train_data_per * nrow(iris))
train_ind <- sample(seq_len(nrow(iris)), size = smp_size)

train <- shuffled_data[train_ind, ]
test <- shuffled_data[-train_ind, ]
train_set <- train[, 1:4]
test_set <- test[, 1:4]
train_labels_str <- train[, 5]
test_labels_str <- test[, 5]
train_labels <- rep(0, length(train_labels_str))
test_labels <- rep(0, length(test_labels_str))
for(i in 1 : length(train_labels)) {
  train_labels[i] <- cat_to_int(train_labels_str[i])
}
for(i in 1 : length(test_labels)) {
  test_labels[i] <- cat_to_int(test_labels_str[i])
}

gauss_size <- 3
km <- kmeans(train_set, hd_size, nstart = 20)
mus <- km$centers
#Calcular las betas, se agrega un espacio más para el BIAS
betas <- runif(gauss_size, 1, 2)
sigmas <- runif(gauss_size, 1, 2)

