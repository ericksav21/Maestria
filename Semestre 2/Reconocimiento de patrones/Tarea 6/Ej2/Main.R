library("tm")
library("SnowballC")
library("e1071")
library("caret")

#data_dir <- "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 6/Ej2/data"
data_dir <- "/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 6/Ej2/data"

text <- Corpus(DirSource(data_dir))
matrix_d <- DocumentTermMatrix(text, control = list(minWordLength = 2, minDocFreq = 5, stemming = T, removePunctuation = T, removeNumbers = T))
d <- DocumentTermMatrix(text, list(dictionary = findFreqTerms(matrix_d, 7)))

c1_n <- 7
c2_n <- 7
train_data_per <- 0.8
no_tests <- 30
classes_v <- factor(c(rep(0, c1_n), rep(1, c2_n)))
a1 <- data.frame(as.matrix(d), classes_v)
colnames(a1)[ncol(a1)] <- 'y'
for(i in 1 : no_tests) {
  shuffled_data <- a1[sample(nrow(a1)), ]
  smp_size <- floor(train_data_per * nrow(a1))
  train_ind <- sample(seq_len(nrow(a1)), size = smp_size)
  
  train_data <- shuffled_data[train_ind, ]
  test_data <- shuffled_data[-train_ind, ]
  
  train_control <- trainControl(method = "cv", number = 10)
  costs <- expand.grid(C = c(0, 0.01, 0.1, 0.5, 1.5))
  model <- train(y ~ ., data = train_data, trControl = train_control, method = "svmLinear", tuneGrid = costs, tuneLength = 5)
  #fit <- svm(y ~ ., data = a1, kernel = "polynomial", type = "C-classification", scale = F)
  
  #Predecir con datos de prueba
  test_labels <- test_data[, ncol(test_data)]
  test_data_f <- test_data[, -ncol(test_data)]
  test_pred <- predict(model, test_data_f)
  print(test_labels)
  print(test_pred)
  print("")
}

#confusionMatrix(test_pred, test_labels)
#plot(model)