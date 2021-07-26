main = src/main.c
compiled = src/main.o

output: $(compiled) 
	gcc $(compiled) -o styre
	rm src/*.o  

$(compiled): $(main) 
	gcc -c $(main) -o $(compiled) 

