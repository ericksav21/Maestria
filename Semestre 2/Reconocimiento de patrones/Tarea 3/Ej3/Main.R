setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 3/Ej3")
#setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 3/Ej3")
d <- read.table("hepatlon")
library("GGally")
library("factoextra")

data = d[1:7]
print(data)
data = scale(data)
p = prcomp(data, center = TRUE, scale = TRUE)
set.seed(7)
#biplot(p)
postscript("Biplot_kmeans_separated.eps")
fviz_pca_biplot(p, label="var", habillage=kmeans(as.matrix(data), 3, nstart=20)$cluster, addEllipses=TRUE, ellipse.level=0.95)
dev.off()

no_clusters <- 3
km <- kmeans(as.matrix(data), no_clusters, nstart = 20, iter.max = 100)
print(km)

#Número de grupos
#wss <- rep(0, 6)
wss <- (nrow(data) - 1) * sum(var(as.vector(data)))
for (i in 1:5){
  wss[i] <- sum(kmeans(as.vector(data), centers = i)$withinss)
}

print(wss)
plot(1:5, wss, type = "b", xlab = "Número de grupos",
     ylab = "Suma de cuadrados entre grupos")

d = dist(data, method = "euclidean") # definimos la distancia
fit = hclust(d)  # definimos el método para hacer clusters
# Generamos el dendograma
plot(fit, main = "") 
rect.hclust(fit, 3, border = rainbow(3))