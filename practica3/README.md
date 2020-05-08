## Práctica 3 MULTICINES SSOO_II

Para compilar usaremos:

```
make
```

Y para ejecutar:

```
make run
```

# Decisiones de diseño adoptadas

Esta práctica ha sido la más compleja hasta el momento. La gran cantidad de hilos involucrados en esta
simulación hace que comprender qué ocurre en cada momento sea complicado. Por eso, debemos tener mucho 
cuidado y aplicar todos los procedimientos aprendidos en clase.

Para el desarrollo de la práctica se ha creado una clase por cada entidad que participaba en la simulación: 
clientes, taquilla, sistema de pago, puestos de comida y reponedor. Además, se han implementado otras clases
como petición de tickets o de palomitas y bebida.  Sin embargo, todo la simulación se articula en el fichero 
`main.cpp`.

En primer lugar, se crean los recursos comunes como son la taquilla, sistema de pago, el reponedor y los puestos
de comida. Tras esto comienza el bucle de donde se crean los clientes. En cuanto el primer cliente es creado empieza
a funcionar la simulación. Todo se organiza mediante mutex, variables de condición y unique_lock().
