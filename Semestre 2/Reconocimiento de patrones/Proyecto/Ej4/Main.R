library("pscl")

#Ejercicio 4

#Cambiar el directorio actual
setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Proyecto/Ej4/")
#setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Proyecto/Ej4/")

#Leer los datos
data <- as.data.frame(read.table("data.txt", sep = ",", header = TRUE))

logit <- function(x) {
  return(1 / (1 + exp(-x)))
}

#Definir todos los modelos
m1 <- glm(cbind(Y, N) ~ Race + AZT, family = binomial(logit), data = data)
m2 <- glm(cbind(Y, N) ~ Race, family = binomial(logit), data = data)
m3 <- glm(cbind(Y, N) ~ AZT, family = binomial(logit), data = data)
m4 <- glm(cbind(Y, N) ~ Race * AZT, family = binomial(logit), data = data)

#Resultados del entrenamiento
summary(m1)
summary(m2)
summary(m3)
summary(m4)

#pR2 test a los modelos
pR2(m1)
pR2(m2)
pR2(m3)
pR2(m4)

#Test ANOVA en los modelos
anova(m1, m2, test = "Chisq")
anova(m1, m3, test = "Chisq")
anova(m1, m4, test = "Chisq")