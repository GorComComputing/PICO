#ifndef SHELL_HPP
#define SHELL_HPP

#define RL_BUFSIZE 20 // Размер буфера ввода
#define TOK_BUFSIZE 64  // Размер буфера с указателями на токены
#define TOK_DELIM " \t\r\n\a" // Разделители для токенизации

#define MAX_LINE 10  // Максимальное количество строчек в программе
#define MAX_LENGTH 20 // Максимальная длина строчки программы
#define MAX_SIZE MAX_LINE * MAX_LENGTH

int cmd_state(char **args);
int cmd_led(char **args);
int cmd_car(char **args);
//int cmd_gps(char **args);
int cmd_laser(char **args);
int cmd_led_green(char **args);
int cmd_led_yellow(char **args);
int cmd_led_red(char **args);
int cmd_photoresistor(char **args);
int cmd_servo(char **args);
int cmd_help(char **args);
int cmd_hum(char **args);
//int cmd_tempOut(char **args);
int cmd_tempIn(char **args);
int cmd_wait(char **args);
int cmd_list(char **args);
int cmd_print(char **args);
int cmd_new(char **args);
int cmd_input(char **args);
int cmd_run(char **args);

void shell();

// Массив имен встроенных команд
char *cmd_str[] = {
  "state",         // Запрос состояния всех датчиков
	"led",           // Включение светодиода
  "car",           // Управление автомобилем
//  "gps",           // Получение данных GPS
  "laser",         // Включение лазера
  "green",         // Включение светодиода
  "yellow",        // Включение светодиода
  "red",           // Включение светодиода
  "light",         // Узнать освещенность
  "servo",         // Задать угол серво
	"help",			     // Справка
//  "tempout", 		   // Узнать температуру на улице
	"tempin", 		   // Узнать температуру внутри
  "hum", 		       // Узнать влажность
  "wait", 		     // Ожидание
	"list",          // Вывод на экран программы
	"print",         // PRINT
	"new",           // Очищает программу
	"input",         // Ввести переменную  
	"run"            // Запуск выполнения программы
};

// Массив указателей на функции встроенных команд
int (*cmd_func[]) (char **) = {
  cmd_state,
	cmd_led,
  cmd_car,
//  cmd_gps,
  cmd_laser,
  cmd_led_green,
  cmd_led_yellow,
  cmd_led_red,
  cmd_photoresistor,
  cmd_servo,
	cmd_help,
//  cmd_tempOut,
	cmd_tempIn,
  cmd_hum,
  cmd_wait,
	cmd_list,
	cmd_print,
	cmd_new,
	cmd_input,
	cmd_run    
};

#endif // SHELL_HPP