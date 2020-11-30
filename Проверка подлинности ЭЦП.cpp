#include<iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int module(int t, int p)           //для отрицательного числа   
{
	do { t = t + p; } while (t < 0);
	return t;
}

int doublelambda(int x, int y, int a, int p)          //лямбда для удвоения точки
{
	int chislo1, chislo2, lambda1;
	chislo1 = 3 * (pow(x, 2)) + a;
	chislo2 = 2 * y;
	if (chislo2 < 0) { chislo1 = -chislo1; chislo2 = -chislo2; }
	if (chislo2 == 0) cout << "error";
	else
	{
		int flag = 0;
		//l*chislo=1 (mod p)
		for (int i = 1; i < p; i++)
		{
			int temp = (i * chislo2) % p;
			if (temp < 0) temp = module(temp, p);
			if (temp == 1) flag = 1;
			if (flag == 1) { chislo2 = i; break; }
		}
		lambda1 = (chislo1 * chislo2) % p;
		if (lambda1 < 0) lambda1 = module(lambda1, p);
		return lambda1;
	}
}

int doublGx(int x, int y, int a, int p)      //поиск x3 для удвоенной точки
{
	int nx = pow(doublelambda(x, y, a, p), 2) - 2 * x;
	nx = nx % p;
	if (nx < 0) nx = module(nx, p);
	return nx;
}

int doublGy(int x, int y, int a, int p)   //поиск y3 для удвоенной точки
{
	int ny = doublelambda(x, y, a, p) * (x - doublGx(x, y, a, p)) - y;
	ny = ny % p;
	if (ny < 0) ny = module(ny, p);
	return ny;
}

int sumlambda(int x1, int y1, int x2, int y2, int p)   //поиск лямбды для суммы точек
{
	int chislo1, chislo2, lambda2;
	chislo1 = y2 - y1;
	chislo2 = x2 - x1;
	if (chislo2 < 0) { chislo1 = -chislo1; chislo2 = -chislo2; }
	if (chislo2 == 0) cout << "error";
	else
	{
		int flag = 0;
		                 //i*chislo1=1 (mod p)  обратное по модулю
		for (int i = 1; i < p; i++)
		{
			int temp = (i * chislo2) % p;
			if (temp < 0) temp = module(temp, p);
			if (temp == 1) flag = 1;
			if (flag == 1) { chislo2 = i; break; }
		}
		lambda2 = (chislo1 * chislo2) % p;
		if (lambda2 < 0) lambda2 = module(lambda2, p);
		return lambda2;
	}
}

int sumx(int x1, int y1, int x2, int y2, int p)   //x3 для суммы
{
	int nx = pow(sumlambda(x1, y1, x2, y2, p), 2) - x1 - x2;
	nx = nx % p;
	if (nx < 0) nx = module(nx, p);
	return nx;
}

int sumy(int x1, int y1, int x2, int y2, int x3, int p)   //y3 для суммы
{
	int ny = sumlambda(x1, y1, x2, y2, p) * (x1 - x3) - y1;
	ny = ny % p;
	if (ny < 0) ny = module(ny, p);
	return ny;
}

int finalx(int x1, int y1, int x2, int y2, int p)         //результат х 
{
	int x3;
	x3 = sumx(x1, y1, x2, y2, p);
	return x3;
}

int finaly(int x1, int y1, int x2, int y2, int p)             //результат у
{
	int x3, y3;
	x3 = sumx(x1, y1, x2, y2, p);
	y3 = sumy(x1, y1, x2, y2, x3, p);
	return y3;
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int Gx = 562, Gy = 89, p = 751, q = 13, a = -1, b = 1, h = 2, r = 7, s = 6, Qx = 135, Qy = 669, firstx, firsty, secondx, secondy, dx3, dy3;
	int check = 0;
	if ((1 <= r) && (r <= q - 1) && (1 <= s) && (s <= q - 1)) check = 1;    //проверка значений
	if (check == 0) cout << "Подпись фальшивая";
	else {
		int v;                           //v
		int flag = 0;
		for (int i = 1; i < q; i++)
		{
			int temp = (i * s) % q;
			if (temp == 1) flag = 1;
			if (flag == 1) { v = i; break; }
		}
		cout << "v=" << v << endl;

		int u1 = (v * h) % q;         //u1
		cout << "u1=" << u1 << endl;

		int u2 = (v * r) % q;         //u2
		cout << "u2=" << u2 << endl;

		if ((u1 < 1) || (u2 < 1)) cout << "error";   
		else
		{
			if (u1 == 1) { firstx = Gx; firsty = Gy; }
			if (u2 == 1) { secondx = Qx; secondy = Qy; }
			if (u1 >= 2)
			{
				dx3 = doublGx(Gx, Gy, a, p);
				dy3 = doublGy(Gx, Gy, a, p);
				if (u1 == 2) { firstx = dx3; firsty = dy3; }
				else
				{
					int x1 = dx3, y1 = dy3, x2 = Gx, y2 = Gy;
					for (int j = 3; j <= u1; j++)
					{
						firstx = finalx(x1, y1, x2, y2, p);
						firsty = finaly(x1, y1, x2, y2, p);
						x1 = firstx;
						y1 = firsty;
					}
					
				}
			}
			if (u2 >= 2)
			{
				dx3 = doublGx(Qx, Qy, a, p);
				dy3 = doublGy(Qx, Qy, a, p);
				if (u2 == 2) { secondx = dx3; secondy = dy3; }
				else
				{
					int x1 = dx3, y1 = dy3, x2 = Qx, y2 = Qy;
					for (int j = 3; j <= u2; j++)
					{
						secondx = finalx(x1, y1, x2, y2, p);
						secondy = finaly(x1, y1, x2, y2, p);
						x1 = secondx;
						y1 = secondy;
					}
					
				}
			}

			cout << "Первое слагаемое  u1*G  (" << firstx << ',' << firsty <<')'<< endl;
			cout << "Второе слагаемое  u2*Q  (" << secondx << ',' << secondy <<')'<< endl;

			int finx = finalx(firstx, firsty, secondx, secondy, p);
			int finy = finaly(firstx, firsty, secondx, secondy, p);
			cout << "Точка X= (" << finx << ',' << finy << ')' << endl;

			int znachenie = finx % q;
			if (znachenie == r) cout << "Подпись действительная" << endl;
			else cout << "Подпись недействительная  r="<<r<<" не равно "<<znachenie<<endl;
		}

	}
}
