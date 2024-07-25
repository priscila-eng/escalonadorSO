compile:
	@gcc testeXX.c -o testeXX; gcc fila.c readfile.c trataDependencia.c escalonador.c -o escalonador
exec:
	@make --no-print-directory compile;
	@./escalonador 2 || true
clean:
	@rm testeXX escalonador