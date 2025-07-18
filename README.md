# CS2D

Remake del juego [CS2D](https://store.steampowered.com/app/666220/CS2D/). Realizado en C++ con SDL2pp y Qt.

![Logo del CS2D](assets/gfx/cs2d.png)

Grupo 13 de la materia Taller de Programación Catedra Veiga

# Integrantes

- **[Maria Fernanda Gareca](https://github.com/fernandagareca)**
- **[Yaco Santamarina](https://github.com/Yakolin)**
- **[Mateo Riat Sapulia](https://github.com/Mriat30)**

# Compilacion con make

```bash
make compile-debug
```

Compila los archivos dentro de las carpetas especificadas en el ´CMakeLists.txt´

```bash
make run-tests
```

Corre los tests , en este caso deberian ser los de protocolo

```bash
make valgrind-debug
```

Corre los tests con valgrind

```bash
make all

make clean
```

Clasicos all y clean que realizan las operaciones de limpieza y all, en este caso, corre los tests con valgrind

# Instalacion

Descargarse el archivo `game.sh` y ejecutarlo 
```bash
./game.sh
```

Desde la ruta en la que se ubica el archivo instalado, ejecutar la siguiente linea para moverse a la carpeta del juego

```bash
cd CS2D-grupo-13
```
# ¿Como jugar?

## Servidor

Una vez instalado y para poder jugar múltiples partidas, primero hace falta levantar un servidor en un puerto especificado, para eso hay que ejecutar la siguiente linea desde el directorio del Juego, es decir, dentro de la carpeta CS2D-grupo-13 creada al instalar el juego. 

```
./server.sh
```

Esto mantendra abierto el servidor en la terminal.Para finalizarlo se debe escribir la letra **q** y pulsar **Enter**. Solo hace falta crear partidas dentro del servidor una vez que tus amigos se conecten

## Cliente

Una vez hecho el paso anterior simplemente los jugadores se podrán conectar al lobby, interfaz la cual se podrán Crear partidas y Unirse a partidas, para hacerlo se debe ejecutar la siguiente linea, parado en el mismo lugar que ejecutaste el server. Podrás entrar al archivo y colocar el numero de puerto del servidor levantado anteriormente y su dirección IP.

```
./client.sh
```

# Desinstalacion

Para desinstalar el juego simplemente ejecutar en el mismo directorio que el instalador la siguiente linea

```
./uninstall.sh
```

# Creditos

Para las clases Socket, Resolver, ResolverError, LibError, Thread y Queue, utilizamos código provisto por la cátedra, el mismo se encuentra en los siguientes repositorios.

- **[Sockets](https://github.com/eldipa/hands-on-sockets-in-cpp)**
- **[Threads y Queue](https://github.com/eldipa/hands-on-threads)**

# Agradecimientos

Queremos agradacer a los docentes de la materia por darnos las herramientas para llevar esto a cabo. En especial a nuestras correctas, [Abril](https://github.com/Pandamos) y [Nathalia](https://github.com/nathencinoza).
Por ultimo agradecer a [Martin](https://github.com/eldipa) docente a cargo del desarrollo de los trabajos

# Documentacion

Se podra encontrar el manual de usuario y la documentacion tecnica en [docs](https://github.com/Yakolin/CS2D-grupo-13/tree/entrega-final/docs)

# Licencia

[GPL v2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html)
