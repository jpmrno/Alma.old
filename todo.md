#TODO:

- Video driver:
	- video_put(position, char, style) o video_put(position, char, color, bg)
	- video_get(position)
	- video_style_get(position)
	- video_style_set(position, style)
	- video_color_get(position)
	- video_color_set(position, color)
	- video_background_get(position)
	- video_background_set(position, background)
	- video_cursor_set(position)
	- video_cursor_get()

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

- WALLOS o wallOS?

- Sonido
	- Musica al iniciar
	- Teclado/piano

- Compartir las librerias de C entre Kernel y User? O tener una para cada uno? O compartir algunas?

- Makefile todas las subcarpetas de src de una, idem con asm y include