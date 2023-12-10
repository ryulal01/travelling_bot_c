# Телеграм бот для путешествий

**Мотивация**

В настоящее время люди часто путешествуют. Хочется предоставить возможность пользователям одновременно искать авиабилеты между городами, оставлять отзывы о своей поездке и смотреть комментарии других пользователей 

**Задача**

Создать телеграм бот, который будет по введенным городам и дате выдавать самый дешевый авиабилет. Также бот должен уметь запоминать историю городов, которые посетил пользователь. Люди смогут оставлять отзывы, которые должны будут храниться в базе данных в системе. По введенному названию города, бот будет возвращать картинку с изображением этого города

**Сколько человек**

Проект индивидуальный

**Функционал**

Пользователи смогут обмениваться своим опытом путешествий
1. Пользователи могут регистрироваться в системе
2. Если пользователь зарегистрирован, он сможет оставить отзыв об указанном городе в системе
3. Все отзывы, оставленные пользователями, должны храниться в базе данных
4. Можно указать два города и дату, бот должен найти самый дешевый авиабилет по указанным данным. Будет использоваться сайт aviasales.
5. Каждый пользователь может указать город и посмотреть последние отзывы по нему
6. Можно просто посмотреть последние комментарии в системе
7. Будет использоваться docker для работы бота
8. Бот умеет отправлять фотографии

**Стек технологий**
1. C
2. docker
3. aviasales

**План**

В первом семестере:
1. Оформить репозиторий проекта
2. Изучить материал про написание ботов на си
3. Посмотреть уже сущетсвующие простые примеры ботов
4. Получить токен, зарегистрировав бота через BotFather
5. Написать свой простой бот с минимальным функционалом
6. Зарегистрироваться на сайте aviasales, получить токен, чтобы иметь возможность смотреть актуальные авиабилеты

Во втором семестре:
1. Добавить новый функционал
2. Научиться интегрировать билеты с сайта aviasales
3. Разобраться, как хранить отзывы в базе данных
4. Создать Docker образ с ботом, запустить его командой docker run
5. Проверить, что весь функционал работает корректно
6. Довести проект до полностью рабочего состояния

**Распределение задач**

Проект индивидуальный, поэтому все задачи выполняются одним человеком

**Прогресс**

1. Получен токен для бота через BotFather

2. Изучена библиотека для написания ботов на си https://github.com/smartnode/telebot

3. С использованием данной библиотеки написана часть кода, которая отвечает за возвращение в чат фотографии города по введенному названию города(также был добавлен CMakeList.txt для сборки проекта)
  
4. После команды /start бот умеет здороваться с новым пользователем
  
5. Для интеграции авиабилетов были отобраны два сайта https://app.travelpayouts.com/programs/151/about или https://app.travelpayouts.com/programs/45/about
 
6. В данный момент бот работает только при открытом терминале, следующей задачей является создание docker образа с ботом
 
