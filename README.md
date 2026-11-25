# Visual Sorts

Визуализация алгоритмов сортировки в реальном времени на C++23 и SFML 3.

Программа перемешивает массив, затем по очереди сортирует его всеми подключёнными
алгоритмами и показывает каждый обмен, сравнение и запись элемента. Рядом с визуализацией
отображается статистика: название текущего алгоритма, размер массива, количество сравнений,
записей и обменов.

> **Идея проекта:** реализация вдохновлена проектом
> [66-m/sorting-visualizer](https://github.com/66-m/sorting-visualizer) -
> _See and hear Sorting Algorithms in Real Time: 22 Algorithms, 30 Visuals_.
> Это не форк, а самостоятельная реализация на C++/SFML, в которой повторяется основная
> идея: наглядно показать работу алгоритмов сортировки. В отличие от оригинала, здесь пока
> нет звукового сопровождения и используется собственный набор визуализаций.

## Возможности

- Визуализация сортировки в реальном времени.
- Два режима отображения: столбцы (`Bar`) и эллипс (`Ellipse`).
- Автоматическое перемешивание массива перед каждым алгоритмом.
- Последовательный запуск всех зарегистрированных алгоритмов.
- Подсчёт сравнений, записей и обменов.
- Синхронизация потока сортировки с потоком отрисовки: за один кадр выполняется
  заданное число операций, поэтому алгоритм не «пролетает» мгновенно.
- Градиентная раскраска элементов: от синего через жёлтый к красному.

## Реализованные алгоритмы

- **Shuffler** - перемешивание Фишера-Йетса перед каждым запуском сортировки.
- **BubbleSort**
- **SelectionSort**
- **MergeSort**
- **QuickSort (схема Ломуто)**
- **QuickSort (схема Хоара)**
- **QuickSort со случайной опорой**
- **QuickSort с двумя опорными элементами**

Чтобы подключить алгоритм, добавьте соответствующий вызов `f.addAlgorithm(...)`
в `src/registery.cpp`.

## Визуализации

- **`Bar`** - классические столбцы, высота соответствует значению.
- **`Ellipse`** - точки на эллипсе: угол зависит от позиции элемента в массиве,
  а расстояние до центра - от отклонения текущего значения от изначального.

Активная визуализация задаётся через парамерты `-t`/`--type` при запуске приложения:

```bash
./build/debug/main -t Bar
```

## Требования

- Linux (путь к шрифту в `src/main.cpp` задан для Linux).
- Компилятор с поддержкой C++23.
- CMake 3.22 или новее.
- SFML 3 (компонент `Graphics`).
- Ninja (используется `CMake`).
- Шрифт JetBrainsMono Nerd Font, путь по умолчанию:
  `/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Regular.ttf`.

Например, для Arch Linux:

```bash
sudo pacman -S cmake ninja sfml ttf-jetbrains-mono-nerd
```

Если шрифт установлен в другое место, измените путь в `src/main.cpp`:

```cpp
constexpr auto font =
    "/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Regular.ttf";
```

## Сборка и запуск

Либо напрямую через CMake:

```bash
cmake --preset debug
cmake --build --preset debug --target main

./build/debug/main
```

## Тесты

> CTest in plans

Тесты проверяют корректность сортировки, которая указывается через директиву
`using Sorter` в начале `namespace test`, на массивах разного размера
(от 2 до 1000 элементов). Сортировщик запускается в отдельном потоке без визуализации,
синхронизация при этом не блокирует выполнение.

```bash
cmake --preset debug
cmake --build --preset debug --target test

./build/debug/test
```

## Настройка

Основные параметры задаются через CLI аргументы:

| Argument    | Sense                                             |
| ----------- | ------------------------------------------------- |
| -h, --help  | Show help                                         |
| -l, --list  | Show available visualisation types                |
| -t, --type  | Set visualisation type (default: bar)             |
| -s, --size  | Set array size \[10, 100000\] (default: 1000)     |
| -t, --type  | Set operations per frame \[1, 1000\] (default: 5) |
| --quadratic | Enable quadtatic sorts (default: false)           |

## Архитектура

```
src/
├── main.cpp                    # точка входа, создание окна и сцены
├── Registry                    # регистрация алгоритмов
├── include/
│   ├── macroses.hpp            # общепроектные макросы
│   ├── Random.hpp              # обёртка над std::mt19937
│   ├── Options.hpp             # структура со всеми доступными CLI-аргументами
│   └── VisualType              # enum со всеми доступными типами визуализаций
├── exceptions/                 # исключения
│   └── ArgsErrors.hpp          # ошибки парсинга `ParseError` и валидации `ValidationError`
├── args/
│   ├── options.hpp             # дефолтные и ограничительные значения Options и вспомогательные функции
│   ├── visual.hpp              # вспомогательные функции для VisualType
│   ├── ArgsParser              # парсер CLI-аргументов
│   ├── ArgsValidator           # валидатор численных значений
│   ├── Args                    # фасад над ArgsParser и ArgsValidator
│   └── Usage                   # вспомогательные класс для печати при аргументах `--help` и `--list`
├── model/
│   ├── VectorModel             # массив, маркеры изменённых элементов, счётчики
│   ├── SyncGate                # синхронизация потока сортировки и отрисовки
│   └── SyncingModel            # фасад над VectorModel и SyncGate
├── sorts/
│   ├── SortingAlgorithm.hpp    # интерфейс алгоритма
│   ├── AlgorithmFactory        # реестр алгоритмов
│   ├── Shuffler                # перемешивание Фишера - Йетса
│   └── *Sort.hpp               # реализации алгоритмов
├── visual/
│   ├── VisualizerFactory       # реестр визуализаций
│   ├── VectorVisualizer        # базовый класс визуализации
│   ├── Bar                     # визуализация столбцами
│   ├── Ellipse                 # визуализация точками на эллипсе
│   └── Statistics.hpp          # текстовая статистика визуализации
└── app/                        # приложение
    ├── SortingManager          # поток, перемешивание и запуск алгоритмов
    └── Scene                   # сцена, отображаемая приложением во время работы
tests/
└── test.cpp                 # тесты сортировки
```

### Как это работает

1. `VectorModel` хранит массив значений `0..N-1`, флаги изменённых элементов и счётчики сравнений, записей и обменов.
2. `SyncingModel` перехватывает операции `compare`, `set` и `swap`. Перед каждой операцией вызывается `SyncGate::check()`.
3. `SyncGate` пропускает `gateSteps` операций, после чего блокирует поток сортировки до следующего кадра. `Scene::update()` на время отрисовки вызывает `lock()`, а после - `unlock()`, тем самым задавая темп визуализации.
4. `SortingManager` запускает `std::jthread`. В нём массив перемешивается, затем по очереди выполняются все алгоритмы из `AlgorithmFactory` с паузой в 2 секунды между этапами.
5. Визуализатор в `update()` читает только помеченные (`markered`) элементы и обновляет их положение; `clearMarkers()` сбрасывает флаги после каждого кадра.
6. Поток сортировки можно остановить через `std::stop_token`: `SyncGate` выбрасывает `SortCanceledException`, который перехватывается в `SortingManager`.

## Добавление своего алгоритма

1. Создайте заголовочный файл в `src/sorts/`, например `MySort.hpp`.
2. Унаследуйте класс от `SortingAlgorithm` и реализуйте методы `name()` и `sort()`.
   В `sort()` используйте только операции `SyncingModel`: `get`, `compare`, `set`, `swap`, чтобы работали и визуализация, и статистика.

```cpp
#pragma once

#include "sorts/SortingAlgorithm.hpp"

class MySort final : public SortingAlgorithm {
  public:
    const std::string_view name() override { return "MySort"; }

    void sort(std::shared_ptr<SyncingModel> model) override {
        // ...
    }
};
```

3. Подключите заголовок и зарегистрируйте алгоритм в `src/Registry.cpp`:

```cpp
#include "sorts/MySort.hpp"

void registerAlgorithms() {
    auto& f = AlgorithmFactory::instance();

    f.addAlgorithm([]() { return std::make_unique<MySort>(); });
}
```

## Добавление своей визуализации

1. Унаследуйте класс от `VectorVisualizer`.
2. Реализуйте `onSetSize()`, `onDraw()` и `update()`.
3. Добавьте новый тип визуализации в `src/include/VisualType.hpp`:

```cpp
#define VISUAL_TYPES(X) \
	X(Bar)              \
	X(Ellipse)          \
	X(MyVisual)
```

4. Зарегистрируйте визуализацию в `src/visual/VisualizerFactory.cpp`:

```cpp
void VisualizerFactory::init() {
	addVisual(visual::VisualType::MyVisual,
			  [](const VectorModel& model) { return std::make_unique<MyVisual>(model); });
}
```

## Благодарности

- [66-m/sorting-visualizer](https://github.com/66-m/sorting-visualizer) - исходная идея
  проекта и источник вдохновения.
- [SFML](https://www.sfml-dev.org/) - окно и графика.
