#setwd("/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 1")
setwd("/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Reconocimiento de patrones/Tarea 1")
d <- read.table("hepatlon")

print(d)
p <- princomp(cbind(d$hurdles, d$highjump, d$shot, d$run200m, d$longjump, d$javelin, d$run800m))
loadings(p)
summary(p)
biplot(p)

plot(p$scores[, 1], d$score)