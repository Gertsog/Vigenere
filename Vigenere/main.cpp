#include <iostream>
#include <string>
using namespace std;

//создание таблицы
void tableCreation(char table[33][33])
{
	char alphabet[33] = { 'А','Б','В','Г','Д','Е','Ё','Ж','З','И','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь','Э','Ю','Я' };

	for (int i = 0; i < 33; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			table[i][j] = alphabet[(j + i) % 33];
		}
	}

	//вывод таблицы
	for (int i = 0; i < 33; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			cout << table[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl << endl;
}

//шифрование отдельного символа
char encrypting(char table[33][33], char originalLetter, char keyLetter)
{
	int stringIndex, columnIndex;
	int j = 0;
	for (int i = 0; i < 33; i++)
	{
		if (table[i][j] == originalLetter)
			stringIndex = i;
	}

	int i = 0;
	for (j = 0; j < 33; j++)
	{
		if (table[i][j] == keyLetter)
			columnIndex = j;
	}
	return table[stringIndex][columnIndex];
}

//расшифровка отдельного символа
char decrypting(char table[33][33], char encryptedLetter, char keyLetter)
{
	int stringIndex, columnIndex;
	int i = 0;
	for (int j = 0; j < 33; j++)
	{
		if (table[i][j] == keyLetter)
			columnIndex = j;
	}

	int j = columnIndex;
	for (i = 0; i < 33; i++)
	{
		if (table[i][j] == encryptedLetter)
			stringIndex = i;
	}
	return table[stringIndex][0];
}

void main()
{
	setlocale(LC_ALL, "rus");
	string key, originalText;
	int charCode, keySize, textSize;
	char originalLetters[256], keyLetters[64], keyText[256], encryptedText[256], decryptedText[256];
	
	char table[33][33];

	tableCreation(table);//создание таблицы

	cout << "Введите исходный текст: ";
	getline(cin, originalText);
	cout << "Введите ключ: ";
	getline(cin, key);

	textSize = originalText.size();
	keySize = key.size();
	
	//преобразование текста в массив
	for (int i = 0; i < textSize; i++)
	{
		originalLetters[i] = (char)originalText[i];
		if (originalLetters[i] == -16)//получение буквы "Ё"
		{
			originalLetters[i] = 'Ё' - 64;//преобразование кодировки буквы "Ё"
		}
		if (originalLetters[i] == ' ' || originalLetters[i] == '.' || originalLetters[i] == ',' || originalLetters[i] == '-')
			originalLetters[i] = originalLetters[i] - 64;
		originalLetters[i] = originalLetters[i] + 64;//64 - особенности преобразования кодировок
	}
	//вывод строки
	cout << endl;
	for (int i = 0; i < textSize; i++)
		cout << originalLetters[i];
	cout << "| оригинальный текст" << endl;

	//преобразование ключа в массив
	for (int i = 0; i < keySize; i++)
	{
		keyLetters[i] = (char)key[i];
		if (keyLetters[i] == -16)//получение буквы "Ё"
		{
			keyLetters[i] = 'Ё' - 64;//преобразование кодировки буквы "Ё"
		}
		keyLetters[i] = keyLetters[i] + 64;
	}

	//создание ключевой строки
	int j = 0;
	for (int i = 0; i < textSize; i++)
	{
		if (originalLetters[i] == ' ' || originalLetters[i] == '.' || originalLetters[i] == ',' || originalLetters[i] == '-')
			keyText[i] = originalLetters[i];
		else
		{
			keyText[i] = keyLetters[j];
			j++;
			if (j >= keySize)
				j = 0;
		}
	}
	//вывод строки
	for (int i = 0; i < textSize; i++)
		cout << keyText[i];
	cout << "| ключевой текст" << endl;

	//шифрование
	for (int i = 0; i < textSize; i++)
	{
		if (originalLetters[i] == ' ' || originalLetters[i] == '.' || originalLetters[i] == ',' || originalLetters[i] == '-')
			encryptedText[i] = originalLetters[i];
		else
		{
			encryptedText[i] = encrypting(table, originalLetters[i], keyText[i]);
		}
	}

	//вывод результата
	for (int i = 0; i < textSize; i++)
	{
		cout << encryptedText[i];
	}
	cout << "| зашифрованный текст" << endl;
	
	//расшифровка
	for (int i = 0; i < textSize; i++)
	{
		if (encryptedText[i] == ' ' || encryptedText[i] == '.' || encryptedText[i] == ',' || encryptedText[i] == '-')
			decryptedText[i] = encryptedText[i];
		else
		{
			decryptedText[i] = decrypting(table, encryptedText[i], keyText[i]);
		}
	}

	//вывод результата
	for (int i = 0; i < textSize; i++)
	{
		cout << decryptedText[i];
	}
	cout << "| расшифрованный текст" << endl;
	cout << endl;

	system("pause");
}