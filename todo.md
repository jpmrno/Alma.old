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
	- video_cursor_enabled(boolean)

- Terminal:
	- terminal_write(terminal, char)
	- terminal_print(terminal, char *)
	- terminal_style(terminal, style)
	- terminal_style_all(terminal, style)
	- ... idem color
	- ... idem background
	- referencia al struct terminal actual, verifica cuando se llama a sus funciones si es la actual tmb imprime en pantalla
	- paginacion (cuantas lineas? doble de alto?)

- Terminal struct:
	- cursor
	- style (o color & background)
	- screen[25][80]
	- styles[25][80]

- Manager:
	- terminalStruct[]
	- terminalActive (numero del vector)
	- quien maneja el screensaver y el cambio de terminales

- Lib
	- write, print, etc con la terminal activa