# Saku
Программа для параллельных вычислений

## API
```c++
// Получаем текущую платформу
auto platform = Kernel::Instance()->GetPlatform();

// Инициализируем операцию
Operation_Pow operation{2, 3};

// Выполняем операцию на платформе
auto result = platform->Handle(operation);
```
