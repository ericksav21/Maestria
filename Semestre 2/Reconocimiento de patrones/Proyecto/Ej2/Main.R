library("caret")
library("GGally")

#Ejercicio 2

#Cambiar el directorio actual
setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Proyecto/Ej2/")
#setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Proyecto/Ej2/")

#Leer los datos
data <- as.data.frame(read.table("data.txt", header = TRUE))
#Indicar la columna 1 como factors
data[, 1] <- as.factor(data[, 1])

logit <- function(x){
  return(1 / (1 + exp(-x)))
}

#Hacer un pairsplot de los datos para visualizar la matriz de correlación de los mismos
ggpairs(data, axisLabels = "none", aes(color = highpm10))

#Se dividen los datos en conjuntos de prueba y entrenamiento aleatoriamente
train_data_per <- 0.70
shuffled_data <- data[sample(nrow(data)),]
smp_size <- floor(train_data_per * nrow(data))
train_ind <- sample(seq_len(nrow(data)), size = smp_size)

train <- shuffled_data[train_ind, ]
test <- shuffled_data[-train_ind, ]
test_labels <- test[, 1]
test[, 1] <- NULL

t_control <- trainControl(method = "cv", number = 10)

#Modelo saturado
glm_model_1 <- train(highpm10 ~ ., data = train, method = "glm", trControl = t_control, family = "binomial")
summary(glm_model_1)
glm_pred_1 <- predict(glm_model_1, test)
confusionMatrix(glm_pred_1, test_labels)

#Modelo como lo sugiere el ejercicio
glm_model_ex <- train(highpm10 ~ time + winddirection + temp2m + cars, data = train, method = "glm", trControl = t_control, family = "binomial")
summary(glm_model_ex)
glm_pred_ex <- predict(glm_model_ex, test)
confusionMatrix(glm_pred_ex, test_labels)

#Modelo con los dos parámetros más importantes del anterior y uno adicional
glm_model_2 <- train(highpm10 ~ cars + winddirection + temp2m, data = train, method = "glm", trControl = t_control, family = "binomial")
summary(glm_model_2)
glm_pred_2 <- predict(glm_model_2, test)
confusionMatrix(glm_pred_2, test_labels)

#Modelo con los dos parámetros más importantes del primero
glm_model_3 <- train(highpm10 ~ cars + winddirection, data = train, method = "glm", trControl = t_control, family = "binomial")
summary(glm_model_3)
glm_pred_3 <- predict(glm_model_3, test)
confusionMatrix(glm_pred_3, test_labels)

#Modelo basado en correlaciones de las variables
glm_model_4 <- train(highpm10 ~ cars * time, data = train, method = "glm", trControl = t_control, family = "binomial")
summary(glm_model_4)
glm_pred_4 <- predict(glm_model_4, test)
confusionMatrix(glm_pred_4, test_labels)

glm_model_5 <- train(highpm10 ~ cars * windspeed + temp2m * winddirection, data = train, method = "glm", trControl = t_control, family = "binomial")
summary(glm_model_5)
glm_pred_5 <- predict(glm_model_5, test)
confusionMatrix(glm_pred_5, test_labels)

#-------Modelos con redes neuronales
#Modelo saturado
nnet_model_1 <- train(highpm10 ~ ., data = train, method = "nnet", trControl = t_control, tuneGrid = expand.grid(size = c(1, 2, 3, 4), decay = c(0.001, 0.1, 1.0, 2.0, 5.0)))
nnet_pred_1 <- predict(nnet_model_1, test)
plot(nnet_model_1)
confusionMatrix(nnet_pred_1, test_labels)

#Modelo con los parámetros más relevantes del modelo saturado del glm
nnet_model_2 <- train(highpm10 ~ cars + winddirection + temp2m, data = train, method = "nnet", trControl = t_control, tuneGrid = expand.grid(size = c(1, 2, 3, 4), decay = c(0.001, 0.1, 1.0, 2.0, 5.0)))
nnet_pred_2 <- predict(nnet_model_2, test)
plot(nnet_model_2)
confusionMatrix(nnet_pred_2, test_labels)

#Modelo basado en correlaciones
nnet_model_3 <- train(highpm10 ~ temp2m + winddirection + windspeed, data = train, method = "nnet", trControl = t_control, tuneGrid = expand.grid(size = c(1, 2, 3), decay = c(0.001, 0.1, 1.0, 2.0, 5.0)))
nnet_pred_3 <- predict(nnet_model_3, test)
confusionMatrix(nnet_pred_3, test_labels)