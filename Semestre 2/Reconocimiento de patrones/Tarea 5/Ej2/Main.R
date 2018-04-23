setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 5/Ej2")
#setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 5/Ej2")
library("class")
library("nnet")

data <- as.data.frame(read.table("data.txt", sep = ",", header = FALSE))
colnames(data) <- c("Variance", "Skewness", "Kurtosis", "Entropy", "Label")

no_tests <- 30
train_data_per <- 0.75
avg_acc_knn <- 0.0
avg_acc_nn <- 0.0

for(t in 1:no_tests) {
  shuffled_data <- data[sample(nrow(data)),]
  smp_size <- floor(train_data_per * nrow(data))
  train_ind <- sample(seq_len(nrow(data)), size = smp_size)
  
  train <- shuffled_data[train_ind, ]
  test <- shuffled_data[-train_ind, ]
  
  train_set <- train[,1:4]
  train_labels <- train[,5]
  train_labels_nn <- class.ind(train_labels)
  
  test_set <- test[, 1:4]
  test_labels <- test[,5]
  
  #Hacer un K-NN
  knn_pred <- knn(train = train_set, test = test_set, cl = train_labels, k = 2)
  #Hacer una NN
  n_net <- nnet(train_labels_nn~Variance+Skewness+Kurtosis+Entropy, size = 3, softmax = T, data = train_set)
  nn_pred <- predict(n_net, test_set)
  
  same_vals_knn <- 0
  same_vals_nn <- 0
  for(i in 1 : length(test_labels)) {
    nn_res_i <- 0
    if(nn_pred[i, 1] < nn_pred[i, 2]) {
      nn_res_i <- 1
    }
    if(test_labels[i] == nn_res_i) {
      same_vals_nn <- same_vals_nn + 1
    }
    if(test_labels[i] == knn_pred[i]) {
      same_vals_knn <- same_vals_knn + 1
    }
  }
  avg_acc_knn <- avg_acc_knn + (same_vals_knn / length(test_labels))
  avg_acc_nn <- avg_acc_nn + (same_vals_nn / length(test_labels))
  
  print(sprintf("Iteración: %d.", t))
  print(sprintf("Knn - No. de datos correctamente predichos: %d, No. de datos totales: %d.\n", same_vals_knn, length(test_labels)))
  print(sprintf("NN - No. de datos correctamente predichos: %d, No. de datos totales: %d.\n", same_vals_nn, length(test_labels)))
  print("")
}

avg_acc_knn <- avg_acc_knn / no_tests
avg_acc_nn <- avg_acc_nn / no_tests
print(sprintf("Tasa de éxito promedio del Knn: %f", avg_acc_knn))
print(sprintf("Tasa de éxito promedio de la red neuronal: %f", avg_acc_nn))