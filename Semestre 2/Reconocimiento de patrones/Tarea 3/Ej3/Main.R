#setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 3/Ej3")
setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 3/Ej3")
d <- read.table("hepatlon")

data = d[1:7]
data = scale(data)
p = prcomp(data, center = TRUE, scale = TRUE)
set.seed(7)
biplot(p)

no_clusters <- 4
km <- kmeans(as.matrix(data), no_clusters, nstart = 20, iter.max = 100)
print(km)

#Número de grupos
#wss <- rep(0, 6)
wss <- (nrow(nrm) - 1) * sum(var(as.vector(nrm)))
for (i in 1:5){
  wss[i] <- sum(kmeans(as.vector(nrm), centers = i)$withinss)
}

plot(1:5, wss, type = "b", xlab = "Número de grupos",
     ylab = "Suma de cuadrados entre grupos")

d = dist(nrm, method = "euclidean") # definimos la distancia
fit = hclust(d)  # definimos el método para hacer clusters
# Generamos el dendograma
plot(fit, main = "") 
rect.hclust(fit, 2, border = rainbow(2))