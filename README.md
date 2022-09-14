# Caso 3
## Notas Ejercicio 1
Para modelar la clase PostfixParser fue necesario investigar como funciona el algoritmo
de conversion Infijo a Postfijo. Se tienen dos pilas; la primera acumula partes de
la expresion postfija, y la segunda guarda el orden de operadores. Cada componente
analizado se procesa distinto segun el caso:

1. Operando
    -> Se apila operando a la expresion
2. Abre parentesis
    -> Se apila operador en las operaciones
3. Cierra parentesis
    -> Vaciamos operadores de la pila a la expresion hasta encontrar un parentesis
4. Operador matematico
    a) Mayor prioridad que el ultimo operador, agregamos el componente a la pila
    b) Prioridad es menor o igual, vaciamos la pila entera a la expresion
    Nota: Los parentesis se ignorar al vaciar la pila y su prioridad se ignora

Para identificar los componentes, se empleo expresiones regulares de un string[],
se accesan mediante un enum que corresponde a cada caso. Al identificar un caso,
se determina como procesar el substring mediante un switch(enum).
La iteracion acaba cuando se consumen todos los substring. Sin embargo, se realiza
un ultimo llamado al metodo appendCalls() para vaciar cualquier operador residual
en la pila de llamadas.

La evaluacion se implemento de forma similar: se consumen los substring del postfijo
y un switch determina que proceso ejecutar segun el enum del caso. Finalmente, se retorna
el ultimo numero que la pila almacena.

Algunas limitaciones a considerar es la falta de manejo de excepciones para:
    a) Division entre 0
    b) Parentesis incompletos
    c) Operandos y operadores sobra Ej. "7 + 8 +" o "1 + 8 15"

Se incluyen algunos ejemplos como demostracion. Para probar el algoritmo se inicializa
un objeto PostfixParser. Para convertir una expresion infija se debe pasar un string
al objeto con el metodo .parseInfix(). Se puede revisar el postfijo con el metodo
.getNotation() y el resultado de la evaluacion con .evaluate()

## Notas Ejercicio 2
La implementacion de una cola mediante stacks requiere mantener el comportamiento
"FIFO", pero un stack tiene un orden tipo "FILO". Los metodos isEmpty(), dequeue()
y front() no cambian su comportamiento de manera significativa.

1. isEmpty() revisa si la estructura lineal tiene o no elementos, resulta irrelevante
si el miembro de la clase Queue es List o Stack, pues ambos ya ofrecen este metodo.
2. dequeue() y front() comparten comportamiento con pop() y top(), pues ambos trabajan
con el puntero head de la lista que les compone.
3. Sin embargo, enqueue() y push() son opuestos, pues enqueue() agrega al final, no al inicio.

Para lograr esta solucion, consideremos como podriamos insertar un elemento al final de una pila.
Podriamos utilizar pop() hasta vaciarla, pero perderiamos los datos previamente ordenados. Podemos
almacenar dichos datos en otra pila para desocupar la pila principal. Por ejemplo:

1. mainStack = [A-B-C   ; tempStack = [      ;  Queue.enqueue(X)
2. mainStack = [A-B     ; tempStack = [C     ;  Iterar tempStack.push( mainStack.pop() )
3. mainStack = [        ; tempStack = [C-B-A ;  Pasar de un stack a otro invierte el orden
4. mainStack = [X       ; tempStack = [C-B-A ;  Podemos regresar elementos tras incluir X
5. mainStack = [X-A-B-C ; tempStack = [      ;  Finalmente, replicamos enqueue() con stacks

Nuevamente, se incluye un ejemplo en el main.cpp que compara los structs Queue y QueueStacks
para efectos de prueba.

## Notas Ejercicio 3
Para el ordenamiento del despegue de los aviones, se tienen las clases Flight y Airport.
La clase Airport se debe instanciar con la cantidad de pistas disponibles y el total de vuelos
a generar. Cuenta con el metodo fillFlights() que genera la cantidad solicitada de vuelos, pero
debe incluirse el rango de horas deseadas. El segundo parametro no es inclusivo, un llamado
airport.fillFlights(7, 9) tendra horarios en horas 7 y 8 AM. Este metodo tambien se encarga de
considerar atrasos posibles de 0 a 17 minutos.

El metodo .assignTracks() distribuye los aviones en cada pista, las cuales son modeladas con Queues.
Para lograr esto, se cuenta con la ayuda establecida por .fillFlights(). Este genera los vuelos y los
almacena en un PriorityQueue segun el TimeValue de cada avion. Este time value esta dado por la
representacion en segundos del horario de cada vuelo. De manera que .assignTracks() reparte un
listado ordenado de vuelos entre cada pista.

Los resultados se pueden comprobar con el metodo .takeOff(), que desencola cada vuelo en orden
e imprime los datos de horario, pista y numero de vuelo.

El main.cpp incluye una corrida de prueba. Se pueden modificar las constantes #define
para probar distinta cantidad de pistas, vuelos y rangos horarios.