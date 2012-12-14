#include <vector>
#include <iostream>
#include "conio.h"
#include "math.h"

using namespace std;
int w, h;
int i, j, p, s, rs, cs;

int neighbors(int &i, int &j, vector <vector<bool>> &pic)
{
	//функция проверяет наличие нулей по соседству
	//т.е. является ли точка граничной
	
	if(i>0 && i<w && j>0 && j<h)
	{
		if(pic[i-1][j] || pic[i+1][j] || pic[i][j-1] || pic[i][j+1])
			return 1;	
		else
			return 0;
	}
	else
		return 0;
}

void something(vector <vector<bool>> &pic)
{
	//функция вычисляет периметр, площадь и координаты
	//центра тяжести
	
	for(i=0; i<w; i++)
		for(j=0; j<h; j++)
			if(pic[i][j])
			{
				s++;	
				rs+=i;
				cs+=j;
				if(neighbors(i, j, pic))
					p++;
			}

		rs/=s;
		cs/=s;
	
}

int square()
{
	//квадрат ли?
	
	if(pow((double)p/4,2)>(s-10) && pow((double)p/4,2)<(s+10))
		return 1;
	return 0;
}

int circle(vector <vector<bool>> &pic)
{
	//эллипс ли?
	
	double mu=0, sigma=0, a, b, ab, c;
	for(i=0; i<w; i++)
		for(j=0; j<h; j++)
			if(neighbors(i,j,pic))
			{
				a = i-rs;
				b = j-cs;
				ab = pow(a,2);
				ab += pow(b,2);
				mu += pow(ab,0.5);
			}
	mu/=p;	
	for(i=0; i<w; i++)
		for(j=0; j<h; j++)
			if(neighbors(i,j,pic))
			{
				a = i-rs;
				b = j-cs;
				ab = pow(a,2);
				ab += pow(b,2);
				sigma += pow(pow(ab,0.5)-mu,2);
			}
	sigma = pow(sigma/p,0.5);
	
	// c - коэффициент "округлости"
	
	c = mu/sigma;	
	if(c>10)
		return 1;
	return 0;
}

int main()
{	
	p=0, s=0, rs=0, cs=0;
	
	//ширина и высота входного изображения
	cin>>w>>h;	
	vector <vector <bool>> pic(w,h);	
	char b;
	for(i=0; i<w; i++)
		for(j=0;j<h;j++)
		{
			cin>>b;
			if(b!='0')
				pic[i][j]=true;
			else
				pic[i][j]=false;
		}	

	something(pic);
	if(square())
	{
		cout<<"square";
		return 0;
	}
	else if(circle(pic))
	{
		cout<<"circle";
		return 0;
	}
	else
	{
		//если на изображении не квадрат
		//и не эллипс, выводим это
		//см. http://acm.timus.ru/problem.aspx?space=1&num=1378
		
		cout<<"triangle";
		return 0;
	}	
	getch();
	return 0;
}

