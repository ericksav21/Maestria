#install.packages("twitteR")
#install.packages("httr")
#install.packages("SchedulerR")
#install.packages("jsonlite")
#
##library("jsonlite")
##library("twitteR")
##library("httr")
library("gmapsdistance")

#kk="AIzaSyAhNh7Y4E3BH-GOD2KdlTY31byV-3ZwLHk" #gmail
kk = "AIzaSyB8dI2oIr38C4teOTdrs1QCyYcX9YV476k" #cimat

key<-set.api.key(kk)


TIME = as.numeric(as.POSIXct(Sys.time())) 


##Origin = c("irpin", "boiarka", "vasilkov", "ukrainka", "brovary", "borispol")
##Destin = Origin
##results = gmapsdistance(origin = Origin, destination = Destin, mode="driving", key=key)
##results = data.frame(results)
##results$QueryTime = rep(TIME, nrow(results))
##write.table(results, "data_near_stadium_horenka_driving.txt")
##
##
## ##DRIVING....
##origin = c("bernabeu", "horenka","anfield")
##destin = c("horenka", "bernabeu", "anfield")
##results = gmapsdistance(origin = origin, destination = destin, mode="driving", key=key)
##results = data.frame(results)
##results$QueryTime = rep(TIME, nrow(results))
##
##write.table(results, "data_teams_stadium_horenka_driving.txt")
##
##
##
## ##WALKING
##
##Origin = c("irpin", "boiarka", "vasilkov", "ukrainka", "brovary", "borispol")
##Destin = Origin
##results = gmapsdistance(origin = Origin, destination = Destin, mode="walking", key=key)
##results = data.frame(results)
##results$QueryTime = rep(TIME, nrow(results))
##
##write.table(results, "data_near_stadium_horenka_walking.txt")
##
##
##Origin = c("bernabeu", "horenka","anfield")
##Destin = c("horenka", "bernabeu", "anfield")
##results = gmapsdistance(origin = Origin, destination = Destin, mode="walking", key=key)
##results = data.frame(results)
##results$QueryTime = rep(TIME, nrow(results))
##
##write.table(results, "data_teams_stadium_horenka_walking.txt")
##
## ##BICYBLING
##
####Origin = c("irpin", "boiarka", "vasilkov", "ukrainka", "brovary", "borispol")
####Destin = Origin
####results = gmapsdistance(origin = Origin, destination = Destin, mode="bicycling", key=key)
####results = data.frame(results)
####results$QueryTime = rep(TIME, nrow(results))
####
####write.table(results, "data_near_stadium_horenka_bicycling.txt")
####
####
####Origin = c("bernabeu", "horenka","anfield")
####Destin = c("horenka", "bernabeu", "anfield")
####results = gmapsdistance(origin = Origin, destination = Destin, mode="bicycling", key=key)
####results = data.frame(results)
####results$QueryTime = rep(TIME, nrow(results))
####
####write.table(results, "data_teams_stadium_horenka_bicycling.txt")
##
##

cont=0
TIME = as.numeric(as.POSIXct(Sys.time())) 
while(cont <= 10)
{
  
  
  Sys.sleep(3600-as.numeric(as.numeric(as.POSIXct(Sys.time()))-TIME))
  TIME = as.numeric(as.POSIXct(Sys.time())) 
  
  
  Origin = c("irpin", "boiarka", "vasilkov", "ukrainka", "brovary", "borispol")
  Destin = Origin
  results = gmapsdistance(origin = Origin, destination = Destin, mode="driving", key=key)
  results = data.frame(results)
  results$QueryTime = rep(TIME, nrow(results))
  
  write.table(results, "data_near_stadium_horenka_driving.txt", append=TRUE, col.names=FALSE)
  
  
  ##DRIVING....
  Origin = c("bernabeu", "horenka","anfield")
  Destin = c("horenka", "bernabeu", "anfield")
  results = gmapsdistance(origin = Origin, destination = Destin, mode="driving", key=key)
  results = data.frame(results)
  results$QueryTime = rep(TIME, nrow(results))
  
  write.table(results, "data_teams_stadium_horenka_driving.txt", append=TRUE, col.names=FALSE)
  
  
  
  ##WALKING
  
  Origin = c("irpin", "boiarka", "vasilkov", "ukrainka", "brovary", "borispol")
  Destin = Origin
  results = gmapsdistance(origin = Origin, destination = Destin, mode="walking", key=key)
  results = data.frame(results)
  results$QueryTime = rep(TIME, nrow(results))
  
  write.table(results, "data_near_stadium_horenka_walking.txt", append=TRUE, col.names=FALSE)
  
  
  Origin = c("bernabeu", "horenka","anfield")
  Destin = c("horenka", "bernabeu", "anfield")
  results = gmapsdistance(origin = Origin, destination = Destin, mode="walking", key=key)
  results = data.frame(results)
  results$QueryTime = rep(TIME, nrow(results))
  
  write.table(results, "data_teams_stadium_horenka_walking.txt", append=TRUE, col.names=FALSE)
  
  ##BICYCLING
  
  ##Origin = c("irpin", "boiarka", "vasilkov", "ukrainka", "brovary", "borispol")
  ##Destin = Origin
  ##results = gmapsdistance(origin = Origin, destination = Destin, mode="bicycling", key=key)
  ##results = data.frame(results)
  ##results$QueryTime = rep(TIME, nrow(results))
  ##
  ##write.table(results, "data_near_stadium_horenka_bicycling.txt", append=TRUE, col.names=FALSE)
  ##
  ##
  ##Origin = c("bernabeu", "horenka","anfield")
  ##Destin = c("horenka", "bernabeu", "anfield")
  ##results = gmapsdistance(origin = Origin, destination = Destin, mode="bicycling", key=key)
  ##results = data.frame(results)
  ##results$QueryTime = rep(TIME, nrow(results))
  ##
  ##write.table(results, "data_teams_stadium_horenka_bicycling.txt", append=TRUE, col.names=FALSE)
  
  #cont = cont+1
}



###get back time timestamps
#as.POSIXct(val, origin="1970-01-01")
