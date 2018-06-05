#install.packages("twitteR")
#install.packages("httr")
#install.packages("SchedulerR")
#install.packages("jsonlite")
#
library("openssl")
library("httpuv")
library("jsonlite")
library("twitteR")
library("httr")
library("gmapsdistance")
library("lubridate")#devtools::install_github("tidyverse/lubridate")



Librarykeys = read.table("keys")
#kk="AIzaSyAhNh7Y4E3BH-GOD2KdlTY31byV-3ZwLHk" #gmail
kk = levels(Librarykeys$V1)[1]# "AIzaSyB8dI2oIr38C4teOTdrs1QCyYcX9YV476k" #cimat

key<-set.api.key(kk)

## 
MAX_RECORRIDO = 3
RANDOM_KM = 2000
NUMBER_RANDOMPOINT=6
UPDATE_SLEEP= 60  #second

###twitter user-information
api_key="Fd0jEFSQWbOXtVGFDOfyR36iP"
api_secret="xJjBGJpqG6adKKZjytmhdKxECOpc99BJ79ZIxpTx8S6aw4LgW8"
access_token="845719437537792000-QT6DmYHQTOyggembsdE4hTza73kfp6y"
access_token_secret="uTH8Jm7uABtcj9HXy3Ns5xJPDI0DRYUmYpmAMXYKEBJDR"
setup_twitter_oauth(api_key,api_secret,access_token,access_token_secret)

PointsCoutry1 = read.table("Points", head=1)
PointsCoutry2 = read.table("Points", head=1)
#names(PointsCoutry1)=c("Origin", "Destine")
#names(PointsCoutry2)=c("Origin", "Destine")

print(Librarykeys)
print(kk)

places = read.table("places2")




GetInformation <-function(distanceInfo, Origin, Destine)
{
	
	###Obtener la información en esta trayectoria..
	GeneralData = data.frame(matrix(nrow=1, ncol= length(distanceInfo)+length(places[,1])+3))
	names(GeneralData) = c(names(distanceInfo), "Query_Time","twitterFavoriteCount","twitterRetweetCount",as.character(places$V1) )
	GeneralData$Time = distanceInfo$Time
	GeneralData$Distance = distanceInfo$Distance
	GeneralData$Status = distanceInfo$Status
	GeneralData$Query_Time = TIME = as.numeric(as.POSIXct(Sys.time())) 
	
	#https://developers.google.com/maps/documentation/directions/intro?hl=es-419
	#https://developers.google.com/places/web-service/search?hl=es-419
	#https://developers.google.com/maps/documentation/distance-matrix/intro?hl=es-419
	#https://cran.rstudio.com/web/packages/mapsapi/vignettes/intro.html
	
	##Consultar indicaciones.....
	Query1=""
	Query1 = paste("https://maps.googleapis.com/maps/api/directions/json?origin=",Origin, sep="")
	Query1 = paste(Query1,"&destination=", sep="") ##Ordenar los lugares por distancia...
	Query1 = paste(Query1,Destine, sep="")
	Query1 = paste(Query1,"&key=", sep="")
	Query1 = paste(Query1,kk, sep="")
	
	data = fromJSON(content(GET(Query1), as =  "text", enconding=UTF-8))

	indexplace=1
	for(j in 7:(6+length(places[,1]))) ##para cada tipo de lugar
	{
		GeneralData[j] = 0	
		routes = data$routes$legs[[1]]$steps[[1]]
		indexSortex=order(routes$duration$value, decreasing=TRUE)
		for( i in 1:min(MAX_RECORRIDO, length(indexSortex)))##Para cada escala o ruta
		{
		      result= DownloadObjectjSON( routes$start_location[indexSortex[i],], as.character(levels(places$V1)[indexplace]) )
		      GeneralData[j] = GeneralData[j]+ mean(result$results$rating, na.rm=TRUE) #getAverageRatings(result)
		}
	  indexplace = indexplace+1
	}

	####Twitter....
	routes = data$routes$legs[[1]]$steps[[1]]
		GeneralData$twitterFavoriteCount = 0
		GeneralData$twitterRetweetCount = 0

		indexSortex=order(routes$duration$value, decreasing=TRUE)
		for( i in 1:min(MAX_RECORRIDO, length(indexSortex)))##Para cada escala o ruta
		{
		      geo=""
		      geo = paste(geo,routes$start_location[indexSortex[i],]$lat, sep="")
		      geo = paste(geo,",", sep="")
		      geo = paste(geo,routes$start_location[indexSortex[i],]$lng, sep="")
		      geo = paste(geo,",2km", sep="")
			get=searchTwitter("", geocode=geo, n=100)
			if(length(get)>2)
			{
		          twitdata=twListToDF(get)
		          timest =abs(hour(Sys.time()) -  hour(twitdata$created))
		          GeneralData$twitterFavoriteCount=GeneralData$twitterFavoriteCount + sum(twitdata$favoriteCount[timest<=100]) 
		          GeneralData$twitterRetweetCount=GeneralData$twitterRetweetCount + sum(twitdata$retweetCount[timest<=100]) 
			}
		}

	#clinton_tweets <- userTimeline("IRAPUATO", n = 3200)
	#tweetsc.df <- twListToDF(twitdata)$created
	#dim(tweetsc.df)
	#date<-Sys.Date()
	#date<-as.character(date)
	#name<-paste(date,".RData")
	##Finally we save the Rdata using as name the date from the download
	#save(tweetsc.df, file =name)



   return (GeneralData)
}

DownloadObjectjSON <-function(location, type)
{
          for( i in levels(Librarykeys$V1))
         {
      	
	   LOCATION = ""
	   LOCATION=paste(LOCATION, location$lat, sep="")
	   LOCATION=paste(LOCATION, ",", sep="")
	   LOCATION=paste(LOCATION, location$lng, sep="")
	   #print(LOCATION)

	   Query2 = paste("https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=",LOCATION, sep="")
	   Query2 = paste(Query2,"&", sep="")
	   Query2 = paste(Query2,"type=", sep="") ##Ordenar los lugares por distancia...
	   Query2 = paste(Query2, type, sep="") ##Ordenar los lugares por distancia...
	   #Query2 = paste(Query2,"&", sep="")
	   #Query2 = paste(Query2,"keyword=oxxo", sep="") ##palabra clave de búsqueda...
	   Query2 = paste(Query2,"&", sep="")
	   Query2 = paste(Query2,"rankby=distance", sep="") ##Ordenar los lugares por distancia...
	   Query2 = paste(Query2,"&", sep="")
	   Query2 = paste(Query2,"key=", sep="")
	   Query2 = paste(Query2,kk, sep="")
           
	   result = fromJSON(content(GET(Query2), as =  "text", enconding=UTF-8))
	   print(Query2)
	   if(result$status == "OK" || result$status == "ZERO_RESULTS" )
           {
             return (result)
           }
           else if(result$status == "OVER_QUERY_LIMIT")
           {
	      kk = i
	      key<-set.api.key(kk)
           }
	   else{quit() } 
         }
}



GenerateSaveInfo <- function(Origin, Destine)
{
   for( i in levels(Librarykeys$V1))
   {
      distanceInfo= gmapsdistance(origin = Origin, destination = Destine, mode="driving", key=key)	
      row=GetInformation(distanceInfo, Origin, Destine)
      row$Origin=Origin
      row$Destine=Destine
      if(distanceInfo$Status == "OK")
      {
         return (row)
      }
      else if(distanceInfo$Status == "OVER_QUERY_LIMIT")
      {
	kk = i
	key<-set.api.key(kk)
      }
	else{quit() } 
   }
}

generateRandomPoint <- function(latitude, longitude, radius, n) {
  rd <- radius / 111300
  u <- runif(n, 0, 1)
  v <- runif(n, 0, 1)
  
  w <- rd * sqrt(u)
  t <- 2 * pi * v
  x <- w * cos(t)
  y <- w * sin(t)
  
  xp <- x / cos(latitude)
  res <- c(y + latitude, xp + longitude)
  return(res)
}

#Origin = "GUADALAJARA"
#Destine = "GUANAJUATO"

#for( i in 1:length(Points[,1]))
#{
#   write.table(GenerateSaveInfo(Points$Origin[i], Points$Destine[i]) , "Report.txt", row.names=FALSE, append=TRUE )
#}
###Guardar los headers....

for( i in 1:NUMBER_RANDOMPOINT)
{
  lat = "40.704404"
  lon = "-73.878401"
	#lat = "39.851429"
  #lon = "-98.580085"
	orig = paste(as.numeric(lat),as.numeric(lon), sep=",")#:"19.303215,-99.150506" ##Center of EUA
	newpoint =   paste(generateRandomPoint(as.numeric(lat), as.numeric(lon),RANDOM_KM,1), collapse=",")
	row=data.frame(newpoint,orig )
	names(row) = names(PointsCoutry1)
	PointsCoutry1 = rbind(PointsCoutry1, row)#paste(newpoint[1], newpoint[2], sep=",") ))

	lat = "23.9197222"
        lon = "-102.16250000000001"
	orig = paste(lat, lon, sep=",")#:"19.303215,-99.150506" ##Center of EUA
	newpoint =   paste(generateRandomPoint(as.numeric(lat),as.numeric(lon),RANDOM_KM,1), collapse=",")
	row=data.frame(newpoint,orig )
	names(row) = names(PointsCoutry2)
	PointsCoutry2 = rbind(PointsCoutry2, row)#paste(newpoint[1], newpoint[2], sep=",") ))

}
for( i in 1:length(PointsCoutry1[,1]))
   {
	value = GenerateSaveInfo(PointsCoutry1$Origin[i], PointsCoutry1$Destine[i])
        write.table( value, append=TRUE, col.names=FALSE, "EUA.txt", row.names=FALSE )
        write.table(names(value), "names.txt")
	print(names(value))
	value = GenerateSaveInfo(PointsCoutry2$Origin[i], PointsCoutry2$Destine[i])
        write.table( value, append=TRUE, col.names=FALSE, "MEXICO.txt", row.names=FALSE )
   }

TIME = as.numeric(as.POSIXct(Sys.time())) 
while(1)
{
   Sys.sleep(UPDATE_SLEEP-as.numeric(as.numeric(as.POSIXct(Sys.time()))-TIME))
   for( i in 1:length(PointsCoutry1[,1]))
   {
      write.table(GenerateSaveInfo(PointsCoutry1$Origin[i], PointsCoutry1$Destine[i]) , append=TRUE, col.names=FALSE, "EUA.txt", row.names=FALSE )
      write.table(GenerateSaveInfo(PointsCoutry2$Origin[i], PointsCoutry2$Destine[i]) , append=TRUE, col.names=FALSE, "MEXICO.txt", row.names=FALSE )
   }
   TIME = as.numeric(as.POSIXct(Sys.time())) 
}



###API http://developer.active.com/docs/read/v2_Activity_API_Search
#LOCATION = "GUANAJUATO"
#Query = paste("http://api.amp.active.com/v2/search?query=",LOCATION, sep="")
#Query = paste(Query,"&api_key=3hyargr4q44r255jzhytmtzj&radius=10000", sep="")
#r <- GET(Query)
#data=fromJSON(Query)
#data$results$assetTopics[[2]]$topic$topicName
#data$results$assetName
#data$results$salesStartDate
#data$results$salesEndDate
