for(i in 1:50) {
  x <- runif(1, 0, 2)
  print(paste(c("El valor elegido para X es: ", x)))
  U <- runif(100, 0, 1)
  #Y <- (U * runif(100, 0, 2)) / 2
  Y <- (U * x) / 2
  print(cor(U, Y))
  #print(paste(c("La correlación de X con Y es: ", cor(U, Y))))
}