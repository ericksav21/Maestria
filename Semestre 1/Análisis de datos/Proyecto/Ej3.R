getDensidad <- function(anchoBanda, g) {
  densidad <- density(data$sbp[g], bw = anchoBanda, kernel="gaussian")
  predictor <- smooth.spline(densidad)
  return(predictor)
}

verosimilitud <- function(anchoBanda, g1, g2) {
  predictor <- getDensidad(anchoBanda, g1)
  pp <- predict(predictor, data$sbp[g2])$y
  logP <- log(pp[pp > 0])
  verosim <- sum(logP)
  return(verosim)
}

generarMuestra <- function(tieneCHD, porcentaje) {
  chd <- data$chd
  index <- 1:length(chd)
  wwchd <- index[chd == tieneCHD]
  
  m <- as.integer(length(wwchd) * porcentaje)
  sindex <- sort(sample(c(1:length(wwchd)), m, replace = F))
  A <- wwchd[sindex]
  B <- wwchd[-sindex]
  
  return(list(A = A, B = B))
}

ej1 <- function(A, B) {
  #Ancho de banda vs verosimilitud
  amin <- 2
  amax <- 10
  verAB <- c()
  verAA <- c()
  h <- c()
  vmax <- -500
  hmax <- 0
  
  for(i in seq(amin, amax, by = 0.1)) {
    vi1 <- verosimilitud(i, A, B)
    vi2 <- verosimilitud(i, A, A)
    verAB <- c(verAB, vi1)
    if(vi1 > vmax) {
      vmax <- vi1
      hmax <- i
    }
    verAA <- c(verAA, vi2)
    h <- c(h, i)
  }
  old.par <- par(mfrow = c(1, 2))
  plot(h, verAB, main="Ancho de banda vs. verosimilitud de B", xlab="Tamaño de paso (h)", ylab="Verosimilitud", type="l", col="red")
  plot(h, verAA, main="Ancho de banda vs. verosimilitud de A", xlab="Tamaño de paso (h)", ylab="Verosimilitud", type="l", col="blue")
  par(old.par)
  
  return(hmax)
}

ej2 <- function(AnoCHD, ACHD, h1, h2, rangoSBP) {
  dSBPNoCHD <- getDensidad(h1, AnoCHD)
  dSBPCCHD <- getDensidad(h2, ACHD)
  probCHD <- sum(data$chd) / length(data$chd)
  probNoCHD <- (1 - probCHD)
  pnum <- predict(dSBPCCHD, rangoSBP)$y * probCHD
  pden <- pnum + predict(dSBPNoCHD, rangoSBP)$y * probNoCHD
  pres <- pnum / pden
  
  return(pres)
}

path <- "/home/e-082017-04/Documents/Maestria/GIT/Semestre 1/Análisis de datos/Proyecto/SAheart.data"
data <- read.table(path, sep=",", head=T, row.names=1)

#Parte 1 - Trabajar con grupos que no tienen CHD
list1 <- generarMuestra(0, 0.75)
A1 <- list1$A
B1 <- list1$B
h1max <- ej1(A1, B1)
paste(c("H óptimo (No CHD): ", h1max), collapse = "")

#Repetir para los que tienen CHD
list2 <- generarMuestra(1, 0.75)
A2 <- list2$A
B2 <- list2$B
h2max <- ej1(A2, B2)
paste(c("H óptimo (CHD): ", h2max), collapse = "")

#Parte 3 - Calcular regla de Bayes para CHD | SBP
rangoSBP <- rep(100:210)
plot(rangoSBP, ej2(A1, A2, h1max, h2max, rangoSBP), type="l", main="Probabilidad de tener CHD en función del SBP", xlab="SBP", ylab="Probabilidad")