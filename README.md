## QUEUE
queue - это императивный язык программирования, который компилируется в С код, а после в исполняемый файл

чтобы скомпилировать код на queue вам нужно установить gcc(без него, вы не сможете скомпилировать С-файл)
после, вы добавляете его в переменные среды и готово!

расширение файла с кодом языка queue - .qe

чтобы скомпилировать код вписываете комманду 'que', после чего пишется входной файл
после написания команды создается .exe/.c файлы с дефолтным названием 'a'
чтобы изменять названия после входного файла пишется флаг -otp, после чего имя выходного файла

пример:
que helloworld.qe -otp helloworld => helloworld.exe/.c


## поддерживается/не поддерживается
поддерживается:
- создание переменных типов char, bool, short, int, long и void(aka ..)
- создание функций
- циклы
- операторы ветвления
- i/o stream's
- массивы

не поддерживается:
- структуры
