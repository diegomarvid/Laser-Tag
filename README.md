# Laser-Tag
 
Laser Tag es una libreria de Arduino que permite tener todas las funcionalidades de las pistolas de laser tag comerciales.

La libreria permite:

* Multiples Equipos
* Multiples Armas
* Personalizacion de armas
* Sistema de Ranking

En las armas se puede elegir la velocidad de disparo, daño, cantidad de balas de una carga.

Cada pistola posee un identificador unico en ASCII que permite poder realizar estadisticas de daños en todos los jugadores.

Para manchar se utilizan emisor LED infrarrojo modulados en 38KHz. La libreria utilizada para esto se desarrollo junto con Laser Tag y se llama MOTT.
Para el escudo es necesario utilizar un receptor infrarrojo adecuado a 38KHz.
