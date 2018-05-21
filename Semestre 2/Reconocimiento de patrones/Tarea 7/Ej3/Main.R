library("rpart")
library("ada")
library("caret")

#Cambiar el directorio actual
setwd("directorio")

data <- as.data.frame(read.table("spambase.data", sep = ",", header = FALSE))
names(data)[length(names(data))] <- "Y"
data$Y <- factor(data$Y)

train_data_per <- 0.75
shuffled_data <- data[sample(nrow(data)),]
smp_size <- floor(train_data_per * nrow(data))
train_ind <- sample(seq_len(nrow(data)), size = smp_size)

train <- shuffled_data[train_ind, ]
test <- shuffled_data[-train_ind, ]
test_labels <- test$Y
#test$Y <- NULL

#Entrenamiento de los árboles de decisión
no_trees <- 100
no_pred <- trunc(sqrt(ncol(train)))
predictions <- matrix(nrow = nrow(test), ncol = no_trees)
for(i in 1 : no_trees) {
  pred <- names(train)[sample(1 : (ncol(train) - 1), no_pred, replace = F)]
  variables <- as.formula(paste("Y ~ ", paste(pred, collapse = "+")))
  sub_set <- train[sample(1 : nrow(train), replace = T), ]
  fit <- rpart(variables, method = "class", data = sub_set)
  predictions[, i] <- predict(fit, newdata = test, type = "class")
  #Plot del modelo cada 10 iteraciones
  if(i %% 10 == 0) {
    plot(fit, uniform = TRUE, main = "Classification Tree for SPAM")
    text(fit, use.n = TRUE, all = TRUE, cex = .8)
  }
}
results <- rep(0, nrow(test))
for(i in 1 : nrow(test)) {
  no_c1 <- 0
  no_c2 <- 0
  for(j in 1 : no_trees) {
    if(predictions[i, j] == 1) {
      no_c1 <- no_c1 + 1
    }
    else {
      no_c2 <- no_c2 + 1
    }
  }
  if(no_c1 > no_c2) {
    results[i] <- 0
  }
  else {
    results[i] <- 1
  }
}
results <- factor(results)
confusionMatrix(results, test$Y)

#Hacer boosting
test_data_per <- 0.25
smp_size <- floor(test_data_per * nrow(test))
test_ind <- sample(seq_len(nrow(test)), size = smp_size)

test_boost <- test[test_ind, ]
test_res <- test[-test_ind, ]
control <- rpart.control(cp = -1, maxdepth = 14, maxcompete = 1, xval = 0)
boost <- ada(Y ~ ., data = train, test.x = test_boost[, -ncol(test_boost)], test.y = test_boost[, ncol(test_boost)], type = "discrete", control = control, iter = 70)
pred_boost <- predict(boost, newdata = test_res[, -ncol(test_res)])
test_labels <- test_res[, ncol(test_res)]
confusionMatrix(pred_boost, test_labels)
