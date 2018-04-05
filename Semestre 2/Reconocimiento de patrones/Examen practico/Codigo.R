setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Examen practico")
library("gdata")
library("GGally")
library("kohonen")
library("missMDA")
library("cluster")
require("kohonen")

data <- read.xls("data.xls")
f_data <- data[data$year == 2017, ]
f_data_old <- data[data$year == 2016, ]
f_data[[1]] <- NULL
f_data[[1]] <- NULL
f_data_old[[1]] <- NULL
f_data_old[[1]] <- NULL

sn <- f_data[, colSums(is.na(f_data)) < (1 - 0.8) * nrow(f_data)]
sn_2 <- f_data_old[, colSums(is.na(f_data_old)) < (1 - 0.8) * nrow(f_data_old)]

#---------- Datos de 2017 ----------#
#Imputar las celdas que tienen NA
sn <- imputePCA(sn)
sn <- data.frame(sn$completeObs)
rownames(sn) <- data[data$year == 2017, ]$country

#Hacer PCA
PCA <- princomp(sn, cor = T)
loadings(PCA)
summary(PCA)
biplot(PCA)

#Trabajar con las proyecciones que aporten la mayor variabilidad
reduced <- PCA$scores[, 1:6]
rownames(reduced) <- data[data$year == 2017, ]$country

#Definimos el método para hacer clusters
fit = hclust(dist(reduced, method = "euclidean"))
#Generamos el dendograma
plot(fit, main = "Dendograma del conjunto de datos 2017") 
rect.hclust(fit, 3, border = rainbow(3))

#fviz_pca_biplot(prcomp(sn, center = T, scale = T), label="var", habillage = kmeans(as.matrix(sn), 3, nstart = 20)$cluster, addEllipses = T, ellipse.level = 0.95) + geom_text_repel(aes(label = rownames(sn)))

#Hacemos KMeans
km <- kmeans(as.matrix(reduced), 3, nstart = 20)
clusplot(sn, km$cluster, main="K-Means del conjunto de datos 2017",
         color = T, col.p = km$cluster, shade = TRUE,
         labels = 2, lines = 0, xlab = "", ylab = "")


#Hacer un SOM
data_train_matrix <- data.matrix(sn)
som_grid <- somgrid(xdim = 10, ydim = 10, topo = "hexagonal")
som_model <- supersom(data_train_matrix, 
                      grid = som_grid, 
                      rlen = 100, 
                      alpha = c(0.05, 0.01), 
                      keep.data = T)
plot(som_model, type = "property", property = getCodes(som_model)[,7], main = colnames(getCodes(som_model))[7])


#---------- Datos de 2016 ----------#
#Imputar las celdas que tienen NA
sn_2 <- imputePCA(sn_2)
sn_2 <- data.frame(sn_2$completeObs)
rownames(sn_2) <- data[data$year == 2016, ]$country

#Hacer PCA
PCA_2 <- princomp(sn_2, cor = T)
loadings(PCA_2)
summary(PCA_2)
biplot(PCA_2)

#Trabajar con las proyecciones que aporten la mayor variabilidad
reduced_2 <- PCA_2$scores[, 1:6]
rownames(reduced_2) <- data[data$year == 2016, ]$country

#Definimos el método para hacer clusters
fit_2 = hclust(dist(reduced_2, method = "euclidean"))
#Generamos el dendograma
plot(fit_2, main = "Dendograma del conjunto de datos 2016") 
rect.hclust(fit_2, 3, border = rainbow(3))

#fviz_pca_biplot(prcomp(sn, center = T, scale = T), label="var", habillage = kmeans(as.matrix(sn), 3, nstart = 20)$cluster, addEllipses = T, ellipse.level = 0.95) + geom_text_repel(aes(label = rownames(sn)))

#Hacemos KMeans
km_2 <- kmeans(as.matrix(sn_2), 3, nstart = 20)
clusplot(sn_2, km_2$cluster, main="K-Means del cojunto de datos 2016",
         color = T, col.p = km_2$cluster, shade = TRUE,
         labels = 2, lines = 0, xlab = "", ylab = "")


#Hacer un SOM
data_train_matrix_2 <- data.matrix(sn_2)
som_grid_2 <- somgrid(xdim = 10, ydim = 10, topo = "hexagonal")
som_model_2 <- supersom(data_train_matrix_2, 
                      grid = som_grid_2, 
                      rlen = 100, 
                      alpha = c(0.05, 0.01), 
                      keep.data = T)
plot(som_model_2, type = "property", property = getCodes(som_model_2)[,1], main = colnames(getCodes(som_model_2))[1])

plot(sn_2[1:nrow(sn_2) - 1, 1], sn[, 1], xlab = "Life Ladder 2016", ylab = "Life Ladder 2017", title("Contraste entre felicidad 2016-2017"), col = "blue")