sim <- rbinom(1000, 9604, 0.5) / 9604
length(sim[sim > 0.49 & sim < 0.51]) / 1000