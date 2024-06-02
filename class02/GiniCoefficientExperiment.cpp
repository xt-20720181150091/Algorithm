#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// 计算基尼系数
double calculateGini(const vector<int>& wealth)
{
    double sumOfAbsoluteDifferences = 0.0;
    double sumOfWealth = 0.0;
    auto n = wealth.size();
    for (size_t i = 0; i < n; i++)
    {
        sumOfWealth += wealth[i];
        for (int j = 0; j < n; j++)
        {
            sumOfAbsoluteDifferences += abs(wealth[i] - wealth[j]);
        }
    }
    return sumOfAbsoluteDifferences / (2.0 * n * sumOfWealth);
}

void experiment(int n, int t)
{
    vector<int> wealth(n, 100);
    vector<bool> hasMoney(n, false);

    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < n; j++)
        {
            hasMoney[j] = wealth[j] > 0;
        }
        for (int j = 0; j < n; j++)
        {
            if (hasMoney[j])
            {
                int other;
                do
                {
                    other = rand() % n;
                } while (other == j);
                wealth[j]--;
                wealth[other]++;
            }
        }
    }

    sort(wealth.begin(), wealth.end());
    cout << "列出每个人的财富(贫穷到富有) : ";
    for (int i = 0; i < n; i++)
    {
        cout << wealth[i] << " ";
        if (i % 10 == 9)
        {
            cout << endl;
        }
    }
    cout << endl << "这个社会的基尼系数为 : " << calculateGini(wealth) << endl;
}

int main()
{
    srand(time(nullptr));
    SetConsoleOutputCP(65001);
    cout << "模拟计算财富分配下的基尼系数" << endl;
    cout << "测试开始" << endl;
    int n = 100;
    int t = 100000;
    cout << "人数 : " << n << endl;
    cout << "轮数 : " << t << endl;
    experiment(n, t);
    cout << "测试结束" << endl;
    return 0;
}