#setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 3/Ej3")
setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 5/Ej2")
library("class")

data <- as.data.frame(read.table("data.txt", sep = ",", header = FALSE))
colnames(data) <- c("Variance", "Skewness", "Kurtosis", "Entropy", "Label")
shuffled_data <- data[sample(nrow(data)),]
smp_size <- floor(0.75 * nrow(data))
train_ind <- sample(seq_len(nrow(data)), size = smp_size)

train <- shuffled_data[train_ind, ]
test <- shuffled_data[-train_ind, ]

train_set <- train[,1:4]
train_labels <- train[,5]
test_set <- test[, 1:4]
test_labels <- test[,5]

knn_pred <- knn(train = train_set, test = test_set, cl = train_labels, k = 2)
print(test_labels)
print(knn_pred)