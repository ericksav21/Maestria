#print(head(USArrests))
#str(USArrests)
#dim(USArrests)
usa <- USArrests
print(usa["Texas",])
print(length(usa[usa[,"Rape"] > 35, 1]))
print(max(usa[usa[,"Murder"] > mean(usa[,"Murder"]), 3]))

greater <- usa[usa[,"Murder"] > mean(usa[,"Murder"]) &
              usa[,"Assault"] > mean(usa[,"Assault"]) &
              usa[,"UrbanPop"] > mean(usa[,"UrbanPop"]) &
              usa[,"Rape"] > mean(usa[,"Rape"]),]
print(rownames(greater))