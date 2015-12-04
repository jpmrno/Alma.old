#TODO:

- Change tSysVideoStyle type name

- Change screen_t type name

- Terminal:
	- terminal_write(terminal, char)
	- terminal_print(terminal, char *)
	- terminal_style(terminal, style)
	- terminal_style_all(terminal, style)
	- ... idem color
	- ... idem background
	- referencia al struct terminal actual, verifica cuando se llama a sus funciones si es la actual tmb imprime en pantalla
	- paginacion (cuantas lineas? doble de alto?)
	- terminal_cursor_enabled(boolean)
	- barra de titulo (arriba) / barra de info (abajo)

- Terminal struct:
	- cursor_position
	- cursor_enabled
	- style (o color & background)
	- screen[25][80]
	- styles[25][80]

- Manager:
	- terminalStruct[NUMERO DE TERMINALES VIRTUALES]
	- terminalActive (numero del vector)
	- maneja el screensaver y el cambio de terminales
	- F1, F2, ..., FN para cambiar entre terminales

- Lib
	- write, print, etc con la terminal activa (o terminal de systema a la #1?)

- Screensaver customizable:
	- clear pantalla, disable cursor, escribir texo y ver si loopea
	- correr funciones? (me parece q no)

- Sonido
	- Musica al iniciar
	- Teclado/piano

- Errores syscalls compartidos entre kernel y user (kernal ya usa common, falta user)

- Manager controla RTC?
