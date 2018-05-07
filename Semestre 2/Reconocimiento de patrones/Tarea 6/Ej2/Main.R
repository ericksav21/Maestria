library("tm")
library("SnowballC")
library("e1071")
library("caret")

#Directorio donde estan los dos conjuntos de datos
data_dir <- "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 6/Ej2/data"
#data_dir <- "/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 6/Ej2/data"

#Leer los datos y crear la matriz de ocurrencias de palabras
text <- Corpus(DirSource(data_dir))
matrix_d <- DocumentTermMatrix(text, control = list(minWordLength = 2, minDocFreq = 5, stemming = T, removePunctuation = T, removeNumbers = T))
d <- DocumentTermMatrix(text, list(dictionary = findFreqTerms(matrix_d, 7)))

#Numero de archivos por cada clase
c1_n <- 990
c2_n <- 994
train_data_per <- 0.8
#Añadir las etiquetas de las clases a la matriz anterior
classes_v <- factor(c(rep(0, c1_n), rep(1, c2_n)))
a1 <- data.frame(as.matrix(d), classes_v)
colnames(a1)[ncol(a1)] <- 'y'
#Crear aleatoriamente los conjuntos de prueba y entrenamiento
shuffled_data <- a1[sample(nrow(a1)), ]
smp_size <- floor(train_data_per * nrow(a1))
train_ind <- sample(seq_len(nrow(a1)), size = smp_size)

train_data <- shuffled_data[train_ind, ]
test_data <- shuffled_data[-train_ind, ]

#Crear el modelo usando una SVM con kernel lineal
train_control <- trainControl(method = "cv", number = 10)
costs <- expand.grid(C = c(0, 0.01, 0.1, 0.5, 1.5, 2.5, 5, 10))
#Pueden salir warnings, pero esto no influye en el entrenamiento del modelo.
model <- train(y ~ ., data = train_data, trControl = train_control, method = "svmLinear", tuneGrid = costs, tuneLength = 5)

#Predecir con datos de prueba
test_labels <- test_data[, ncol(test_data)]
test_data_f <- test_data[, -ncol(test_data)]
test_pred <- predict(model, test_data_f)
#Obtener el porcentaje de aciertos obtenidos en las predicciones
avg_acc <- 0.0
r1 <- as.vector(test_labels, mode = "integer")
r2 <- as.vector(test_pred, mode = "integer")
for(i in 1 : length(r1)) {
  if(r1[i] == r2[i]) {
    avg_acc = avg_acc + 1;
  }
}
avg_acc = avg_acc / length(test_labels);
print(sprintf("Porcentaje de aciertos con el conjunto de prueba: %f\n", avg_acc));

#Matriz de confusion
confusionMatrix(test_pred, test_labels)
#Plot del accuracy generado en la CV con los diferentes parametros de penalizacion
plot(model)