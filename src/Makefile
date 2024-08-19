compile:
	@gcc testeXX.c -o testeXX; gcc fila.c readfile.c trataDependencia.c escalonador.c -o escalona
exec:
	@make --no-print-directory compile;
	@./escalona 4 || true
clean:
	@rm testeXX escalona