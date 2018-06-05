library("caret")

#Ejercicio 3

#Cambiar el directorio actual
setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Proyecto/Ej3/")
#setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Proyecto/Ej3/")

#Leer los datos
data <- as.data.frame(read.table("spambase.data", sep = ",", header = FALSE))
names(data)[length(names(data))] <- "Y"
#Indicar la columna Y como factors
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

#Hacer cross-validation con 5 grupos de datos
t_control <- trainControl(method = "cv", number = 5)

#Hacer una lista de todos los modelos a probar
print("AdaBoost entrenando...")
#Este clasificador usa tres niveles de profundidad en los árboles
ada_model <- train(Y ~ ., data = train, method = "gbm", trControl = t_control, train.fraction = 0.9)
print("SVM entrenando...")
#Se usa un kernel lineal además de un conjunto amplio de parámetros de penalización
svm_model <- train(Y ~ ., data = train, method = "svmLinear", trControl = t_control, tuneGrid = expand.grid(C = c(0.01, 0.1, 0.5, 1.5, 2.5, 5, 10)), tuneLength = 5)
print("KNN entrenando...")
#Se usan de 2 a 5 vecinos en este algoritmo
knn_model <- train(Y ~ ., data = train, method = "knn", trControl = t_control, tuneGrid = expand.grid(k = c(2, 3, 4, 5)))
print("NNnet entrenando...")
#Se usan de 1 a 3 capas ocultas además de un conjunto amplio de tamaños de paso
nnet_model <- train(Y ~ ., data = train, method = "nnet", trControl = t_control, tuneGrid = expand.grid(size = c(1, 2, 3), decay = c(0.001, 0.1, 1.0, 2.0, 5.0)))
print("Regresión logística entrenando...")
#Se usa una familia binomial
glm_model <- train(Y ~ ., data = train, method = "glm", trControl = t_control, family = "binomial")

#Hacer predicciones y validar los modelos
ada_pred <- predict(ada_model, test)
svm_pred <- predict(svm_model, test)
knn_pred <- predict(knn_model, test)
nnet_pred <- predict(nnet_model, test)
glm_pred <- predict(glm_model, test)

#Matriz de confusión de ADA
confusionMatrix(ada_pred, test_labels)
#Matriz de confusión de SVM
confusionMatrix(svm_pred, test_labels)
#Matriz de confusión de KNN
confusionMatrix(knn_pred, test_labels)
#Matriz de confusión de NNet
confusionMatrix(nnet_pred, test_labels)
#Matriz de confusión de Regresión logística
confusionMatrix(glm_pred, test_labels)

#Visualización de los modelos en la fase de entrenamiento con sus diferentes parámetros
plot(ada_model)
plot(svm_model)
plot(knn_model)
plot(nnet_model)
summary(glm_model)