#!/bin/bash

mkdir -p ../build

echo "Создание документации для BrickGame в формате HTML..."
cat > ../build/dvi.html << EOL
<!DOCTYPE html>
<html>
<head>
  <title>BrickGame Tetris Documentation</title>
  <style>
    body{
      font-family:Arial,sans-serif;
      line-height:1.6;
      max-width:1000px;
      margin:0 auto;
      padding:20px
    }
    h1,h2,h3{color:#333}
    code{
      background:#f4f4f4;
      padding:2px 5px;
      border-radius:3px
    }
    pre{
      background:#f4f4f4;
      padding:10px;
      border-radius:5px;
      overflow:auto
    }
    .function{
      margin-bottom:20px;
      border-left:3px solid #0066cc;
      padding-left:15px
    }
  </style>
</head>
<body>
  <h1>BrickGame Tetris</h1>
  <p>Игра Tetris, реализованная с использованием языка программирования C.</p>

  <h2>Управление:</h2>
  <ul>
    <li>Пробел - Начать игру</li>
    <li>Стрелка влево - Переместить фигуру влево</li>
    <li>Стрелка вправо - Переместить фигуру вправо</li>
    <li>Стрелка вниз - Ускорить падение фигуры</li>
    <li>r - Повернуть фигуру</li>
    <li>p - Пауза</li>
    <li>q - Выйти из игры</li>
  </ul>

  <h2>Механика игры:</h2>
  <p>Игра реализует все стандартные механики Tetris:</p>
  <ul>
    <li>Вращение фигур</li>
    <li>Горизонтальное перемещение фигур</li>
    <li>Ускорение падения фигуры</li>
    <li>Отображение следующей фигуры</li>
    <li>Уничтожение заполненных рядов</li>
    <li>Конец игры при достижении верха игрового поля</li>
  </ul>

  <p>Игра также содержит дополнительные бонусные механики:</p>
  <ul>
    <li>Подсчет очков за уничтожение рядов</li>
    <li>Сохранение максимального счета</li>
    <li>Уровневая механика, увеличивающая скорость игры</li>
  </ul>

  <h2>Библиотечные функции:</h2>

  <h3>Основные функции (s21_tetris.h):</h3>
  <div class='function'>
    <h4>void userInput(UserAction_t action, bool hold)</h4>
    <p>Обрабатывает ввод пользователя и выполняет соответствующие действия.</p>
    <ul>
      <li><strong>action</strong> - Действие, которое должно быть выполнено.</li>
      <li><strong>hold</strong> - Указывает, должно ли действие удерживаться.</li>
    </ul>
  </div>

  <div class='function'>
    <h4>GameInfo_t updateCurrentState()</h4>
    <p>Обновляет текущее состояние игры.</p>
    <p>Возвращает обновленную информацию об игре.</p>
    <p><strong>Предупреждение:</strong> После окончания игры поля field и next в возвращаемой структуре будут равны NULL, что указывает на окончание игры.</p>
  </div>

  <h3>Функции конечного автомата (s21_fsm.h):</h3>
  <div class='function'>
    <h4>void transitionToState()</h4>
    <p>Осуществляет переход между состояниями игры.</p>
  </div>

  <div class='function'>
    <h4>void stateOfStart()</h4>
    <p>Обработчик начального состояния игры.</p>
  </div>

  <div class='function'>
    <h4>void stateOfSpawn()</h4>
    <p>Обработчик состояния создания новой фигуры.</p>
  </div>

  <div class='function'>
    <h4>void stateOfMoving()</h4>
    <p>Обработчик состояния падения фигуры.</p>
  </div>

  <div class='function'>
    <h4>void stateOfShifting()</h4>
    <p>Обработчик состояния смещения фигуры.</p>
  </div>

  <div class='function'>
    <h4>void stateOfAttaching()</h4>
    <p>Обработчик состояния прикрепления фигуры к игровому полю.</p>
  </div>

  <div class='function'>
    <h4>void stateOfGameOver()</h4>
    <p>Обработчик состояния окончания игры.</p>
  </div>

  <div class='function'>
    <h4>void processShift()</h4>
    <p>Обрабатывает логику смещения фигуры.</p>
  </div>

  <div class='function'>
    <h4>bool processAttaching()</h4>
    <p>Обрабатывает логику прикрепления фигуры к игровому полю.</p>
    <p>Возвращает информацию о том, привело ли прикрепление к окончанию игры.</p>
  </div>

  <div class='function'>
    <h4>bool processGameOver()</h4>
    <p>Проверяет условие окончания игры.</p>
    <p>Возвращает информацию о том, нужно ли закончить игру.</p>
  </div>
</body>
</html>
EOL

echo "Документация создана в ../build/dvi.html" 