//Уфологи обнаружили на некоторой местности K точек посадки НЛО. 
//Так как всем известно, что инопланетяне очень любят треугольники, 
//вам была поставлена задача найти треугольник с самой меньшей площадью, 
//который только можно из них построить, 
//определить его гоеметрический центр и провести от него линию к самой удаленной от него точке посадки НЛО. 
//Узнав длину этой линии человечество получит шанс узнать хоть что-нибудь о наших братьях по разуму.
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>

using namespace std;

struct Point {
    double x;
    double y;
};

// Функция для вычисления площади треугольника по координатам его вершин
double Area(const Point& p1, const Point& p2, const Point& p3) {
    return 0.5 * abs((p1.x - p3.x) * (p2.y - p1.y) - (p1.x - p2.x) * (p3.y - p1.y));
}

// Функция для вычисления расстояния между двумя точками
double Distance(const Point& p1, const Point& p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

// Функция для нахождения треугольника с наименьшей площадью
vector<Point> MinimumArea(const vector<Point>& points) {
    double minArea = numeric_limits<double>::max();
    vector<Point> minTriangle;

    int n = points.size();

    // Полный перебор всех возможных треугольников
    for (int i = 0; i < n - 2; ++i) 
    {
        for (int j = i + 1; j < n - 1; ++j) 
        {
            for (int k = j + 1; k < n; ++k) 
            {
                double a = sqrt(pow(points[j].x - points[i].x, 2) + pow(points[j].y - points[i].y, 2));
                double b = sqrt(pow(points[k].x - points[j].x, 2) + pow(points[k].y - points[j].y, 2));
                double c = sqrt(pow(points[k].x - points[i].x, 2) + pow(points[k].y - points[i].y, 2));
                if (a + b > c && a + c > b && b + c > a) 
                {
                    double area = Area(points[i], points[j], points[k]);
                    if (area < minArea) {
                        minArea = area;
                        minTriangle = { points[i], points[j], points[k] };
                    }
                }
                else 
                {
                    cout << "Нельзя составить треугольник " << endl;
                    exit;
                }
                
            }
        }
    }
    cout << endl;
    cout << "Минимальная площадь треугольника: " << minArea << "\n";

    return minTriangle;
}

// Функция для нахождения самой удаленной точки от заданного центра
Point FarPoint(const vector<Point>& points, const Point& center) {
    double maxDistance = 0.0;
    Point farthestPoint;

    for (const Point& point : points) {
        double distance = Distance(center, point);
        if (distance > maxDistance) {
            maxDistance = distance;
            farthestPoint = point;
        }
    }
    return farthestPoint;
}

int main() {
    int k;

    setlocale(LC_ALL, "Russian");

    cout << "Введите количество точек: ";
    while (!(cin >> k) || k < 3 || k != (int)k)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  Ошибка: количество точек меньше 3 или введено дробное число/буква/символ" << endl;
        cout << "Введите заново количество точек: ";
    }

    vector<Point> points(k);
    cout << "Введите координаты точек:\n";
    for (int i = 0; i < k; ++i) {
        cout << "Точка " << i + 1 << ":\n";
        cout << "  Координата X: ";

        while (!(cin >> points[i].x))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "  Ошибка: некорректный ввод" << endl;
            cout << "  Введите заново координату X: ";
        }
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "  Координата Y: ";
        while (!(cin >> points[i].y))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "  Ошибка: некорректный ввод" << endl;
            cout << "  Введите заново координату Y: ";
        }
        cin.clear();
        cin.ignore(10000, '\n');

    }
    vector<Point> minTriangle = MinimumArea(points);

    // Вычисление геометрического центра треугольника
    double centerX = (minTriangle[0].x + minTriangle[1].x + minTriangle[2].x) / 3.0;
    double centerY = (minTriangle[0].y + minTriangle[1].y + minTriangle[2].y) / 3.0;
    Point center = { centerX, centerY };
    Point farthestPoint = FarPoint(points, center);

    // Вычисление длины линии от центра к самой удаленной точке
    double distance = Distance(center, farthestPoint);

    cout << "Треугольник с наименьшей площадью:\n";
    for (int i = 0; i < 3; ++i) {
        cout << "Вершина " << ": (" << minTriangle[i].x << ", " << minTriangle[i].y << ")\n";
    }
    cout << endl;
    cout << "Геометрический центр треугольника: (" << center.x << ", " << center.y << ")\n";
    cout << endl;
    cout << "Самая удаленная точка от центра: (" << farthestPoint.x << ", " << farthestPoint.y << ")\n";
    cout << endl;
    cout << "Длина линии от центра к самой удаленной точке: " << distance << "\n";
    cout << endl;

    return 0;
}

