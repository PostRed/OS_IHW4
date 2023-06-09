# Коломникова Анастасия БПИ216 Вариант 33
### Задание сделано на 5 баллов
#### Пляшущие человечки. На тайном собрании глав преступного мира города Лондона председатель собрания профессор Мориарти постановил: отныне вся переписка между преступниками должна вестись тайнописью. В качестве стандарта были выбраны «пляшущие человечки», шифр, в котором каждой букве латинского алфавита соответствует хитроумный значок. Реализовать приложение, шифрующее исходный текст (в качестве ключа используется кодовая таблица, устанавливающая однозначное соответствие между каждой буквой и каким-нибудь числом). Каждый процесс–шифровальщик шифрует свои кусочки текста, многократно получаемые от менеджера. Распределение фрагментов текста между процессами–шифровальщиками осуществляется процессом–менеджером, который передает каждому процессу участок текста, получает от него результат, передает следующий незашифрованный фрагмент. Он же собирает из отдельных фрагментов зашифрованный текст. Количество процессов задается опционально. Каждый процесс может выполнять свою работу за случайное время. 
![image](https://github.com/PostRed/OS_IHW4/blob/main/sherlock.png)

Профессор Мориарти в моем случае опять оказался программистом и его щифр заключается в сдвиге символов на 2 позиции по ASCI таблице ([как и в идз3!](https://github.com/PostRed/OS_IHW3))

argv[1] = IP, argv[2] - порт, argv[3] - текст

Реализация программы на 5 баллов:

:white_check_mark: код клиента (с комментариями) лежит [здесь](https://github.com/PostRed/OS_IHW4/blob/main/first.c)

я создаю сокет, который используется для соединения с сервером, отправляю инициализирующее сообщение на сервер, чтобы получить начальный индекс текста `start`, его длину `len` и сам текст `text`, шифрую текст просто сдвигая каждый символ и отправляю результат обратно на сервер.

:white_check_mark: код сервера (с комментариями) лежит  [здесь](https://github.com/PostRed/OS_IHW4/blob/main/second.c)

тут проиходит получение инициализирующего сообщения и отправка начального индекса текста `start`, его длины `len`, и самого текста `text`.
