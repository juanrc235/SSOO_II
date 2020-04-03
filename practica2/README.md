## Práctica 2 SSOOIIGLE

Para compilar usaremos:

```
make
```

Y para ejecutar:

```
make run
```
Ejecutará el buscador con un fichero de prueba con diferentes casos.
Adicionalmente podemos ejecutar ejemplos reales con:

```
make run2
```
y con:


```
make run3
```

# Decisiones de diseño adoptadas

Para buscar una palabra en una imagen deberemos crear un objeto Buscador, al cual
pasaremos como parámetros la palabra a buscar, el fichero dónde buscarla y el
número de hilo que el usuario quiere que se lance. El objeto buscador nos da
acceso a una serie de métodos, a destacar:

 - test_file() :: devuelve false si no se puede abrir el fichero.
 - buscar() :: agrupa todas las tareas que se llevan a cabo para buscar las palabras
 - devolver_resultado() :: nos devuelve la estructura de datos que contiene los
 resultados de la búsqueda.

En cuanto a la estructura de datos, es un map de objetos Resultado y enteros
(número de hilo, preserva el orden). Cada objeto Resultado pertenece a un hilo.
Cada objeto Resultado tiene a su vez una lista de objetos Linea. Cada objeto
Linea tiene la string con el resultado el número de línea donde se encuentra.

En cuanto a la forma de búsqueda uso una librería de expresiones regulares, regex.
Para tratar una línea (y mostrar la salida correcta), primero elimino los signos
de puntuación, lo que hace más sencillo usar más regex para parsear la línea y
mostrar la salida correcta.
