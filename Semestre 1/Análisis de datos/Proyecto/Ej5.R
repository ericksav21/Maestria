library(MASS)

ej1 <- function(datos) {
  len <- length(datos$duration)
  dduration <- datos$duration
  wwaiting <- datos$waiting
  
  waiting <- wwaiting[-1]
  duration <- dduration[-len]
  
  #Parte A
  predictor <- lm(waiting ~ duration, data=datos)
  predictorM <- lm(waiting ~ I(duration^2) + I(duration^3), data=datos)
  
  return(list(p = predictor, pm = predictorM))
}

ej2 <- function(datos) {
  len <- length(datos$duration)
  duration <- datos$duration
  waiting <- datos$waiting
  
  #Mejora del modelo añadiendo predictores
  w1 <- waiting[-1]
  w11 <- w1[-length(w1)] #Tiene -2 valores pero comienza en i+1
  w2 = w1[-1] #Tiene -2 valores pero comienza en i+2
  
  d1 <- duration[-1]
  d11 <- d1[-length(d1)] #Tiene -2 valores y comienza en i+1
  
  d2 <- duration[-len] #Tiene -2 valores pero sigue comenzando en i
  d22 <- d2[-length(d2)]
  
  predictorB <- lm(w2 ~ d11 + d22 + w11)
  
  return(predictorB)
}

vc1 <- function(datos) {
  #Validación cruzada
  k <- 5
  datos$id <- sample(1:k, nrow(datos), replace=TRUE)
  lista <- 1:k
  errores <- c()
  
  for(i in 1:k) {
    gPrueba <- subset(datos, id %in% i)
    gEntrenamiento <- subset(datos, id %in% lista[-i])
    
    modelo <- ej1(gEntrenamiento)$p
    predictor <- predict(modelo, gPrueba)
    ei <- (predictor - gPrueba$waiting)^2
    errores <- sqrt(mean(ei))
  }
  return(mean(errores))
}

vc2 <- function(datos) {
  #Validación cruzada
  k <- 5
  datos$id <- sample(1:k, nrow(datos), replace=TRUE)
  lista <- 1:k
  errores <- c()
  
  for(i in 1:k) {
    gPrueba <- subset(datos, id %in% i)
    gEntrenamiento <- subset(datos, id %in% lista[-i])
    
    modelo <- ej2(gEntrenamiento)
    
    duration <- gPrueba$duration
    waiting <- gPrueba$waiting
    
    w1 <- waiting[-1]
    w11 <- w1[-length(w1)]
    w2 = w1[-1]
    
    d1 <- duration[-1]
    d11 <- d1[-length(d1)]
    
    d2 <- duration[-length(duration)]
    d22 <- d2[-length(d2)]
    mPredictor <- data.frame(d11 = d11, d22 = d22, w11 = w11, w2 = w2)
    predictor <- predict(modelo, mPredictor)
    ei <- (predictor - mPredictor$w2)^2
    errores <- sqrt(mean(ei))
  }
  return(mean(errores))
}

datos <- data.frame(geyser)

pej1 <- ej1(datos);

summary(pej1$p)
summary(pej1$pm)

#Obtener el intervalo de confianza para el valor de Y
dp <- data.frame(duration = 4.5)
pd <- predict(pej1$p, dp, interval="prediction")
print(pd)

predictorB <- ej2(datos)
summary(predictorB)

paste(c("Error medio de predicción (modelo 1): ", vc1(datos)), collapse = "")
paste(c("Error medio de predicción (modelo 2): ", vc1(datos)), collapse = "")