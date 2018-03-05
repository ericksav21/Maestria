setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 2/Ej5")
library("gdata")
library("GGally")
library("kohonen")

data <- read.xls("data.xlsx")
f_data <- data[data$year == 2016, ]
f_data[[1]] <- NULL
f_data[[2]] <- NULL

sn <- f_data[, colSums(is.na(f_data)) < (1 - 0.9) * nrow(f_data)]
sn <- sn[, -1]
print(f_data)

#Hacer PCA
PCA <- princomp(~., sn, na.action = na.exclude)
loadings(PCA)
summary(PCA)
biplot(PCA)
ggpairs(sn, diag = list(continuous = "density"), axisLabels = "none")

#SOM
data_train_matrix <- data.matrix(sn)
som_grid <- somgrid(xdim = 10, ydim = 10, topo = "hexagonal")
som_model <- supersom(data_train_matrix, 
                 grid=som_grid, 
                 rlen=100, 
                 alpha=c(0.05, 0.01), 
                 keep.data = TRUE )

plot(som_model, type = "property", property = getCodes(som_model)[,4], main=colnames(getCodes(som_model))[4])

#Dendograma
rownames(sn) <- f_data$country
scale = scale(sn)
d = dist(scale, method = "euclidean") # definimos la distancia
fit = hclust(d)  # definimos el método para hacer clusters
# Generamos el dendograma
plot(fit, main="") 
rect.hclust(fit, 3, border=rainbow(2))

#Isomap
data_train_matrix <- data.matrix(sn)
d_low = Iso