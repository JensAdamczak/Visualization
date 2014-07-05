# Produce file with coordinates that can be visualized with POVray
set.seed(123)
x <- rnorm(100)
y <- rnorm(100)*2 + 20
z <- y*2 + x + rnorm(100)

result <- data.frame(x=x, y=y, z=z)

normalize <- function(x){
               (x-min(x, na.rm=TRUE))/(max(x, na.rm=TRUE)-min(x, na.rm=TRUE))}

result <- as.data.frame(apply(result, 2, normalize))

write.table(result, "Testfile.csv", sep=",", quote=FALSE, 
            row.names=FALSE, col.names=FALSE, eol=",")
