
# Saku
**Saku** - программа для параллельных вычислений и обработки больших объёмов данных.

Содержит
в себе реализацию большинства численных методов ориентированных на многоядерные процессоры (CPU/GPU)
, а так же дополнительный набор функций для работы со статистическими данными и изображениями.

## Использование
После запуска Saku выбирите подходящую из доступных в системе платформ:
```
>>> kernel
Список доступных платформ:
 --> [0] Runtime Platform
     [1] OpenCL 2.0: Intel(R) Core(TM) i3-4330 CPU @ 3.50GHz

>>> set_platform(1)
```
Если какое-либо устройство отсутствует в списке платформ, то проверьте наличие установленного
драйвера CUDA/OpenCL.

Saku имеет очень простой синтаксис состоящий из переменных, функций, перечислений и строк.


### Переменные
Переменная представляет собою ссылку на некоторый объект любого типа. Для создания новой переменной
достаточно указать её имя и присвоить ей некоторое значение:
```
>>> var = sin(3.14)
```
Имя переменной должно содержать в себе только буквы или знак подчёркивания и не должно 
конфликтовать с какой-либо из доступных комманд.

Значения переменных можно присваить друг другу без каких-либо ограничений по типу:
```
>>> variables
Переменные:
 value   arg        = { x : 3.14 }
 number  pi         = 3.14
>>> arg = pi
>>> variables
Переменные:
 number  arg        = 3.14
 number  pi         = 3.14
```

Для вывода значения единственной переменной просто укажите её имя:
```
>>> var
1.0
```

### Перечисления
Перечисления этот способ создания вектора, содержащего в себе объекты разных типов. Для
создания вектора достаточно указать его значения через запятую:
```
>>> "Denis", 3.14, ( 4, 5 )
[ "Denis", 3.14, [ 4, 5 ] ]

>>> var = "Denis", 3.14, ( 4, 5 )
>>> var
[ "Denis", 3.14, [ 4, 5 ] ]
```

### Функции
Синтаксис функций аналогичен синтаксису в любом другом языке:
```
>>> sin(3.14)
1.0
>>> load_image("photo.png")
photo.png
>>> function_value("x * 2", value(x,3))
6
```
