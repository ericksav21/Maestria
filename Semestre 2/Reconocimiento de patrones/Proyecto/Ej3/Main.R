library("rpart")
library("caret")

#Cambiar el directorio actual
setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Proyecto/Ej3/")

data <- as.data.frame(read.table("spambase.data", sep = ",", header = FALSE))
names(data)[length(names(data))] <- "Y"
data$Y <- factor(data$Y)

#Se dividen los datos en conjuntos de prueba y entrenamiento aleatoriamente
train_data_per <- 0.70
shuffled_data <- data[sample(nrow(data)),]
smp_size <- floor(train_data_per * nrow(data))
train_ind <- sample(seq_len(nrow(data)), size = smp_size)

train <- shuffled_data[train_ind, ]
test <- shuffled_data[-train_ind, ]
test_labels <- test$Y
test$Y <- NULL

#Hacer una lista de todos los modelos a probar
t_control <- trainControl(method = "cv", number = 5)

print("AdaBoost entrenando...")
ada_model <- train(Y ~ ., data = train, method = "gbm", trControl = t_control, train.fraction = 0.9)
print("SVM entrenando...")
svm_model <- train(Y ~ ., data = train, method = "svmLinear", trControl = t_control, tuneGrid = expand.grid(C = c(0.01, 0.1, 0.5, 1.5, 2.5, 5, 10)), tuneLength = 5)
print("KNN entrenando...")
knn_model <- train(Y ~ ., data = train, method = "knn", trControl = t_control, tuneGrid = expand.grid(k = c(2, 3, 4, 5)))
print("NNnet entrenando...")
nnet_model <- train(Y ~ ., data = train, method = "nnet", trControl = t_control, tuneGrid = expand.grid(size = c(1:3)))
print("Regresión logística entrenando...")
glm_model <- train(Y ~ ., data = train, method = "glm", trControl = t_control, family="binomial")

#Hacer predicciones y validar los modelos
ada_pred <- predict(ada_model, test)
svm_pred <- predict(svm_model, test)
knn_pred <- predict(knn_model, test)
nnet_pred <- predict(nnet_model, test)
glm_pred <- predict(glm_model, test)