Análisis y Diseño de Sistemas en Tiempo Real
En Ingeniería en Computación - UNTreF

Profesor: Claudio Aciti
Realizado por:

   - Julián Moreno 
   - Lucas Del Rio
   - Sebastián Roldán

Trabajo de Cursada
Consigna:

Se tienen tres tareas de tiempo real T1, T2 y T3 (inician todas en 0), con la siguiente descripción:

T1 se ejecuta cada 400 ms con prioridad 10. En cada ejecución lee la variable N, prende el Led 1 e imprime el valor N * 1. 
T2 se ejecuta cada 600 ms con prioridad 8. En cada ejecución lee la variable N, prende el Led 2 e imprime el valor N * 10. 
T3 se ejecuta cada 800 ms con prioridad 6. En cada ejecución lee la variable N, prende el Led 3 e imprime el valor N * 100.

Ademas se tienen dos pulsadores P1 y P4. P1 dispara cada vez que es presionado a la tarea T4. Esta tarea aumenta en 1 a la variable N. (No se prende ninguna luz, ni se imprime nada por pantalla)

P4 dispara cada vez que es presionado a la tarea T5. Esta tarea prende el led 4 e imprime el valor N*1000

Inicialmente N=1
Comentarios:

Se llevó a cabo la realización del Trabajo correspondiente, ejecutando las tareas y obteniendo la secuencia de luces esperada sin mayores inconvenientes.
La Tarea que involucra Pulsador junto con Led fue un poco más costosa ya que debimos comprender bien cómo es que produce la lectura del Pulsador y por cuánto tiempo efectúa esa lectura en busca del accionar del mismo.

Para la impresión en consola se trabajó para que se muestren los valores esperados en Terminal luego de ejecutar el comando "make openocd", pero no se ha logrado el resultado esperado por eso mismo el código de impresión está comentado. Ocurría que la ejecución de 2 o 3 tareas con impresión era exitosa pero cuando corrían todas había cierto error que no fue posible solucionar.
