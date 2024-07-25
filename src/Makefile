compile:
	@gcc testeXX.c -o testeXX; gcc fila.c readfile.c trataDependencia.c escalonador.c -o escalona
exec:
	@make --no-print-directory compile;
	@./escalona 2 || true
clean:
	@rm testeXX escalona