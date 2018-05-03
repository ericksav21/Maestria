library("tm")
library("SnowballC")
library("e1071")
library("caret")

data_1_dir <- "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 6/Ej2/data1"
data_2_dir <- "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 6/Ej2/data2"
text_1 <- Corpus(DirSource(data_1_dir))
matrix_1 <- DocumentTermMatrix(text_1, control = list(minWordLength = 2, minDocFreq = 5, stemming = T, removePunctuation = T, removeNumbers = T))
d1 <- DocumentTermMatrix(text_1, list(dictionary = findFreqTerms(matrix_1, 7)))

text_2 <- Corpus(DirSource(data_2_dir))
matrix_2 <- DocumentTermMatrix(text_2, control = list(minWordLength = 2, minDocFreq = 5, stemming = T, removePunctuation = T, removeNumbers = T))
d2 <- DocumentTermMatrix(text_2, list(dictionary = findFreqTerms(matrix_2, 4)))

a1 <- as.matrix(d1)
a2 <- as.matrix(d2)
cn1 <- colnames(a1)
cn2 <- colnames(a2)
string_1 <- paste(cn1, collapse = " ")
string_2 <- paste(cn2, collapse = " ")
concat <- c(string_1, string_2)
corpus <- VCorpus(VectorSource(concat))
tdm <- DocumentTermMatrix(corpus, list(removePunctuation = T, stopwords = T, stemming = T, removeNumbers = T))
train <- as.matrix(tdm)
train <- cbind(train, c(0, 1))
colnames(train)[ncol(train)] <- 'y'
train <- as.data.frame(train)
train$y <- as.factor(train$y)

fit <- svm(y ~ ., data = train, kernel = "polynomial", type = "C-classification", scale = F)
#fit <- train(y ~ ., data = train, method = "bayesglm")
pred = predict(fit, newdata = train[-ncol(train)], interval = "prediction")
as.matrix(pred)