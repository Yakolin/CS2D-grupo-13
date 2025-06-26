# CS2D

Remake del juego [CS2D](https://store.steampowered.com/app/666220/CS2D/). Realizado en C++ con SDL2pp y Qt.

![Logo del CS2D](assets/gfx/cs2d.png)

Repositorio del grupo 13 de la materia Taller de Programación Catedra Veiga

# Integrantes

- **Maria Fernanda Gareca**
- **Yaco Santamarina**
- **Mateo Riat Sapulia**

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

Abrir una terminal y ejecutar las siguientes lineas:

Clonar el repositorio:

```bash
git clone git@github.com:Yakolin/CS2D-grupo-13.git
```

Desde la ruta en la que se ubica el repositorio, ejecutar la siguiente linea para moverse a la carpeta del juego

```bash
cd CS2D-grupo-13
```

## Instalar el juego globalmente

Una vez que estamos parado dentro de la carpeta del juego, debemos ejecutar la siguiente linea para instalar todas las dependencias

```bash
./install.sh
```

Esto permitira levantar el servidor y la vez levantar los multiples usuarios que quieran jugar

# ¿Como jugar?

## Servidor

Para poder jugar multiples partidas primero hace falta levantar un servidor en un puerto especificado, para eso hay que ejecutar la siguiente linea desde cualquier directorio, se podra elegir cualquier puerto, mas precisamente cualquier puerto no perteneciente a los _well_known_ports_ (puertos del [0, 1023])

```
CS2D_server <n_puerto>
```

Esto mantendra abierto el servidor en la terminal.Para finalizarlo se debe escribir la letra **q** y pulsar **Enter**. Solo hace falta crear partidas dentro del servidor una vez que tus amigos se conecten

## Cliente

Una vez hecho el paso anterior simplemente los jugadores se podran conectar al lobby, interfaz la cual se podran _Crear partidas_ y _Unirse a partidas_, para hacerlo se debe ejecutar la siguiente linea, parado en el directorio en el que fue clonado el repositorio, colocando en n_puerto el numero de puerto del servidor levantado anteriormente y su direccion IP

```
CS2D_client <ip_server> <n_puerto>
```

# Creditos

Para las clases Socket, Resolver, ResolverError, LibError, Thread y Queue, utilizamos código provisto por la cátedra, el mismo se encuentra en los siguientes repositorios.

- **[Sockets](https://github.com/eldipa/hands-on-sockets-in-cpp)**
- **[Threads y Queue](https://github.com/eldipa/hands-on-threads)**

# Documentacion

Se podra encontrar el manual de usuario y la documentacion tecnica en [docs](https://github.com/Yakolin/CS2D-grupo-13/tree/entrega-final/docs)

# Licencia

[GPL v2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html)
