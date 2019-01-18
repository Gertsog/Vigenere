#include <iostream>
#include <string>
using namespace std;

//�������� �������
void tableCreation(char table[33][33])
{
	char alphabet[33] = { '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�' };

	for (int i = 0; i < 33; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			table[i][j] = alphabet[(j + i) % 33];
		}
	}

	//����� �������
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

//���������� ���������� �������
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

//����������� ���������� �������
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

	tableCreation(table);//�������� �������

	cout << "������� �������� �����: ";
	getline(cin, originalText);
	cout << "������� ����: ";
	getline(cin, key);

	textSize = originalText.size();
	keySize = key.size();
	
	//�������������� ������ � ������
	for (int i = 0; i < textSize; i++)
	{
		originalLetters[i] = (char)originalText[i];
		if (originalLetters[i] == -16)//��������� ����� "�"
		{
			originalLetters[i] = '�' - 64;//�������������� ��������� ����� "�"
		}
		if (originalLetters[i] == ' ' || originalLetters[i] == '.' || originalLetters[i] == ',' || originalLetters[i] == '-')
			originalLetters[i] = originalLetters[i] - 64;
		originalLetters[i] = originalLetters[i] + 64;//64 - ����������� �������������� ���������
	}
	//����� ������
	cout << endl;
	for (int i = 0; i < textSize; i++)
		cout << originalLetters[i];
	cout << "| ������������ �����" << endl;

	//�������������� ����� � ������
	for (int i = 0; i < keySize; i++)
	{
		keyLetters[i] = (char)key[i];
		if (keyLetters[i] == -16)//��������� ����� "�"
		{
			keyLetters[i] = '�' - 64;//�������������� ��������� ����� "�"
		}
		keyLetters[i] = keyLetters[i] + 64;
	}

	//�������� �������� ������
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
	//����� ������
	for (int i = 0; i < textSize; i++)
		cout << keyText[i];
	cout << "| �������� �����" << endl;

	//����������
	for (int i = 0; i < textSize; i++)
	{
		if (originalLetters[i] == ' ' || originalLetters[i] == '.' || originalLetters[i] == ',' || originalLetters[i] == '-')
			encryptedText[i] = originalLetters[i];
		else
		{
			encryptedText[i] = encrypting(table, originalLetters[i], keyText[i]);
		}
	}

	//����� ����������
	for (int i = 0; i < textSize; i++)
	{
		cout << encryptedText[i];
	}
	cout << "| ������������� �����" << endl;
	
	//�����������
	for (int i = 0; i < textSize; i++)
	{
		if (encryptedText[i] == ' ' || encryptedText[i] == '.' || encryptedText[i] == ',' || encryptedText[i] == '-')
			decryptedText[i] = encryptedText[i];
		else
		{
			decryptedText[i] = decrypting(table, encryptedText[i], keyText[i]);
		}
	}

	//����� ����������
	for (int i = 0; i < textSize; i++)
	{
		cout << decryptedText[i];
	}
	cout << "| �������������� �����" << endl;
	cout << endl;

	system("pause");
}