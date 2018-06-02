#install.packages("twitteR")
#install.packages("httr")
#install.packages("SchedulerR")
#install.packages("jsonlite")
#
library("jsonlite")
library("twitteR")
library("httr")
library("gmapsdistance")
key <-set.api.key("AIzaSyDQkoDE9JSpotkOyI7Ohe2sjChJTKF1itE")
Origin = c("Estadio+Olímpico+de+Kiev")
results = gmapsdistance(origin = "GUADALAJARA", destination = "GUANAJUATO", mode="driving", key=key)


###twitter user-information
api_key="Fd0jEFSQWbOXtVGFDOfyR36iP"
api_secret="xJjBGJpqG6adKKZjytmhdKxECOpc99BJ79ZIxpTx8S6aw4LgW8"
access_token="845719437537792000-QT6DmYHQTOyggembsdE4hTza73kfp6y"
access_token_secret="uTH8Jm7uABtcj9HXy3Ns5xJPDI0DRYUmYpmAMXYKEBJDR"
setup_twitter_oauth(api_key,api_secret,access_token,access_token_secret)
clinton_tweets <- userTimeline("Guanajuato", n = 3200)
tweetsc.df <- twListToDF(clinton_tweets)
dim(tweetsc.df)
#date<-Sys.Date()
#date<-as.character(date)
#name<-paste(date,".RData")
##Finally we save the Rdata using as name the date from the download
#save(tweetsc.df, file =name)


##API http://developer.active.com/docs/read/v2_Activity_API_Search
LOCATION = "Mexico"
Query = paste("http://api.amp.active.com/v2/search?query=",LOCATION, sep="")
Query = paste(Query,"&api_key=3hyargr4q44r255jzhytmtzj&radius=10000", sep="")
r <- GET(Query)
data=fromJSON(Query)
data$results$assetTopics[[2]]$topic$topicName
data$results$assetName
data$results$salesStartDate
data$results$salesEndDate
