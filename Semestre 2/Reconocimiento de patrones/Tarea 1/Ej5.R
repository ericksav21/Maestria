setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 1")
#setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 1")
temp <- matrix(scan("oef2.data.dat"), 35, 12, byrow = T)

nombresestaciones <- c("St. John_s", "Charlottetown", "Halifax",
                       "Sydney", "Yarmouth", "Fredericton",
                       "Arvida", "Montreal", "Quebec City",
                       "Schefferville", "Sherbrooke", "Kapuskasing",
                       "London", "Ottawa", "Thunder Bay",
                       "Toronto", "Churchill", "The Pas",
                       "Winnipeg", "Prince Albert", "Regina",
                       "Beaverlodge", "Calgary", "Edmonton",
                       "Kamloops", "Prince George", "Prince Rupert",
                       "Vancouver", "Victoria", "Dawson",
                       "Whitehorse", "Frobisher Bay", "Inuvik",
                       "Resolute", "Yellowknife")

rownames(temp) <- nombresestaciones
p <- princomp(temp)
print(temp)
loadings(p)
summary(p)
biplot(p)
i <- seq(1, length(p$scores[,1]))
print(p$scores)
j <- seq(1, length(p$scores[,2]))
plot(i, p$scores[,1], xlab = "i", ylab = "1er CP", title("Gráfica del primer CP"))
lines(i, p$scores[,1])
plot(j, p$scores[,2], xlab = "i", ylab = "2do CP", title("Gráfica del segundo CP"))
lines(j, p$scores[,2])