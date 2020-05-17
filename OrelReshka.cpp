/* Напишите программу, моделирующую бросание монеты с помощью генерации случайных чисел. 
После каждого броска монеты, программа должна записывать в файл результат: Орёл или Решка. 
Выполните бросок монеты 100 раз и подсчитайте, сколько раз появилась каждая сторона монеты.
*/

#include <iostream>
#include <fstream>   // для работы с файлами
#include <cstdlib>   // для функций выбора случайного числа srand() и rand() и exit из файла
#include <ctime>     // чтобы в randomize опираться на время запуска программы
#include <string>

// функция выбора случайного числа между двумя заданными значениями
static unsigned short getRandomNumber(unsigned short min, unsigned short max)
{
	static const double fraction = 1.0 / static_cast<double>(RAND_MAX + 1.0);
	return static_cast<unsigned short>(rand() * fraction * (max - min + 1) + min);
}

// подкидываем монету и осуществляем запись результата в файл
void record_to_file(std::fstream& data_file, const unsigned& try_number)
{
	for (unsigned short i = 1; i <= try_number; i++)
	{
		if (getRandomNumber(0, 1) == 0)
			data_file << "Решка" << std::endl;
		else
			data_file << "Орёл" << std::endl;
	}
}

// считываем значения из файла, считая количество каждого результата
void read_from_file(std::fstream& data_file, const unsigned& try_number)
{
	// т.к. до этого была запись в файл, перемещаем файловый указатель в начало файла для чтения
	data_file.seekp(0, std::ios::beg);

	// переменные для подсчёта количества результатов орла и решки:
	unsigned reshka_n{ 0 };
	unsigned orel_n{ 0 };

	for (unsigned short i = 1; i <= try_number; i++)
	{
		std::string one_result;
		getline(data_file, one_result);
		if (one_result == "Решка")
			reshka_n++;
		else
			orel_n++;
	}
	data_file.clear(); // очищаем файл, чтобы использовать его повторно при следующем запуске программы

	// выводим результат:
	std::cout << "Количество результатов решки: " << reshka_n << std::endl;
	std::cout << "Количество результатов орла: " << orel_n << std::endl;
}

int main()
{
	// подключаем кириллицу для вывода сообщений
	setlocale(LC_CTYPE, "rus");

	//аналог randomize с привязкой ко времени запуска:
	srand(static_cast<unsigned int>(time(0)));
	rand();

	// создаём файловую переменную для файла statistics.txt и проверяем файл:
	std::fstream data_file("statistics.txt");
	if (!data_file)
	{
		std::cerr << "Невозможно открыть файл для записи и чтения значений!" << std::endl;
		exit(1);
	}

	const unsigned try_number = 100;
	record_to_file(data_file, try_number);
	read_from_file(data_file, try_number);

	return 0;
}
