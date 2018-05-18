library("rpart")

#setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 7/Ej3")
setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 7/Ej3")

data <- as.data.frame(read.table("spambase.data", sep = ",", header = FALSE))
names(data)[length(names(data))] <- "Y"
data$Y <- factor(data$Y)

train_data_per <- 0.75
shuffled_data <- data[sample(nrow(data)),]
smp_size <- floor(train_data_per * nrow(data))
train_ind <- sample(seq_len(nrow(data)), size = smp_size)

train <- shuffled_data[train_ind, ]
test <- shuffled_data[-train_ind, ]

#Entrenamiento de los árboles de decisión
fit <- rpart(Y ~ ., method = "class", data = train)
printcp(fit)
plot(fit, uniform = TRUE, main = "Classification Tree for SPAM")
text(fit, use.n = TRUE, all = TRUE, cex = .8)