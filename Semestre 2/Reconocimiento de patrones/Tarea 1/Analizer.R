library("rpart")
library("caret")
library("GGally")

#Cambiar el directorio actual
setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Proyecto/Ej1/metadata/")
#setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Proyecto/Ej1/metadata/")

dataAngeles <- as.data.frame(read.table("Angeles.txt", sep = " ", header = FALSE))
dataAngeles$V3 <- NULL
dataAngeles$V5 <- NULL
dataAngeles$V6 <- NULL
dataAngeles$V10 <- NULL

deg2rad <- function(deg) {
  return((deg * pi) / (180.0))
}

getDistance <- function(v1, v2) {
  s1 <- unlist(strsplit(toString(v1), ",", fixed = F))
  s2 <- unlist(strsplit(toString(v2), ",", fixed = F))
  lat1 <- as.numeric(s1[1])
  lon1 <- as.numeric(s1[2])
  lat2 <- as.numeric(s2[1])
  lon2 <- as.numeric(s2[2])
  
  r <- 6371 * 1000
  phi1 <- deg2rad(lat1)
  phi2 <- deg2rad(lat2)
  d_phi <- deg2rad(lat2 - lat1)
  d_lambda <- deg2rad(lon2 - lon1)
  
  a <- sin(d_phi / 2.0) * sin(d_phi / 2.0) + cos(phi1 / 2.0) * cos(phi2) * sin(d_lambda / 2.0) * sin(d_lambda / 2.0)
  c <- 2.0 * atan2(sqrt(a), sqrt(1.0 - a))
  
  return(r * c)
}

rows <- dim(dataAngeles)[1]
dataAngeles <- cbind(dataAngeles, rep(0, rows))
colnames(dataAngeles)[dim(dataAngeles)[2]] <- "distance"
for(i in 1 : rows) {
  dataAngeles$distance[i] <- getDistance(dataAngeles$V19[i], dataAngeles$V20[i])
}
dataAngeles$V19 <- NULL
dataAngeles$V20 <- NULL

ggpairs(dataAngeles, axisLabels = "none")
#p <- princomp(dataAngeles, cor = T)
#summary(p)
#biplot(p)

logit <- function(x) {
  return(1 / (1 + exp(-x)))
}

model <- glm(V2 ~ ., data = dataAngeles)
res <- predict(model, dataAngeles)