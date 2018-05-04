library("tm")
library("SnowballC")
library("e1071")
library("caret")

data_1_dir <- "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 6/Ej2/data1"
data_2_dir <- "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 6/Ej2/data2"
#data_1_dir <- "/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 6/Ej2/data1"
#data_2_dir <- "/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 6/Ej2/data2"

text_1 <- Corpus(DirSource(data_1_dir))
matrix_1 <- DocumentTermMatrix(text_1, control = list(minWordLength = 2, minDocFreq = 5, stemming = T, removePunctuation = T, removeNumbers = T))
d1 <- DocumentTermMatrix(text_1, list(dictionary = findFreqTerms(matrix_1, 7)))

c_c <- c(0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1)
c_c <- factor(c_c)
a1 <- data.frame(as.matrix(d1), c_c)
colnames(a1)[ncol(a1)] <- 'y'
#a1[, ncol(a1)] <- as.factor(a1[, ncol(a1)])
train_control <- trainControl(method = "cv", number = 10)
costs <- expand.grid(C = c(0, 0.01, 0.1, 0.5, 1.5))
model <- train(y ~ ., data = a1, trControl = train_control, method = "svmLinear", tuneGrid = costs, tuneLength = 5)
#fit <- svm(y ~ ., data = a1, kernel = "polynomial", type = "C-classification", scale = F)
test_pred <- predict(model, newdata = a1[, -ncol(a1)])
confusionMatrix(test_pred, a1[, ncol(a1)])
plot(model)